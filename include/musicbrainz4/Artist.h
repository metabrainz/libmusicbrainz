/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

#ifndef _MUSICBRAINZ4_ARTIST_H
#define _MUSICBRAINZ4_ARTIST_H

#include <string>
#include <iostream>

#include "musicbrainz4/GenericList.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CArtistPrivate;
	class CLifespan;
	class CAlias;
	class CRecording;
	class CRelease;
	class CReleaseGroup;
	class CLabel;
	class CWork;
	class CRelation;
	class CTag;
	class CUserTag;
	class CRating;
	class CUserRating;

	class CArtist
	{
	public:
		CArtist(const XMLNode& Node=XMLNode::emptyNode());
		CArtist(const CArtist& Other);
		CArtist& operator =(const CArtist& Other);
		~CArtist();

		std::string ID() const;
		std::string Type() const;
		std::string Name() const;
		std::string SortName() const;
		std::string Gender() const;
		std::string Country() const;
		std::string Disambiguation() const;
		CLifespan *Lifespan() const;
		CGenericList<CAlias> *AliasList() const;
		CGenericList<CRecording> *RecordingList() const;
		CGenericList<CRelease> *ReleaseList() const;
		CGenericList<CReleaseGroup> *ReleaseGroupList() const;
		CGenericList<CLabel> *LabelList() const;
		CGenericList<CWork> *WorkList() const;
		CGenericList<CRelation> *RelationList() const;
		CGenericList<CTag> *TagList() const;
		CGenericList<CUserTag> *UserTagList() const;
		CRating *Rating() const;
		CUserRating *UserRating() const;

	private:
		void Cleanup();
		
		CArtistPrivate * const m_d;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CArtist& Artist);

#endif
