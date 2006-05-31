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

const string Artist::TYPE_PERSON = NS_MMD_1 + "Person"; 
const string Artist::TYPE_GROUP = NS_MMD_1 + "Group"; 

Artist::Artist(const string &id, const string &type, const string &name, const string &sortName)
    : Entity(id)
{
    setType(type);
    setName(name);
    setSortName(sortName);
}

Artist::~Artist()
{
	for (ReleaseList::iterator i = releases.begin(); i != releases.end(); i++) 
		delete *i;
	releases.clear();
 	
	for (ArtistAliasList::iterator i = aliases.begin(); i != aliases.end(); i++) 
		delete *i;
	aliases.clear(); 	
}

string
Artist::getType() const
{
    return type;
}

void
Artist::setType(const string &value)
{
    type = value;
}

string
Artist::getName() const
{
    return name;
}

void
Artist::setName(const string &value)
{
    name = value;
}

string
Artist::getSortName() const
{
    return sortName;
}

void
Artist::setSortName(const string &value)
{
    sortName = value;
}

string
Artist::getDisambiguation() const
{
    return disambiguation;
}

void
Artist::setDisambiguation(const string &value)
{
    disambiguation = value;
}

string
Artist::getBeginDate() const
{
    return beginDate;
}

void
Artist::setBeginDate(const string &value)
{
    beginDate = value;
}

string
Artist::getEndDate() const
{
    return endDate;
}

void
Artist::setEndDate(const string &value)
{
    endDate = value;
} 

ReleaseList &
Artist::getReleases()
{
    return releases;
}

void
Artist::addRelease(Release *release)
{
    releases.push_back(release);
}

ArtistAliasList &
Artist::getAliases()
{
    return aliases;
}

void
Artist::addAlias(ArtistAlias *alias)
{
    aliases.push_back(alias);
}

