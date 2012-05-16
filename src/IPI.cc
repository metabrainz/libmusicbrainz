/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

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
#include "musicbrainz4/defines.h"

#include "musicbrainz4/IPI.h"

class MusicBrainz4::CIPIPrivate
{
	public:
		CIPIPrivate()
		{
		}

		std::string m_IPI;
};

MusicBrainz4::CIPI::CIPI(const XMLNode& Node)
:	CEntity(),
	m_d(new CIPIPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "IPI node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);

		if (Node.getText())
		{
			ProcessItem(Node,m_d->m_IPI);
		}
	}
}

MusicBrainz4::CIPI::CIPI(const CIPI& Other)
:	CEntity(),
	m_d(new CIPIPrivate)
{
	*this=Other;
}

MusicBrainz4::CIPI& MusicBrainz4::CIPI::operator =(const CIPI& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_IPI=Other.m_d->m_IPI;
	}

	return *this;
}

MusicBrainz4::CIPI::~CIPI()
{
	delete m_d;
}

MusicBrainz4::CIPI *MusicBrainz4::CIPI::Clone()
{
	return new CIPI(*this);
}

void MusicBrainz4::CIPI::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	std::cerr << "Unrecognised IPI attribute: '" << Name << "'" << std::endl;
}

void MusicBrainz4::CIPI::ParseElement(const XMLNode& Node)
{
	std::string Name=Node.getName();

	std::cerr << "Unrecognised IPI element: '" << Name << "'" << std::endl;
}

std::string MusicBrainz4::CIPI::GetElementName()
{
	return "ipi";
}

std::string MusicBrainz4::CIPI::IPI() const
{
	return m_d->m_IPI;
}

std::ostream& MusicBrainz4::CIPI::Serialise(std::ostream& os) const
{
	os << "IPI:" << std::endl;

	CEntity::Serialise(os);

	os << "\tIPI: " << IPI() << std::endl;

	return os;
}

