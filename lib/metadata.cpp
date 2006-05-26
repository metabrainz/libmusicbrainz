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
 
#include <musicbrainz3/metadata.h>

using namespace MusicBrainz;

Metadata::Metadata()
    : artist(NULL), track(NULL), release(NULL)
{
}

void 
Metadata::setArtist(Artist *value)
{
    artist = value;
}

void 
Metadata::setTrack(Track *value)
{
    track = value;
}
void 
Metadata::setRelease(Release *value)
{
    release = value;
}

Artist * 
Metadata::getArtist() const
{
    return artist;
}

Track * 
Metadata::getTrack() const
{
    return track;
}

Release * 
Metadata::getRelease() const
{
    return release;
}

UserList &
Metadata::getUserList()
{
	return userList;
}

ArtistResultList &
Metadata::getArtistResults()
{
	return artistResults;
}

TrackResultList &
Metadata::getTrackResults()
{
	return trackResults;
}

ReleaseResultList &
Metadata::getReleaseResults()
{
	return releaseResults;
}

