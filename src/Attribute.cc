/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

#include "musicbrainz4/Attribute.h"

class MusicBrainz4::CAttributePrivate
{
	public:
		std::string m_Text;
};
		
MusicBrainz4::CAttribute::CAttribute(const XMLNode& Node)
:	m_d(new CAttributePrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Attribute node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.getText())
			m_d->m_Text=Node.getText();
	}
}

MusicBrainz4::CAttribute::CAttribute(const CAttribute& Other)
:	m_d(new CAttributePrivate)
{
	*this=Other;
}

MusicBrainz4::CAttribute& MusicBrainz4::CAttribute::operator =(const CAttribute& Other)
{
	if (this!=&Other)
	{
		m_d->m_Text=Other.m_d->m_Text;
	}

	return *this;
}

MusicBrainz4::CAttribute::~CAttribute()
{
	delete m_d;
}

std::string MusicBrainz4::CAttribute::Text() const
{
	return m_d->m_Text;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CAttribute& Attribute)
{
	os << "Attribute:" << std::endl;

	os << "\tText: " << Attribute.Text() << std::endl;

	return os;
}


