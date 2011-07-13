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

#include "musicbrainz4/CDStub.h"

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
		CGenericList<CNonMBTrack> *m_NonMBTrackList;
};

MusicBrainz4::CCDStub::CCDStub(const XMLNode& Node)
:	m_d(new CCDStubPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "CDStub node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("id"))
			m_d->m_ID=Node.getAttribute("id");

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("title"==NodeName)
			{
				m_d->m_Title=NodeValue;
			}
			else if ("artist"==NodeName)
			{
				m_d->m_Artist=NodeValue;
			}
			else if ("barcode"==NodeName)
			{
				m_d->m_Barcode=NodeValue;
			}
			else if ("comment"==NodeName)
			{
				m_d->m_Comment=NodeValue;
			}
			else if ("track-list"==NodeName)
			{
				m_d->m_NonMBTrackList=new CGenericList<CNonMBTrack>(ChildNode,"track");
			}
			else
			{
				std::cerr << "Unrecognised cd stub node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CCDStub::CCDStub(const CCDStub& Other)
:	m_d(new CCDStubPrivate)
{
	*this=Other;
}

MusicBrainz4::CCDStub& MusicBrainz4::CCDStub::operator =(const CCDStub& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Title=Other.m_d->m_Title;
		m_d->m_Artist=Other.m_d->m_Artist;
		m_d->m_Barcode=Other.m_d->m_Barcode;
		m_d->m_Comment=Other.m_d->m_Comment;

		if (Other.m_d->m_NonMBTrackList)
			m_d->m_NonMBTrackList=new CGenericList<CNonMBTrack>(*Other.m_d->m_NonMBTrackList);
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

MusicBrainz4::CGenericList<MusicBrainz4::CNonMBTrack> *MusicBrainz4::CCDStub::NonMBTrackList() const
{
	return m_d->m_NonMBTrackList;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CCDStub& CDStub)
{
	os << "CDStub:" << std::endl;

	os << "\tID:      " << CDStub.ID() << std::endl;
	os << "\tTitle:   " << CDStub.Title() << std::endl;
	os << "\tArtist:  " << CDStub.Artist() << std::endl;
	os << "\tBarcode: " << CDStub.Barcode() << std::endl;
	os << "\tComment: " << CDStub.Comment() << std::endl;

	if (CDStub.NonMBTrackList())
		os << *CDStub.NonMBTrackList() << std::endl;

	return os;
}
