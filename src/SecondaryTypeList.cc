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

#include "musicbrainz4/SecondaryTypeList.h"

#include "musicbrainz4/SecondaryType.h"

class MusicBrainz4::CSecondaryTypeListPrivate
{
	public:
		CSecondaryTypeListPrivate()
		{
		}
};

MusicBrainz4::CSecondaryTypeList::CSecondaryTypeList(const XMLNode& Node)
:	CListImpl<CSecondaryType>(),
	m_d(new CSecondaryTypeListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "SecondaryTypeList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CSecondaryTypeList::CSecondaryTypeList(const CSecondaryTypeList& Other)
:	CListImpl<CSecondaryType>(),
	m_d(new CSecondaryTypeListPrivate)
{
	*this=Other;
}

MusicBrainz4::CSecondaryTypeList& MusicBrainz4::CSecondaryTypeList::operator =(const CSecondaryTypeList& Other)
{
	if (this!=&Other)
	{
		CListImpl<CSecondaryType>::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CSecondaryTypeList::~CSecondaryTypeList()
{
	delete m_d;
}

MusicBrainz4::CSecondaryTypeList *MusicBrainz4::CSecondaryTypeList::Clone()
{
	return new CSecondaryTypeList(*this);
}

bool MusicBrainz4::CSecondaryTypeList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CListImpl<CSecondaryType>::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CSecondaryTypeList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	RetVal=CListImpl<CSecondaryType>::ParseElement(Node);

	return RetVal;
}

std::string MusicBrainz4::CSecondaryTypeList::GetElementName()
{
	return "secondary-type-list";
}

std::ostream& MusicBrainz4::CSecondaryTypeList::Serialise(std::ostream& os) const
{
	os << "Secondary type list:" << std::endl;

	CListImpl<CSecondaryType>::Serialise(os);

	return os;
}
