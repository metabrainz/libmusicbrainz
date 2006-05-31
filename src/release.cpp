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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
 
#include <string>
#include <musicbrainz3/model.h>

using namespace std;
using namespace MusicBrainz;

const string Release::TYPE_NONE = NS_MMD_1 + "None";
	
const string Release::TYPE_ALBUM = NS_MMD_1 + "Album";
const string Release::TYPE_SINGLE = NS_MMD_1 + "Single";
const string Release::TYPE_EP = NS_MMD_1 + "EP";
const string Release::TYPE_COMPILATION = NS_MMD_1 + "Compilation";	
const string Release::TYPE_SOUNDTRACK = NS_MMD_1 + "Soundtrack";
const string Release::TYPE_SPOKENWORD = NS_MMD_1 + "Spokenword";
const string Release::TYPE_INTERVIEW = NS_MMD_1 + "Interview";
const string Release::TYPE_AUDIOBOOK = NS_MMD_1 + "Audiobook";
const string Release::TYPE_LIVE = NS_MMD_1 + "Live";
const string Release::TYPE_REMIX = NS_MMD_1 + "Remix";	
const string Release::TYPE_OTHER = NS_MMD_1 + "Other";

const string Release::TYPE_OFFICIAL = NS_MMD_1 + "Official";
const string Release::TYPE_PROMOTION = NS_MMD_1 + "Promotion";
const string Release::TYPE_BOOTLEG = NS_MMD_1 + "Bootleg";	

Release::Release(const string &id, const string &title)
	: Entity(id), artist(0)
{
	setTitle(title);
}

Release::~Release()
{
	if (artist)
		delete artist;
	
	for (TrackList::iterator i = tracks.begin(); i != tracks.end(); i++) 
		delete *i;
	tracks.clear();
	
	for (DiscList::iterator i = discs.begin(); i != discs.end(); i++) 
		delete *i;
	discs.clear();
	
	for (ReleaseEventList::iterator i = releaseEvents.begin(); i != releaseEvents.end(); i++) 
		delete *i;
	releaseEvents.clear();
}

string
Release::getTitle() const
{
	return title;
}

void
Release::setTitle(const string &value)
{
	title = value;
}

string
Release::getTextLanguage() const
{
	return textLanguage;
}

void
Release::setTextLanguage(const string &value)
{
	textLanguage = value;
}

string
Release::getTextScript() const
{
	return textScript;
}

void
Release::setTextScript(const string &value)
{
	textScript = value;
}

Artist *
Release::getArtist()
{
	return artist;
}

void
Release::setArtist(Artist *value)
{
	if (artist)
		delete artist;
	artist = value;
}

string
Release::getAsin() const
{
	return asin;
}

void
Release::setAsin(const string &value)
{
	asin = value;
}

TrackList &
Release::getTracks()
{
	return tracks;
}

int
Release::getTracksOffset() const
{
	return tracksOffset;
}

void
Release::setTracksOffset(const int value)
{
	tracksOffset = value;
}

DiscList &
Release::getDiscs()
{
	return discs;
}

ReleaseEventList &
Release::getReleaseEvents()
{
	return releaseEvents;
}


