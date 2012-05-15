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

#include "musicbrainz5/ArtistCredit.h"

#include "musicbrainz5/NameCreditList.h"
#include "musicbrainz5/NameCredit.h"

class MusicBrainz5::CArtistCreditPrivate
{
	public:
		CArtistCreditPrivate()
		:	m_NameCreditList(0)
		{
		}

		CNameCreditList *m_NameCreditList;
};

MusicBrainz5::CArtistCredit::CArtistCredit(const XMLNode& Node)
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

MusicBrainz5::CArtistCredit::CArtistCredit(const CArtistCredit& Other)
:	CEntity(),
	m_d(new CArtistCreditPrivate)
{
	*this=Other;
}

MusicBrainz5::CArtistCredit& MusicBrainz5::CArtistCredit::operator =(const CArtistCredit& Other)
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

MusicBrainz5::CArtistCredit::~CArtistCredit()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CArtistCredit::Cleanup()
{
	delete m_d->m_NameCreditList;
	m_d->m_NameCreditList=0;
}

MusicBrainz5::CArtistCredit *MusicBrainz5::CArtistCredit::Clone()
{
	return new CArtistCredit(*this);
}

bool MusicBrainz5::CArtistCredit::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	bool RetVal=true;

	std::cerr << "Unrecognised artistcredit attribute: '" << Name << "'" << std::endl;
	RetVal=false;


	return RetVal;
}

bool MusicBrainz5::CArtistCredit::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("name-credit"==NodeName)
	{
		//The artist credit element is a special case, in that all it contains is a list of name-credits
		//Parsing of this list is handled in the constructor
	}
	else
	{
		std::cerr << "Unrecognised artistcredit element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz5::CArtistCredit::GetElementName()
{
	return "artist-credit";
}

MusicBrainz5::CNameCreditList *MusicBrainz5::CArtistCredit::NameCreditList() const
{
	return m_d->m_NameCreditList;
}

std::ostream& MusicBrainz5::CArtistCredit::Serialise(std::ostream& os) const
{
	os << "Artist credit:" << std::endl;

	CEntity::Serialise(os);

	if (NameCreditList())
		os << *NameCreditList() << std::endl;

	return os;
}
