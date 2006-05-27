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
 
#ifndef __MUSICBRAINZ3_METADATA_H__
#define __MUSICBRAINZ3_METADATA_H__

#include <musicbrainz3/model.h>
#include <musicbrainz3/results.h>

namespace MusicBrainz
{
	
	/**
	 * Represents a parsed Music Metadata XML document.
	 *
	 * The Music Metadata XML format is very flexible and may contain a
	 * diverse set of data (e.g. an artist, a release and a list of tracks),
	 * but usually only a small subset is used (either an artist, a release
	 * or a track, or a lists of objects from one class).
	 *
	 * @see MbXmlParser for reading
	 */
	class MB_API Metadata 
	{
	public:
	
		Metadata();
		
		virtual ~Metadata();
		
		/**
		 * Returns an artist.
		 *
		 * @return a pointer to Artist object, or NULL
		 */
		Artist *getArtist() const;
		
		/**
		 * Sets the artist.
		 *
		 * @param artist a pointer to Artist object, or NULL
		 */
		void setArtist(Artist *artist);
		
		/**
		 * Returns a release.
		 *
		 * @return a pointer to Release object, or NULL
		 */
		Release *getRelease() const;
		
		/**
		 * Sets the release.
		 *
		 * @param release a pointer to Release object, or NULL
		 */
		void setRelease(Release *release);
		
		/**
		 * Returns a track.
		 *
		 * @return a pointer to Track object, or NULL
		 */
		Track *getTrack() const;
		
		/**
		 * Sets the track.
		 *
		 * @param track a pointer to Track object, or NULL
		 */
		void setTrack(Track *track);
		
		/**
		 * Returns a list of users.
		 *
		 * @return a vector of pointers to User objects
		 *
		 * @note This is a MusicBrainz extension.
		 */
		UserList &getUserList();
		
		/**
		 * Returns a artist result list. 
		 *
		 * @return a vector of pointers to ArtistResult objects
		 */
		ArtistResultList &getArtistResults();
		
		/**
		 * Returns a track result list. 
		 *
		 * @return a vector of pointers to TrackResult objects
		 */
		TrackResultList &getTrackResults();
		
		/**
		 * Returns a release result list. 
		 *
		 * @return a vector of pointers to ReleaseResult objects
		 */
		ReleaseResultList &getReleaseResults();
		
	private:
	
		Artist *artist;
		Release *release;
		Track *track;
		UserList userList;
		ArtistResultList artistResults;
		TrackResultList trackResults;
		ReleaseResultList releaseResults;
	};
	
}

#endif

