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

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

/**
 * Create a new instance of #Mb4Query.
 *
 * @see MusicBrainz4::CQuery::CQuery
 *
 * @param UserAgent User agent to be passed to submissions
 * @param Server Server to use, pass null to use the default server
 * @param Port Port to use, pass 0 to use the default port
 *
 * @return The newly created #Mb4Query object. This object <b>must</b> be deleted once
 *				finished with.
 */

	Mb4Query mb4_query_new(const char *UserAgent, const char *Server, int Port);

/**
 * Set the username for authenticating to MusicBrainz
 *
 * @see MusicBrainz4::CQuery::SetUserName
 *
 * @param Query #Mb4Query object
 * @param UserName Username to use
 */
	void mb4_query_set_username(Mb4Query Query, const char *UserName);

/**
 * Set the password for authenticating to MusicBrainz
 *
 * @see MusicBrainz4::CQuery::SetPassword
 *
 * @param Query #Mb4Query object
 * @param Password Password to use
 */
	void mb4_query_set_password(Mb4Query Query, const char *Password);

/**
 * Set the proxy server
 *
 * @see MusicBrainz4::CQuery::SetProxyHost
 *
 * @param Query #Mb4Query object
 * @param ProxyHost Proxy server to use
 */
	void mb4_query_set_proxyhost(Mb4Query Query, const char *ProxyHost);

/**
 *	Set the port to use on the proxy server
 *
 * @see MusicBrainz4::CQuery::SetProxyPort
 *
 * @param Query #Mb4Query object
 * @param ProxyPort Port to use on proxy server
 */
	void mb4_query_set_proxyport(Mb4Query Query, int ProxyPort);

/**
 *	Set the username to use to authenticate to the proxy server
 *
 * @see MusicBrainz4::CQuery::SetProxyUserName
 *
 * @param Query #Mb4Query object
 * @param	ProxyUserName User name to use
 */
	void mb4_query_set_proxyusername(Mb4Query Query, const char *ProxyUserName);

/**
 * Set the password to use to authenticate to the proxy server
 *
 * @see MusicBrainz4::CQuery::SetProxyPassword
 *
 * @param Query #Mb4Query object
 * @param ProxyPassword Password to use
 */
	void mb4_query_set_proxypassword(Mb4Query Query, const char *ProxyPassword);

/**
 *	Return a list of releases that match the specified Disc ID
 *
 * @see MusicBrainz4::CQuery::LookupDiscID
 *
 * @param Query #Mb4Query object
 * @param	DiscID DiscID to lookup
 *
 * @return A #Mb4ReleaseList object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4ReleaseList mb4_query_lookup_discid(Mb4Query Query, const char *DiscID);

/**
 * Return full information about a specific release
 *
 * @see MusicBrainz4::CQuery::LookupRelease
 *
 * @param Query #Mb4Query object
 * @param	Release Release to return information for
 *
 * @return A #Mb4Release object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Release mb4_query_lookup_release(Mb4Query Query, const char *Release);

/**
 *	Perform a generic query
 *
 * @see MusicBrainz4::CQuery::Query
 *
 * @param Query #Mb4Query object
 * @param	Entity The entity to query
 * @param ID The ID to query
 * @param Resource The resource to query
 * @param	NumParams The number of parameters in the following arrays
 * @param ParamNames Array of strings containing parameter names
 * @param	ParamValues Array of space seperated parameter values
 *
 * @return A #Mb4Metadata object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Metadata mb4_query_query(Mb4Query Query, const char *Entity, const char *ID, const char *Resource, int NumParams, char **ParamNames, char **ParamValues);

/**
 *	Add a list of releases to a collection
 *
 * @see MusicBrainz4::CQuery::AddCollectionEntries
 *
 * @param Query #Mb4Query object
 * @param	Collection ID of collection to add releases to
 * @param	NumEntries The number of entries to add
 * @param Entries Array of strings of release IDs to add
 *
 * @return 0 on failure, 1 on success
 */
	unsigned char mb4_query_add_collection_entries(Mb4Query Query, const char *Collection, int NumEntries, const char **Entries);

/**
 *	Delete a list of releases from a collection
 *
 * @see MusicBrainz4::CQuery::AddCollectionEntries
 *
 * @param Query #Mb4Query object
 * @param	Collection ID of collection to delete releases from
 * @param	NumEntries The number of entries to delete
 * @param Entries Array of strings of release IDs to delete
 *
 * @return 0 on failure, 1 on success
 */
	unsigned char mb4_query_delete_collection_entries(Mb4Query Query, const char *Collection, int NumEntries, const char **Entries);

/**
 * @see MusicBrainz4::CQuery::tQueryResult
 */

	typedef enum
	{
			eQuery_Success=0,
			eQuery_ConnectionError,
			eQuery_Timeout,
			eQuery_AuthenticationError,
			eQuery_FetchError,
			eQuery_RequestError,
			eQuery_ResourceNotFound
	} tQueryResult;

/**
 * @see MusicBrainz4::CQuery::LastResult
 *
 * @param Query #Mb4Query object
 *
 * @return Last query result code
 */
	tQueryResult mb4_query_get_lastresult(Mb4Query Query);

