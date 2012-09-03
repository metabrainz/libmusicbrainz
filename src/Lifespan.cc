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

#include "musicbrainz5/Lifespan.h"

class MusicBrainz5::CLifespanPrivate
{
	public:
		std::string m_Begin;
		std::string m_End;
		std::string m_Ended;
};

MusicBrainz5::CLifespan::CLifespan(const XMLNode& Node)
:	CEntity(),
	m_d(new CLifespanPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Lifespan node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CLifespan::CLifespan(const CLifespan& Other)
:	CEntity(),
	m_d(new CLifespanPrivate)
{
	*this=Other;
}

MusicBrainz5::CLifespan& MusicBrainz5::CLifespan::operator =(const CLifespan& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_Begin=Other.m_d->m_Begin;
		m_d->m_End=Other.m_d->m_End;
		m_d->m_Ended=Other.m_d->m_Ended;
	}

	return *this;
}

MusicBrainz5::CLifespan::~CLifespan()
{
	delete m_d;
}

MusicBrainz5::CLifespan *MusicBrainz5::CLifespan::Clone()
{
	return new CLifespan(*this);
}

void MusicBrainz5::CLifespan::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	std::cerr << "Unrecognised lifespan attribute: '" << Name << "'" << std::endl;
}

void MusicBrainz5::CLifespan::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	if ("begin"==NodeName)
	{
		ProcessItem(Node,m_d->m_Begin);
	}
	else if ("end"==NodeName)
	{
		ProcessItem(Node,m_d->m_End);
	}
	else if ("ended"==NodeName)
	{
		ProcessItem(Node,m_d->m_Ended);
	}
	else
	{
		std::cerr << "Unrecognised lifespan element: '" << NodeName << "'" << std::endl;
	}
}

std::string MusicBrainz5::CLifespan::GetElementName()
{
	return "life-span";
}

std::string MusicBrainz5::CLifespan::Begin() const
{
	return m_d->m_Begin;
}

std::string MusicBrainz5::CLifespan::End() const
{
	return m_d->m_End;
}

std::string MusicBrainz5::CLifespan::Ended() const
{
	return m_d->m_Ended;
}

std::ostream& MusicBrainz5::CLifespan::Serialise(std::ostream& os) const
{
	os << "Lifespan:" << std::endl;

	CEntity::Serialise(os);

	os << "\tBegin: " << Begin() << std::endl;
	os << "\tEnd:   " << End() << std::endl;
	os << "\tEnded: " << Ended() << std::endl;

	return os;
}
