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

#include "musicbrainz5/ISO31661CodeList.h"

#include "musicbrainz5/ISO31661Code.h"

class MusicBrainz5::CISO31661CodeListPrivate
{
	public:
		CISO31661CodeListPrivate()
		{
		}
};

MusicBrainz5::CISO31661CodeList::CISO31661CodeList(const XMLNode& Node)
:	CListImpl<CISO31661Code>(),
	m_d(new CISO31661CodeListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "ISO31661CodeList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CISO31661CodeList::CISO31661CodeList(const CISO31661CodeList& Other)
:	CListImpl<CISO31661Code>(),
	m_d(new CISO31661CodeListPrivate)
{
	*this=Other;
}

MusicBrainz5::CISO31661CodeList& MusicBrainz5::CISO31661CodeList::operator =(const CISO31661CodeList& Other)
{
	if (this!=&Other)
	{
		CListImpl<CISO31661Code>::operator =(Other);
	}

	return *this;
}

MusicBrainz5::CISO31661CodeList::~CISO31661CodeList()
{
	delete m_d;
}

MusicBrainz5::CISO31661CodeList *MusicBrainz5::CISO31661CodeList::Clone()
{
	return new CISO31661CodeList(*this);
}

void MusicBrainz5::CISO31661CodeList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	CListImpl<CISO31661Code>::ParseAttribute(Name,Value);
}

void MusicBrainz5::CISO31661CodeList::ParseElement(const XMLNode& Node)
{
	CListImpl<CISO31661Code>::ParseElement(Node);
}

std::string MusicBrainz5::CISO31661CodeList::GetElementName()
{
	return "iso-3166-1-code-list";
}

std::ostream& MusicBrainz5::CISO31661CodeList::Serialise(std::ostream& os) const
{
	os << "ISO31661Code list:" << std::endl;

	CListImpl<CISO31661Code>::Serialise(os);

	return os;
}
