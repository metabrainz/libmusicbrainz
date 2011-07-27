/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libmusicbrainz4 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include "musicbrainz4/Disc.h"

#include "musicbrainz4/ReleaseList.h"

class MusicBrainz4::CDiscPrivate
{
	public:
		CDiscPrivate()
		:	m_Sectors(0),
			m_ReleaseList(0)
		{
		}

		std::string m_ID;
		int m_Sectors;
		CReleaseList *m_ReleaseList;
};

MusicBrainz4::CDisc::CDisc(const XMLNode& Node)
:	CEntity(),
	m_d(new CDiscPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Disc node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CDisc::CDisc(const CDisc& Other)
:	CEntity(),
	m_d(new CDiscPrivate)
{
	*this=Other;
}

MusicBrainz4::CDisc& MusicBrainz4::CDisc::operator =(const CDisc& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Sectors=Other.m_d->m_Sectors;

		if (Other.m_d->m_ReleaseList)
			m_d->m_ReleaseList=new CReleaseList(*Other.m_d->m_ReleaseList);
	}

	return *this;
}

MusicBrainz4::CDisc::~CDisc()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz4::CDisc::Cleanup()
{
	delete m_d->m_ReleaseList;
	m_d->m_ReleaseList=0;
}

MusicBrainz4::CDisc *MusicBrainz4::CDisc::Clone()
{
	return new CDisc(*this);
}

bool MusicBrainz4::CDisc::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("id"==Name)
		RetVal=ProcessItem(Value,m_d->m_ID);
	else
	{
		std::cerr << "Unrecognised disc attribute: '" << Name << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

bool MusicBrainz4::CDisc::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("sectors"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Sectors);
	}
	else if ("release-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ReleaseList);
	}
	else
	{
		std::cerr << "Unrecognised disc element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz4::CDisc::ElementName() const
{
	return "disc";
}

std::string MusicBrainz4::CDisc::ID() const
{
	return m_d->m_ID;
}

int MusicBrainz4::CDisc::Sectors() const
{
	return m_d->m_Sectors;
}

MusicBrainz4::CReleaseList *MusicBrainz4::CDisc::ReleaseList() const
{
	return m_d->m_ReleaseList;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CDisc& Disc)
{
	os << "Disc:" << std::endl;

	MusicBrainz4::CEntity *Base=(MusicBrainz4::CEntity *)&Disc;

	os << *Base << std::endl;

	os << "\tID:      " << Disc.ID() << std::endl;
	os << "\tSectors: " << Disc.Sectors() << std::endl;

	if (Disc.ReleaseList())
		os << *Disc.ReleaseList() << std::endl;

	return os;
}

