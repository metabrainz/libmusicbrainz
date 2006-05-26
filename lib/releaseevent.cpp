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
 
#include <string>
#include <musicbrainz3/releaseevent.h>

using namespace std;
using namespace MusicBrainz;

ReleaseEvent::ReleaseEvent(const string &country, const string &dateStr)
    : country(country), dateStr(dateStr)
{
}

string
ReleaseEvent::getCountry() const
{
    return country;
}

void
ReleaseEvent::setCountry(const string &value)
{
    country = value;
}

string
ReleaseEvent::getDate() const
{
    return dateStr;
}

void
ReleaseEvent::setDate(const string &value)
{
    dateStr = value;
}

