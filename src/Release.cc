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

#include "musicbrainz4/Release.h"

#include <string.h>

#include "musicbrainz4/TextRepresentation.h"
#include "musicbrainz4/ArtistCredit.h"
#include "musicbrainz4/ReleaseGroup.h"
#include "musicbrainz4/Medium.h"
#include "musicbrainz4/LabelInfo.h"
#include "musicbrainz4/Relation.h"

MusicBrainz4::CRelease::CRelease(const XMLNode& Node)
:	m_TextRepresentation(0),
	m_ArtistCredit(0),
	m_ReleaseGroup(0),
	m_LabelInfoList(0),
	m_MediumList(0),
	m_RelationList(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Release node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("id"))
			m_ID=Node.getAttribute("id");

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("title"==NodeName)
			{
				m_Title=NodeValue;
			}
			else if ("status"==NodeName)
			{
				m_Status=NodeValue;
			}
			else if ("quality"==NodeName)
			{
				m_Quality=NodeValue;
			}
			else if ("disambiguation"==NodeName)
			{
				m_Disambiguation=NodeValue;
			}
			else if ("packaging"==NodeName)
			{
				m_Packaging=NodeValue;
			}
			else if ("text-representation"==NodeName)
			{
				m_TextRepresentation=new CTextRepresentation(ChildNode);
			}
			else if ("artist-credit"==NodeName)
			{
				m_ArtistCredit=new CArtistCredit(ChildNode);
			}
			else if ("release-group"==NodeName)
			{
				m_ReleaseGroup=new CReleaseGroup(ChildNode);
			}

			else if ("date"==NodeName)
			{
				m_Date=NodeValue;
			}
			else if ("country"==NodeName)
			{
				m_Country=NodeValue;
			}
			else if ("barcode"==NodeName)
			{
				m_Barcode=NodeValue;
			}
			else if ("asin"==NodeName)
			{
				m_ASIN=NodeValue;
			}
			else if ("label-info-list"==NodeName)
			{
				m_LabelInfoList=new CGenericList<CLabelInfo>(ChildNode,"label-info");
			}
			else if ("medium-list"==NodeName)
			{
				m_MediumList=new CGenericList<CMedium>(ChildNode,"medium");
			}
			else if ("relation-list"==NodeName)
			{
				m_RelationList=new CGenericList<CRelation>(ChildNode,"relation");
			}
			else
			{
				std::cerr << "Unrecognised release node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CRelease::CRelease(const CRelease& Other)
:	m_TextRepresentation(0),
	m_ArtistCredit(0),
	m_ReleaseGroup(0),
	m_LabelInfoList(0),
	m_MediumList(0),
	m_RelationList(0)
{
	*this=Other;
}

MusicBrainz4::CRelease& MusicBrainz4::CRelease::operator =(const CRelease& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_ID=Other.m_ID;
		m_Title=Other.m_Title;
		m_Status=Other.m_Status;
		m_Quality=Other.m_Quality;
		m_Disambiguation=Other.m_Disambiguation;
		m_Packaging=Other.m_Packaging;

		if (Other.m_TextRepresentation)
			m_TextRepresentation=new CTextRepresentation(*Other.m_TextRepresentation);

		if (Other.m_ArtistCredit)
			m_ArtistCredit=new CArtistCredit(*Other.m_ArtistCredit);

		if (Other.m_ReleaseGroup)
			m_ReleaseGroup=new CReleaseGroup(*Other.m_ReleaseGroup);

		m_Date=Other.m_Date;
		m_Country=Other.m_Country;
		m_Barcode=Other.m_Barcode;
		m_ASIN=Other.m_ASIN;

		if (Other.m_LabelInfoList)
			m_LabelInfoList=new CGenericList<CLabelInfo>(*Other.m_LabelInfoList);

		if (Other.m_MediumList)
			m_MediumList=new CGenericList<CMedium>(*Other.m_MediumList);

		if (Other.m_RelationList)
			m_RelationList=new CGenericList<CRelation>(*Other.m_RelationList);
	}

	return *this;
}

MusicBrainz4::CRelease::~CRelease()
{
	Cleanup();
}

void MusicBrainz4::CRelease::Cleanup()
{
	delete m_TextRepresentation;
	m_TextRepresentation=0;

	delete m_ArtistCredit;
	m_ArtistCredit=0;

	delete m_ReleaseGroup;
	m_ReleaseGroup=0;

	delete m_LabelInfoList;
	m_LabelInfoList=0;

	delete m_MediumList;
	m_MediumList=0;

	delete m_RelationList;
	m_RelationList=0;
}

std::string MusicBrainz4::CRelease::ID() const
{
	return m_ID;
}

std::string MusicBrainz4::CRelease::Title() const
{
	return m_Title;
}

std::string MusicBrainz4::CRelease::Status() const
{
	return m_Status;
}

std::string MusicBrainz4::CRelease::Quality() const
{
	return m_Quality;
}

std::string MusicBrainz4::CRelease::Disambiguation() const
{
	return m_Disambiguation;
}

std::string MusicBrainz4::CRelease::Packaging() const
{
	return m_Packaging;
}

MusicBrainz4::CTextRepresentation *MusicBrainz4::CRelease::TextRepresentation() const
{
	return m_TextRepresentation;
}

MusicBrainz4::CArtistCredit *MusicBrainz4::CRelease::ArtistCredit() const
{
	return m_ArtistCredit;
}

MusicBrainz4::CReleaseGroup *MusicBrainz4::CRelease::ReleaseGroup() const
{
	return m_ReleaseGroup;
}

std::string MusicBrainz4::CRelease::Date() const
{
	return m_Date;
}

std::string MusicBrainz4::CRelease::Country() const
{
	return m_Country;
}

std::string MusicBrainz4::CRelease::Barcode() const
{
	return m_Barcode;
}

std::string MusicBrainz4::CRelease::ASIN() const
{
	return m_ASIN;
}

MusicBrainz4::CGenericList<MusicBrainz4::CLabelInfo> *MusicBrainz4::CRelease::LabelInfoList() const
{
	return m_LabelInfoList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CMedium> *MusicBrainz4::CRelease::MediumList() const
{
	return m_MediumList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRelation> *MusicBrainz4::CRelease::RelationList() const
{
	return m_RelationList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CMedium> MusicBrainz4::CRelease::MediaMatchingDiscID(const std::string& DiscID) const
{
	CGenericList<MusicBrainz4::CMedium> Ret;

	std::list<MusicBrainz4::CMedium> Media=m_MediumList->Items();
	std::list<MusicBrainz4::CMedium>::const_iterator ThisMedium=Media.begin();
	while (ThisMedium!=Media.end())
	{
		MusicBrainz4::CMedium Medium=(*ThisMedium);

		if (Medium.ContainsDiscID(DiscID))
			Ret.push_back(Medium);

		++ThisMedium;
	}

	return Ret;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CRelease& Release)
{
	os << "Release:" << std::endl;

	os << "\tID:                  " << Release.ID() << std::endl;
	os << "\tTitle:               " << Release.Title() << std::endl;
	os << "\tStatus:              " << Release.Status() << std::endl;
	os << "\tQuality:             " << Release.Quality() << std::endl;
	os << "\tDisambiguation:      " << Release.Disambiguation() << std::endl;
	os << "\tPackaging:           " << Release.Packaging() << std::endl;

	if (Release.TextRepresentation())
		os << *Release.TextRepresentation();

	if (Release.ArtistCredit())
		os << *Release.ArtistCredit() << std::endl;

	if (Release.ReleaseGroup())
		os << *Release.ReleaseGroup() << std::endl;

	os << "\tDate:                " << Release.Date() << std::endl;
	os << "\tCountry:             " << Release.Country() << std::endl;
	os << "\tBarcode:             " << Release.Barcode() << std::endl;
	os << "\tASIN:                " << Release.ASIN() << std::endl;

	if (Release.LabelInfoList())
		os << *Release.LabelInfoList() << std::endl;

	if (Release.MediumList())
		os << *Release.MediumList() << std::endl;

	if (Release.RelationList())
		os << *Release.RelationList() << std::endl;

	return os;
}
