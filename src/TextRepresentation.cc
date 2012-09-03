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

#include "musicbrainz5/TextRepresentation.h"

class MusicBrainz5::CTextRepresentationPrivate
{
	public:
		std::string m_Language;
		std::string m_Script;
};

MusicBrainz5::CTextRepresentation::CTextRepresentation(const XMLNode& Node)
:	CEntity(),
	m_d(new CTextRepresentationPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Text representation node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CTextRepresentation::CTextRepresentation(const CTextRepresentation& Other)
:	CEntity(),
	m_d(new CTextRepresentationPrivate)
{
	*this=Other;
}

MusicBrainz5::CTextRepresentation& MusicBrainz5::CTextRepresentation::operator =(const CTextRepresentation& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_Language=Other.m_d->m_Language;
		m_d->m_Script=Other.m_d->m_Script;
	}

	return *this;
}

MusicBrainz5::CTextRepresentation::~CTextRepresentation()
{
	delete m_d;
}

MusicBrainz5::CTextRepresentation *MusicBrainz5::CTextRepresentation::Clone()
{
	return new CTextRepresentation(*this);
}

void MusicBrainz5::CTextRepresentation::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	std::cerr << "Unrecognised textrepresentation attribute: '" << Name << "'" << std::endl;
}

void MusicBrainz5::CTextRepresentation::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	if ("language"==NodeName)
	{
		ProcessItem(Node,m_d->m_Language);
	}
	else if ("script"==NodeName)
	{
		ProcessItem(Node,m_d->m_Script);
	}
	else
	{
		std::cerr << "Unrecognised textrepresentation element: '" << NodeName << "'" << std::endl;
	}
}

std::string MusicBrainz5::CTextRepresentation::GetElementName()
{
	return "text-representation";
}

std::string MusicBrainz5::CTextRepresentation::Language() const
{
	return m_d->m_Language;
}

std::string MusicBrainz5::CTextRepresentation::Script() const
{
	return m_d->m_Script;
}

std::ostream& MusicBrainz5::CTextRepresentation::Serialise(std::ostream& os) const
{
	os << "\tText Representation:" << std::endl;

	CEntity::Serialise(os);

	os << "\t\tLanguage: " << Language() << std::endl;
	os << "\t\tScript:   " << Script() << std::endl;

	return os;
}

