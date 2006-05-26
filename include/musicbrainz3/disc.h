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
 
#ifndef __MUSICBRAINZ3_DISC_H__
#define __MUSICBRAINZ3_DISC_H__

#include <string>
#include <vector>
#include <utility>
#include <musicbrainz3/musicbrainz.h>

namespace MusicBrainz
{
	
	/**
	 * Represents an Audio CD.
	 *
	 * This class represents an Audio CD. A disc can have an ID (the
	 * MusicBrainz DiscID), which is calculated from the CD's table of
	 * contents (TOC). There may also be data from the TOC like the length
	 * of the disc in sectors, as well as position and length of the tracks.
	 *
	 * Note that different TOCs, maybe due to different pressings, lead to
	 * different DiscIDs. Conversely, if two different discs have the same
	 * TOC, they also have the same DiscID (which is unlikely but not
	 * impossible). DiscIDs are always 28 characters long and look like this:
	 * \a 'J68I_CDcUFdCRCIbHSEbTBCbooA-'. Sometimes they are also referred
	 * to as CDIndex IDs.
	 *
	 * The MusicBrainz web service (WebService) only returns
	 * the DiscID and the number of sectors. The DiscID calculation function 
	 * readDisc, however, can retrieve the other
	 * attributes of Disc from an Audio CD in the disc drive. 
	 */
	class MB_API Disc
	{
	public:

		typedef std::pair<int, int> Track;
		typedef std::vector<Disc::Track> TrackList;
	
		/**
		 * Constructor.
		 *
		 * @param id a string containing a 28-character DiscID  
		 */
		Disc(const std::string &id = std::string());

		/**
		 * Destructor.
		 */
		virtual ~Disc();
		
		/**
		 * Returns the MusicBrainz DiscID. 
		 * 
		 * @return a string containing a 28-character DiscID  
		 */
		std::string getId() const;
		
		/**
		 * Sets the MusicBrainz DiscId. 
		 *
		 * @param value a string containing a 28-character DiscID 
		 */
		void setId(const std::string &value);

		int getSectors() const;
		void setSectors(const int sectors);
		
		int getFirstTrackNum() const;
		void setFirstTrackNum(const int trackNum);
		
		int getLastTrackNum() const;
		void setLastTrackNum(const int trackNum);
		
		const Disc::TrackList &getTracks() const;
		
		/**
		 * Adds a track to the list.
		 *
		 * @see getTracks 
		 */
		void addTrack(Disc::Track track);
		
	private:

		std::string id;
		int sectors;
		int firstTrackNum;
		int lastTrackNum;
		Disc::TrackList tracks;
	};
	
}

#endif