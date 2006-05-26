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
 
#ifndef __MUSICBRAINZ3_TRACK_H__
#define __MUSICBRAINZ3_TRACK_H__

#include <string>
#include <musicbrainz3/musicbrainz.h>
#include <musicbrainz3/entity.h>

namespace MusicBrainz
{
    
	class Artist;
	
    /**
     * Represents a track.
     *
     * This class represents a track which may appear on one or more releases.
     * A track may be associated with exactly one artist (the I{main} artist).
     *
     * Using getReleases, you can find out on which releases this track
     * appears. To get the track number, too, use the
     * Release::getTracksOffset method.
     *
     * @note Currently, the MusicBrainz server doesn't support tracks to
     *       be on more than one release.
     *
     * @see Release, Artist 
     */
    
    class MB_API Track : public Entity
    {
    public:
    
        /**
         * Constructor.
         *
         * @param id a string containing an absolute URI 
         * @param title a string containing the title 
         */
        Track(const std::string &id = "", const std::string &title = "");
        
        /**
         * Returns the track's title.
         *
         * The style and format of this attribute is specified by the
         * style guide.
         *
         * @return a string containing an absolute URI
         * 
         * @see <a href="http://musicbrainz.org/style.html">The MusicBrainz
         *      Style Guidelines</a> 
         */
        std::string getTitle() const;
        
        /**
         * Sets the track's title.
		 *
		 * @param title: a string containing the title
		 *
		 * @see: getTitle 
         */
        void setTitle(const std::string &title);
		
		Artist *getArtist();
		void setArtist(Artist *value);
        
		int getDuration() const;
		void setDuration(const int duration);
		
    private:
        
        std::string title;
		int duration;
		Artist *artist;
    };
    
}

#endif