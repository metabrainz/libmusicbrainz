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

#include "musicbrainz5/Offset.h"

class MusicBrainz5::COffsetPrivate
{
	public:
		COffsetPrivate()
		:	m_Position(0),
			m_Offset(0)
		{
		}

		int m_Position;
		int m_Offset;
};

MusicBrainz5::COffset::COffset(const XMLNode& Node)
:	CEntity(),
	m_d(new COffsetPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Offset node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);

		if (Node.getText())
			ProcessItem(Node, m_d->m_Offset);
	}
}

MusicBrainz5::COffset::COffset(const COffset& Other)
:	CEntity(),
	m_d(new COffsetPrivate)
{
	*this=Other;
}

MusicBrainz5::COffset& MusicBrainz5::COffset::operator =(const COffset& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_Position=Other.m_d->m_Position;
		m_d->m_Offset=Other.m_d->m_Offset;
	}

	return *this;
}

MusicBrainz5::COffset::~COffset()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::COffset::Cleanup()
{
}

MusicBrainz5::COffset *MusicBrainz5::COffset::Clone()
{
	return new COffset(*this);
}

void MusicBrainz5::COffset::ParseAttribute(const std::string& Name, const std::string& Value)
{
	if ("position"==Name)
		ProcessItem(Value,m_d->m_Position);
	else
	{
		std::cerr << "Unrecognised offset attribute: '" << Name << "'" << std::endl;
	}
}

void MusicBrainz5::COffset::ParseElement(const XMLNode& Node)
{
	std::cerr << "Unrecognised offset element: '" << Node.getName() << "'" << std::endl;
}

std::string MusicBrainz5::COffset::GetElementName()
{
	return "offset";
}

int MusicBrainz5::COffset::Position() const
{
	return m_d->m_Position;
}

int MusicBrainz5::COffset::Offset() const
{
	return m_d->m_Offset;
}

std::ostream& MusicBrainz5::COffset::Serialise(std::ostream& os) const
{
	os << "Offset:" << std::endl;

	CEntity::Serialise(os);

	os << "\tPosition: " << Position() << std::endl;
	os << "\tOffset:   " << Offset() << std::endl;

	return os;
}
