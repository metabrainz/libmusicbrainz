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

#include "musicbrainz5/Message.h"

class MusicBrainz5::CMessagePrivate
{
public:
		std::string m_Text;
};

MusicBrainz5::CMessage::CMessage(const XMLNode& Node)
:	CEntity(),
	m_d(new CMessagePrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Message node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CMessage::CMessage(const CMessage& Other)
:	CEntity(),
	m_d(new CMessagePrivate)
{
	*this=Other;
}

MusicBrainz5::CMessage& MusicBrainz5::CMessage::operator =(const CMessage& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_Text=Other.m_d->m_Text;
	}

	return *this;
}

MusicBrainz5::CMessage::~CMessage()
{
	delete m_d;
}

MusicBrainz5::CMessage *MusicBrainz5::CMessage::Clone()
{
	return new CMessage(*this);
}

bool MusicBrainz5::CMessage::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	bool RetVal=true;

	std::cerr << "Unrecognised message attribute: '" << Name << "'" << std::endl;
	RetVal=false;

	return RetVal;
}

bool MusicBrainz5::CMessage::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if (NodeName=="text")
		RetVal=ProcessItem(Node,m_d->m_Text);
	else
	{
		std::cerr << "Unrecognised message element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz5::CMessage::GetElementName()
{
	return "message";
}

std::string MusicBrainz5::CMessage::Text() const
{
	return m_d->m_Text;
}

std::ostream& MusicBrainz5::CMessage::Serialise(std::ostream& os) const
{
	os << "Message:" << std::endl;

	CEntity::Serialise(os);

	os << "\tText: " << Text() << std::endl;

	return os;
}
