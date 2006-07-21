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

class Track::TrackPrivate
{
public:
	TrackPrivate() :
		artist(0),
		duration(0)
		{}
		
	std::string title;
	Artist *artist;
	int duration;
};

Track::Track(const string &id, const string &title)
    : Entity(id)
{
	d = new TrackPrivate();
	
	d->title = title;
}

Track::~Track()
{
	if (d->artist)
		delete d->artist;
	
	delete d;
}

string
Track::getTitle() const
{
    return d->title;
}

void
Track::setTitle(const string &value)
{
    d->title = value;
}

Artist *
Track::getArtist()
{
	return d->artist;
}

void
Track::setArtist(Artist *value)
{
	if (d->artist)
		delete d->artist;
	d->artist = value;
}

int
Track::getDuration() const
{
    return d->duration;
}

void
Track::setDuration(const int value)
{
    d->duration = value;
}


