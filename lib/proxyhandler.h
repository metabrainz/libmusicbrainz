/* --------------------------------------------------------------------------

   MusicBrainz -- The Internet music metadatabase

   Copyright (C) 2000 Emusic.com
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

----------------------------------------------------------------------------*/

#ifndef _PROXYHANDLER_H_
#define _PROXYHANDLER_H_

#include "errors.h"
#include <string>
using namespace std;

class ProxyHandler {
public:  
  /** Proxy Handler Constructor. */
  ProxyHandler();

  /** Proxy Handler Constructor.
   * Creates a proxy handler using the proxy server's url and port number. 
   * @param proxyUrl - the address of the proxy server.
   * @param port - the port number of the proxy server.
   */ 
  ProxyHandler(const string &proxyUrl, unsigned int port);

  /** Destructor. */
  ~ProxyHandler();

public:
  /** Sets the proxy server's address.
   * @param proxyUrl - the address of the proxy server.
   */
  void SetUrl(const string &proxyUrl);

  /** Gets the proxy server's address.
   * @returns the address of the proxy server.  An empty string is 
   * returned if no address is available.
   */
  string GetUrl();

  /** Sets the proxy server's port number.
   * @param port - the port number of the proxy server.
   */
  void SetPort(unsigned int port);

  /** Gets the proxy server's port number.
   * @returns the proxy number of the proxy server.
   */
  unsigned int GetPort();

  /** Sets the proxy server's credentials needed to use the proxy server.
   * @param username - the username. It cannot contain a colon, ":".
   * @param password - the password.
   */
  Error SetCredentials(const string &username, const string &password);

  /** Sets whether or not the proxy handler was successful in logging in. 
   * @param successful - a boolean value for whether the authentication was successful.
   */
  void SetAuthenticated(bool status);

  /** Gets the authentication status of the proxy handler.
   * @returns true if the proxy has been authenticated, false otherwise.
   */
  bool IsAuthenticated();

  /** Saves the request header information for resending after authentication.
   * @param query - the query in the request header
   * @param file - the file being requested
   * @param data - the data in the request packet
   */
  void SaveRequestInfo(const string& query, const string& file, const string& data);

  /** Performs authentication against the proxy server.
   * @param headerInfo - the request header
   * @param httpResponse - the new request header that will be returned with the authorization header.
   * @returns kError_NoErr if successful, otherwise an Error value is returned.
   */
  Error Authenticate(const string &headerInfo, string &httpResponse);

private:
  /** 
   * Creates the proxy authorization header using the Basic algorithm. 
   * @returns the authorization string to be appended to the original request header.
   */
  string DoBasicAuthentication();

  /**
   * Creates the proxy authorization header using the MD5 digest algorithm.
   * @param headerInfo - the original request header
   * @returns the authorization string to be appended to the original request header.
   */
  string DoMD5DigestAuthentication(const string &headerInfo);

  /** Converts an ascii string to a hexadecimal string. 
   * @param ascii - the ascii string to convert.
   * @returns the hexadecimal string
   */
  string ConvertToHex(const string &ascii);

private:
  string m_server;     /**< The url of the proxy server. */
  unsigned int m_port; /**< The port number to connect to on the proxy server. */
  string m_username;   /**< The username used for authenticating with the proxy server. */
  string m_password;   /**< The password used for authentication with the proxy server. */
  bool m_status;       /**< The authentication status: true if logged in, false if not. */
  /**
   * The http request buffer will hold the request header if proxy authentication is needed.
   * After authentication has been performed a modified request header will be created using
   * the original request header and the new authorization header info.
   */
  string m_httpRequestBuf[3];
};

#endif
