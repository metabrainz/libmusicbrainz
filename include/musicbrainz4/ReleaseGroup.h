/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   libmusicbrainz4 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#ifndef _MUSICBRAINZ4_RELEASE_GROUP_H
#define _MUSICBRAINZ4_RELEASE_GROUP_H

#include <string>
#include <iostream>

#include "musicbrainz4/Entity.h"
#include "musicbrainz4/ReleaseList.h"
#include "musicbrainz4/RelationList.h"
#include "musicbrainz4/TagList.h"
#include "musicbrainz4/UserTagList.h"
#include "musicbrainz4/SecondaryTypeList.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CReleaseGroupPrivate;

	class CArtistCredit;
	class CRating;
	class CUserRating;
	class CSecondaryType;

	class CReleaseGroup: public CEntity
	{
	public:
		CReleaseGroup(const XMLNode& Node=XMLNode::emptyNode());
		CReleaseGroup(const CReleaseGroup& Other);
		CReleaseGroup& operator =(const CReleaseGroup& Other);
		virtual ~CReleaseGroup();

		virtual CReleaseGroup *Clone();

		std::string ID() const;

		/**
		 * @deprecated Returns the type for this release group
		 *
		 * Returns the type for this release group.
		 *
		 * <b>This method is deprecated, please use MusicBrainz4::CReleaseGroup::PrimaryType
		 * and MusicBrainz4::CReleaseGroup::SecondaryTypeList</b>
		 *
		 * @return The type for this release group
		 */

		LIBMB4_DEPRECATED(MusicBrainz4::CReleaseGroup::PrimaryType) std::string Type() const;
		std::string PrimaryType() const;
		std::string Title() const;
		std::string Disambiguation() const;
		std::string FirstReleaseDate() const;
		CArtistCredit *ArtistCredit() const;
		CReleaseList *ReleaseList() const;

		/**
		 * @deprecated Returns the <b>last</b> relation list for this release group
		 *
		 * Returns the <b>last</b> relation list for this release group. To return all
		 * relation lists, see MusicBrainz4::CReleaseGroup::RelationListList
		 *
		 * <b>This method is deprecated, please use MusicBrainz4::CReleaseGroup::RelationListList</b>
		 *
		 * @return The <b>last</b> relation list for this release group
		 */

		LIBMB4_DEPRECATED(MusicBrainz4::CReleaseGroup::RelationListList) CRelationList *RelationList() const;
		CRelationListList *RelationListList() const;
		CTagList *TagList() const;
		CUserTagList *UserTagList() const;
		CRating *Rating() const;
		CUserRating *UserRating() const;
		CSecondaryTypeList *SecondaryTypeList() const;

		virtual std::ostream& Serialise(std::ostream& os) const;
		static std::string GetElementName();

	protected:
		virtual void ParseAttribute(const std::string& Name, const std::string& Value);
		virtual void ParseElement(const XMLNode& Node);

	private:
		void Cleanup();

		CReleaseGroupPrivate * const m_d;
	};
}

#endif
