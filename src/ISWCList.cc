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

#include "musicbrainz5/ISWCList.h"

#include "musicbrainz5/ISWC.h"

class MusicBrainz5::CISWCListPrivate
{
	public:
		CISWCListPrivate()
		{
		}
};

MusicBrainz5::CISWCList::CISWCList(const XMLNode& Node)
:	CListImpl<CISWC>(),
	m_d(new CISWCListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "ISWCList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CISWCList::CISWCList(const CISWCList& Other)
:	CListImpl<CISWC>(),
	m_d(new CISWCListPrivate)
{
	*this=Other;
}

MusicBrainz5::CISWCList& MusicBrainz5::CISWCList::operator =(const CISWCList& Other)
{
	if (this!=&Other)
	{
		CListImpl<CISWC>::operator =(Other);
	}

	return *this;
}

MusicBrainz5::CISWCList::~CISWCList()
{
	delete m_d;
}

MusicBrainz5::CISWCList *MusicBrainz5::CISWCList::Clone()
{
	return new CISWCList(*this);
}

void MusicBrainz5::CISWCList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	CListImpl<CISWC>::ParseAttribute(Name,Value);
}

void MusicBrainz5::CISWCList::ParseElement(const XMLNode& Node)
{
	CListImpl<CISWC>::ParseElement(Node);
}

std::string MusicBrainz5::CISWCList::GetElementName()
{
	return "iswc-list";
}

std::ostream& MusicBrainz5::CISWCList::Serialise(std::ostream& os) const
{
	os << "ISWC list:" << std::endl;

	CListImpl<CISWC>::Serialise(os);

	return os;
}
