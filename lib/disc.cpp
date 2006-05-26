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
 
#include <musicbrainz3/disc.h>

using namespace std;
using namespace MusicBrainz;

Disc::Disc(const string &id)
	: id(id)
{
}

Disc::~Disc()
{
    tracks.clear();
}

string
Disc::getId() const
{
    return id;
}

void
Disc::setId(const string &value)
{
    id = value;
}

int
Disc::getSectors() const
{
    return sectors;
}

void
Disc::setSectors(const int value)
{
    sectors = value;
}

int
Disc::getFirstTrackNum() const
{
    return firstTrackNum;
}

void
Disc::setFirstTrackNum(const int value)
{
    firstTrackNum = value;
}

int
Disc::getLastTrackNum() const
{
    return lastTrackNum;
}

void
Disc::setLastTrackNum(const int value)
{
    lastTrackNum = value;
}

const Disc::TrackList &
Disc::getTracks() const
{
    return tracks;
}

void
Disc::addTrack(Disc::Track track)
{
    tracks.push_back(track);
}

