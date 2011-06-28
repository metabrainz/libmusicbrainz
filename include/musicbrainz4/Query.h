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

#ifndef _MUSICBRAINZ4_QUERY_H
#define _MUSICBRAINZ4_QUERY_H

#include "musicbrainz4/GenericList.h"

#include "musicbrainz4/Release.h"
#include "musicbrainz4/Metadata.h"

#include "musicbrainz4/xmlParser.h"

#include <string>
#include <map>
#include <vector>

/**
 * @mainpage libmusicbrainz4
 *
 * This is the documentation for libmusicbrainz4, a library for retrieving data from
 * the <a target="_blank" href="http://www.musicbrainz.org">MusicBrainz</a> service.
 *
 * The main entry point to the library is the MusicBrainz4::CQuery object.
 *
 * For details of the C interface, see the documentation for the file mb4_c.h.
 *
 * Please report any issues with this library at
 * <a target="_blank" href="http://tickets.musicbrainz.org/">http://tickets.musicbrainz.org/</a>.
 */

namespace MusicBrainz4
{
	class CQueryPrivate;

	/**
	 * @brief Main object for generating queries to MusicBrainz
	 *
	 * This object is the main entry point for the library, generating a query to the
	 * MusicBrainz service, and parsing the results. The resultant objects can be used
	 * to retrieve information appropriate to the query.
	 *
	 * For information on generating queries and the expected responses, see the
	 * documentation for the
	 * <a target="_blank" href="http://musicbrainz.org/doc/XML_Web_Service/Version_2">web service</a>.
	 *
	 * @b Note It is the responsibility of the caller to validate any pointers returned
	 * from the library. It is valid for a pointer to be NULL if the information was not
	 * present in the response from the MusicBrainz service.
	 *
	 * @b Note The ownership of any pointers returned from the C++ interfaces remains
	 * with the library. The caller should not delete any pointer returned from the
	 * library. Users of the C library should take note of the documentation for each
	 * individual function in mb4_c.h
	 */
	class CQuery
	{
	public:
		typedef std::map<std::string,std::string> tParamMap;

		/**
		 * @brief Constructor for MusicBrainz::CQuery object
		 *
		 * This is the constructor for the MusicBrainz::CQuery object.
		 *
		 * @param UserAgent User agent to use in any queries and submissions
		 * @param Server Server to be used (defaults to www.musicbrainz.org if not specified)
		 * @param Port Port to use (defaults to 80 if not specified)
		 *
		 */

		CQuery(const std::string& UserAgent, const std::string& Server="www.musicbrainz.org", int Port=80);

		~CQuery();

		/**
		 * @brief Set the user name
		 *
		 * Set the user name to use when authenticating to the MusicBrainz service
		 *
		 * @param UserName Username to use
		 */

		void SetUserName(const std::string& UserName);

		/**
		 * @brief Set the password
		 *
		 * Set the password to use when authenticating to the MusicBrainz service
		 *
		 * @param Password Password to use
		 */

		void SetPassword(const std::string& Password);

		/**
		 * @brief Set proxy server
		 *
		 * Set the proxy server to use for queries. @b Note The http_proxy environment variable
		 * will be used to set a 'default' proxy server. Calls to this method will override any
		 * proxy settings set by the http_proxy environment variable.
		 *
		 * @param ProxyHost Proxy server to use
		 */

		void SetProxyHost(const std::string& ProxyHost);

		/**
		 * @brief Set proxy server port
		 *
		 * Set the proxy server port to use for queries. @b Note The http_proxy environment variable
		 * will be used to set a 'default' proxy server. Calls to this method will override any
		 * proxy settings set by the http_proxy environment variable.
		 *
		 * @param ProxyPort Proxy port to use
		 */

		void SetProxyPort(int ProxyPort);

		/**
		 * @brief Set proxy server user name
		 *
		 * Set the user name to use when authenticating to the proxy server. @b Note The http_proxy
		 * environment variable will be used to set a 'default' proxy server. Calls to this method
		 * will override any proxy settings set by the http_proxy environment variable.
		 *
		 * @param ProxyUserName Proxy user name to use
		 */

		void SetProxyUserName(const std::string& ProxyUserName);

		/**
		 * @brief Set proxy server password
		 *
		 * Set the password to use when authenticating to the proxy server. @b Note The http_proxy
		 * environment variable will be used to set a 'default' proxy server. Calls to this method
		 * will override any proxy settings set by the http_proxy environment variable.
		 *
		 * @param ProxyPassword Proxy password to use
		 */

		void SetProxyPassword(const std::string& ProxyPassword);

		/**
		 * @brief Return a list of releases that match a disc ID
		 *
		 * Request a list of releases matching the specified disc ID.
		 *
		 * @param DiscID Disc id to match
		 *
		 * @return MusicBrainz4::CRelease list
		 */

		CGenericList<CRelease> LookupDiscID(const std::string& DiscID);

		/**
		 * @brief Return full information about a release
		 *
		 * Query for detailed information about a specific release
		 *
		 * @param ReleaseID MusicBrainz release ID to lookup
		 *
		 * @return MusicBrainz::CRelease object
		 */

		CRelease LookupRelease(const std::string& ReleaseID);

		/**
		 * @brief Perform a generic query
		 *
		 * Performs a generic query.
		 *
		 * Assuming the following parameters are set:
		 *
		 * "param1" = "p1v1 p1v2 p1v3"<br>
		 * "param2" = "p2v1"<br>
		 * "param3" = ""<br>
		 *
		 * The following query will be generated:
		 *
		 * /ws/2/Entity/ID/Resource?param1=p1v1+p1v2+p1v3&param2=p2v1&param3
		 *
		 * If any of ID or Resource are empty, those components will be omitted from the query.
		 *
		 * For full details about generating queries, see the
		 * <a target="_blank" href="http://musicbrainz.org/doc/XML_Web_Service/Version_2">web service</a>
		 * documentation.
		 *
		 * @param Entity Entity to lookup (e.g. artist, release, discid)
		 * @param ID The MusicBrainz ID of the entity
		 * @param Resource The resource (currently only used for collections)
		 * @param Params Map of parameters to add to the query (e.g. inc)
		 *
		 * @return MusicBrainz4::CMetadata object
		 */

		CMetadata Query(const std::string& Entity,const std::string& ID="",const std::string& Resource="",const tParamMap& Params=tParamMap());

		/**
		 * @brief Add entries to the specified collection
		 *
		 * Add a list of releases to the specified collection.
		 *
		 * @param CollectionID The MusicBrainz ID of the collection to add entries to
		 * @param Entries List of MusicBrainz Release IDs to add to the collection
		 *
		 * @return true if successful, false otherwise
		 */

		bool AddCollectionEntries(const std::string& CollectionID, std::vector<std::string>& Entries);

		/**
		 * @brief Delete entries from the specified collection
		 *
		 * Delete a list of releases from the specified collection.
		 *
		 * @param CollectionID The MusicBrainz ID of the collection to delete entries from
		 * @param Entries List of MusicBrainz Release IDs to delete from the collection
		 *
		 * @return true if successful, false otherwise
		 */

		bool DeleteCollectionEntries(const std::string& CollectionID, std::vector<std::string>& Entries);

	private:
		CQueryPrivate * const m_d;

		CMetadata PerformQuery(const std::string& Query);
		void WaitRequest() const;
		std::string UserAgent() const;
		bool EditCollection(const std::string& CollectionID, std::vector<std::string>& Entries, const std::string& Action);
		std::string URIEscape(const std::string& URI);
		std::string URLEncode(const std::map<std::string,std::string>& Params);
	};
}

#endif
