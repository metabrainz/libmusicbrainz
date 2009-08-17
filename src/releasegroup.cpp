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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * 
 */
 
#include <string>
#include <musicbrainz3/model.h>
#include "utils_private.h"

using namespace std;
using namespace MusicBrainz;

const string ReleaseGroup::TYPE_NONE = NS_MMD_1 + "None";
	
const string ReleaseGroup::TYPE_ALBUM = NS_MMD_1 + "Album";
const string ReleaseGroup::TYPE_SINGLE = NS_MMD_1 + "Single";
const string ReleaseGroup::TYPE_EP = NS_MMD_1 + "EP";
const string ReleaseGroup::TYPE_COMPILATION = NS_MMD_1 + "Compilation";	
const string ReleaseGroup::TYPE_SOUNDTRACK = NS_MMD_1 + "Soundtrack";
const string ReleaseGroup::TYPE_SPOKENWORD = NS_MMD_1 + "Spokenword";
const string ReleaseGroup::TYPE_INTERVIEW = NS_MMD_1 + "Interview";
const string ReleaseGroup::TYPE_AUDIOBOOK = NS_MMD_1 + "Audiobook";
const string ReleaseGroup::TYPE_LIVE = NS_MMD_1 + "Live";
const string ReleaseGroup::TYPE_REMIX = NS_MMD_1 + "Remix";	
const string ReleaseGroup::TYPE_OTHER = NS_MMD_1 + "Other";

class ReleaseGroup::ReleaseGroupPrivate
{
public:
	ReleaseGroupPrivate() :
		artist(NULL)
		{}
	
	std::string title;
	std::string type;
	Artist *artist;
};

ReleaseGroup::ReleaseGroup(const string &id, const string &title)
	: Entity(id)
{
	d = new ReleaseGroupPrivate();
	
	d->title = title;
}

ReleaseGroup::~ReleaseGroup()
{
	if (d->artist)
		delete d->artist;
	
	delete d;
}

SIMPLE_STRING_SETTER_GETTER(ReleaseGroup, Title, title);
SIMPLE_STRING_SETTER_GETTER(ReleaseGroup, Type, type);

Artist *
ReleaseGroup::getArtist()
{
	return d->artist;
}

void
ReleaseGroup::setArtist(Artist *value)
{
	if (d->artist)
		delete d->artist;
	d->artist = value;
}
