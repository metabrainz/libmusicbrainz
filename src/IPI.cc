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

#include "musicbrainz5/IPI.h"

class MusicBrainz5::CIPIPrivate
{
	public:
		CIPIPrivate()
		{
		}

		std::string m_IPI;
};

MusicBrainz5::CIPI::CIPI(const XMLNode& Node)
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

MusicBrainz5::CIPI::CIPI(const CIPI& Other)
:	CEntity(),
	m_d(new CIPIPrivate)
{
	*this=Other;
}

MusicBrainz5::CIPI& MusicBrainz5::CIPI::operator =(const CIPI& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_IPI=Other.m_d->m_IPI;
	}

	return *this;
}

MusicBrainz5::CIPI::~CIPI()
{
	delete m_d;
}

MusicBrainz5::CIPI *MusicBrainz5::CIPI::Clone()
{
	return new CIPI(*this);
}

bool MusicBrainz5::CIPI::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	bool RetVal=true;

	std::cerr << "Unrecognised IPI attribute: '" << Name << "'" << std::endl;
	RetVal=false;

	return RetVal;
}

bool MusicBrainz5::CIPI::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string Name=Node.getName();

	std::cerr << "Unrecognised IPI element: '" << Name << "'" << std::endl;
	RetVal=false;

	return RetVal;
}

std::string MusicBrainz5::CIPI::GetElementName()
{
	return "ipi";
}

std::string MusicBrainz5::CIPI::IPI() const
{
	return m_d->m_IPI;
}

std::ostream& MusicBrainz5::CIPI::Serialise(std::ostream& os) const
{
	os << "IPI:" << std::endl;

	CEntity::Serialise(os);

	os << "\tIPI: " << IPI() << std::endl;

	return os;
}

