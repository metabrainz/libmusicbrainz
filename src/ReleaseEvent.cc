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

#include "musicbrainz5/ReleaseEvent.h"

#include "musicbrainz5/Area.h"

class MusicBrainz5::CReleaseEventPrivate
{
	public:
		CReleaseEventPrivate()
		:	m_Area(0)
		{
		}

		std::string m_Date;
		CArea *m_Area;
};

MusicBrainz5::CReleaseEvent::CReleaseEvent(const XMLNode& Node)
:	CEntity(),
	m_d(new CReleaseEventPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Artist node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CReleaseEvent::CReleaseEvent(const CReleaseEvent& Other)
:	CEntity(),
	m_d(new CReleaseEventPrivate)
{
	*this=Other;
}

MusicBrainz5::CReleaseEvent& MusicBrainz5::CReleaseEvent::operator =(const CReleaseEvent& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_Date=Other.m_d->m_Date;

		if (Other.m_d->m_Area)
			m_d->m_Area=new CArea(*Other.m_d->m_Area);
	}

	return *this;
}

MusicBrainz5::CReleaseEvent::~CReleaseEvent()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CReleaseEvent::Cleanup()
{
	delete m_d->m_Area;
	m_d->m_Area=0;
}

MusicBrainz5::CReleaseEvent *MusicBrainz5::CReleaseEvent::Clone()
{
	return new CReleaseEvent(*this);
}

void MusicBrainz5::CReleaseEvent::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
#ifdef _MB5_DEBUG_
	std::cerr << "Unrecognised releaseevent attribute: '" << Name << "'" << std::endl;
#else
	(void)Name;
#endif
}

void MusicBrainz5::CReleaseEvent::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	if ("date"==NodeName)
	{
		ProcessItem(Node,m_d->m_Date);
	}
	else if ("area"==NodeName)
	{
		ProcessItem(Node,m_d->m_Area);
	}
	else
	{
#ifdef _MB5_DEBUG_
		std::cerr << "Unrecognised releaseevent element: '" << NodeName << "'" << std::endl;
#endif
	}
}

std::string MusicBrainz5::CReleaseEvent::GetElementName()
{
	return "release-event";
}

std::string MusicBrainz5::CReleaseEvent::Date() const
{
	return m_d->m_Date;
}

MusicBrainz5::CArea *MusicBrainz5::CReleaseEvent::Area() const
{
	return m_d->m_Area;
}

std::ostream& MusicBrainz5::CReleaseEvent::Serialise(std::ostream& os) const
{
	os << "ReleaseEvent:" << std::endl;

	CEntity::Serialise(os);

	os << "\tDate: " << Date() << std::endl;

	if (Area())
		os << *Area() << std::endl;

	return os;
}

