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

#include "musicbrainz5/ISO31662Code.h"

class MusicBrainz5::CISO31662CodePrivate
{
	public:
		CISO31662CodePrivate()
		{
		}

		std::string m_Code;
};

MusicBrainz5::CISO31662Code::CISO31662Code(const XMLNode& Node)
:	CEntity(),
	m_d(new CISO31662CodePrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "ISO31662Code node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);

		if (Node.getText())
			ProcessItem(Node,m_d->m_Code);
	}
}

MusicBrainz5::CISO31662Code::CISO31662Code(const CISO31662Code& Other)
:	CEntity(),
	m_d(new CISO31662CodePrivate)
{
	*this=Other;
}

MusicBrainz5::CISO31662Code& MusicBrainz5::CISO31662Code::operator =(const CISO31662Code& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_Code=Other.m_d->m_Code;
	}

	return *this;
}

MusicBrainz5::CISO31662Code::~CISO31662Code()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CISO31662Code::Cleanup()
{
}

MusicBrainz5::CISO31662Code *MusicBrainz5::CISO31662Code::Clone()
{
	return new CISO31662Code(*this);
}

void MusicBrainz5::CISO31662Code::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
#ifdef _MB5_DEBUG_
	std::cerr << "Unrecognised ISO31662Code attribute: '" << Name << "'" << std::endl;
#else
	(void)Name;
#endif
}

void MusicBrainz5::CISO31662Code::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

#ifdef _MB5_DEBUG_
	std::cerr << "Unrecognised ISO31662Code element: '" << NodeName << "'" << std::endl;
#endif
}

std::string MusicBrainz5::CISO31662Code::GetElementName()
{
	return "iso-3166-2-code";
}

std::string MusicBrainz5::CISO31662Code::Code() const
{
	return m_d->m_Code;
}

std::ostream& MusicBrainz5::CISO31662Code::Serialise(std::ostream& os) const
{
	os << "ISO31662Code:" << std::endl;

	CEntity::Serialise(os);

	os << "\tCode: " << Code() << std::endl;

	return os;
}

