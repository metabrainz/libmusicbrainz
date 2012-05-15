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

/**
 * Create a new instance of #Mb5Query.
 *
 * @see MusicBrainz5::CQuery::CQuery
 *
 * @param UserAgent User agent to be passed to submissions
 * @param Server Server to use, pass null to use the default server
 * @param Port Port to use, pass 0 to use the default port
 *
 * @return The newly created #Mb5Query object. This object <b>must</b> be deleted once
 *				finished with.
 */

	Mb5Query mb5_query_new(const char *UserAgent, const char *Server, int Port);

/**
 * Set the username for authenticating to MusicBrainz
 *
 * @see MusicBrainz5::CQuery::SetUserName
 *
 * @param Query #Mb5Query object
 * @param UserName Username to use
 */
	void mb5_query_set_username(Mb5Query Query, const char *UserName);

/**
 * Set the password for authenticating to MusicBrainz
 *
 * @see MusicBrainz5::CQuery::SetPassword
 *
 * @param Query #Mb5Query object
 * @param Password Password to use
 */
	void mb5_query_set_password(Mb5Query Query, const char *Password);

/**
 * Set the proxy server
 *
 * @see MusicBrainz5::CQuery::SetProxyHost
 *
 * @param Query #Mb5Query object
 * @param ProxyHost Proxy server to use
 */
	void mb5_query_set_proxyhost(Mb5Query Query, const char *ProxyHost);

/**
 *	Set the port to use on the proxy server
 *
 * @see MusicBrainz5::CQuery::SetProxyPort
 *
 * @param Query #Mb5Query object
 * @param ProxyPort Port to use on proxy server
 */
	void mb5_query_set_proxyport(Mb5Query Query, int ProxyPort);

/**
 *	Set the username to use to authenticate to the proxy server
 *
 * @see MusicBrainz5::CQuery::SetProxyUserName
 *
 * @param Query #Mb5Query object
 * @param	ProxyUserName User name to use
 */
	void mb5_query_set_proxyusername(Mb5Query Query, const char *ProxyUserName);

/**
 * Set the password to use to authenticate to the proxy server
 *
 * @see MusicBrainz5::CQuery::SetProxyPassword
 *
 * @param Query #Mb5Query object
 * @param ProxyPassword Password to use
 */
	void mb5_query_set_proxypassword(Mb5Query Query, const char *ProxyPassword);

/**
 *	Return a list of releases that match the specified Disc ID
 *
 * @see MusicBrainz5::CQuery::LookupDiscID
 *
 * @param Query #Mb5Query object
 * @param	DiscID DiscID to lookup
 *
 * @return A #Mb5ReleaseList object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb5ReleaseList mb5_query_lookup_discid(Mb5Query Query, const char *DiscID);

/**
 * Return full information about a specific release
 *
 * @see MusicBrainz5::CQuery::LookupRelease
 *
 * @param Query #Mb5Query object
 * @param	Release Release to return information for
 *
 * @return A #Mb5Release object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb5Release mb5_query_lookup_release(Mb5Query Query, const char *Release);

/**
 *	Perform a generic query
 *
 * @see MusicBrainz5::CQuery::Query
 *
 * @param Query #Mb5Query object
 * @param	Entity The entity to query
 * @param ID The ID to query
 * @param Resource The resource to query
 * @param	NumParams The number of parameters in the following arrays
 * @param ParamNames Array of strings containing parameter names
 * @param	ParamValues Array of space seperated parameter values
 *
 * @return A #Mb5Metadata object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb5Metadata mb5_query_query(Mb5Query Query, const char *Entity, const char *ID, const char *Resource, int NumParams, char **ParamNames, char **ParamValues);

/**
 *	Add a list of releases to a collection
 *
 * @see MusicBrainz5::CQuery::AddCollectionEntries
 *
 * @param Query #Mb5Query object
 * @param	Collection ID of collection to add releases to
 * @param	NumEntries The number of entries to add
 * @param Entries Array of strings of release IDs to add
 *
 * @return 0 on failure, 1 on success
 */
	unsigned char mb5_query_add_collection_entries(Mb5Query Query, const char *Collection, int NumEntries, const char **Entries);

/**
 *	Delete a list of releases from a collection
 *
 * @see MusicBrainz5::CQuery::AddCollectionEntries
 *
 * @param Query #Mb5Query object
 * @param	Collection ID of collection to delete releases from
 * @param	NumEntries The number of entries to delete
 * @param Entries Array of strings of release IDs to delete
 *
 * @return 0 on failure, 1 on success
 */
	unsigned char mb5_query_delete_collection_entries(Mb5Query Query, const char *Collection, int NumEntries, const char **Entries);

/**
 * @see MusicBrainz5::CQuery::tQueryResult
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
 * @see MusicBrainz5::CQuery::LastResult
 *
 * @param Query #Mb5Query object
 *
 * @return Last query result code
 */
	tQueryResult mb5_query_get_lastresult(Mb5Query Query);

