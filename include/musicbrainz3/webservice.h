/*
 * MusicBrainz -- The Internet music metadatabase
 *
 * Copyright (C) 2006 Lukas Lalinsky
 *  
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
 
#ifndef __MUSICBRAINZ3_WEBSERVICE_H__
#define __MUSICBRAINZ3_WEBSERVICE_H__

#include <string>
#include <musicbrainz3/musicbrainz.h> 
#include <musicbrainz3/iwebservice.h>

namespace MusicBrainz
{
  
	/**
	 * An interface to the MusicBrainz XML web service via HTTP.
	 *
	 * By default, this class uses the MusicBrainz server but may be
	 * configured for accessing other servers as well using the
	 * constructor (WebService::WebService). This implements IWebService, so
	 * additional documentation on method parameters can be found there.
	 */
	
	class MB_API WebService : public IWebService
	{
	public:
	
		/**
		 * Constructor.
		 * 
		 * This can be used without parameters. In this case, the
		 * MusicBrainz server will be used.
		 *
		 * @param host: a string containing a host name
		 * @param port: an integer containing a port number
		 * @param pathPrefix: a string prepended to all URLs
		 * @param username: a string containing a MusicBrainz user name
		 * @param password: a string containing the user's password
		 * @param realm: a string containing the realm used for authentication
		 */
		WebService(const std::string host="musicbrainz.org", const int port=80,
				   const std::string pathPrefix="/ws", const std::string username="",
				   const std::string password="", const std::string realm="musicbrainz.org");

		/**
		 * Query the web service via HTTP-GET.
		 *
		 * Returns a string containing the result or raises a
		 * WebServiceError. Conditions leading to errors may be
		 * invalid entities, IDs, \a include or \a filter parameters
		 * and unsupported version numbers. 
		 */
		std::string get(std::string entity, std::string id, std::string version="1"); 

		/**
		 * Initialized networking environment required by the web service.
		 *
		 * @note You must call this method at start of your program.
		 *
		 * @see cleanup
		 */
		static void init();
		
		/**
		 * Cleans up networking environment.
		 *
		 * @note You must call this method at end of your program.
		 *
		 * @see init
		 */
		static void cleanup();

	private:
	
		std::string host;
		int port;
		std::string pathPrefix;
		std::string username;
		std::string password;
		std::string realm;
		
	};
	
}

#endif