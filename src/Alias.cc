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

#include "musicbrainz4/Alias.h"

class MusicBrainz4::CAliasPrivate
{
public:
		std::string m_Locale;
		std::string m_Text;
};

MusicBrainz4::CAlias::CAlias(const XMLNode& Node)
:	CEntity(),
	m_d(new CAliasPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Alias node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);

		if (Node.getText())
			ProcessItem(Node,m_d->m_Text);
	}
}

MusicBrainz4::CAlias::CAlias(const CAlias& Other)
:	CEntity(),
	m_d(new CAliasPrivate)
{
	*this=Other;
}

MusicBrainz4::CAlias& MusicBrainz4::CAlias::operator =(const CAlias& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_Locale=Other.m_d->m_Locale;
		m_d->m_Text=Other.m_d->m_Text;
	}

	return *this;
}

MusicBrainz4::CAlias::~CAlias()
{
	delete m_d;
}

MusicBrainz4::CAlias *MusicBrainz4::CAlias::Clone()
{
	return new CAlias(*this);
}

bool MusicBrainz4::CAlias::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("locale"==Name)
		m_d->m_Locale=Value;
	else
	{
		std::cerr << "Unrecognised alias attribute: '" << Name << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;

}

bool MusicBrainz4::CAlias::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();
	std::cerr << "Unrecognised alias element: '" << NodeName << std::endl;
	RetVal=false;

	return RetVal;
}

std::string MusicBrainz4::CAlias::GetElementName()
{
	return "alias";
}

std::string MusicBrainz4::CAlias::Locale() const
{
	return m_d->m_Locale;
}

std::string MusicBrainz4::CAlias::Text() const
{
	return m_d->m_Text;
}

std::ostream& MusicBrainz4::CAlias::Serialise(std::ostream& os) const
{
	os << "Alias:" << std::endl;

	CEntity::Serialise(os);

	os << "\tLocale: " << Locale() << std::endl;
	os << "\tText:   " << Text() << std::endl;

	return os;
}
