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

#ifndef _MUSICBRAINZ4_RELEASE_H
#define _MUSICBRAINZ4_RELEASE_H

#include "musicbrainz4/GenericList.h"

#include <string>
#include <iostream>

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CTextRepresentation;
	class CArtistCredit;
	class CReleaseGroup;
	class CLabelInfo;
	class CMedium;
	class CRelation;

	class CRelease
	{
	public:
		CRelease(const XMLNode& Node=XMLNode::emptyNode());
		CRelease(const CRelease& Other);
		CRelease& operator =(const CRelease& Other);
		~CRelease();

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
		CGenericList<CLabelInfo> *LabelInfoList() const;
		CGenericList<CMedium> *MediumList() const;
		CGenericList<CRelation> *RelationList() const;

		CGenericList<CMedium> MediaMatchingDiscID(const std::string& DiscID) const;

	private:
		void Cleanup();

		std::string m_ID;
		std::string m_Title;
		std::string m_Status;
		std::string m_Quality;
		std::string m_Disambiguation;
		std::string m_Packaging;
		CTextRepresentation *m_TextRepresentation;
		CArtistCredit *m_ArtistCredit;
		CReleaseGroup *m_ReleaseGroup;
		std::string m_Date;
		std::string m_Country;
		std::string m_Barcode;
		std::string m_ASIN;
		CGenericList<CLabelInfo> *m_LabelInfoList;
		CGenericList<CMedium> *m_MediumList;
		CGenericList<CRelation> *m_RelationList;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CRelease& Release);

#endif