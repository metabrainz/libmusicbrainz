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
 *
 * $Id$
 */
 
#include <string>
#include <musicbrainz3/model.h>

using namespace std;
using namespace MusicBrainz;

Track::Track(const string &id, const string &title)
    : Entity(id), artist(0), duration(0)
{
    setTitle(title);
}

Track::~Track()
{
	if (artist)
		delete artist;
}

string
Track::getTitle() const
{
    return title;
}

void
Track::setTitle(const string &value)
{
    title = value;
}

Artist *
Track::getArtist()
{
	return artist;
}

void
Track::setArtist(Artist *value)
{
	if (artist)
		delete artist;
	artist = value;
}

int
Track::getDuration() const
{
    return duration;
}

void
Track::setDuration(const int value)
{
    duration = value;
}


