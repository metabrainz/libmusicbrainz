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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * $Id$
 */
 
#include <string>
#include <musicbrainz3/releaseevent.h>
#include "utils_private.h"

using namespace std;
using namespace MusicBrainz;

class ReleaseEvent::ReleaseEventPrivate
{
public:
	ReleaseEventPrivate()
		{}
		
	string country;
	string dateStr;
	string catalogNumber;
	string barcode;
};

ReleaseEvent::ReleaseEvent(const string &country, const string &dateStr)
{
	d = new ReleaseEventPrivate();
	
	d->country = country;
	d->dateStr = dateStr;
}

ReleaseEvent::~ReleaseEvent()
{
	delete d;
}

SIMPLE_STRING_SETTER_GETTER(ReleaseEvent, Country, country);
SIMPLE_STRING_SETTER_GETTER(ReleaseEvent, CatalogNumber, catalogNumber);
SIMPLE_STRING_SETTER_GETTER(ReleaseEvent, Barcode, barcode);
SIMPLE_STRING_SETTER_GETTER(ReleaseEvent, Date, dateStr);
