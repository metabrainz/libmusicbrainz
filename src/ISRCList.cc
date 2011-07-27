/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libmusicbrainz4 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include "musicbrainz4/ISRCList.h"

#include "musicbrainz4/ISRC.h"

class MusicBrainz4::CISRCListPrivate
{
	public:
};

MusicBrainz4::CISRCList::CISRCList(const XMLNode& Node)
:	CList(),
	m_d(new CISRCListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "ISRCList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CISRCList::CISRCList(const CISRCList& Other)
:	CList(),
	m_d(new CISRCListPrivate)
{
	*this=Other;
}

MusicBrainz4::CISRCList& MusicBrainz4::CISRCList::operator =(const CISRCList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CISRCList::~CISRCList()
{
	delete m_d;
}

MusicBrainz4::CISRCList *MusicBrainz4::CISRCList::Clone()
{
	return new CISRCList(*this);
}

bool MusicBrainz4::CISRCList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CISRCList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("isrc"==NodeName)
	{
		CISRC *Item=0;

		RetVal=ProcessItem(Node,Item);
		if (RetVal)
			AddItem(Item);
	}
	else
	{
		RetVal=CList::ParseElement(Node);
	}

	return RetVal;
}

std::string MusicBrainz4::CISRCList::ElementName() const
{
	return "isrc-list";
}

MusicBrainz4::CISRC *MusicBrainz4::CISRCList::Item(int Item) const
{
	return dynamic_cast<CISRC *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CISRCList& ISRCList)
{
	os << "ISRC list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&ISRCList;

	os << *Base << std::endl;

	for (int count=0;count<ISRCList.NumItems();count++)
	{
		MusicBrainz4::CISRC *Item=ISRCList.Item(count);

		os << *Item;
	}

	return os;
}
