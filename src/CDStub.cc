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

#include "musicbrainz4/CDStub.h"

#include "musicbrainz4/NonMBTrackList.h"
#include "musicbrainz4/NonMBTrack.h"

class MusicBrainz4::CCDStubPrivate
{
	public:
		CCDStubPrivate()
		:	m_NonMBTrackList(0)
		{
		}

		std::string m_ID;
		std::string m_Title;
		std::string m_Artist;
		std::string m_Barcode;
		std::string m_Comment;
		CNonMBTrackList *m_NonMBTrackList;
};

MusicBrainz4::CCDStub::CCDStub(const XMLNode& Node)
:	CEntity(),
	m_d(new CCDStubPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "CDStub node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CCDStub::CCDStub(const CCDStub& Other)
:	CEntity(),
	m_d(new CCDStubPrivate)
{
	*this=Other;
}

MusicBrainz4::CCDStub& MusicBrainz4::CCDStub::operator =(const CCDStub& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Title=Other.m_d->m_Title;
		m_d->m_Artist=Other.m_d->m_Artist;
		m_d->m_Barcode=Other.m_d->m_Barcode;
		m_d->m_Comment=Other.m_d->m_Comment;

		if (Other.m_d->m_NonMBTrackList)
			m_d->m_NonMBTrackList=new CNonMBTrackList(*Other.m_d->m_NonMBTrackList);
	}

	return *this;
}

MusicBrainz4::CCDStub::~CCDStub()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz4::CCDStub::Cleanup()
{
	delete m_d->m_NonMBTrackList;
	m_d->m_NonMBTrackList=0;
}

MusicBrainz4::CCDStub *MusicBrainz4::CCDStub::Clone()
{
	return new CCDStub(*this);
}

bool MusicBrainz4::CCDStub::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("id"==Name)
		m_d->m_ID=Value;
	else
	{
		std::cerr << "Unrecognised cdstub attribute: '" << Name << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

bool MusicBrainz4::CCDStub::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("title"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Title);
	}
	else if ("artist"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Artist);
	}
	else if ("barcode"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Barcode);
	}
	else if ("comment"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Comment);
	}
	else if ("track-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_NonMBTrackList);
	}
	else
	{
		std::cerr << "Unrecognised cd stub element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz4::CCDStub::GetElementName()
{
	return "cdstub";
}

std::string MusicBrainz4::CCDStub::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz4::CCDStub::Title() const
{
	return m_d->m_Title;
}

std::string MusicBrainz4::CCDStub::Artist() const
{
	return m_d->m_Artist;
}

std::string MusicBrainz4::CCDStub::Barcode() const
{
	return m_d->m_Barcode;
}

std::string MusicBrainz4::CCDStub::Comment() const
{
	return m_d->m_Comment;
}

MusicBrainz4::CNonMBTrackList *MusicBrainz4::CCDStub::NonMBTrackList() const
{
	return m_d->m_NonMBTrackList;
}

std::ostream& MusicBrainz4::CCDStub::Serialise(std::ostream& os) const
{
	os << "CDStub:" << std::endl;

	CEntity::Serialise(os);

	os << "\tID:      " << ID() << std::endl;
	os << "\tTitle:   " << Title() << std::endl;
	os << "\tArtist:  " << Artist() << std::endl;
	os << "\tBarcode: " << Barcode() << std::endl;
	os << "\tComment: " << Comment() << std::endl;

	if (NonMBTrackList())
		os << *NonMBTrackList() << std::endl;

	return os;
}
