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

#include "musicbrainz4/Track.h"

#include <sstream>

#include "musicbrainz4/Recording.h"

MusicBrainz4::CTrack::CTrack(const XMLNode& Node)
:	m_Recording(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Track node: " << std::endl << Node.createXMLString(true) << std::endl;

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("position"==NodeName)
			{
				std::stringstream os;
				os << NodeValue;
				os >> m_Position;
			}
			else if ("title"==NodeName)
			{
				m_Title=NodeValue;
			}
			else if ("recording"==NodeName)
			{
				m_Recording=new CRecording(ChildNode);
			}
			else
			{
				std::cerr << "Unrecognised track node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CTrack::CTrack(const CTrack& Other)
:	m_Recording(0)
{
	*this=Other;
}

MusicBrainz4::CTrack& MusicBrainz4::CTrack::operator =(const CTrack& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_Position=Other.m_Position;
		m_Title=Other.m_Title;

		if (Other.m_Recording)
			m_Recording=new CRecording(*Other.m_Recording);
	}

	return *this;
}

MusicBrainz4::CTrack::~CTrack()
{
	Cleanup();
}

void MusicBrainz4::CTrack::Cleanup()
{
	delete m_Recording;
	m_Recording=0;
}

int MusicBrainz4::CTrack::Position() const
{
	return m_Position;
}

std::string MusicBrainz4::CTrack::Title() const
{
	return m_Title;
}

MusicBrainz4::CRecording *MusicBrainz4::CTrack:: Recording() const
{
	return m_Recording;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CTrack& Track)
{
	os << "Track:" << std::endl;

	os << "\tPosition: " << Track.Position() << std::endl;
	os << "\tTitle:    " << Track.Title() << std::endl;

	if (Track.Recording())
		os << *Track.Recording() << std::endl;

	return os;
}
