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

#include "musicbrainz5/Tag.h"

class MusicBrainz5::CTagPrivate
{
	public:
		CTagPrivate()
		:	m_Count(0)
		{
		}

		int m_Count;
		std::string m_Name;
};

MusicBrainz5::CTag::CTag(const XMLNode& Node)
:	CEntity(),
	m_d(new CTagPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Tag node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CTag::CTag(const CTag& Other)
:	CEntity(),
	m_d(new CTagPrivate)
{
	*this=Other;
}

MusicBrainz5::CTag& MusicBrainz5::CTag::operator =(const CTag& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_Count=Other.m_d->m_Count;
		m_d->m_Name=Other.m_d->m_Name;
	}

	return *this;
}

MusicBrainz5::CTag::~CTag()
{
	delete m_d;
}

MusicBrainz5::CTag *MusicBrainz5::CTag::Clone()
{
	return new CTag(*this);
}

bool MusicBrainz5::CTag::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("count"==Name)
	{
		RetVal=ProcessItem(Value,m_d->m_Count);
	}
	else
	{
		std::cerr << "Unrecognised tag attribute: '" << Name << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

bool MusicBrainz5::CTag::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("name"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Name);
	}
	else
	{
		std::cerr << "Unrecognised tag element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz5::CTag::GetElementName()
{
	return "tag";
}

int MusicBrainz5::CTag::Count() const
{
	return m_d->m_Count;
}

std::string MusicBrainz5::CTag::Name() const
{
	return m_d->m_Name;
}

std::ostream& MusicBrainz5::CTag::Serialise(std::ostream& os) const
{
	os << "Tag:" << std::endl;

	CEntity::Serialise(os);

	os << "\tCount: " << Count() << std::endl;
	os << "\tName:  " << Name() << std::endl;

	return os;
}
