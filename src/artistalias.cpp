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
 */
 
#include <musicbrainz3/artistalias.h>

using namespace std;
using namespace MusicBrainz;

ArtistAlias::ArtistAlias(const string &value, const string &type, const string &script)
	: value(value), type(type), script(script)
{
}

string
ArtistAlias::getType() const
{
	return type;
}

void
ArtistAlias::setType(const string &value)
{
	type = value;
}

string
ArtistAlias::getValue() const
{
	return value;
}

void
ArtistAlias::setValue(const string &value_)
{
	value = value_;
}

string
ArtistAlias::getScript() const
{
	return script;
}

void
ArtistAlias::setScript(const string &value)
{
	script = value;
}

