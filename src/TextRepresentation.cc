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

#include "musicbrainz4/TextRepresentation.h"

class MusicBrainz4::CTextRepresentationPrivate
{
	public:
		std::string m_Language;
		std::string m_Script;
};

MusicBrainz4::CTextRepresentation::CTextRepresentation(const XMLNode& Node)
:	CEntity(),
	m_d(new CTextRepresentationPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Text representation node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CTextRepresentation::CTextRepresentation(const CTextRepresentation& Other)
:	CEntity(),
	m_d(new CTextRepresentationPrivate)
{
	*this=Other;
}

MusicBrainz4::CTextRepresentation& MusicBrainz4::CTextRepresentation::operator =(const CTextRepresentation& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_Language=Other.m_d->m_Language;
		m_d->m_Script=Other.m_d->m_Script;
	}

	return *this;
}

MusicBrainz4::CTextRepresentation::~CTextRepresentation()
{
	delete m_d;
}

MusicBrainz4::CTextRepresentation *MusicBrainz4::CTextRepresentation::Clone()
{
	return new CTextRepresentation(*this);
}

bool MusicBrainz4::CTextRepresentation::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	bool RetVal=true;

	std::cerr << "Unrecognised textrepresentation attribute: '" << Name << "'" << std::endl;
	RetVal=false;

	return RetVal;
}

bool MusicBrainz4::CTextRepresentation::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("language"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Language);
	}
	else if ("script"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Script);
	}
	else
	{
		std::cerr << "Unrecognised textrepresentation element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz4::CTextRepresentation::GetElementName()
{
	return "text-representation";
}

std::string MusicBrainz4::CTextRepresentation::Language() const
{
	return m_d->m_Language;
}

std::string MusicBrainz4::CTextRepresentation::Script() const
{
	return m_d->m_Script;
}

std::ostream& MusicBrainz4::CTextRepresentation::Serialise(std::ostream& os) const
{
	os << "\tText Representation:" << std::endl;

	CEntity::Serialise(os);

	os << "\t\tLanguage: " << Language() << std::endl;
	os << "\t\tScript:   " << Script() << std::endl;

	return os;
}

