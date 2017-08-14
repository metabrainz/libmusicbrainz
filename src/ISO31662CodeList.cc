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

#include "musicbrainz5/ISO31662CodeList.h"

#include "musicbrainz5/ISO31662Code.h"

class MusicBrainz5::CISO31662CodeListPrivate
{
	public:
		CISO31662CodeListPrivate()
		{
		}
};

MusicBrainz5::CISO31662CodeList::CISO31662CodeList(const XMLNode& Node)
:	CListImpl<CISO31662Code>(),
	m_d(new CISO31662CodeListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "ISO31662CodeList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CISO31662CodeList::CISO31662CodeList(const CISO31662CodeList& Other)
:	CListImpl<CISO31662Code>(),
	m_d(new CISO31662CodeListPrivate)
{
	*this=Other;
}

MusicBrainz5::CISO31662CodeList& MusicBrainz5::CISO31662CodeList::operator =(const CISO31662CodeList& Other)
{
	if (this!=&Other)
	{
		CListImpl<CISO31662Code>::operator =(Other);
	}

	return *this;
}

MusicBrainz5::CISO31662CodeList::~CISO31662CodeList()
{
	delete m_d;
}

MusicBrainz5::CISO31662CodeList *MusicBrainz5::CISO31662CodeList::Clone()
{
	return new CISO31662CodeList(*this);
}

void MusicBrainz5::CISO31662CodeList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	CListImpl<CISO31662Code>::ParseAttribute(Name,Value);
}

void MusicBrainz5::CISO31662CodeList::ParseElement(const XMLNode& Node)
{
	CListImpl<CISO31662Code>::ParseElement(Node);
}

std::string MusicBrainz5::CISO31662CodeList::GetElementName()
{
	return "iso-3166-2-code-list";
}

std::ostream& MusicBrainz5::CISO31662CodeList::Serialise(std::ostream& os) const
{
	os << "ISO31662Code list:" << std::endl;

	CListImpl<CISO31662Code>::Serialise(os);

	return os;
}
