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

#include "musicbrainz4/Message.h"

class MusicBrainz4::CMessagePrivate
{
public:
		std::string m_Text;
};

MusicBrainz4::CMessage::CMessage(const XMLNode& Node)
:	m_d(new CMessagePrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Message node: " << std::endl << Node.createXMLString(true) << std::endl;

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if (NodeName=="text")
				m_d->m_Text=NodeValue;
		}
	}
}

MusicBrainz4::CMessage::CMessage(const CMessage& Other)
:	m_d(new CMessagePrivate)
{
	*this=Other;
}

MusicBrainz4::CMessage& MusicBrainz4::CMessage::operator =(const CMessage& Other)
{
	if (this!=&Other)
	{
		m_d->m_Text=Other.m_d->m_Text;
	}

	return *this;
}

MusicBrainz4::CMessage::~CMessage()
{
	delete m_d;
}

std::string MusicBrainz4::CMessage::Text() const
{
	return m_d->m_Text;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CMessage& Message)
{
	os << "Message:" << std::endl;

	os << "\tText: " << Message.Text() << std::endl;

	return os;
}
