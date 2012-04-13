/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libmusicbrainz4 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include "config.h"

#include "musicbrainz4/Lifespan.h"

class MusicBrainz4::CLifespanPrivate
{
	public:
		std::string m_Begin;
		std::string m_End;
};

MusicBrainz4::CLifespan::CLifespan(const XMLNode& Node)
:	CEntity(),
	m_d(new CLifespanPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Lifespan node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CLifespan::CLifespan(const CLifespan& Other)
:	CEntity(),
	m_d(new CLifespanPrivate)
{
	*this=Other;
}

MusicBrainz4::CLifespan& MusicBrainz4::CLifespan::operator =(const CLifespan& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_Begin=Other.m_d->m_Begin;
		m_d->m_End=Other.m_d->m_End;
	}

	return *this;
}

MusicBrainz4::CLifespan::~CLifespan()
{
	delete m_d;
}

MusicBrainz4::CLifespan *MusicBrainz4::CLifespan::Clone()
{
	return new CLifespan(*this);
}

bool MusicBrainz4::CLifespan::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	bool RetVal=true;

	std::cerr << "Unrecognised lifespan attribute: '" << Name << "'" << std::endl;
	RetVal=false;

	return RetVal;
}

bool MusicBrainz4::CLifespan::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("begin"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Begin);
	}
	else if ("end"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_End);
	}
	else
	{
		std::cerr << "Unrecognised lifespan element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz4::CLifespan::GetElementName()
{
	return "life-span";
}

std::string MusicBrainz4::CLifespan::Begin() const
{
	return m_d->m_Begin;
}

std::string MusicBrainz4::CLifespan::End() const
{
	return m_d->m_End;
}

std::ostream& MusicBrainz4::CLifespan::Serialise(std::ostream& os) const
{
	os << "Lifespan:" << std::endl;

	CEntity::Serialise(os);

	os << "\tBegin: " << Begin() << std::endl;
	os << "\tEnd:   " << End() << std::endl;

	return os;
}
