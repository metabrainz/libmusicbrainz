/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libmusicbrainz5 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include "config.h"
#include "musicbrainz5/defines.h"

#include "musicbrainz5/Release.h"

#include <string.h>

#include "musicbrainz5/TextRepresentation.h"
#include "musicbrainz5/ArtistCredit.h"
#include "musicbrainz5/ReleaseGroup.h"
#include "musicbrainz5/Medium.h"
#include "musicbrainz5/LabelInfoList.h"
#include "musicbrainz5/LabelInfo.h"
#include "musicbrainz5/RelationList.h"
#include "musicbrainz5/RelationListList.h"
#include "musicbrainz5/Relation.h"
#include "musicbrainz5/MediumList.h"
#include "musicbrainz5/Medium.h"
#include "musicbrainz5/Collection.h"
#include "musicbrainz5/CollectionList.h"

class MusicBrainz5::CReleasePrivate
{
	public:
		CReleasePrivate()
		:	m_TextRepresentation(0),
			m_ArtistCredit(0),
			m_ReleaseGroup(0),
			m_LabelInfoList(0),
			m_MediumList(0),
			m_RelationListList(0),
			m_CollectionList(0)
		{
		}

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
		CLabelInfoList *m_LabelInfoList;
		CMediumList *m_MediumList;
		CRelationListList *m_RelationListList;
		CCollectionList *m_CollectionList;
};

MusicBrainz5::CRelease::CRelease(const XMLNode& Node)
:	CEntity(),
	m_d(new CReleasePrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Release node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CRelease::CRelease(const CRelease& Other)
:	CEntity(),
	m_d(new CReleasePrivate)
{
	*this=Other;
}

MusicBrainz5::CRelease& MusicBrainz5::CRelease::operator =(const CRelease& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Title=Other.m_d->m_Title;
		m_d->m_Status=Other.m_d->m_Status;
		m_d->m_Quality=Other.m_d->m_Quality;
		m_d->m_Disambiguation=Other.m_d->m_Disambiguation;
		m_d->m_Packaging=Other.m_d->m_Packaging;

		if (Other.m_d->m_TextRepresentation)
			m_d->m_TextRepresentation=new CTextRepresentation(*Other.m_d->m_TextRepresentation);

		if (Other.m_d->m_ArtistCredit)
			m_d->m_ArtistCredit=new CArtistCredit(*Other.m_d->m_ArtistCredit);

		if (Other.m_d->m_ReleaseGroup)
			m_d->m_ReleaseGroup=new CReleaseGroup(*Other.m_d->m_ReleaseGroup);

		m_d->m_Date=Other.m_d->m_Date;
		m_d->m_Country=Other.m_d->m_Country;
		m_d->m_Barcode=Other.m_d->m_Barcode;
		m_d->m_ASIN=Other.m_d->m_ASIN;

		if (Other.m_d->m_LabelInfoList)
			m_d->m_LabelInfoList=new CLabelInfoList(*Other.m_d->m_LabelInfoList);

		if (Other.m_d->m_MediumList)
			m_d->m_MediumList=new CMediumList(*Other.m_d->m_MediumList);

		if (Other.m_d->m_RelationListList)
			m_d->m_RelationListList=new CRelationListList(*Other.m_d->m_RelationListList);

		if (Other.m_d->m_CollectionList)
			m_d->m_CollectionList=new CCollectionList(*Other.m_d->m_CollectionList);
	}

	return *this;
}

MusicBrainz5::CRelease::~CRelease()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CRelease::Cleanup()
{
	delete m_d->m_TextRepresentation;
	m_d->m_TextRepresentation=0;

	delete m_d->m_ArtistCredit;
	m_d->m_ArtistCredit=0;

	delete m_d->m_ReleaseGroup;
	m_d->m_ReleaseGroup=0;

	delete m_d->m_LabelInfoList;
	m_d->m_LabelInfoList=0;

	delete m_d->m_MediumList;
	m_d->m_MediumList=0;

	delete m_d->m_RelationListList;
	m_d->m_RelationListList=0;
}

MusicBrainz5::CRelease *MusicBrainz5::CRelease::Clone()
{
	return new CRelease(*this);
}

bool MusicBrainz5::CRelease::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("id"==Name)
		m_d->m_ID=Value;
	else
	{
		std::cerr << "Unrecognised release attribute: '" << Name << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

bool MusicBrainz5::CRelease::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("title"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Title);
	}
	else if ("status"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Status);
	}
	else if ("quality"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Quality);
	}
	else if ("disambiguation"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Disambiguation);
	}
	else if ("packaging"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Packaging);
	}
	else if ("text-representation"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_TextRepresentation);
	}
	else if ("artist-credit"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ArtistCredit);
	}
	else if ("release-group"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ReleaseGroup);
	}
	else if ("date"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Date);
	}
	else if ("country"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Country);
	}
	else if ("barcode"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Barcode);
	}
	else if ("asin"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ASIN);
	}
	else if ("label-info-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_LabelInfoList);
	}
	else if ("medium-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_MediumList);
	}
	else if ("relation-list"==NodeName)
	{
		RetVal=ProcessRelationList(Node,m_d->m_RelationListList);
	}
	else if ("collection-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_CollectionList);
	}
	else
	{
		std::cerr << "Unrecognised release element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz5::CRelease::GetElementName()
{
	return "release";
}

std::string MusicBrainz5::CRelease::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz5::CRelease::Title() const
{
	return m_d->m_Title;
}

std::string MusicBrainz5::CRelease::Status() const
{
	return m_d->m_Status;
}

std::string MusicBrainz5::CRelease::Quality() const
{
	return m_d->m_Quality;
}

std::string MusicBrainz5::CRelease::Disambiguation() const
{
	return m_d->m_Disambiguation;
}

std::string MusicBrainz5::CRelease::Packaging() const
{
	return m_d->m_Packaging;
}

MusicBrainz5::CTextRepresentation *MusicBrainz5::CRelease::TextRepresentation() const
{
	return m_d->m_TextRepresentation;
}

MusicBrainz5::CArtistCredit *MusicBrainz5::CRelease::ArtistCredit() const
{
	return m_d->m_ArtistCredit;
}

MusicBrainz5::CReleaseGroup *MusicBrainz5::CRelease::ReleaseGroup() const
{
	return m_d->m_ReleaseGroup;
}

std::string MusicBrainz5::CRelease::Date() const
{
	return m_d->m_Date;
}

std::string MusicBrainz5::CRelease::Country() const
{
	return m_d->m_Country;
}

std::string MusicBrainz5::CRelease::Barcode() const
{
	return m_d->m_Barcode;
}

std::string MusicBrainz5::CRelease::ASIN() const
{
	return m_d->m_ASIN;
}

MusicBrainz5::CLabelInfoList *MusicBrainz5::CRelease::LabelInfoList() const
{
	return m_d->m_LabelInfoList;
}

MusicBrainz5::CMediumList *MusicBrainz5::CRelease::MediumList() const
{
	return m_d->m_MediumList;
}

MusicBrainz5::CRelationListList *MusicBrainz5::CRelease::RelationListList() const
{
	return m_d->m_RelationListList;
}

MusicBrainz5::CCollectionList *MusicBrainz5::CRelease::CollectionList() const
{
	return m_d->m_CollectionList;
}

MusicBrainz5::CMediumList MusicBrainz5::CRelease::MediaMatchingDiscID(const std::string& DiscID) const
{
	MusicBrainz5::CMediumList Ret;

	if (m_d->m_MediumList)
	{
		for (int count=0;count<m_d->m_MediumList->NumItems();count++)
		{
			MusicBrainz5::CMedium *Medium=m_d->m_MediumList->Item(count);

			if (Medium->ContainsDiscID(DiscID))
				Ret.AddItem(new MusicBrainz5::CMedium(*Medium));
		}
	}

	return Ret;
}

std::ostream& MusicBrainz5::CRelease::Serialise(std::ostream& os) const
{
	os << "Release:" << std::endl;

	CEntity::Serialise(os);

	os << "\tID:                  " << ID() << std::endl;
	os << "\tTitle:               " << Title() << std::endl;
	os << "\tStatus:              " << Status() << std::endl;
	os << "\tQuality:             " << Quality() << std::endl;
	os << "\tDisambiguation:      " << Disambiguation() << std::endl;
	os << "\tPackaging:           " << Packaging() << std::endl;

	if (TextRepresentation())
		os << *TextRepresentation();

	if (ArtistCredit())
		os << *ArtistCredit() << std::endl;

	if (ReleaseGroup())
		os << *ReleaseGroup() << std::endl;

	os << "\tDate:                " << Date() << std::endl;
	os << "\tCountry:             " << Country() << std::endl;
	os << "\tBarcode:             " << Barcode() << std::endl;
	os << "\tASIN:                " << ASIN() << std::endl;

	if (LabelInfoList())
		os << *LabelInfoList() << std::endl;

	if (MediumList())
		os << *MediumList() << std::endl;

	if (RelationListList())
		os << *RelationListList() << std::endl;

	if (CollectionList())
		os << *CollectionList() << std::endl;

	return os;
}
