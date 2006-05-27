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
 
#ifndef __MUSICBRAINZ3_LISTS_H__
#define __MUSICBRAINZ3_LISTS_H__

#include <vector>

namespace MusicBrainz
{
	
	class Artist;
	class ArtistAlias;
	class ArtistResult;
	class Disc;
	class Relation;
	class Release;
	class ReleaseEvent;
	class ReleaseResult;
	class Track;
	class TrackResult;
	class User;
	
	typedef std::vector<Artist *> ArtistList;
	typedef std::vector<ArtistAlias *> ArtistAliasList;
	typedef std::vector<ArtistResult *> ArtistResultList;
	typedef std::vector<Disc *> DiscList;
	typedef std::vector<Relation *> RelationList;
	typedef std::vector<Release *> ReleaseList;
	typedef std::vector<ReleaseEvent *> ReleaseEventList;
	typedef std::vector<ReleaseResult *> ReleaseResultList;
	typedef std::vector<Track *> TrackList;
	typedef std::vector<TrackResult *> TrackResultList;
	typedef std::vector<User *> UserList;
	
}

#endif
