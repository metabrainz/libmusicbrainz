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

#ifndef _MUSICBRAINZ5_QUERY_H
#define _MUSICBRAINZ5_QUERY_H

#include "defines.h"

#include "Entity.h"

#include "musicbrainz5/ReleaseList.h"
#include "musicbrainz5/Metadata.h"

#include "musicbrainz5/xmlParser.h"

#include <string>
#include <map>
#include <vector>

/**
 * @mainpage libmusicbrainz5
 *
 * This is the documentation for libmusicbrainz5, a library for retrieving data from
 * the <a target="_blank" href="http://musicbrainz.org">MusicBrainz</a> service.
 *
 * The main entry point to the library is the MusicBrainz5::CQuery object.
 *
 * For details of the C interface, see the documentation for the file mb5_c.h.
 *
 * Please report any issues with this library at
 * <a target="_blank" href="http://tickets.musicbrainz.org/">http://tickets.musicbrainz.org/</a>.
 *
 * @par Compiling and Linking
 *
 * This package provides a pkg-config script that returns the necessary compiler
 * and linker flags, as well as the version number.  To build a small sample
 * program one would use:
 *
 * @par
 *     <tt>g++ -o test_app test_app.cpp `pkg-config libmusicbrainz5 --cflags --libs`</tt>
 *
 * If you don't want/can't use pkg-config and you are using the C API, make sure
 * you link in the C++ standard library:
 *
 * @par
 *     <tt>gcc -o test_app test_app.c -lmusicbrainz5 -lm -lstdc++</tt>
 *
 * @par Example:
 *
 * A brief example showing how to lookup a list of releases matching a disc id
 *
@code
MusicBrainz5::CQuery Query("cdlookupexample-1.0");

try
{
	MusicBrainz5::CMetadata Metadata=Query.Query("discid",DiscID);
	if (Metadata.Disc() && Metadata.Disc()->ReleaseList())
	{
		MusicBrainz5::CReleaseList *ReleaseList=Metadata.Disc()->ReleaseList();

		std::cout << "Found " << ReleaseList->NumItems() << " release(s)" << std::endl;

		for (int count=0;count<ReleaseList->NumItems();count++)
		{
			MusicBrainz5::CRelease *Release=ReleaseList->Item(count);

			std::cout << "Basic release: " << std::endl << *Release << std::endl;

			//The releases returned from LookupDiscID don't contain full information

			MusicBrainz5::CQuery::tParamMap Params;
			Params["inc"]="artists labels recordings release-groups url-rels discids artist-credits";

			Metadata=Query.Query("release",Release.ID(),"",Params);
			if (Metadata.Release())
			{
				MusicBrainz5::CRelease *FullRelease=Metadata.Release();

				std::cout << *FullRelease << std::endl;
			}
		}
	}
}

catch (MusicBrainz5::CConnectionError& Error)
{
	std::cout << "Connection Exception: '" << Error.what() << "'" << std::endl;
	std::cout << "LastResult: " << Query.LastResult() << std::endl;
	std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
	std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
}

catch (MusicBrainz5::CTimeoutError& Error)
{
	std::cout << "Timeout Exception: '" << Error.what() << "'" << std::endl;
	std::cout << "LastResult: " << Query.LastResult() << std::endl;
	std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
	std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
}

catch (MusicBrainz5::CAuthenticationError& Error)
{
	std::cout << "Authentication Exception: '" << Error.what() << "'" << std::endl;
	std::cout << "LastResult: " << Query.LastResult() << std::endl;
	std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
	std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
}

catch (MusicBrainz5::CFetchError& Error)
{
	std::cout << "Fetch Exception: '" << Error.what() << "'" << std::endl;
	std::cout << "LastResult: " << Query.LastResult() << std::endl;
	std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
	std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
}

catch (MusicBrainz5::CRequestError& Error)
{
	std::cout << "Request Exception: '" << Error.what() << "'" << std::endl;
	std::cout << "LastResult: " << Query.LastResult() << std::endl;
	std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
	std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
}

catch (MusicBrainz5::CResourceNotFoundError& Error)
{
	std::cout << "ResourceNotFound Exception: '" << Error.what() << "'" << std::endl;
	std::cout << "LastResult: " << Query.LastResult() << std::endl;
	std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
	std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
}
@endcode
 */

namespace MusicBrainz5
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
	 * For information on search syntax, see the documentation for
	 * <a target="_blank" href="http://wiki.musicbrainz.org/Text_Search_Syntax">search syntax</a>.
	 *
	 * @b Note It is the responsibility of the caller to validate any pointers returned
	 * from the library. It is valid for a pointer to be NULL if the information was not
	 * present in the response from the MusicBrainz service.
	 *
	 * @b Note The ownership of any pointers returned from the C++ interfaces remains
	 * with the library. The caller should not delete any pointer returned from the
	 * library. Users of the C library should take note of the documentation for each
	 * individual function in mb5_c.h
	 */
	class CQuery
	{
	public:
		typedef std::map<std::string,std::string> tParamMap;

		/**
		 * @brief Enumerated type for query status
		 *
		 * Enumerated type for query status
		 */
		enum tQueryResult
		{
			eQuery_Success=0,
			eQuery_ConnectionError,
			eQuery_Timeout,
			eQuery_AuthenticationError,
			eQuery_FetchError,
			eQuery_RequestError,
			eQuery_ResourceNotFound
		};

		/**
		 * @brief Constructor for MusicBrainz::CQuery object
		 *
		 * This is the constructor for the MusicBrainz::CQuery object.
		 *
		 * @param UserAgent User agent to use in any queries and submissions. The format
		 * 		is @c "application-version", where application is your application's name
		 *		and version is a version number which may not contain a '-' character.
		 * @param Server Server to be used (defaults to musicbrainz.org if not specified)
		 * @param Port Port to use (defaults to 80 if not specified)
		 *
		 */

		CQuery(const std::string& UserAgent, const std::string& Server="musicbrainz.org", int Port=80);

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
		 * @return MusicBrainz5::CReleaseList
		 */

		CReleaseList LookupDiscID(const std::string& DiscID);

		/**
		 * @brief Return full information about a release
		 *
		 * Query for detailed information about a specific release
		 *
		 * @param ReleaseID MusicBrainz release ID to lookup
		 *
		 * @return MusicBrainz::CRelease object
		 *
		 * @throw CConnectionError An error occurred connecting to the web server
		 * @throw CTimeoutError A timeout occurred when connecting to the web server
		 * @throw CAuthenticationError An authentication error occurred
		 * @throw CFetchError An error occurred fetching data
		 * @throw CRequestError The request was invalid
		 * @throw CResourceNotFoundError The requested resource was not found
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
		 * @return MusicBrainz5::CMetadata object
		 *
		 * @throw CConnectionError An error occurred connecting to the web server
		 * @throw CTimeoutError A timeout occurred when connecting to the web server
		 * @throw CAuthenticationError An authentication error occurred
		 * @throw CFetchError An error occurred fetching data
		 * @throw CRequestError The request was invalid
		 * @throw CResourceNotFoundError The requested resource was not found
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
		 *
		 * @throw CConnectionError An error occurred connecting to the web server
		 * @throw CTimeoutError A timeout occurred when connecting to the web server
		 * @throw CAuthenticationError An authentication error occurred
		 * @throw CFetchError An error occurred fetching data
		 * @throw CRequestError The request was invalid
		 * @throw CResourceNotFoundError The requested resource was not found
		 */

		bool AddCollectionEntries(const std::string& CollectionID, const std::vector<std::string>& Entries);

		/**
		 * @brief Delete entries from the specified collection
		 *
		 * Delete a list of releases from the specified collection.
		 *
		 * @param CollectionID The MusicBrainz ID of the collection to delete entries from
		 * @param Entries List of MusicBrainz Release IDs to delete from the collection
		 *
		 * @return true if successful, false otherwise
		 *
		 * @throw CConnectionError An error occurred connecting to the web server
		 * @throw CTimeoutError A timeout occurred when connecting to the web server
		 * @throw CAuthenticationError An authentication error occurred
		 * @throw CFetchError An error occurred fetching data
		 * @throw CRequestError The request was invalid
		 * @throw CResourceNotFoundError The requested resource was not found
		 */

		bool DeleteCollectionEntries(const std::string& CollectionID, const std::vector<std::string>& Entries);

		/**
		 * @brief Return result of the last query
		 *
		 * Return the result of the last query
		 *
		 * @return Result of last query
		 */

		CQuery::tQueryResult LastResult() const;

		/**
		 * @brief Return HTTP code of the last query
		 *
		 * Return the HTTP code of the last query
		 *
		 * @return HTTP code of last query
		 */
		int LastHTTPCode() const;

		/**
		 * @brief Return error message from the last query
		 *
		 * Return the error message from the last query
		 *
		 * @return Error message from last query
		 */
		std::string LastErrorMessage() const;

		/**
		 * @brief Return the library version
		 *
		 * Return the library version
		 *
		 * @return Library version
		 */
		std::string Version() const;

	private:
		CQueryPrivate * const m_d;

		CMetadata PerformQuery(const std::string& Query);
		void WaitRequest() const;
		std::string UserAgent() const;
		bool EditCollection(const std::string& CollectionID, const std::vector<std::string>& Entries, const std::string& Action);
		std::string URIEscape(const std::string& URI);
		std::string URLEncode(const std::map<std::string,std::string>& Params);
	};
}

#endif
