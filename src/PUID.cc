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

#include "musicbrainz5/PUID.h"

#include "musicbrainz5/RecordingList.h"
#include "musicbrainz5/Recording.h"

class MusicBrainz5::CPUIDPrivate
{
	public:
		CPUIDPrivate()
		:	m_RecordingList(0)
		{
		}

		std::string m_ID;
		CRecordingList *m_RecordingList;
};

MusicBrainz5::CPUID::CPUID(const XMLNode& Node)
:	CEntity(),
	m_d(new CPUIDPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "PUID node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CPUID::CPUID(const CPUID& Other)
:	CEntity(),
	m_d(new CPUIDPrivate)
{
	*this=Other;
}

MusicBrainz5::CPUID& MusicBrainz5::CPUID::operator =(const CPUID& Other)
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

MusicBrainz5::CPUID::~CPUID()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CPUID::Cleanup()
{
	delete m_d->m_RecordingList;
	m_d->m_RecordingList=0;
}

MusicBrainz5::CPUID *MusicBrainz5::CPUID::Clone()
{
	return new CPUID(*this);
}

bool MusicBrainz5::CPUID::ParseAttribute(const std::string& Name, const std::string& Value)
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

bool MusicBrainz5::CPUID::ParseElement(const XMLNode& Node)
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

std::string MusicBrainz5::CPUID::GetElementName()
{
	return "puid";
}

std::string MusicBrainz5::CPUID::ID() const
{
	return m_d->m_ID;
}

MusicBrainz5::CRecordingList *MusicBrainz5::CPUID::RecordingList() const
{
	return m_d->m_RecordingList;
}

std::ostream& MusicBrainz5::CPUID::Serialise(std::ostream& os) const
{
	os << "PUID:" << std::endl;

	CEntity::Serialise(os);

	os << "\tID: " << ID() << std::endl;

	if (RecordingList())
		os << *RecordingList() << std::endl;

	return os;
}

