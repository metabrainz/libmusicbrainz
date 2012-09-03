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

#include "musicbrainz5/ISWC.h"


class MusicBrainz5::CISWCPrivate
{
	public:
		CISWCPrivate()
		{
		}

		std::string m_ISWC;
};

MusicBrainz5::CISWC::CISWC(const XMLNode& Node)
:	CEntity(),
	m_d(new CISWCPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "ISWC node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);

		if (Node.getText())
			ProcessItem(Node,m_d->m_ISWC);
	}
}

MusicBrainz5::CISWC::CISWC(const CISWC& Other)
:	CEntity(),
	m_d(new CISWCPrivate)
{
	*this=Other;
}

MusicBrainz5::CISWC& MusicBrainz5::CISWC::operator =(const CISWC& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_ISWC=Other.m_d->m_ISWC;
	}

	return *this;
}

MusicBrainz5::CISWC::~CISWC()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CISWC::Cleanup()
{
}

MusicBrainz5::CISWC *MusicBrainz5::CISWC::Clone()
{
	return new CISWC(*this);
}

void MusicBrainz5::CISWC::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	std::cerr << "Unrecognised ISWC attribute: '" << Name << "'" << std::endl;
}

void MusicBrainz5::CISWC::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	std::cerr << "Unrecognised ISWC element: '" << NodeName << "'" << std::endl;
}

std::string MusicBrainz5::CISWC::GetElementName()
{
	return "iswc";
}

std::string MusicBrainz5::CISWC::ISWC() const
{
	return m_d->m_ISWC;
}

std::ostream& MusicBrainz5::CISWC::Serialise(std::ostream& os) const
{
	os << "ISWC:" << std::endl;

	CEntity::Serialise(os);

	os << "\tISWC: " << ISWC() << std::endl;

	return os;
}
