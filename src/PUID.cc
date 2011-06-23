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

#include "musicbrainz4/PUID.h"

#include "musicbrainz4/GenericList.h"
#include "musicbrainz4/Recording.h"

class MusicBrainz4::CPUIDPrivate
{
	public:
		CPUIDPrivate()
		:	m_RecordingList(0)
		{
		}
		
		std::string m_ID;
		CGenericList<CRecording> *m_RecordingList;
};

MusicBrainz4::CPUID::CPUID(const XMLNode& Node)
:	m_d(new CPUIDPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "PUID node: " << std::endl << Node.createXMLString(true) << std::endl;

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
				std::cerr << "Unrecognised PUID node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CPUID::CPUID(const CPUID& Other)
:	m_d(new CPUIDPrivate)
{
	*this=Other;
}

MusicBrainz4::CPUID& MusicBrainz4::CPUID::operator =(const CPUID& Other)
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

MusicBrainz4::CPUID::~CPUID()
{
	Cleanup();
	
	delete m_d;
}

void MusicBrainz4::CPUID::Cleanup()
{
	delete m_d->m_RecordingList;
	m_d->m_RecordingList=0;
}

std::string MusicBrainz4::CPUID::ID() const
{
	return m_d->m_ID;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRecording> *MusicBrainz4::CPUID::RecordingList() const
{
	return m_d->m_RecordingList;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CPUID& PUID)
{
	os << "PUID:" << std::endl;

	os << "\tID: " << PUID.ID() << std::endl;

	if (PUID.RecordingList())
		os << *PUID.RecordingList() << std::endl;

	return os;
}

