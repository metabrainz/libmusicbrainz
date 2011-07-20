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

#include "musicbrainz4/UserTag.h"

class MusicBrainz4::CUserTagPrivate
{
	public:
		std::string m_Name;
};

MusicBrainz4::CUserTag::CUserTag(const XMLNode& Node)
:	CEntity(),
	m_d(new CUserTagPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "UserTag node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CUserTag::CUserTag(const CUserTag& Other)
:	CEntity(),
	m_d(new CUserTagPrivate)
{
	*this=Other;
}

MusicBrainz4::CUserTag& MusicBrainz4::CUserTag::operator =(const CUserTag& Other)
{
	if (this!=&Other)
	{
		m_d->m_Name=Other.m_d->m_Name;
	}

	return *this;
}

MusicBrainz4::CUserTag::~CUserTag()
{
	delete m_d;
}

bool MusicBrainz4::CUserTag::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	bool RetVal=true;

	std::cerr << "Unrecognised usertag attribute: '" << Name << "'" << std::endl;
	RetVal=false;

	return RetVal;
}

bool MusicBrainz4::CUserTag::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("name"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Name);
	}
	else
	{
		std::cerr << "Unrecognised UserTag element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz4::CUserTag::Name() const
{
	return m_d->m_Name;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CUserTag& UserTag)
{
	os << "UserTag:" << std::endl;

	MusicBrainz4::CEntity *Base=(MusicBrainz4::CEntity *)&UserTag;

	os << *Base << std::endl;

	os << "\tName:  " << UserTag.Name() << std::endl;

	return os;
}
