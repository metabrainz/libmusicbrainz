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

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include "musicbrainz4/PUID.h"

#include "musicbrainz4/GenericList.h"
#include "musicbrainz4/RecordingList.h"

class MusicBrainz4::CPUIDPrivate
{
	public:
		CPUIDPrivate()
		:	m_RecordingList(0)
		{
		}

		std::string m_ID;
		CRecordingList *m_RecordingList;
};

MusicBrainz4::CPUID::CPUID(const XMLNode& Node)
:	CEntity(),
	m_d(new CPUIDPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "PUID node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CPUID::CPUID(const CPUID& Other)
:	CEntity(),
	m_d(new CPUIDPrivate)
{
	*this=Other;
}

MusicBrainz4::CPUID& MusicBrainz4::CPUID::operator =(const CPUID& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_ID=Other.m_d->m_ID;

		if (Other.m_d->m_RecordingList)
			m_d->m_RecordingList=new CRecordingList(*Other.m_d->m_RecordingList);
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

MusicBrainz4::CPUID *MusicBrainz4::CPUID::Clone()
{
	return new CPUID(*this);
}

bool MusicBrainz4::CPUID::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("id"==Name)
		m_d->m_ID=Value;
	else
	{
		std::cerr << "Unrecognised puid attribute: '" << Name << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

bool MusicBrainz4::CPUID::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("recording-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_RecordingList);
	}
	else
	{
		std::cerr << "Unrecognised PUID element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz4::CPUID::ElementName() const
{
	return "puid";
}

std::string MusicBrainz4::CPUID::ID() const
{
	return m_d->m_ID;
}

MusicBrainz4::CRecordingList *MusicBrainz4::CPUID::RecordingList() const
{
	return m_d->m_RecordingList;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CPUID& PUID)
{
	os << "PUID:" << std::endl;

	MusicBrainz4::CEntity *Base=(MusicBrainz4::CEntity *)&PUID;

	os << *Base << std::endl;

	os << "\tID: " << PUID.ID() << std::endl;

	if (PUID.RecordingList())
		os << *PUID.RecordingList() << std::endl;

	return os;
}

