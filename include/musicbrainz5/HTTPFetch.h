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

#ifndef _MUSICBRAINZ5_HTTP_FETCH_
#define _MUSICBRAINZ5_HTTP_FETCH_

#include <string>
#include <vector>

namespace MusicBrainz5
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

	/**
	 * Exception thrown when an error occurs connecting to web service
	 */

	class CConnectionError: public CExceptionBase
	{
	public:
			CConnectionError(const std::string& ErrorMessage)
			: CExceptionBase(ErrorMessage,"Connection error")
			{
			}
	};

	/**
	 * Exception thrown when a connection to the web service times out
	 */

	class CTimeoutError: public CExceptionBase
	{
	public:
			CTimeoutError(const std::string& ErrorMessage)
			: CExceptionBase(ErrorMessage,"Timeout error")
			{
			}
	};

	/**
	 * Exception thrown when an authentication error occurs
	 */

	class CAuthenticationError: public CExceptionBase
	{
	public:
			CAuthenticationError(const std::string& ErrorMessage)
			: CExceptionBase(ErrorMessage,"Authentication error")
			{
			}
	};

	/**
	 * Exception thrown when an error occurs fetching data
	 */

	class CFetchError: public CExceptionBase
	{
	public:
			CFetchError(const std::string& ErrorMessage)
			: CExceptionBase(ErrorMessage,"Fetch error")
			{
			}
	};

	/**
	 * Exception thrown when an invalid request is made
	 */

	class CRequestError: public CExceptionBase
	{
	public:
			CRequestError(const std::string& ErrorMessage)
			: CExceptionBase(ErrorMessage,"Request error")
			{
			}
	};

	/**
	 * Exception thrown when the requested resource is not found
	 */

	class CResourceNotFoundError: public CExceptionBase
	{
	public:
			CResourceNotFoundError(const std::string& ErrorMessage)
			: CExceptionBase(ErrorMessage,"Resource not found error")
			{
			}
	};

	/**
	 * @brief Object for make HTTP requests
	 *
	 * Object to be used to make HTTP requests
	 *
	 */
	class CHTTPFetch
	{
	public:
		/**
		 * @brief Constructor
		 *
		 * Constructor
		 *
		 * @param UserAgent User agent string to send
		 * @param Host Host name to connect to
		 * @param Port Port to connect to (80 by default)
		 */


		CHTTPFetch(const std::string& UserAgent, const std::string& Host, int Port=80);
		~CHTTPFetch();

		/**
		 * @brief Set the user name to use
		 *
		 * Set the user name to use when authenticating with the web server
		 *
		 * @param UserName User name to use
		 */

		void SetUserName(const std::string& UserName);

		/**
		 * @brief Set the password to use
		 *
		 * Set the password to use when authenticating with the web server
		 *
		 * @param Password Password to use
		 */

		void SetPassword(const std::string& Password);

		/**
		 * @brief Set the proxy server to use
		 *
		 * Set the proxy server to use when connecting with the web server
		 *
		 * @param ProxyHost Proxy server to use
		 */

		void SetProxyHost(const std::string& ProxyHost);

		/**
		 * @brief Set the proxy port to use
		 *
		 * Set the proxy server port to use when connecting to the web server
		 *
		 * @param ProxyPort Proxy server port to use
		 */

		void SetProxyPort(int ProxyPort);

		/**
		 * @brief Set the proxy user name to use
		 *
		 * Set the user name to use when authenticating with the proxy server
		 *
		 * @param ProxyUserName Proxy user name to use
		 */

		void SetProxyUserName(const std::string& ProxyUserName);

		/**
		 * @brief Set the proxy password to use
		 *
		 * Set the password to use when authenticating with the proxy server
		 *
		 * @param ProxyPassword Proxy server password to use
		 */

		void SetProxyPassword(const std::string& ProxyPassword);

		/**
		 * @brief Make a request to the server
		 *
		 * Make a request to the server
		 *
		 * @param URL URL to request
		 * @param Request Request type (GET by default)
		 *
		 * @return Number of bytes received
		 *
		 * @throw CConnectionError An error occurred connecting to the web server
		 * @throw CTimeoutError A timeout occurred when connecting to the web server
		 * @throw CAuthenticationError An authentication error occurred
		 * @throw CFetchError An error occurred fetching data
		 * @throw CRequestError The request was invalid
		 * @throw CResourceNotFoundError The requested resource was not found
		 */

		int Fetch(const std::string& URL, const std::string& Request="GET");

		/**
		 * @brief Get the data receieved
		 *
		 * Get the data received from the request
		 *
		 * @return Data received
		 */

		std::vector<unsigned char> Data() const;

		/**
		 * @brief libneon result code from the request
		 *
		 * Return the result code from the request
		 *
		 * @return libneon result code from the request
		 */

		int Result() const;

		/**
		 * @brief Status
		 *
		 * Return the HTTP status code from the request
		 *
		 * @return HTTP status code from the request
		 */

		int Status() const;

		/**
		 * @brief Return the error message from the request
		 *
		 * Return the error message from the request
		 *
		 * @return Error message from the request
		 */

		std::string ErrorMessage() const;

	private:
		CHTTPFetchPrivate * const m_d;

		static int httpAuth(void *userdata, const char *realm, int attempts, char *username, char *password);
		static int proxyAuth(void *userdata, const char *realm, int attempts, char *username, char *password);
		static int httpResponseReader(void *userdata, const char *buf, size_t len);
	};
}

#endif
