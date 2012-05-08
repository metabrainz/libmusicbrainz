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

#ifndef _MUSICBRAINZ4_WORK_H
#define _MUSICBRAINZ4_WORK_H

#include <string>

#include "musicbrainz4/Entity.h"
#include "musicbrainz4/AliasList.h"
#include "musicbrainz4/RelationList.h"
#include "musicbrainz4/TagList.h"
#include "musicbrainz4/UserTagList.h"
#include "musicbrainz4/ISWCList.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CWorkPrivate;

	class CArtistCredit;
	class CISWC;
	class CRating;
	class CUserRating;

	class CWork: public CEntity
	{
	public:
		CWork(const XMLNode& Node=XMLNode::emptyNode());
		CWork(const CWork& Other);
		CWork& operator =(const CWork& Other);
		virtual ~CWork();

		virtual CWork *Clone();

		std::string ID() const;
		std::string Type() const;
		std::string Title() const;
		CArtistCredit *ArtistCredit() const;

		/**
		 * @deprecated Returns the <b>first</b> ISWC for this work
		 *
		 * Returns the <b>first</b> ISWC for this work. To return all
		 * ISWCs, see MusicBrainz4::CWork::ISWCList
		 *
		 * <b>This method is deprecated, please use MusicBrainz4::CWork::ISWCList</b>
		 *
		 * @return The <b>first</b> ISWC for this work
		 */

		LIBMB4_DEPRECATED(MusicBrainz4::CWork::ISWCList) std::string ISWC() const;

		CISWCList *ISWCList() const;
		std::string Disambiguation() const;
		CAliasList *AliasList() const;

		/**
		 * @deprecated Returns the <b>last</b> relation list for this work
		 *
		 * Returns the <b>last</b> relation list for this work. To return all
		 * relation lists, see MusicBrainz4::CWork::RelationListList
		 *
		 * <b>This method is deprecated, please use MusicBrainz4::CWork::RelationListList</b>
		 *
		 * @return The <b>last</b> relation list for this work
		 */

		LIBMB4_DEPRECATED(MusicBrainz4::CWork::RelationListList) CRelationList *RelationList() const;
		CRelationListList *RelationListList() const;
		CTagList *TagList() const;
		CUserTagList *UserTagList() const;
		CRating *Rating() const;
		CUserRating *UserRating() const;
		std::string Language() const;

		virtual std::ostream& Serialise(std::ostream& os) const;
		static std::string GetElementName();

	protected:
		virtual bool ParseAttribute(const std::string& Name, const std::string& Value);
		virtual bool ParseElement(const XMLNode& Node);

	private:
		void Cleanup();

		CWorkPrivate * const m_d;
	};
}

#endif

