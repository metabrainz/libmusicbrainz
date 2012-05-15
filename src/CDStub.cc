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

#include "musicbrainz5/CDStub.h"

#include "musicbrainz5/NonMBTrackList.h"
#include "musicbrainz5/NonMBTrack.h"

class MusicBrainz5::CCDStubPrivate
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

MusicBrainz5::CCDStub::CCDStub(const XMLNode& Node)
:	CEntity(),
	m_d(new CCDStubPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "CDStub node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CCDStub::CCDStub(const CCDStub& Other)
:	CEntity(),
	m_d(new CCDStubPrivate)
{
	*this=Other;
}

MusicBrainz5::CCDStub& MusicBrainz5::CCDStub::operator =(const CCDStub& Other)
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

MusicBrainz5::CCDStub::~CCDStub()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CCDStub::Cleanup()
{
	delete m_d->m_NonMBTrackList;
	m_d->m_NonMBTrackList=0;
}

MusicBrainz5::CCDStub *MusicBrainz5::CCDStub::Clone()
{
	return new CCDStub(*this);
}

bool MusicBrainz5::CCDStub::ParseAttribute(const std::string& Name, const std::string& Value)
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

bool MusicBrainz5::CCDStub::ParseElement(const XMLNode& Node)
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

std::string MusicBrainz5::CCDStub::GetElementName()
{
	return "cdstub";
}

std::string MusicBrainz5::CCDStub::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz5::CCDStub::Title() const
{
	return m_d->m_Title;
}

std::string MusicBrainz5::CCDStub::Artist() const
{
	return m_d->m_Artist;
}

std::string MusicBrainz5::CCDStub::Barcode() const
{
	return m_d->m_Barcode;
}

std::string MusicBrainz5::CCDStub::Comment() const
{
	return m_d->m_Comment;
}

MusicBrainz5::CNonMBTrackList *MusicBrainz5::CCDStub::NonMBTrackList() const
{
	return m_d->m_NonMBTrackList;
}

std::ostream& MusicBrainz5::CCDStub::Serialise(std::ostream& os) const
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
