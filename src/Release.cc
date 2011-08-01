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

#include "musicbrainz4/Release.h"

#include <string.h>

#include "musicbrainz4/TextRepresentation.h"
#include "musicbrainz4/ArtistCredit.h"
#include "musicbrainz4/ReleaseGroup.h"
#include "musicbrainz4/Medium.h"
#include "musicbrainz4/LabelInfoList.h"
#include "musicbrainz4/RelationList.h"
#include "musicbrainz4/MediumList.h"

class MusicBrainz4::CReleasePrivate
{
	public:
		CReleasePrivate()
		:	m_TextRepresentation(0),
			m_ArtistCredit(0),
			m_ReleaseGroup(0),
			m_LabelInfoList(0),
			m_MediumList(0),
			m_RelationList(0)
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
		CRelationList *m_RelationList;
};

MusicBrainz4::CRelease::CRelease(const XMLNode& Node)
:	CEntity(),
	m_d(new CReleasePrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Release node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CRelease::CRelease(const CRelease& Other)
:	CEntity(),
	m_d(new CReleasePrivate)
{
	*this=Other;
}

MusicBrainz4::CRelease& MusicBrainz4::CRelease::operator =(const CRelease& Other)
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

		if (Other.m_d->m_RelationList)
			m_d->m_RelationList=new CRelationList(*Other.m_d->m_RelationList);
	}

	return *this;
}

MusicBrainz4::CRelease::~CRelease()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz4::CRelease::Cleanup()
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

	delete m_d->m_RelationList;
	m_d->m_RelationList=0;
}

MusicBrainz4::CRelease *MusicBrainz4::CRelease::Clone()
{
	return new CRelease(*this);
}

bool MusicBrainz4::CRelease::ParseAttribute(const std::string& Name, const std::string& Value)
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

bool MusicBrainz4::CRelease::ParseElement(const XMLNode& Node)
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
		RetVal=ProcessItem(Node,m_d->m_RelationList);
	}
	else
	{
		std::cerr << "Unrecognised release element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz4::CRelease::GetElementName()
{
	return "release";
}

std::string MusicBrainz4::CRelease::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz4::CRelease::Title() const
{
	return m_d->m_Title;
}

std::string MusicBrainz4::CRelease::Status() const
{
	return m_d->m_Status;
}

std::string MusicBrainz4::CRelease::Quality() const
{
	return m_d->m_Quality;
}

std::string MusicBrainz4::CRelease::Disambiguation() const
{
	return m_d->m_Disambiguation;
}

std::string MusicBrainz4::CRelease::Packaging() const
{
	return m_d->m_Packaging;
}

MusicBrainz4::CTextRepresentation *MusicBrainz4::CRelease::TextRepresentation() const
{
	return m_d->m_TextRepresentation;
}

MusicBrainz4::CArtistCredit *MusicBrainz4::CRelease::ArtistCredit() const
{
	return m_d->m_ArtistCredit;
}

MusicBrainz4::CReleaseGroup *MusicBrainz4::CRelease::ReleaseGroup() const
{
	return m_d->m_ReleaseGroup;
}

std::string MusicBrainz4::CRelease::Date() const
{
	return m_d->m_Date;
}

std::string MusicBrainz4::CRelease::Country() const
{
	return m_d->m_Country;
}

std::string MusicBrainz4::CRelease::Barcode() const
{
	return m_d->m_Barcode;
}

std::string MusicBrainz4::CRelease::ASIN() const
{
	return m_d->m_ASIN;
}

MusicBrainz4::CLabelInfoList *MusicBrainz4::CRelease::LabelInfoList() const
{
	return m_d->m_LabelInfoList;
}

MusicBrainz4::CMediumList *MusicBrainz4::CRelease::MediumList() const
{
	return m_d->m_MediumList;
}

MusicBrainz4::CRelationList *MusicBrainz4::CRelease::RelationList() const
{
	return m_d->m_RelationList;
}

MusicBrainz4::CMediumList MusicBrainz4::CRelease::MediaMatchingDiscID(const std::string& DiscID) const
{
	MusicBrainz4::CMediumList Ret;

	if (m_d->m_MediumList)
	{
		for (int count=0;count<m_d->m_MediumList->NumItems();count++)
		{
			MusicBrainz4::CMedium *Medium=m_d->m_MediumList->Item(count);

			if (Medium->ContainsDiscID(DiscID))
				Ret.AddItem(new MusicBrainz4::CMedium(*Medium));
		}
	}

	return Ret;
}

std::ostream& MusicBrainz4::CRelease::Serialise(std::ostream& os) const
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

	if (RelationList())
		os << *RelationList() << std::endl;

	return os;
}
