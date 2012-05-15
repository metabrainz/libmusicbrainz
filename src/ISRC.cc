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

#include "musicbrainz5/ISRC.h"

#include "musicbrainz5/RecordingList.h"
#include "musicbrainz5/Recording.h"

class MusicBrainz5::CISRCPrivate
{
	public:
		CISRCPrivate()
		:	m_RecordingList(0)
		{
		}

		std::string m_ID;
		CRecordingList *m_RecordingList;
};

MusicBrainz5::CISRC::CISRC(const XMLNode& Node)
:	CEntity(),
	m_d(new CISRCPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "ISRC node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CISRC::CISRC(const CISRC& Other)
:	CEntity(),
	m_d(new CISRCPrivate)
{
	*this=Other;
}

MusicBrainz5::CISRC& MusicBrainz5::CISRC::operator =(const CISRC& Other)
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

MusicBrainz5::CISRC::~CISRC()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CISRC::Cleanup()
{
	delete m_d->m_RecordingList;
	m_d->m_RecordingList=0;
}

MusicBrainz5::CISRC *MusicBrainz5::CISRC::Clone()
{
	return new CISRC(*this);
}

bool MusicBrainz5::CISRC::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("id"==Name)
		m_d->m_ID=Value;
	else
	{
		std::cerr << "Unrecognised isrc attribute: '" << Name << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

bool MusicBrainz5::CISRC::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("recording-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_RecordingList);
	}
	else
	{
		std::cerr << "Unrecognised ISRC element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz5::CISRC::GetElementName()
{
	return "isrc";
}

std::string MusicBrainz5::CISRC::ID() const
{
	return m_d->m_ID;
}

MusicBrainz5::CRecordingList *MusicBrainz5::CISRC::RecordingList() const
{
	return m_d->m_RecordingList;
}

std::ostream& MusicBrainz5::CISRC::Serialise(std::ostream& os) const
{
	os << "ISRC:" << std::endl;

	CEntity::Serialise(os);

	os << "\tID: " << ID() << std::endl;

	if (RecordingList())
		os << *RecordingList() << std::endl;

	return os;
}

