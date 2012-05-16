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

#include "config.h"
#include "musicbrainz4/defines.h"

#include "musicbrainz4/Tag.h"

class MusicBrainz4::CTagPrivate
{
	public:
		CTagPrivate()
		:	m_Count(0)
		{
		}

		int m_Count;
		std::string m_Name;
};

MusicBrainz4::CTag::CTag(const XMLNode& Node)
:	CEntity(),
	m_d(new CTagPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Tag node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CTag::CTag(const CTag& Other)
:	CEntity(),
	m_d(new CTagPrivate)
{
	*this=Other;
}

MusicBrainz4::CTag& MusicBrainz4::CTag::operator =(const CTag& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_Count=Other.m_d->m_Count;
		m_d->m_Name=Other.m_d->m_Name;
	}

	return *this;
}

MusicBrainz4::CTag::~CTag()
{
	delete m_d;
}

MusicBrainz4::CTag *MusicBrainz4::CTag::Clone()
{
	return new CTag(*this);
}

void MusicBrainz4::CTag::ParseAttribute(const std::string& Name, const std::string& Value)
{
	if ("count"==Name)
	{
		ProcessItem(Value,m_d->m_Count);
	}
	else
	{
		std::cerr << "Unrecognised tag attribute: '" << Name << "'" << std::endl;
	}
}

void MusicBrainz4::CTag::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	if ("name"==NodeName)
	{
		ProcessItem(Node,m_d->m_Name);
	}
	else
	{
		std::cerr << "Unrecognised tag element: '" << NodeName << "'" << std::endl;
	}
}

std::string MusicBrainz4::CTag::GetElementName()
{
	return "tag";
}

int MusicBrainz4::CTag::Count() const
{
	return m_d->m_Count;
}

std::string MusicBrainz4::CTag::Name() const
{
	return m_d->m_Name;
}

std::ostream& MusicBrainz4::CTag::Serialise(std::ostream& os) const
{
	os << "Tag:" << std::endl;

	CEntity::Serialise(os);

	os << "\tCount: " << Count() << std::endl;
	os << "\tName:  " << Name() << std::endl;

	return os;
}
