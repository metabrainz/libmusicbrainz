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

#include "musicbrainz5/NameCredit.h"

#include "musicbrainz5/Artist.h"

class MusicBrainz5::CNameCreditPrivate
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

MusicBrainz5::CNameCredit::CNameCredit(const XMLNode& Node)
:	CEntity(),
	m_d(new CNameCreditPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Name credit node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CNameCredit::CNameCredit(const CNameCredit& Other)
:	CEntity(),
	m_d(new CNameCreditPrivate)
{
	*this=Other;
}

MusicBrainz5::CNameCredit& MusicBrainz5::CNameCredit::operator =(const CNameCredit& Other)
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

MusicBrainz5::CNameCredit::~CNameCredit()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CNameCredit::Cleanup()
{
	delete m_d->m_Artist;
	m_d->m_Artist=0;
}

MusicBrainz5::CNameCredit *MusicBrainz5::CNameCredit::Clone()
{
	return new CNameCredit(*this);
}

bool MusicBrainz5::CNameCredit::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("joinphrase"==Name)
		m_d->m_JoinPhrase=Value;
	else
	{
		std::cerr << "Unrecognised namecredit attribute: '" << Name << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

bool MusicBrainz5::CNameCredit::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;


	std::string NodeName=Node.getName();

	if ("name"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Name);
	}
	else if ("artist"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Artist);
	}
	else
	{
		std::cerr << "Unrecognised name credit element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz5::CNameCredit::GetElementName()
{
	return "name-credit";
}

std::string MusicBrainz5::CNameCredit::JoinPhrase() const
{
	return m_d->m_JoinPhrase;
}

std::string MusicBrainz5::CNameCredit::Name() const
{
	return m_d->m_Name;
}

MusicBrainz5::CArtist *MusicBrainz5::CNameCredit::Artist() const
{
	return m_d->m_Artist;
}

std::ostream& MusicBrainz5::CNameCredit::Serialise(std::ostream& os) const
{
	os << "Name credit:" << std::endl;

	CEntity::Serialise(os);

	os << "\tJoin phrase: " << JoinPhrase() << std::endl;
	os << "\tName:        " << Name() << std::endl;

	if (Artist())
		os << *Artist() << std::endl;

	return os;
}


