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

#include "musicbrainz5/SecondaryTypeList.h"

#include "musicbrainz5/SecondaryType.h"

class MusicBrainz5::CSecondaryTypeListPrivate
{
	public:
		CSecondaryTypeListPrivate()
		{
		}
};

MusicBrainz5::CSecondaryTypeList::CSecondaryTypeList(const XMLNode& Node)
:	CListImpl<CSecondaryType>(),
	m_d(new CSecondaryTypeListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "SecondaryTypeList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CSecondaryTypeList::CSecondaryTypeList(const CSecondaryTypeList& Other)
:	CListImpl<CSecondaryType>(),
	m_d(new CSecondaryTypeListPrivate)
{
	*this=Other;
}

MusicBrainz5::CSecondaryTypeList& MusicBrainz5::CSecondaryTypeList::operator =(const CSecondaryTypeList& Other)
{
	if (this!=&Other)
	{
		CListImpl<CSecondaryType>::operator =(Other);
	}

	return *this;
}

MusicBrainz5::CSecondaryTypeList::~CSecondaryTypeList()
{
	delete m_d;
}

MusicBrainz5::CSecondaryTypeList *MusicBrainz5::CSecondaryTypeList::Clone()
{
	return new CSecondaryTypeList(*this);
}

void MusicBrainz5::CSecondaryTypeList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	CListImpl<CSecondaryType>::ParseAttribute(Name,Value);
}

void MusicBrainz5::CSecondaryTypeList::ParseElement(const XMLNode& Node)
{
	CListImpl<CSecondaryType>::ParseElement(Node);
}

std::string MusicBrainz5::CSecondaryTypeList::GetElementName()
{
	return "secondary-type-list";
}

std::ostream& MusicBrainz5::CSecondaryTypeList::Serialise(std::ostream& os) const
{
	os << "Secondary type list:" << std::endl;

	CListImpl<CSecondaryType>::Serialise(os);

	return os;
}
