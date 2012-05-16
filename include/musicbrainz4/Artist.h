/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libmusicbrainz4 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#ifndef _MUSICBRAINZ4_ARTIST_H
#define _MUSICBRAINZ4_ARTIST_H

#include <string>
#include <iostream>

#include "musicbrainz4/Entity.h"
#include "musicbrainz4/IPIList.h"
#include "musicbrainz4/ReleaseList.h"
#include "musicbrainz4/AliasList.h"
#include "musicbrainz4/RecordingList.h"
#include "musicbrainz4/ReleaseGroupList.h"
#include "musicbrainz4/LabelList.h"
#include "musicbrainz4/WorkList.h"
#include "musicbrainz4/RelationList.h"
#include "musicbrainz4/TagList.h"
#include "musicbrainz4/UserTagList.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
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

		/**
		 * @deprecated Returns one of the IPIs for this artist
		 *
		 * Returns one of the IPIs for this artist. To return all
		 * IPIs, see MusicBrainz4::CArtist::IPIList
		 *
		 * <b>This method is deprecated, please use MusicBrainz4::CArtist::IPIList</b>
		 *
		 * @return One of the IPIs for this artist
		 */

		LIBMB4_DEPRECATED(MusicBrainz4::CArtist::IPIList) std::string IPI() const;
		CIPIList *IPIList() const;
		CLifespan *Lifespan() const;
		CAliasList *AliasList() const;
		CRecordingList *RecordingList() const;
		CReleaseList *ReleaseList() const;
		CReleaseGroupList *ReleaseGroupList() const;
		CLabelList *LabelList() const;
		CWorkList *WorkList() const;

		/**
		 * @deprecated Returns the <b>last</b> relation list for this artist
		 *
		 * Returns the <b>last</b> relation list for this artist. To return all
		 * relation lists, see MusicBrainz4::CArtist::RelationListList
		 *
		 * <b>This method is deprecated, please use MusicBrainz4::CArtist::RelationListList</b>
		 *
		 * @return The <b>last</b> relation list for this artist
		 */

		LIBMB4_DEPRECATED(MusicBrainz4::CArtist::RelationListList) CRelationList *RelationList() const;
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
