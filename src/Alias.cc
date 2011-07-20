/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

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
		m_d->m_Locale=Other.m_d->m_Locale;
		m_d->m_Text=Other.m_d->m_Text;
	}

	return *this;
}

MusicBrainz4::CAlias::~CAlias()
{
	delete m_d;
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

std::string MusicBrainz4::CAlias::Locale() const
{
	return m_d->m_Locale;
}

std::string MusicBrainz4::CAlias::Text() const
{
	return m_d->m_Text;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CAlias& Alias)
{
	os << "Alias:" << std::endl;

	MusicBrainz4::CEntity *Base=(MusicBrainz4::CEntity *)&Alias;

	os << *Base << std::endl;

	os << "\tLocale: " << Alias.Locale() << std::endl;
	os << "\tText:   " << Alias.Text() << std::endl;

	return os;
}
