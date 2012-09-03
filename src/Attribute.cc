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

#include "musicbrainz5/Attribute.h"

class MusicBrainz5::CAttributePrivate
{
	public:
		std::string m_Text;
};

MusicBrainz5::CAttribute::CAttribute(const XMLNode& Node)
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

MusicBrainz5::CAttribute::CAttribute(const CAttribute& Other)
:	CEntity(),
	m_d(new CAttributePrivate)
{
	*this=Other;
}

MusicBrainz5::CAttribute& MusicBrainz5::CAttribute::operator =(const CAttribute& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_Text=Other.m_d->m_Text;
	}

	return *this;
}

MusicBrainz5::CAttribute::~CAttribute()
{
	delete m_d;
}

MusicBrainz5::CAttribute *MusicBrainz5::CAttribute::Clone()
{
	return new CAttribute(*this);
}

void MusicBrainz5::CAttribute::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	std::cerr << "Unrecognised attribute attribute: '" << Name << "'" << std::endl;
}

void MusicBrainz5::CAttribute::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	std::cerr << "Unrecognised attribute element: '" << NodeName << "'" << std::endl;
}

std::string MusicBrainz5::CAttribute::GetElementName()
{
	return "attribute";
}

std::string MusicBrainz5::CAttribute::Text() const
{
	return m_d->m_Text;
}

std::ostream& MusicBrainz5::CAttribute::Serialise(std::ostream& os) const
{
	os << "Attribute:" << std::endl;

	CEntity::Serialise(os);

	os << "\tText: " << Text() << std::endl;

	return os;
}


