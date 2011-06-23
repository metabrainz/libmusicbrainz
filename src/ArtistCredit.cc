/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

#include "musicbrainz4/ArtistCredit.h"

class MusicBrainz4::CArtistCreditPrivate
{
	public:
		CArtistCreditPrivate()
		:	m_NameCreditList(0)
		{
		}
		
		CGenericList<CNameCredit> *m_NameCreditList;
};
		
MusicBrainz4::CArtistCredit::CArtistCredit(const XMLNode& Node)
:	m_d(new CArtistCreditPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Artist credit node: " << std::endl << Node.createXMLString(true) << std::endl;

		m_d->m_NameCreditList=new CGenericList<CNameCredit>(Node,"name-credit");
	}
}

MusicBrainz4::CArtistCredit::CArtistCredit(const CArtistCredit& Other)
:	m_d(new CArtistCreditPrivate)
{
	*this=Other;
}

MusicBrainz4::CArtistCredit& MusicBrainz4::CArtistCredit::operator =(const CArtistCredit& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		if (Other.m_d->m_NameCreditList)
			m_d->m_NameCreditList=new CGenericList<CNameCredit>(*Other.m_d->m_NameCreditList);
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

MusicBrainz4::CGenericList<MusicBrainz4::CNameCredit> *MusicBrainz4::CArtistCredit::NameCreditList() const
{
	return m_d->m_NameCreditList;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CArtistCredit& ArtistCredit)
{
	os << "Artist credit:" << std::endl;

	if (ArtistCredit.NameCreditList())
		os << *ArtistCredit.NameCreditList() << std::endl;

	return os;
}
