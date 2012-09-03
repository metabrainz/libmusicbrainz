/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   libmusicbrainz4 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include "config.h"
#include "musicbrainz4/defines.h"

#include "musicbrainz4/ISRC.h"

#include "musicbrainz4/RecordingList.h"
#include "musicbrainz4/Recording.h"

class MusicBrainz4::CISRCPrivate
{
	public:
		CISRCPrivate()
		:	m_RecordingList(0)
		{
		}

		std::string m_ID;
		CRecordingList *m_RecordingList;
};

MusicBrainz4::CISRC::CISRC(const XMLNode& Node)
:	CEntity(),
	m_d(new CISRCPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "ISRC node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CISRC::CISRC(const CISRC& Other)
:	CEntity(),
	m_d(new CISRCPrivate)
{
	*this=Other;
}

MusicBrainz4::CISRC& MusicBrainz4::CISRC::operator =(const CISRC& Other)
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

MusicBrainz4::CISRC *MusicBrainz4::CISRC::Clone()
{
	return new CISRC(*this);
}

void MusicBrainz4::CISRC::ParseAttribute(const std::string& Name, const std::string& Value)
{
	if ("id"==Name)
		m_d->m_ID=Value;
	else
	{
		std::cerr << "Unrecognised isrc attribute: '" << Name << "'" << std::endl;
	}
}

void MusicBrainz4::CISRC::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	if ("recording-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_RecordingList);
	}
	else
	{
		std::cerr << "Unrecognised ISRC element: '" << NodeName << "'" << std::endl;
	}
}

std::string MusicBrainz4::CISRC::GetElementName()
{
	return "isrc";
}

std::string MusicBrainz4::CISRC::ID() const
{
	return m_d->m_ID;
}

MusicBrainz4::CRecordingList *MusicBrainz4::CISRC::RecordingList() const
{
	return m_d->m_RecordingList;
}

std::ostream& MusicBrainz4::CISRC::Serialise(std::ostream& os) const
{
	os << "ISRC:" << std::endl;

	CEntity::Serialise(os);

	os << "\tID: " << ID() << std::endl;

	if (RecordingList())
		os << *RecordingList() << std::endl;

	return os;
}

