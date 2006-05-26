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
 
// TODO: support for namespaces and full MMD 
 
#include <string>
#include <iostream>
#include <string.h>
#include <musicbrainz3/mbxmlparser.h>
#include "xmlParser/xmlParser.h"

using namespace std;
using namespace MusicBrainz;

static bool
getBoolAttribute(XMLNode node, string name)
{
	const char *value = node.getAttribute(name.c_str());
	return value ? value == "true" : false;
}

static int
getIntAttribute(XMLNode node, string name, int def = 0)
{
	const char *value = node.getAttribute(name.c_str());
	return value ? atoi(value) : def;
}

static string
getTextAttribute(XMLNode node, string name, string def = "")
{
	const char *value = node.getAttribute(name.c_str());
	return value ? string(value) : string(def);
}

static string
getText(XMLNode node)
{
	string text;
	for (int i = 0; i < node.nText(); i++) 
		text += node.getText(i);
	return text;
} 

static int
getInt(XMLNode node, int def = 0)
{
	string text = getText(node);
	return text.empty() ? def : atoi(text.c_str());
} 

static void addArtistsToList(XMLNode listNode, ArtistList &resultList);
static void addDiscsToList(XMLNode listNode, DiscList &resultList);
static void addReleasesToList(XMLNode listNode, ReleaseList &resultList);
static void addReleaseEventsToList(XMLNode listNode, ReleaseEventList &resultList);
static void addTracksToList(XMLNode listNode, TrackList &resultList);

static Artist *
createArtist(XMLNode artistNode)
{
	Artist *artist = new Artist(getTextAttribute(artistNode, "id"));
	string type = getTextAttribute(artistNode, "type");
	if (!type.empty()) 
		artist->setType(NS_MMD_1 + type);
	for (int i = 0; i < artistNode.nChildNode(); i++) {
		XMLNode node = artistNode.getChildNode(i);
		string name = node.getName(); 
		if (name == "name") {
			artist->setName(getText(node));
		}
		else if (name == "sort-name") {
			artist->setSortName(getText(node));
		}
		else if (name == "disambiguation") {
			artist->setDisambiguation(getText(node));
		}
		else if (name == "life-span") {
			const char *begin = node.getAttribute("begin");
			const char *end = node.getAttribute("end");
			if (begin)
				artist->setBeginDate(string(begin));
			if (end)
				artist->setEndDate(string(end));
		}
	}
	return artist; 
}

static Release *
createRelease(XMLNode releaseNode)
{
	Release *release = new Release(getTextAttribute(releaseNode, "id"));
	for (int i = 0; i < releaseNode.nChildNode(); i++) {
		XMLNode node = releaseNode.getChildNode(i);
		string name = node.getName(); 
		if (name == "title") {
			release->setTitle(getText(node));
		}
		else if (name == "text-representation") {
			release->setTextLanguage(getTextAttribute(node, "language"));
			release->setTextScript(getTextAttribute(node, "script"));
		}
		else if (name == "asin") {
			release->setAsin(getText(node));
		}
		else if (name == "artist") {
			release->setArtist(createArtist(node));
		}
		else if (name == "release-event-list") {
			addReleaseEventsToList(node, release->getReleaseEvents());
		}
		else if (name == "disc-list") {
			addDiscsToList(node, release->getDiscs());
		}
		else if (name == "track-list") {
			release->setTracksOffset(getIntAttribute(node, "offset"));
			addTracksToList(node, release->getTracks());
		}
/*		else if (name == "relation-list") {
			release->setTitle(getText(node));
		}*/
	}
	return release;
}

static Track *
createTrack(XMLNode trackNode)
{
	string id = trackNode.getAttribute("id");
	Track *track = new Track(id);
	for (int i = 0; i < trackNode.nChildNode(); i++) {
		XMLNode node = trackNode.getChildNode(i);
		string name = node.getName(); 
		if (name == "title") {
			track->setTitle(getText(node));
		}
		else if (name == "artist") {
			track->setArtist(createArtist(node));
		}
		else if (name == "duration") {
			track->setDuration(getInt(node));
		}
	}
	return track;
}

static User *
createUser(XMLNode userNode)
{
	User *user = new User();
	for (int i = 0; i < userNode.nChildNode(); i++) {
		XMLNode node = userNode.getChildNode(i);
		string name = node.getName();
		if (name == "name") { 
			user->setName(getText(node));
		}
		else if (name == "ext:nag") {
			user->setShowNag(getBoolAttribute(node, "show"));
		}
	}
	return user;
}

static Disc *
createDisc(XMLNode discNode)
{
	Disc *disc = new Disc(getTextAttribute(discNode, "id"));
	return disc;
}

static ReleaseEvent *
createReleaseEvent(XMLNode releaseEventNode)
{
	ReleaseEvent *releaseEvent = 
		new ReleaseEvent(getTextAttribute(releaseEventNode, "country"),
						 getTextAttribute(releaseEventNode, "date"));
	return releaseEvent;
}

static void
addArtistResults(XMLNode listNode, ArtistResultList &resultList)
{
}

static void
addReleaseResults(XMLNode listNode, ReleaseResultList &resultList)
{
}

static void
addTrackResults(XMLNode listNode, TrackResultList &resultList)
{
}

template<typename T, typename TL>
static void
addToList(XMLNode listNode, TL &resultList, T *(*creator)(XMLNode))
{
	for (int i = 0; i < listNode.nChildNode(); i++) {
		XMLNode node = listNode.getChildNode(i);
		resultList.push_back(creator(node));
	}
}

static void
addArtistsToList(XMLNode listNode, ArtistList &resultList)
{
	addToList<Artist, ArtistList>(listNode, resultList, &createArtist);
}

static void
addDiscsToList(XMLNode listNode, DiscList &resultList)
{
	addToList<Disc, DiscList>(listNode, resultList, &createDisc);
}

static void
addReleasesToList(XMLNode listNode, ReleaseList &resultList)
{
	addToList<Release, ReleaseList>(listNode, resultList, &createRelease);
}

static void
addReleaseEventsToList(XMLNode listNode, ReleaseEventList &resultList)
{
	addToList<ReleaseEvent, ReleaseEventList>(listNode, resultList, &createReleaseEvent);
}

static void
addTracksToList(XMLNode listNode, TrackList &resultList)
{
	addToList<Track, TrackList>(listNode, resultList, &createTrack);
}

static void
addUsersToList(XMLNode listNode, UserList &resultList)
{
	addToList<User, UserList>(listNode, resultList, &createUser);
}

MbXmlParser::MbXmlParser()
{
}

Metadata *
MbXmlParser::parse(const std::string &data)
{
	XMLNode root = XMLNode::parseString(data.c_str(), "metadata");
	
	if (root.isEmpty() || root.getName() != string("metadata")) {
		throw ParseError();
	}
	
	Metadata *md = new Metadata();
	try {
		for (int i = 0; i < root.nChildNode(); i++) {
			XMLNode node = root.getChildNode(i);
			string name = node.getName(); 
			if (name == string("artist")) {
				md->setArtist(createArtist(node));
			}
			else if (name == string("track")) {
				md->setTrack(createTrack(node));
			}
			else if (name == string("release")) {
				md->setRelease(createRelease(node));
			}
			else if (name == string("artist-list")) {
				addArtistResults(node, md->getArtistResults());
			}
			else if (name == string("track-list")) {
				addTrackResults(node, md->getTrackResults());
			}
			else if (name == string("release-list")) {
				addReleaseResults(node, md->getReleaseResults());
			}
			else if (name == string("ext:user-list")) {
				addUsersToList(node, md->getUserList());
			}
		}
	}
	catch (...) {
		delete md;
		throw ParseError();
	}
	
	return md;
}


