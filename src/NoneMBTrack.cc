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

#include "musicbrainz4/NoneMBTrack.h"

#include "ParserUtils.h"

class MusicBrainz4::CNoneMBTrackPrivate
{
	public:
		CNoneMBTrackPrivate()
		:	m_Length(0)
		{
		}

		std::string m_Title;
		std::string m_Artist;
		int m_Length;
};

MusicBrainz4::CNoneMBTrack::CNoneMBTrack(const XMLNode& Node)
:	m_d(new CNoneMBTrackPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "NoneMBTrack node: " << std::endl << Node.createXMLString(true) << std::endl;

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
			else if ("length"==NodeName)
			{
				ProcessItem(NodeValue,m_d->m_Length);
			}
			else
			{
				std::cerr << "Unrecognised none MB track node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CNoneMBTrack::CNoneMBTrack(const CNoneMBTrack& Other)
:	m_d(new CNoneMBTrackPrivate)
{
	*this=Other;
}

MusicBrainz4::CNoneMBTrack& MusicBrainz4::CNoneMBTrack::operator =(const CNoneMBTrack& Other)
{
	if (this!=&Other)
	{
		m_d->m_Title=Other.m_d->m_Title;
		m_d->m_Artist=Other.m_d->m_Artist;
		m_d->m_Length=Other.m_d->m_Length;
	}

	return *this;
}

MusicBrainz4::CNoneMBTrack::~CNoneMBTrack()
{
	delete m_d;
}

std::string MusicBrainz4::CNoneMBTrack::Title() const
{
	return m_d->m_Title;
}

std::string MusicBrainz4::CNoneMBTrack::Artist() const
{
	return m_d->m_Artist;
}

int MusicBrainz4::CNoneMBTrack::Length() const
{
	return m_d->m_Length;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CNoneMBTrack& NoneMBTrack)
{
	os << "NoneMBTrack:" << std::endl;

	os << "\tTitle:  " << NoneMBTrack.Title() << std::endl;
	os << "\tArtist: " << NoneMBTrack.Artist() << std::endl;
	os << "\tLength: " << NoneMBTrack.Length() << std::endl;

	return os;
}
