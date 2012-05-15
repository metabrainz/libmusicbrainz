/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

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

#include <stdlib.h>
#include <string.h>

#include "ne_session.h"
#include "ne_auth.h"
#include "ne_string.h"
#include "ne_request.h"

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
		std::string m_ErrorMessage;
		std::string m_UserName;
		std::string m_Password;
		std::string m_ProxyHost;
		int m_ProxyPort;
		std::string m_ProxyUserName;
		std::string m_ProxyPassword;
};

MusicBrainz5::CHTTPFetch::CHTTPFetch(const std::string& UserAgent, const std::string& Host, int Port)
:	m_d(new CHTTPFetchPrivate)
{
	m_d->m_UserAgent=UserAgent;

	for (std::string::size_type Pos=0;Pos<m_d->m_UserAgent.length();Pos++)
		if (m_d->m_UserAgent[Pos]=='-')
			m_d->m_UserAgent[Pos]='/';

 	m_d->m_Host=Host;
	m_d->m_Port=Port;

	// Parse http_proxy environmnent variable
	const char *http_proxy = getenv("http_proxy");
	if (http_proxy)
	{
		ne_uri uri;
		if (!ne_uri_parse(http_proxy, &uri))
		{
			if (uri.host)
				m_d->m_ProxyHost = uri.host;
			if (uri.port)
				m_d->m_ProxyPort = uri.port;

			if (uri.userinfo)
			{
				char *pos = strchr(uri.userinfo, ':');
				if (pos)
				{
					*pos = '\0';
					m_d->m_ProxyUserName = uri.userinfo;
					m_d->m_ProxyPassword = pos + 1;
				}
				else
				{
					m_d->m_ProxyUserName = uri.userinfo;
				}
			}
		}

		ne_uri_free(&uri);
	}
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

	ne_sock_init();

	ne_session *sess=ne_session_create("http", m_d->m_Host.c_str(), m_d->m_Port);
	if (sess)
	{
		ne_set_useragent(sess, m_d->m_UserAgent.c_str());

		ne_set_server_auth(sess, httpAuth, this);

		// Use proxy server
		if (!m_d->m_ProxyHost.empty())
		{
			ne_session_proxy(sess, m_d->m_ProxyHost.c_str(), m_d->m_ProxyPort);
			ne_set_proxy_auth(sess, proxyAuth, this);
		}

		ne_request *req = ne_request_create(sess, Request.c_str(), URL.c_str());
		if (Request=="PUT")
			ne_set_request_body_buffer(req,0,0);

		if (Request!="GET")
			ne_set_request_flag(req, NE_REQFLAG_IDEMPOTENT, 0);

		ne_add_response_body_reader(req, ne_accept_2xx, httpResponseReader, &m_d->m_Data);

		m_d->m_Result = ne_request_dispatch(req);
		m_d->m_Status = ne_get_status(req)->code;

		Ret=m_d->m_Data.size();

		ne_request_destroy(req);

		m_d->m_ErrorMessage = ne_get_error(sess);

		ne_session_destroy(sess);

		switch (m_d->m_Result)
		{
			case NE_OK:
				break;

			case NE_CONNECT:
			case NE_LOOKUP:
				throw CConnectionError(m_d->m_ErrorMessage);
				break;

			case NE_TIMEOUT:
				throw CTimeoutError(m_d->m_ErrorMessage);
				break;

			case NE_AUTH:
			case NE_PROXYAUTH:
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

	ne_sock_exit();

	return Ret;
}

int MusicBrainz5::CHTTPFetch::httpAuth(void *userdata, const char *realm, int attempts,
					 char *username, char *password)
{
	realm=realm;

	MusicBrainz5::CHTTPFetch *Fetch = (MusicBrainz5::CHTTPFetch *)userdata;
	strncpy(username, Fetch->m_d->m_UserName.c_str(), NE_ABUFSIZ);
	strncpy(password, Fetch->m_d->m_Password.c_str(), NE_ABUFSIZ);
	return attempts;
}

int MusicBrainz5::CHTTPFetch::proxyAuth(void *userdata, const char *realm, int attempts,
					 char *username, char *password)
{
	realm=realm;

	MusicBrainz5::CHTTPFetch *Fetch = (MusicBrainz5::CHTTPFetch *)userdata;
	strncpy(username, Fetch->m_d->m_ProxyUserName.c_str(), NE_ABUFSIZ);
	strncpy(password, Fetch->m_d->m_ProxyPassword.c_str(), NE_ABUFSIZ);
	return attempts;
}

int MusicBrainz5::CHTTPFetch::httpResponseReader(void *userdata, const char *buf, size_t len)
{
	std::vector<unsigned char> *buffer = reinterpret_cast<std::vector<unsigned char> *>(userdata);

	buffer->insert(buffer->end(),buf,buf+len);

	return 0;
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
