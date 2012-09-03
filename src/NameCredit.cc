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

#include "musicbrainz4/NameCredit.h"

#include "musicbrainz4/Artist.h"

class MusicBrainz4::CNameCreditPrivate
{
	public:
		CNameCreditPrivate()
		:	m_Artist(0)
		{
		}

		std::string m_JoinPhrase;
		std::string m_Name;
		CArtist *m_Artist;
};

MusicBrainz4::CNameCredit::CNameCredit(const XMLNode& Node)
:	CEntity(),
	m_d(new CNameCreditPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Name credit node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CNameCredit::CNameCredit(const CNameCredit& Other)
:	CEntity(),
	m_d(new CNameCreditPrivate)
{
	*this=Other;
}

MusicBrainz4::CNameCredit& MusicBrainz4::CNameCredit::operator =(const CNameCredit& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_JoinPhrase=Other.m_d->m_JoinPhrase;
		m_d->m_Name=Other.m_d->m_Name;

		if (Other.m_d->m_Artist)
			m_d->m_Artist=new CArtist(*Other.m_d->m_Artist);
	}

	return *this;
}

MusicBrainz4::CNameCredit::~CNameCredit()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz4::CNameCredit::Cleanup()
{
	delete m_d->m_Artist;
	m_d->m_Artist=0;
}

MusicBrainz4::CNameCredit *MusicBrainz4::CNameCredit::Clone()
{
	return new CNameCredit(*this);
}

void MusicBrainz4::CNameCredit::ParseAttribute(const std::string& Name, const std::string& Value)
{
	if ("joinphrase"==Name)
		m_d->m_JoinPhrase=Value;
	else
	{
		std::cerr << "Unrecognised namecredit attribute: '" << Name << "'" << std::endl;
	}
}

void MusicBrainz4::CNameCredit::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	if ("name"==NodeName)
	{
		ProcessItem(Node,m_d->m_Name);
	}
	else if ("artist"==NodeName)
	{
		ProcessItem(Node,m_d->m_Artist);
	}
	else
	{
		std::cerr << "Unrecognised name credit element: '" << NodeName << "'" << std::endl;
	}
}

std::string MusicBrainz4::CNameCredit::GetElementName()
{
	return "name-credit";
}

std::string MusicBrainz4::CNameCredit::JoinPhrase() const
{
	return m_d->m_JoinPhrase;
}

std::string MusicBrainz4::CNameCredit::Name() const
{
	return m_d->m_Name;
}

MusicBrainz4::CArtist *MusicBrainz4::CNameCredit::Artist() const
{
	return m_d->m_Artist;
}

std::ostream& MusicBrainz4::CNameCredit::Serialise(std::ostream& os) const
{
	os << "Name credit:" << std::endl;

	CEntity::Serialise(os);

	os << "\tJoin phrase: " << JoinPhrase() << std::endl;
	os << "\tName:        " << Name() << std::endl;

	if (Artist())
		os << *Artist() << std::endl;

	return os;
}


