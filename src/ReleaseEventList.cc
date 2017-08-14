/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2017 Andrew Hawkins

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

#include "musicbrainz5/ReleaseEventList.h"

#include "musicbrainz5/ReleaseEvent.h"

class MusicBrainz5::CReleaseEventListPrivate
{
	public:
		CReleaseEventListPrivate()
		{
		}
};

MusicBrainz5::CReleaseEventList::CReleaseEventList(const XMLNode& Node)
:	CListImpl<CReleaseEvent>(),
	m_d(new CReleaseEventListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "SecondaryTypeList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CReleaseEventList::CReleaseEventList(const CReleaseEventList& Other)
:	CListImpl<CReleaseEvent>(),
	m_d(new CReleaseEventListPrivate)
{
	*this=Other;
}

MusicBrainz5::CReleaseEventList& MusicBrainz5::CReleaseEventList::operator =(const CReleaseEventList& Other)
{
	if (this!=&Other)
	{
		CListImpl<CReleaseEvent>::operator =(Other);
	}

	return *this;
}

MusicBrainz5::CReleaseEventList::~CReleaseEventList()
{
	delete m_d;
}

MusicBrainz5::CReleaseEventList *MusicBrainz5::CReleaseEventList::Clone()
{
	return new CReleaseEventList(*this);
}

void MusicBrainz5::CReleaseEventList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	CListImpl<CReleaseEvent>::ParseAttribute(Name,Value);
}

void MusicBrainz5::CReleaseEventList::ParseElement(const XMLNode& Node)
{
	CListImpl<CReleaseEvent>::ParseElement(Node);
}

std::string MusicBrainz5::CReleaseEventList::GetElementName()
{
	return "release-event-list";
}

std::ostream& MusicBrainz5::CReleaseEventList::Serialise(std::ostream& os) const
{
	os << "Release event list:" << std::endl;

	CListImpl<CReleaseEvent>::Serialise(os);

	return os;
}
