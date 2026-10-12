/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   libmusicbrainz5 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include "config.h"
#include "musicbrainz5/defines.h"

#include "musicbrainz5/HTTPFetch.h"

#include <sstream>

#include <curl/curl.h>

#ifdef _WIN32
	#include <windows.h>

	typedef CRITICAL_SECTION tLock;

	static void initLock(tLock *Lock) { InitializeCriticalSection(Lock); }
	static void destroyLock(tLock *Lock) { DeleteCriticalSection(Lock); }
	static void lock(tLock *Lock) { EnterCriticalSection(Lock); }
	static void unlock(tLock *Lock) { LeaveCriticalSection(Lock); }
#else
	#include <pthread.h>

	typedef pthread_mutex_t tLock;

	static void initLock(tLock *Lock) { pthread_mutex_init(Lock,0); }
	static void destroyLock(tLock *Lock) { pthread_mutex_destroy(Lock); }
	static void lock(tLock *Lock) { pthread_mutex_lock(Lock); }
	static void unlock(tLock *Lock) { pthread_mutex_unlock(Lock); }
#endif

// Connections, DNS lookups and TLS sessions are shared between all requests
// made by the library, so consecutive requests can reuse the same connection
static CURLSH *SharedData=0;
static tLock SharedLocks[CURL_LOCK_DATA_LAST];

static void lockSharedData(CURL *handle, curl_lock_data data, curl_lock_access access, void *userptr)
{
	(void)handle;
	(void)access;
	(void)userptr;

	lock(&SharedLocks[data]);
}

static void unlockSharedData(CURL *handle, curl_lock_data data, void *userptr)
{
	(void)handle;
	(void)userptr;

	unlock(&SharedLocks[data]);
}

#if defined(__GNUC__)
__attribute__((constructor))
#else
	#error Non GCC compiler detected
#endif
static void initialize_curl()
{
	curl_global_init(CURL_GLOBAL_DEFAULT);

	for (int Lock=0;Lock<CURL_LOCK_DATA_LAST;Lock++)
		initLock(&SharedLocks[Lock]);

	SharedData=curl_share_init();
	if (SharedData)
	{
		curl_share_setopt(SharedData, CURLSHOPT_LOCKFUNC, lockSharedData);
		curl_share_setopt(SharedData, CURLSHOPT_UNLOCKFUNC, unlockSharedData);
		curl_share_setopt(SharedData, CURLSHOPT_SHARE, CURL_LOCK_DATA_DNS);
		curl_share_setopt(SharedData, CURLSHOPT_SHARE, CURL_LOCK_DATA_SSL_SESSION);
#if LIBCURL_VERSION_NUM >= 0x073900
		curl_share_setopt(SharedData, CURLSHOPT_SHARE, CURL_LOCK_DATA_CONNECT);
#endif
	}
}

#if defined(__GNUC__)
__attribute__((destructor))
#else
	#error Non GCC compiler detected
#endif
static void destroy_curl()
{
	if (SharedData)
	{
		curl_share_cleanup(SharedData);
		SharedData=0;
	}

	for (int Lock=0;Lock<CURL_LOCK_DATA_LAST;Lock++)
		destroyLock(&SharedLocks[Lock]);

	curl_global_cleanup();
}

class MusicBrainz5::CHTTPFetchPrivate
{
	public:
		CHTTPFetchPrivate()
		:	m_Port(80),
			m_Result(0),
			m_Status(0),
			m_ProxyPort(0)
		{
		}

		std::string m_UserAgent;
		std::string m_Host;
		int m_Port;
		std::vector<unsigned char> m_Data;
		int m_Result;
		int m_Status;
		std::string m_StatusLine;
		std::string m_ErrorMessage;
		std::string m_UserName;
		std::string m_Password;
		std::string m_ProxyHost;
		int m_ProxyPort;
		std::string m_ProxyUserName;
		std::string m_ProxyPassword;
};

static size_t curlWriteCallback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	std::vector<unsigned char> *buffer = reinterpret_cast<std::vector<unsigned char> *>(userdata);

	buffer->insert(buffer->end(),ptr,ptr+size*nmemb);

	return size*nmemb;
}

static size_t curlHeaderCallback(char *buffer, size_t size, size_t nitems, void *userdata)
{
	std::string *StatusLine = reinterpret_cast<std::string *>(userdata);
	std::string Header(buffer,size*nitems);

	// Keep the reason phrase of the last status line (e.g. "404 Not Found"),
	// which is what libneon used to report as the error message
	if (Header.compare(0,5,"HTTP/")==0)
	{
		std::string::size_type Pos=Header.find(' ');
		if (Pos!=std::string::npos)
		{
			*StatusLine=Header.substr(Pos+1);

			std::string::size_type End=StatusLine->find_last_not_of("\r\n ");
			StatusLine->erase(End==std::string::npos ? 0 : End+1);
		}
	}

	return size*nitems;
}

// Reason phrases for status codes the web service returns, for responses
// that don't include one (HTTP/2 has no reason phrase)
static const char *reasonPhrase(long Status)
{
	switch (Status)
	{
		case 200: return "OK";
		case 400: return "Bad Request";
		case 401: return "Unauthorized";
		case 403: return "Forbidden";
		case 404: return "Not Found";
		case 407: return "Proxy Authentication Required";
		case 500: return "Internal Server Error";
		case 502: return "Bad Gateway";
		case 503: return "Service Unavailable";
		case 504: return "Gateway Timeout";
		default: return 0;
	}
}

static size_t curlReadCallback(char *buffer, size_t size, size_t nitems, void *userdata)
{
	(void)buffer;
	(void)size;
	(void)nitems;
	(void)userdata;

	// Requests are sent with an empty body
	return 0;
}

MusicBrainz5::CHTTPFetch::CHTTPFetch(const std::string& UserAgent, const std::string& Host, int Port)
:	m_d(new CHTTPFetchPrivate)
{
	m_d->m_UserAgent=UserAgent;

	for (std::string::size_type Pos=0;Pos<m_d->m_UserAgent.length();Pos++)
		if (m_d->m_UserAgent[Pos]=='-')
			m_d->m_UserAgent[Pos]='/';

 	m_d->m_Host=Host;
	m_d->m_Port=Port;

	// The http_proxy environment variable is handled by libcurl itself
}

MusicBrainz5::CHTTPFetch::~CHTTPFetch()
{
	delete m_d;
}

void MusicBrainz5::CHTTPFetch::SetUserName(const std::string& UserName)
{
	m_d->m_UserName=UserName;
}

void MusicBrainz5::CHTTPFetch::SetPassword(const std::string& Password)
{
	m_d->m_Password=Password;
}

void MusicBrainz5::CHTTPFetch::SetProxyHost(const std::string& ProxyHost)
{
	m_d->m_ProxyHost=ProxyHost;
}

void MusicBrainz5::CHTTPFetch::SetProxyPort(int ProxyPort)
{
	m_d->m_ProxyPort=ProxyPort;
}

void MusicBrainz5::CHTTPFetch::SetProxyUserName(const std::string& ProxyUserName)
{
	m_d->m_ProxyUserName=ProxyUserName;
}

void MusicBrainz5::CHTTPFetch::SetProxyPassword(const std::string& ProxyPassword)
{
	m_d->m_ProxyPassword=ProxyPassword;
}

int MusicBrainz5::CHTTPFetch::Fetch(const std::string& URL, const std::string& Request)
{
	int Ret=0;

	m_d->m_Data.clear();
	m_d->m_Result=CURLE_OK;
	m_d->m_Status=0;
	m_d->m_StatusLine.clear();
	m_d->m_ErrorMessage.clear();

	CURL *curl=curl_easy_init();
	if (curl)
	{
		std::stringstream os;
		os << (m_d->m_Port==443 ? "https" : "http") << "://" << m_d->m_Host << ":" << m_d->m_Port << URL;
		std::string FullURL=os.str();

		char ErrorBuffer[CURL_ERROR_SIZE];
		ErrorBuffer[0]='\0';

		struct curl_slist *Headers=0;

		curl_easy_setopt(curl, CURLOPT_URL, FullURL.c_str());
		curl_easy_setopt(curl, CURLOPT_USERAGENT, m_d->m_UserAgent.c_str());
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, ErrorBuffer);
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);

		if (SharedData)
			curl_easy_setopt(curl, CURLOPT_SHARE, SharedData);

		// Abort if the server stops sending data for two minutes
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 1L);
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 120L);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &m_d->m_Data);
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, curlHeaderCallback);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &m_d->m_StatusLine);

		if (!m_d->m_UserName.empty())
		{
			curl_easy_setopt(curl, CURLOPT_USERNAME, m_d->m_UserName.c_str());
			curl_easy_setopt(curl, CURLOPT_PASSWORD, m_d->m_Password.c_str());
			curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC | CURLAUTH_DIGEST);
		}

		// Use proxy server
		if (!m_d->m_ProxyHost.empty())
		{
			curl_easy_setopt(curl, CURLOPT_PROXY, m_d->m_ProxyHost.c_str());
			if (m_d->m_ProxyPort)
				curl_easy_setopt(curl, CURLOPT_PROXYPORT, (long)m_d->m_ProxyPort);
		}

		if (!m_d->m_ProxyUserName.empty())
		{
			curl_easy_setopt(curl, CURLOPT_PROXYUSERNAME, m_d->m_ProxyUserName.c_str());
			curl_easy_setopt(curl, CURLOPT_PROXYPASSWORD, m_d->m_ProxyPassword.c_str());
			curl_easy_setopt(curl, CURLOPT_PROXYAUTH, CURLAUTH_BASIC | CURLAUTH_DIGEST);
		}

		if (Request=="PUT")
		{
			curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
			curl_easy_setopt(curl, CURLOPT_INFILESIZE, 0L);
			curl_easy_setopt(curl, CURLOPT_READFUNCTION, curlReadCallback);

			Headers=curl_slist_append(Headers, "Expect:");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, Headers);
		}
		else if (Request!="GET")
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, Request.c_str());

		CURLcode Result=curl_easy_perform(curl);

		long Status=0;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &Status);

		m_d->m_Result=Result;
		m_d->m_Status=Status;

		if (Result!=CURLE_OK)
			m_d->m_ErrorMessage=ErrorBuffer[0] ? ErrorBuffer : curl_easy_strerror(Result);
		else if (m_d->m_StatusLine.find(' ')!=std::string::npos)
			m_d->m_ErrorMessage=m_d->m_StatusLine;
		else
		{
			std::stringstream StatusStream;
			StatusStream << Status;

			const char *Reason=reasonPhrase(Status);
			if (Reason)
				StatusStream << " " << Reason;

			m_d->m_ErrorMessage=StatusStream.str();
		}

		curl_slist_free_all(Headers);
		curl_easy_cleanup(curl);

		// Only the body of successful responses is returned, as with libneon
		if (m_d->m_Status<200 || m_d->m_Status>299)
			m_d->m_Data.clear();

		Ret=m_d->m_Data.size();

		switch (m_d->m_Result)
		{
			case CURLE_OK:
				break;

			case CURLE_COULDNT_CONNECT:
			case CURLE_COULDNT_RESOLVE_HOST:
			case CURLE_COULDNT_RESOLVE_PROXY:
				throw CConnectionError(m_d->m_ErrorMessage);
				break;

			case CURLE_OPERATION_TIMEDOUT:
				throw CTimeoutError(m_d->m_ErrorMessage);
				break;

			case CURLE_LOGIN_DENIED:
				throw CAuthenticationError(m_d->m_ErrorMessage);
				break;

			default:
				throw CFetchError(m_d->m_ErrorMessage);
				break;
		}

		switch (m_d->m_Status)
		{
			case 200:
				break;

			case 400:
				throw CRequestError(m_d->m_ErrorMessage);
				break;

			case 401:
			case 407:
				throw CAuthenticationError(m_d->m_ErrorMessage);
				break;

			case 404:
				throw CResourceNotFoundError(m_d->m_ErrorMessage);
				break;

			default:
				throw CFetchError(m_d->m_ErrorMessage);
				break;
		}
	}

	return Ret;
}

std::vector<unsigned char> MusicBrainz5::CHTTPFetch::Data() const
{
	return m_d->m_Data;
}

int MusicBrainz5::CHTTPFetch::Result() const
{
	return m_d->m_Result;
}

int MusicBrainz5::CHTTPFetch::Status() const
{
	return m_d->m_Status;
}

std::string MusicBrainz5::CHTTPFetch::ErrorMessage() const
{
	return m_d->m_ErrorMessage;
}
