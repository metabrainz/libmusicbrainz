/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   libmusicbrainz5 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#ifndef _MUSICBRAINZ5_ARTIST_H
#define _MUSICBRAINZ5_ARTIST_H

#include <string>
#include <iostream>

#include "musicbrainz5/Entity.h"
#include "musicbrainz5/IPIList.h"
#include "musicbrainz5/ReleaseList.h"
#include "musicbrainz5/AliasList.h"
#include "musicbrainz5/RecordingList.h"
#include "musicbrainz5/ReleaseGroupList.h"
#include "musicbrainz5/LabelList.h"
#include "musicbrainz5/WorkList.h"
#include "musicbrainz5/RelationList.h"
#include "musicbrainz5/TagList.h"
#include "musicbrainz5/UserTagList.h"

#include "musicbrainz5/xmlParser.h"

namespace MusicBrainz5
{
	class CArtistPrivate;
	class CLifespan;
	class CRating;
	class CUserRating;

	class CArtist: public CEntity
	{
	public:
		CArtist(const XMLNode& Node=XMLNode::emptyNode());
		CArtist(const CArtist& Other);
		CArtist& operator =(const CArtist& Other);
		virtual ~CArtist();

		virtual CArtist *Clone();

		std::string ID() const;
		std::string Type() const;
		std::string Name() const;
		std::string SortName() const;
		std::string Gender() const;
		std::string Country() const;
		std::string Disambiguation() const;
		CIPIList *IPIList() const;
		CLifespan *Lifespan() const;
		CAliasList *AliasList() const;
		CRecordingList *RecordingList() const;
		CReleaseList *ReleaseList() const;
		CReleaseGroupList *ReleaseGroupList() const;
		CLabelList *LabelList() const;
		CWorkList *WorkList() const;
		CRelationListList *RelationListList() const;
		CTagList *TagList() const;
		CUserTagList *UserTagList() const;
		CRating *Rating() const;
		CUserRating *UserRating() const;

		virtual std::ostream& Serialise(std::ostream& os) const;
		static std::string GetElementName();

	protected:
		virtual void ParseAttribute(const std::string& Name, const std::string& Value);
		virtual void ParseElement(const XMLNode& Node);

	private:
		void Cleanup();

		CArtistPrivate * const m_d;
	};
}

#endif
