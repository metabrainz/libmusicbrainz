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

#include "musicbrainz4/ISRC.h"

class MusicBrainz4::CISRCPrivate
{
	public:
		CISRCPrivate()
		:	m_RecordingList(0)
		{
		}		

		std::string m_ID;
		CGenericList<CRecording> *m_RecordingList;
};

MusicBrainz4::CISRC::CISRC(const XMLNode& Node)
:	m_d(new CISRCPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "ISRC node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("id"))
			m_d->m_ID=Node.getAttribute("id");

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("recording-list"==NodeName)
			{
				m_d->m_RecordingList=new CGenericList<CRecording>(ChildNode,"recording");
			}
			else
			{
				std::cerr << "Unrecognised ISRC node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CISRC::CISRC(const CISRC& Other)
:	m_d(new CISRCPrivate)
{
	*this=Other;
}

MusicBrainz4::CISRC& MusicBrainz4::CISRC::operator =(const CISRC& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_d->m_ID=Other.m_d->m_ID;

		if (Other.m_d->m_RecordingList)
			m_d->m_RecordingList=new CGenericList<CRecording>(*Other.m_d->m_RecordingList);
	}

	return *this;
}

MusicBrainz4::CISRC::~CISRC()
{
	Cleanup();
	
	delete m_d;
}

void MusicBrainz4::CISRC::Cleanup()
{
	delete m_d->m_RecordingList;
	m_d->m_RecordingList=0;
}

std::string MusicBrainz4::CISRC::ID() const
{
	return m_d->m_ID;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRecording> *MusicBrainz4::CISRC::RecordingList() const
{
	return m_d->m_RecordingList;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CISRC& ISRC)
{
	os << "ISRC:" << std::endl;

	os << "\tID: " << ISRC.ID() << std::endl;

	if (ISRC.RecordingList())
		os << *ISRC.RecordingList() << std::endl;

	return os;
}

