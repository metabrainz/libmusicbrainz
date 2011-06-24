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

#include "musicbrainz4/Medium.h"

#include "musicbrainz4/Disc.h"
#include "musicbrainz4/Track.h"

#include "ParserUtils.h"

class MusicBrainz4::CMediumPrivate
{
	public:
		CMediumPrivate()
		:	m_DiscList(0),
			m_TrackList(0)
		{
		}

		std::string m_Title;
		int m_Position;
		std::string m_Format;
		CGenericList<CDisc> *m_DiscList;
		CGenericList<CTrack> *m_TrackList;
};

MusicBrainz4::CMedium::CMedium(const XMLNode& Node)
:	m_d(new CMediumPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Medium node: " << std::endl << Node.createXMLString(true) << std::endl;

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
			else if ("position"==NodeName)
			{
				ProcessItem(NodeValue,m_d->m_Position);
			}
			else if ("format"==NodeName)
			{
				m_d->m_Format=NodeValue;
			}
			else if ("disc-list"==NodeName)
			{
				m_d->m_DiscList=new CGenericList<CDisc>(ChildNode,"disc");
			}
			else if ("track-list"==NodeName)
			{
				m_d->m_TrackList=new CGenericList<CTrack>(ChildNode,"track");
			}
			else
			{
				std::cerr << "Unrecognised medium node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CMedium::CMedium(const CMedium& Other)
:	m_d(new CMediumPrivate)
{
	*this=Other;
}

MusicBrainz4::CMedium& MusicBrainz4::CMedium::operator =(const CMedium& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_d->m_Title=Other.m_d->m_Title;
		m_d->m_Position=Other.m_d->m_Position;
		m_d->m_Format=Other.m_d->m_Format;

		if (Other.m_d->m_DiscList)
			m_d->m_DiscList=new CGenericList<CDisc>(*Other.m_d->m_DiscList);

		if (Other.m_d->m_TrackList)
			m_d->m_TrackList=new CGenericList<CTrack>(*Other.m_d->m_TrackList);
	}

	return *this;
}

MusicBrainz4::CMedium::~CMedium()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz4::CMedium::Cleanup()
{
	delete m_d->m_DiscList;
	m_d->m_DiscList=0;

	delete m_d->m_TrackList;
	m_d->m_TrackList=0;
}

std::string MusicBrainz4::CMedium::Title() const
{
	return m_d->m_Title;
}

int MusicBrainz4::CMedium::Position() const
{
	return m_d->m_Position;
}

std::string MusicBrainz4::CMedium::Format() const
{
	return m_d->m_Format;
}

MusicBrainz4::CGenericList<MusicBrainz4::CDisc> *MusicBrainz4::CMedium::DiscList() const
{
	return m_d->m_DiscList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CTrack> *MusicBrainz4::CMedium::TrackList() const
{
	return m_d->m_TrackList;
}

bool MusicBrainz4::CMedium::ContainsDiscID(const std::string& DiscID) const
{
	bool RetVal=false;

	std::list<CDisc> DiscList=m_d->m_DiscList->Items();
	std::list<CDisc>::const_iterator ThisDisc=DiscList.begin();
	while (!RetVal && ThisDisc!=DiscList.end())
	{
		CDisc Disc=*ThisDisc;

		if (Disc.ID()==DiscID)
			RetVal=true;

		++ThisDisc;
	}

	return RetVal;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CMedium& Medium)
{
	os << "Medium:" << std::endl;

	os << "\tTitle:    " << Medium.Title() << std::endl;
	os << "\tPosition: " << Medium.Position() << std::endl;
	os << "\tFormat:   " << Medium.Format() << std::endl;

	if (Medium.DiscList())
		os << *Medium.DiscList() << std::endl;

	if (Medium.TrackList())
		os << *Medium.TrackList() << std::endl;

	return os;
}
