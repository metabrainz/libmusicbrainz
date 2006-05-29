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
 
#ifndef __MUSICBRAINZ3_QUERY_H__
#define __MUSICBRAINZ3_QUERY_H__

#include <string>
#include <musicbrainz3/webservice.h>
#include <musicbrainz3/metadata.h>
#include <musicbrainz3/model.h> 

namespace MusicBrainz
{
  
	/**
	 * A simple interface to the MusicBrainz web service.
	 *
	 * This is a facade which provides a simple interface to the MusicBrainz
	 * web service. It hides all the details like fetching data from a server,
	 * parsing the XML and creating an object tree. Using this class, you can
	 * request data by ID or search the \e collection of all resources
	 * (artists, releases, or tracks) to retrieve those matching given
	 * criteria. 
	 *
	 * @todo Add examples here.
	 */
	
	class MB_API Query
	{
	public:

		/**
		 * Constructor.
		 *
		 * The \a ws parameter has to be a subclass of IWebService.
		 * If it isn't given, the default WebService class is used to
		 * create an IWebService instance.
		 *
		 * If the constructor is called without arguments, an instance
		 * of WebService is used, preconfigured to use the MusicBrainz
		 * server. This should be enough for most users.
		 * 
		 * If you want to use queries which require authentication you
		 * have to pass a WebService instance where user name and
		 * password have been set.
		 *
		 * The \a clientId parameter is required for data submission.
		 * The format is \c "application-version", where \c application
		 * is your application's name and \c version is a version
		 * number which may not contain a '-' character.
		 *
		 * @param ws a pointer to subclass instance of IWebService, or \c NULL
		 * @param clientId a string containing the application's ID
		 */
		Query(IWebService *ws, const std::string &clientId);

		/**
		 * Destructor.
		 */
		virtual ~Query();
		 
		/**
		 * Returns an artist.
		 *
		 * If no artist with that ID can be found, \a include contains
		 * invalid tags or there's a server problem, an exception is
		 * raised.
		 *
		 * @param id a string containing the artist's ID
		 * @param include an ArtistIncludes instance
		 *
		 * @return a pointer to Artist instance, or \c NULL
		 *
		 * @note If the returned pointer is not \c NULL, the caller takes
		 * responsibility for deleting it when it is no longer needed.
		 *
		 * @throw ConnectionError couldn't connect to server
		 * @throw RequestError invalid ID or include tags
		 * @throw ResourceNotFoundError artist doesn't exist
		 * @throw ResponseError server returned invalid data
		 */
		 
		Artist *getArtistById(const std::string &id,
							  const ArtistIncludes &include = ArtistIncludes());
		
		/**
		 * Returns a release.
		 *
		 * If no release with that ID can be found, C{include} contains
		 * invalid tags or there's a server problem, and exception is
		 * raised. 
		 *
		 * @param id a string containing the release's ID
		 * @param include an ReleaseIncludes instance
		 *
		 * @return a pointer to Release instance, or \c NULL
		 *
		 * @note If the returned pointer is not \c NULL, the caller takes
		 * responsibility for deleting it when it is no longer needed.
		 *
		 * @throw ConnectionError couldn't connect to server
		 * @throw RequestError invalid ID or include tags
		 * @throw ResourceNotFoundError artist doesn't exist
		 * @throw ResponseError server returned invalid data
		 */
		 
		Release *getReleaseById(const std::string &id,
								const ReleaseIncludes &include = ReleaseIncludes());
		
		/**
		 * Returns a track.
		 *
		 * If no track with that ID can be found, \a include contains
		 * invalid tags or there's a server problem, and exception is
		 * raised.  
		 *
		 * @param id a string containing the track's ID
		 * @param include an TrackIncludes instance
		 *
		 * @return a pointer to Track instance, or \c NULL
		 *
		 * @note If the returned pointer is not \c NULL, the caller takes
		 * responsibility for deleting it when it is no longer needed.
		 *
		 * @throw ConnectionError couldn't connect to server
		 * @throw RequestError invalid ID or include tags
		 * @throw ResourceNotFoundError artist doesn't exist
		 * @throw ResponseError server returned invalid data
		 */
		 
		Track *getTrackById(const std::string &id,
							const TrackIncludes &include = TrackIncludes());
		
	protected:
	
		template<typename IT, typename FT>
		Metadata *getFromWebService(const std::string &entity,
									const std::string &id,
									const IT &include = IT(),
									const FT &filter = FT());
		
	private:
	
		IWebService *ws;
		std::string clientId;		
	};
	
}

#endif
