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

#include "musicbrainz5/ISO31663Code.h"

class MusicBrainz5::CISO31663CodePrivate
{
	public:
		CISO31663CodePrivate()
		{
		}

		std::string m_Code;
};

MusicBrainz5::CISO31663Code::CISO31663Code(const XMLNode& Node)
:	CEntity(),
	m_d(new CISO31663CodePrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "ISO31663Code node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);

		if (Node.getText())
			ProcessItem(Node,m_d->m_Code);
	}
}

MusicBrainz5::CISO31663Code::CISO31663Code(const CISO31663Code& Other)
:	CEntity(),
	m_d(new CISO31663CodePrivate)
{
	*this=Other;
}

MusicBrainz5::CISO31663Code& MusicBrainz5::CISO31663Code::operator =(const CISO31663Code& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_Code=Other.m_d->m_Code;
	}

	return *this;
}

MusicBrainz5::CISO31663Code::~CISO31663Code()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CISO31663Code::Cleanup()
{
}

MusicBrainz5::CISO31663Code *MusicBrainz5::CISO31663Code::Clone()
{
	return new CISO31663Code(*this);
}

void MusicBrainz5::CISO31663Code::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
#ifdef _MB5_DEBUG_
	std::cerr << "Unrecognised ISO31663Code attribute: '" << Name << "'" << std::endl;
#else
	(void)Name;
#endif
}

void MusicBrainz5::CISO31663Code::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

#ifdef _MB5_DEBUG_
	std::cerr << "Unrecognised ISO31663Code element: '" << NodeName << "'" << std::endl;
#endif
}

std::string MusicBrainz5::CISO31663Code::GetElementName()
{
	return "iso-3166-1-code";
}

std::string MusicBrainz5::CISO31663Code::Code() const
{
	return m_d->m_Code;
}

std::ostream& MusicBrainz5::CISO31663Code::Serialise(std::ostream& os) const
{
	os << "ISO31663Code:" << std::endl;

	CEntity::Serialise(os);

	os << "\tCode: " << Code() << std::endl;

	return os;
}

