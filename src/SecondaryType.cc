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

#include "musicbrainz5/SecondaryType.h"


class MusicBrainz5::CSecondaryTypePrivate
{
	public:
		CSecondaryTypePrivate()
		{
		}

		std::string m_SecondaryType;
};

MusicBrainz5::CSecondaryType::CSecondaryType(const XMLNode& Node)
:	CEntity(),
	m_d(new CSecondaryTypePrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "SecondaryType node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);

		if (Node.getText())
			ProcessItem(Node,m_d->m_SecondaryType);
	}
}

MusicBrainz5::CSecondaryType::CSecondaryType(const CSecondaryType& Other)
:	CEntity(),
	m_d(new CSecondaryTypePrivate)
{
	*this=Other;
}

MusicBrainz5::CSecondaryType& MusicBrainz5::CSecondaryType::operator =(const CSecondaryType& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_SecondaryType=Other.m_d->m_SecondaryType;
	}

	return *this;
}

MusicBrainz5::CSecondaryType::~CSecondaryType()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CSecondaryType::Cleanup()
{
}

MusicBrainz5::CSecondaryType *MusicBrainz5::CSecondaryType::Clone()
{
	return new CSecondaryType(*this);
}

void MusicBrainz5::CSecondaryType::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	std::cerr << "Unrecognised secondary type attribute: '" << Name << "'" << std::endl;
}

void MusicBrainz5::CSecondaryType::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	std::cerr << "Unrecognised secondary type element: '" << NodeName << "'" << std::endl;
}

std::string MusicBrainz5::CSecondaryType::GetElementName()
{
	return "secondary-type";
}

std::string MusicBrainz5::CSecondaryType::SecondaryType() const
{
	return m_d->m_SecondaryType;
}

std::ostream& MusicBrainz5::CSecondaryType::Serialise(std::ostream& os) const
{
	os << "Secondary Type:" << std::endl;

	CEntity::Serialise(os);

	os << "\tSecondaryType: " << SecondaryType() << std::endl;

	return os;
}
