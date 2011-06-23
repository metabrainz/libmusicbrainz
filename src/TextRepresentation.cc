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

#include "musicbrainz4/TextRepresentation.h"

MusicBrainz4::CTextRepresentation::CTextRepresentation(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Text representation node: " << std::endl << Node.createXMLString(true) << std::endl;

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("language"==NodeName)
			{
				m_Language=NodeValue;
			}
			else if ("script"==NodeName)
			{
				m_Script=NodeValue;
			}
		}
	}
}

MusicBrainz4::CTextRepresentation::CTextRepresentation(const CTextRepresentation& Other)
{
	*this=Other;
}

MusicBrainz4::CTextRepresentation& MusicBrainz4::CTextRepresentation::operator =(const CTextRepresentation& Other)
{
	if (this!=&Other)
	{
		m_Language=Other.m_Language;
		m_Script=Other.m_Script;
	}

	return *this;
}

std::string MusicBrainz4::CTextRepresentation::Language() const
{
	return m_Language;
}

std::string MusicBrainz4::CTextRepresentation::Script() const
{
	return m_Script;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CTextRepresentation& TextRepresentation)
{
	os << "\tText Representation:" << std::endl;

	os << "\t\tLanguage: " << TextRepresentation.Language() << std::endl;
	os << "\t\tScript:   " << TextRepresentation.Script() << std::endl;

	return os;
}

