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

#include "musicbrainz4/ArtistCredit.h"

#include "musicbrainz4/NameCreditList.h"
#include "musicbrainz4/NameCredit.h"

class MusicBrainz4::CArtistCreditPrivate
{
	public:
		CArtistCreditPrivate()
		:	m_NameCreditList(0)
		{
		}

		CNameCreditList *m_NameCreditList;
};

MusicBrainz4::CArtistCredit::CArtistCredit(const XMLNode& Node)
:	CEntity(),
	m_d(new CArtistCreditPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Artist credit node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);

		m_d->m_NameCreditList=new CNameCreditList(Node);
	}
}

MusicBrainz4::CArtistCredit::CArtistCredit(const CArtistCredit& Other)
:	CEntity(),
	m_d(new CArtistCreditPrivate)
{
	*this=Other;
}

MusicBrainz4::CArtistCredit& MusicBrainz4::CArtistCredit::operator =(const CArtistCredit& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		if (Other.m_d->m_NameCreditList)
			m_d->m_NameCreditList=new CNameCreditList(*Other.m_d->m_NameCreditList);
	}

	return *this;
}

MusicBrainz4::CArtistCredit::~CArtistCredit()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz4::CArtistCredit::Cleanup()
{
	delete m_d->m_NameCreditList;
	m_d->m_NameCreditList=0;
}

MusicBrainz4::CArtistCredit *MusicBrainz4::CArtistCredit::Clone()
{
	return new CArtistCredit(*this);
}

void MusicBrainz4::CArtistCredit::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	std::cerr << "Unrecognised artistcredit attribute: '" << Name << "'" << std::endl;
}

void MusicBrainz4::CArtistCredit::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	if ("name-credit"==NodeName)
	{
		//The artist credit element is a special case, in that all it contains is a list of name-credits
		//Parsing of this list is handled in the constructor
	}
	else
	{
		std::cerr << "Unrecognised artistcredit element: '" << NodeName << "'" << std::endl;
	}
}

std::string MusicBrainz4::CArtistCredit::GetElementName()
{
	return "artist-credit";
}

MusicBrainz4::CNameCreditList *MusicBrainz4::CArtistCredit::NameCreditList() const
{
	return m_d->m_NameCreditList;
}

std::ostream& MusicBrainz4::CArtistCredit::Serialise(std::ostream& os) const
{
	os << "Artist credit:" << std::endl;

	CEntity::Serialise(os);

	if (NameCreditList())
		os << *NameCreditList() << std::endl;

	return os;
}
