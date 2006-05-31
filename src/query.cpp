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
#include <iostream>
#include <musicbrainz3/utils.h>
#include <musicbrainz3/query.h>
#include <musicbrainz3/mbxmlparser.h>

using namespace std;
using namespace MusicBrainz;

Query::Query(IWebService *ws_, const string &clientId)
	: ws(ws_), own_ws(false), clientId(clientId) 
{
	if (!ws) {
		ws = new WebService();
		own_ws = true;
	}
}

Query::~Query()
{
	if (own_ws && ws)
		delete ws;
}

Artist *
Query::getArtistById(const string &id,
					 const ArtistIncludes *include)
{
	string uuid = extractUuid(id);
	Metadata *metadata = getFromWebService("artist", uuid, include); 
	Artist *artist = metadata->getArtist(true);
	delete metadata;
	return artist;
}

Release *
Query::getReleaseById(const string &id,
					 const ReleaseIncludes *include)
{
	string uuid = extractUuid(id);
	Metadata *metadata = getFromWebService("release", uuid, include); 
	Release *release = metadata->getRelease(true);
	delete metadata;
	return release;
}

Track *
Query::getTrackById(const string &id,
					 const TrackIncludes *include)
{
	string uuid = extractUuid(id);
	Metadata *metadata = getFromWebService("track", uuid, include); 
	Track *track = metadata->getTrack(true);
	delete metadata;
	return track;
}

User *
Query::getUserByName(const string &name)
{
	Metadata *metadata = getFromWebService("user", "", NULL, &UserFilter().name(name));
	UserList list = metadata->getUserList(true);
	delete metadata;
	if (list.size() > 0) 
		return list[0];
	else
		throw ResponseError("response didn't contain user data");
}

ArtistResultList 
Query::getArtists(const ArtistFilter *filter)
{
	Metadata *metadata = getFromWebService("artist", "", NULL, filter);
	ArtistResultList list = metadata->getArtistResults(true);
	delete metadata;
	return list;
}

ReleaseResultList 
Query::getReleases(const ReleaseFilter *filter)
{
	Metadata *metadata = getFromWebService("release", "", NULL, filter);
	ReleaseResultList list = metadata->getReleaseResults(true);
	delete metadata;
	return list;
}

TrackResultList 
Query::getTracks(const TrackFilter *filter)
{
	Metadata *metadata = getFromWebService("track", "", NULL, filter);
	TrackResultList list = metadata->getTrackResults(true);
	delete metadata;
	return list;
}

Metadata *
Query::getFromWebService(const string &entity,
						 const string &id,
						 const IIncludes *include,
						 const IFilter *filter)
{
	const IIncludes::IncludeList includeParams(include ? include->createIncludeTags() : IIncludes::IncludeList());
	const IFilter::ParameterList filterParams(filter ? filter->createParameters() : IFilter::ParameterList());
	string content = ws->get(entity, id, includeParams, filterParams);
	try {
		MbXmlParser parser;
		return parser.parse(content);
	}
	catch (ParseError &e) {
		throw ResponseError(e.what());
	}
}

