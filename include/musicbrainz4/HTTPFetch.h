/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

#ifndef _MUSICBRAINZ4_HTTP_FETCH_
#define _MUSICBRAINZ4_HTTP_FETCH_

#include <string>
#include <vector>

namespace MusicBrainz4
{
	class CHTTPFetchPrivate;

	class CExceptionBase: public std::exception
	{
	public:
		CExceptionBase(const std::string& ErrorMessage, const std::string& Exception)
		:	m_ErrorMessage(ErrorMessage),
			m_Exception(Exception)
		{
			m_FullMessage=m_Exception + ": " + m_ErrorMessage;
		}

		virtual ~CExceptionBase() throw() {};

	  virtual const char* what() const throw()
	  {
	    return m_FullMessage.c_str();
	  }

	 private:
		std::string m_ErrorMessage;
		std::string m_Exception;
		std::string m_FullMessage;
	};

	class CConnectionError: public CExceptionBase
	{
	public:
			CConnectionError(const std::string& ErrorMessage)
			: CExceptionBase(ErrorMessage,"Connection error")
			{
			}
	};

	class CTimeoutError: public CExceptionBase
	{
	public:
			CTimeoutError(const std::string& ErrorMessage)
			: CExceptionBase(ErrorMessage,"Timeout error")
			{
			}
	};

	class CAuthenticationError: public CExceptionBase
	{
	public:
			CAuthenticationError(const std::string& ErrorMessage)
			: CExceptionBase(ErrorMessage,"Authentication error")
			{
			}
	};

	class CFetchError: public CExceptionBase
	{
	public:
			CFetchError(const std::string& ErrorMessage)
			: CExceptionBase(ErrorMessage,"Fetch error")
			{
			}
	};

	class CRequestError: public CExceptionBase
	{
	public:
			CRequestError(const std::string& ErrorMessage)
			: CExceptionBase(ErrorMessage,"Request error")
			{
			}
	};

	class CResourceNotFoundError: public CExceptionBase
	{
	public:
			CResourceNotFoundError(const std::string& ErrorMessage)
			: CExceptionBase(ErrorMessage,"Resource not found error")
			{
			}
	};

	class CHTTPFetch
	{
	public:
		CHTTPFetch(const std::string& UserAgent, const std::string& Host, int Port=80);
		~CHTTPFetch();

		void SetUserName(const std::string& UserName);
		void SetPassword(const std::string& Password);
		void SetProxyHost(const std::string& ProxyHost);
		void SetProxyPort(int ProxyPort);
		void SetProxyUserName(const std::string& ProxyUserName);
		void SetProxyPassword(const std::string& ProxyPassword);
		int Fetch(const std::string& URL, const std::string& Request="GET");
		std::vector<unsigned char> Data() const;
		int Result() const;
		int Status() const;
		std::string ErrorMessage() const;

	private:
		CHTTPFetchPrivate * const m_d;

		static int httpAuth(void *userdata, const char *realm, int attempts, char *username, char *password);
		static int proxyAuth(void *userdata, const char *realm, int attempts, char *username, char *password);
		static int httpResponseReader(void *userdata, const char *buf, size_t len);
	};
}

#endif
