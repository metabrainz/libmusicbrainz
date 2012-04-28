/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

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

#include "musicbrainz4/SecondaryType.h"


class MusicBrainz4::CSecondaryTypePrivate
{
	public:
		CSecondaryTypePrivate()
		{
		}

		std::string m_SecondaryType;
};

MusicBrainz4::CSecondaryType::CSecondaryType(const XMLNode& Node)
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

MusicBrainz4::CSecondaryType::CSecondaryType(const CSecondaryType& Other)
:	CEntity(),
	m_d(new CSecondaryTypePrivate)
{
	*this=Other;
}

MusicBrainz4::CSecondaryType& MusicBrainz4::CSecondaryType::operator =(const CSecondaryType& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_SecondaryType=Other.m_d->m_SecondaryType;
	}

	return *this;
}

MusicBrainz4::CSecondaryType::~CSecondaryType()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz4::CSecondaryType::Cleanup()
{
}

MusicBrainz4::CSecondaryType *MusicBrainz4::CSecondaryType::Clone()
{
	return new CSecondaryType(*this);
}

bool MusicBrainz4::CSecondaryType::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	bool RetVal=true;

	std::cerr << "Unrecognised secondary type attribute: '" << Name << "'" << std::endl;
	RetVal=false;

	return RetVal;
}

bool MusicBrainz4::CSecondaryType::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	std::cerr << "Unrecognised secondary type element: '" << NodeName << "'" << std::endl;
	RetVal=false;

	return RetVal;
}

std::string MusicBrainz4::CSecondaryType::GetElementName()
{
	return "secondary-type";
}

std::string MusicBrainz4::CSecondaryType::SecondaryType() const
{
	return m_d->m_SecondaryType;
}

std::ostream& MusicBrainz4::CSecondaryType::Serialise(std::ostream& os) const
{
	os << "Secondary Type:" << std::endl;

	CEntity::Serialise(os);

	os << "\tSecondaryType: " << SecondaryType() << std::endl;

	return os;
}
