/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

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

#include "musicbrainz5/UserTag.h"

class MusicBrainz5::CUserTagPrivate
{
	public:
		std::string m_Name;
};

MusicBrainz5::CUserTag::CUserTag(const XMLNode& Node)
:	CEntity(),
	m_d(new CUserTagPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "UserTag node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CUserTag::CUserTag(const CUserTag& Other)
:	CEntity(),
	m_d(new CUserTagPrivate)
{
	*this=Other;
}

MusicBrainz5::CUserTag& MusicBrainz5::CUserTag::operator =(const CUserTag& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_Name=Other.m_d->m_Name;
	}

	return *this;
}

MusicBrainz5::CUserTag::~CUserTag()
{
	delete m_d;
}

MusicBrainz5::CUserTag *MusicBrainz5::CUserTag::Clone()
{
	return new CUserTag(*this);
}

void MusicBrainz5::CUserTag::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	std::cerr << "Unrecognised usertag attribute: '" << Name << "'" << std::endl;
}

void MusicBrainz5::CUserTag::ParseElement(const XMLNode& Node)
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

std::string MusicBrainz5::CUserTag::GetElementName()
{
	return "user-tag";
}

std::string MusicBrainz5::CUserTag::Name() const
{
	return m_d->m_Name;
}

std::ostream& MusicBrainz5::CUserTag::Serialise(std::ostream& os) const
{
	os << "UserTag:" << std::endl;

	CEntity::Serialise(os);

	os << "\tName:  " << Name() << std::endl;

	return os;
}
