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

#include "musicbrainz4/Attribute.h"

class MusicBrainz4::CAttributePrivate
{
	public:
		std::string m_Text;
};

MusicBrainz4::CAttribute::CAttribute(const XMLNode& Node)
:	CEntity(),
	m_d(new CAttributePrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Attribute node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);

		if (Node.getText())
			ProcessItem(Node,m_d->m_Text);
	}
}

MusicBrainz4::CAttribute::CAttribute(const CAttribute& Other)
:	CEntity(),
	m_d(new CAttributePrivate)
{
	*this=Other;
}

MusicBrainz4::CAttribute& MusicBrainz4::CAttribute::operator =(const CAttribute& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_Text=Other.m_d->m_Text;
	}

	return *this;
}

MusicBrainz4::CAttribute::~CAttribute()
{
	delete m_d;
}

MusicBrainz4::CAttribute *MusicBrainz4::CAttribute::Clone()
{
	return new CAttribute(*this);
}

void MusicBrainz4::CAttribute::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	std::cerr << "Unrecognised attribute attribute: '" << Name << "'" << std::endl;
}

void MusicBrainz4::CAttribute::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	std::cerr << "Unrecognised attribute element: '" << NodeName << "'" << std::endl;
}

std::string MusicBrainz4::CAttribute::GetElementName()
{
	return "attribute";
}

std::string MusicBrainz4::CAttribute::Text() const
{
	return m_d->m_Text;
}

std::ostream& MusicBrainz4::CAttribute::Serialise(std::ostream& os) const
{
	os << "Attribute:" << std::endl;

	CEntity::Serialise(os);

	os << "\tText: " << Text() << std::endl;

	return os;
}


