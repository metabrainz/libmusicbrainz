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

#include "musicbrainz4/Alias.h"

class MusicBrainz4::CAliasPrivate
{
public:
		std::string m_Locale;
		std::string m_Text;
		std::string m_SortName;
		std::string m_Type;
		std::string m_Primary;
		std::string m_BeginDate;
		std::string m_EndDate;
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
		m_d->m_SortName=Other.m_d->m_SortName;
		m_d->m_Type=Other.m_d->m_Type;
		m_d->m_Primary=Other.m_d->m_Primary;
		m_d->m_BeginDate=Other.m_d->m_BeginDate;
		m_d->m_EndDate=Other.m_d->m_EndDate;
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

void MusicBrainz4::CAlias::ParseAttribute(const std::string& Name, const std::string& Value)
{
	if ("locale"==Name)
		m_d->m_Locale=Value;
	else if ("sort-name"==Name)
		m_d->m_SortName=Value;
	else if ("type"==Name)
		m_d->m_Type=Value;
	else if ("primary"==Name)
		m_d->m_Primary=Value;
	else if ("begin-date"==Name)
		m_d->m_BeginDate=Value;
	else if ("end-date"==Name)
		m_d->m_EndDate=Value;
	else
	{
		std::cerr << "Unrecognised alias attribute: '" << Name << "'" << std::endl;
	}
}

void MusicBrainz4::CAlias::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();
	std::cerr << "Unrecognised alias element: '" << NodeName << std::endl;
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

std::string MusicBrainz4::CAlias::SortName() const
{
	return m_d->m_SortName;
}

std::string MusicBrainz4::CAlias::Type() const
{
	return m_d->m_Type;
}

std::string MusicBrainz4::CAlias::Primary() const
{
	return m_d->m_Primary;
}

std::string MusicBrainz4::CAlias::BeginDate() const
{
	return m_d->m_BeginDate;
}

std::string MusicBrainz4::CAlias::EndDate() const
{
	return m_d->m_EndDate;
}

std::ostream& MusicBrainz4::CAlias::Serialise(std::ostream& os) const
{
	os << "Alias:" << std::endl;

	CEntity::Serialise(os);

	os << "\tLocale:    " << Locale() << std::endl;
	os << "\tText:      " << Text() << std::endl;
	os << "\tSort Name: " << SortName() << std::endl;
	os << "\tType:      " << Type() << std::endl;
	os << "\tPrimary:   " << Primary() << std::endl;
	os << "\tBeginDate: " << BeginDate() << std::endl;
	os << "\tEndDate:   " << EndDate() << std::endl;

	return os;
}
