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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifdef HAVE_DISCID
#include <discid/discid.h>
#endif
#include <musicbrainz3/disc.h>
#include "utilspriv.h"

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

Disc::TrackList &
Disc::getTracks()
{
    return tracks;
}

void
Disc::addTrack(Disc::Track track)
{
    tracks.push_back(track);
}

Disc *
MusicBrainz::readDisc(const std::string &deviceName)
{
#ifdef HAVE_DISCID
	DiscId *discid = discid_new();
	if (!discid) {
		throw DiscError("Couldn't create a new DiscId instance.");
	}
	
	if (!discid_read(discid, deviceName.empty() ? NULL : deviceName.c_str())) {
		string msg(discid_get_error_msg(discid));
		discid_free(discid);
		throw DiscError(msg);
	}
	
	Disc *disc = new Disc;
	disc->setId(discid_get_id(discid));
	disc->setSectors(discid_get_sectors(discid));
	disc->setFirstTrackNum(discid_get_first_track_num(discid));
	disc->setLastTrackNum(discid_get_last_track_num(discid));
	for (int i = disc->getFirstTrackNum(); i <= disc->getLastTrackNum(); i++) {
		disc->addTrack(Disc::Track(discid_get_track_offset(discid, i),
								   discid_get_track_length(discid, i)));
	}
	
	discid_free(discid);
	return disc;
#else
	throw DiscError("libdiscid is not available.");
#endif
}

std::string
MusicBrainz::getSubmissionUrl(Disc *disc, const std::string &host, int port)
{
	string netloc;
	if (port == 80) 
		netloc = host;
	else
		netloc = host + ":" + intToString(port);
	
	string toc = intToString(disc->getFirstTrackNum())
		+ "+" + intToString(disc->getLastTrackNum())
		+ "+" + intToString(disc->getSectors());
		
	for (Disc::TrackList::const_iterator i = disc->getTracks().begin();
			i < disc->getTracks().end(); i++) {
		toc += "+" + intToString(i->first);
	}
	
	return "http://" + netloc + "/bare/cdlookup.html?id=" + disc->getId()
		+ "&toc=" + toc + "&tracks=" + intToString(disc->getLastTrackNum());
}

