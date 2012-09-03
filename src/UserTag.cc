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

#include "musicbrainz4/UserTag.h"

class MusicBrainz4::CUserTagPrivate
{
	public:
		std::string m_Name;
};

MusicBrainz4::CUserTag::CUserTag(const XMLNode& Node)
:	CEntity(),
	m_d(new CUserTagPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "UserTag node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CUserTag::CUserTag(const CUserTag& Other)
:	CEntity(),
	m_d(new CUserTagPrivate)
{
	*this=Other;
}

MusicBrainz4::CUserTag& MusicBrainz4::CUserTag::operator =(const CUserTag& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_Name=Other.m_d->m_Name;
	}

	return *this;
}

MusicBrainz4::CUserTag::~CUserTag()
{
	delete m_d;
}

MusicBrainz4::CUserTag *MusicBrainz4::CUserTag::Clone()
{
	return new CUserTag(*this);
}

void MusicBrainz4::CUserTag::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	std::cerr << "Unrecognised usertag attribute: '" << Name << "'" << std::endl;
}

void MusicBrainz4::CUserTag::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	if ("name"==NodeName)
	{
		ProcessItem(Node,m_d->m_Name);
	}
	else
	{
		std::cerr << "Unrecognised UserTag element: '" << NodeName << "'" << std::endl;
	}
}

std::string MusicBrainz4::CUserTag::GetElementName()
{
	return "user-tag";
}

std::string MusicBrainz4::CUserTag::Name() const
{
	return m_d->m_Name;
}

std::ostream& MusicBrainz4::CUserTag::Serialise(std::ostream& os) const
{
	os << "UserTag:" << std::endl;

	CEntity::Serialise(os);

	os << "\tName:  " << Name() << std::endl;

	return os;
}
