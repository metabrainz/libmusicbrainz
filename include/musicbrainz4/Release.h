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

#ifndef _MUSICBRAINZ4_RELEASE_H
#define _MUSICBRAINZ4_RELEASE_H

#include "musicbrainz4/Entity.h"
#include "musicbrainz4/LabelInfoList.h"
#include "musicbrainz4/RelationList.h"
#include "musicbrainz4/MediumList.h"
#include "musicbrainz4/CollectionList.h"

#include "musicbrainz4/xmlParser.h"

#include <string>
#include <iostream>

namespace MusicBrainz4
{
	class CReleasePrivate;

	class CTextRepresentation;
	class CArtistCredit;
	class CReleaseGroup;
	class CMedium;

	class CRelease: public CEntity
	{
	public:
		CRelease(const XMLNode& Node=XMLNode::emptyNode());
		CRelease(const CRelease& Other);
		CRelease& operator =(const CRelease& Other);
		virtual ~CRelease();

		virtual CRelease *Clone();

		std::string ID() const;
		std::string Title() const;
		std::string Status() const;
		std::string Quality() const;
		std::string Disambiguation() const;
		std::string Packaging() const;
		CTextRepresentation *TextRepresentation() const;
		CArtistCredit *ArtistCredit() const;
		CReleaseGroup *ReleaseGroup() const;
		std::string Date() const;
		std::string Country() const;
		std::string Barcode() const;
		std::string ASIN() const;
		CLabelInfoList *LabelInfoList() const;
		CMediumList *MediumList() const;

		/**
		 * Returns the <b>last</b> relation list for this release
		 *
		 * Returns the <b>last</b> relation list for this release. To return all
		 * relation lists, see MusicBrainz4::CRelease::RelationListList
		 *
		 * <b>This method is deprecated, please use MusicBrainz4::CRelease::RelationListList</b>
		 *
		 * @return The <b>last</b> relation list for this release
		 */

		CRelationList *RelationList() const LIBMB4_DEPRECATED;
		CRelationListList *RelationListList() const;
		CCollectionList *CollectionList() const;

		CMediumList MediaMatchingDiscID(const std::string& DiscID) const;

		virtual std::ostream& Serialise(std::ostream& os) const;
		static std::string GetElementName();

	protected:
		virtual bool ParseAttribute(const std::string& Name, const std::string& Value);
		virtual bool ParseElement(const XMLNode& Node);

	private:
		void Cleanup();

		CReleasePrivate * const m_d;
	};
}

#endif
