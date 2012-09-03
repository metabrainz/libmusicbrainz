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

#ifndef _MUSICBRAINZ5_RELEASE_H
#define _MUSICBRAINZ5_RELEASE_H

#include "musicbrainz5/Entity.h"
#include "musicbrainz5/LabelInfoList.h"
#include "musicbrainz5/RelationList.h"
#include "musicbrainz5/MediumList.h"
#include "musicbrainz5/CollectionList.h"

#include "musicbrainz5/xmlParser.h"

#include <string>
#include <iostream>

namespace MusicBrainz5
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
		CRelationListList *RelationListList() const;
		CCollectionList *CollectionList() const;

		CMediumList MediaMatchingDiscID(const std::string& DiscID) const;

		virtual std::ostream& Serialise(std::ostream& os) const;
		static std::string GetElementName();

	protected:
		virtual void ParseAttribute(const std::string& Name, const std::string& Value);
		virtual void ParseElement(const XMLNode& Node);

	private:
		void Cleanup();

		CReleasePrivate * const m_d;
	};
}

#endif
