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

#include "musicbrainz4/Alias.h"

class MusicBrainz4::CAliasPrivate
{
public:
		std::string m_Type;
		std::string m_Script;
		std::string m_Text;
};

MusicBrainz4::CAlias::CAlias(const XMLNode& Node)
:	m_d(new CAliasPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Relation node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("type"))
			m_d->m_Type=Node.getAttribute("type");

		if (Node.isAttributeSet("script"))
			m_d->m_Script=Node.getAttribute("script");

		if (Node.getText())
			m_d->m_Text=Node.getText();
	}
}

MusicBrainz4::CAlias::CAlias(const CAlias& Other)
:	m_d(new CAliasPrivate)
{
	*this=Other;
}

MusicBrainz4::CAlias& MusicBrainz4::CAlias::operator =(const CAlias& Other)
{
	if (this!=&Other)
	{
		m_d->m_Type=Other.m_d->m_Type;
		m_d->m_Script=Other.m_d->m_Type;
		m_d->m_Text=Other.m_d->m_Text;
	}

	return *this;
}

MusicBrainz4::CAlias::~CAlias()
{
	delete m_d;
}

std::string MusicBrainz4::CAlias::Type() const
{
	return m_d->m_Type;
}

std::string MusicBrainz4::CAlias::Script() const
{
	return m_d->m_Script;
}

std::string MusicBrainz4::CAlias::Text() const
{
	return m_d->m_Text;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CAlias& Alias)
{
	os << "Alias:" << std::endl;

	os << "\tType:   " << Alias.Type() << std::endl;
	os << "\tScript: " << Alias.Script() << std::endl;
	os << "\tText:   " << Alias.Text() << std::endl;

	return os;
}
