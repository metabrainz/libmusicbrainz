/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

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

#include "musicbrainz5/Alias.h"

class MusicBrainz5::CAliasPrivate
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

MusicBrainz5::CAlias::CAlias(const XMLNode& Node)
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

MusicBrainz5::CAlias::CAlias(const CAlias& Other)
:	CEntity(),
	m_d(new CAliasPrivate)
{
	*this=Other;
}

MusicBrainz5::CAlias& MusicBrainz5::CAlias::operator =(const CAlias& Other)
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

MusicBrainz5::CAlias::~CAlias()
{
	delete m_d;
}

MusicBrainz5::CAlias *MusicBrainz5::CAlias::Clone()
{
	return new CAlias(*this);
}

bool MusicBrainz5::CAlias::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

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
		RetVal=false;
	}

	return RetVal;

}

bool MusicBrainz5::CAlias::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();
	std::cerr << "Unrecognised alias element: '" << NodeName << std::endl;
	RetVal=false;

	return RetVal;
}

std::string MusicBrainz5::CAlias::GetElementName()
{
	return "alias";
}

std::string MusicBrainz5::CAlias::Locale() const
{
	return m_d->m_Locale;
}

std::string MusicBrainz5::CAlias::Text() const
{
	return m_d->m_Text;
}

std::string MusicBrainz5::CAlias::SortName() const
{
	return m_d->m_SortName;
}

std::string MusicBrainz5::CAlias::Type() const
{
	return m_d->m_Type;
}

std::string MusicBrainz5::CAlias::Primary() const
{
	return m_d->m_Primary;
}

std::string MusicBrainz5::CAlias::BeginDate() const
{
	return m_d->m_BeginDate;
}

std::string MusicBrainz5::CAlias::EndDate() const
{
	return m_d->m_EndDate;
}

std::ostream& MusicBrainz5::CAlias::Serialise(std::ostream& os) const
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
