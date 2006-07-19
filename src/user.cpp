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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA	 02111-1307	 USA
 *
 * $Id$
 */
 
#include <string>
#include <musicbrainz3/user.h>

using namespace std;
using namespace MusicBrainz;

User::User()
{
}

string
User::getName() const
{
	return name;
}

void
User::setName(const string &value)
{
	name = value;
}

bool
User::getShowNag() const
{
	return showNag;
}

void
User::setShowNag(bool value)
{
	showNag = value;
}

const std::vector<std::string> &
User::getTypes() const
{
	return types;
}

void
User::addType(const string &type)
{
	types.push_back(type);
}

int
User::getNumTypes() const
{
	return types.size();
}

string 
User::getType(int i) const
{
	return types[i];
}

