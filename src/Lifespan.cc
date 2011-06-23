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

#include "musicbrainz4/Lifespan.h"

MusicBrainz4::CLifespan::CLifespan(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Lifespan node: " << std::endl << Node.createXMLString(true) << std::endl;

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("begin"==NodeName)
			{
				m_Begin=NodeValue;
			}
			else if ("end"==NodeName)
			{
				m_End=NodeValue;
			}
			else
			{
				std::cerr << "Unrecognised lifespan node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CLifespan::CLifespan(const CLifespan& Other)
{
	*this=Other;
}

MusicBrainz4::CLifespan& MusicBrainz4::CLifespan::operator =(const CLifespan& Other)
{
	if (this!=&Other)
	{
		m_Begin=Other.m_Begin;
		m_End=Other.m_End;
	}

	return *this;
}

std::string MusicBrainz4::CLifespan::Begin() const
{
	return m_Begin;
}

std::string MusicBrainz4::CLifespan::End() const
{
	return m_End;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CLifespan& Lifespan)
{
	os << "Lifespan:" << std::endl;

	os << "\tBegin: " << Lifespan.Begin() << std::endl;
	os << "\tEnd:   " << Lifespan.End() << std::endl;

	return os;
}
