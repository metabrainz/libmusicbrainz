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
:	m_d(new CUserTagPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "UserTag node: " << std::endl << Node.createXMLString(true) << std::endl;

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("name"==NodeName)
			{
				m_d->m_Name=NodeValue;
			}
			else
			{
				std::cerr << "Unrecognised UserTag node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CUserTag::CUserTag(const CUserTag& Other)
:	m_d(new CUserTagPrivate)
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

std::string MusicBrainz4::CUserTag::Name() const
{
	return m_d->m_Name;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CUserTag& UserTag)
{
	os << "UserTag:" << std::endl;

	os << "\tName:  " << UserTag.Name() << std::endl;

	return os;
}
