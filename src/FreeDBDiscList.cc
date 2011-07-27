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

#include "musicbrainz4/FreeDBDiscList.h"

#include "musicbrainz4/FreeDBDisc.h"

class MusicBrainz4::CFreeDBDiscListPrivate
{
	public:
};

MusicBrainz4::CFreeDBDiscList::CFreeDBDiscList(const XMLNode& Node)
:	CList(),
	m_d(new CFreeDBDiscListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "FreeDBDiscList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CFreeDBDiscList::CFreeDBDiscList(const CFreeDBDiscList& Other)
:	CList(),
	m_d(new CFreeDBDiscListPrivate)
{
	*this=Other;
}

MusicBrainz4::CFreeDBDiscList& MusicBrainz4::CFreeDBDiscList::operator =(const CFreeDBDiscList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CFreeDBDiscList::~CFreeDBDiscList()
{
	delete m_d;
}

MusicBrainz4::CFreeDBDiscList *MusicBrainz4::CFreeDBDiscList::Clone()
{
	return new CFreeDBDiscList(*this);
}

bool MusicBrainz4::CFreeDBDiscList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CFreeDBDiscList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("freedb-disc"==NodeName)
	{
		CFreeDBDisc *Item=0;

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

std::string MusicBrainz4::CFreeDBDiscList::ElementName() const
{
	return "freedb-disc-list";
}

MusicBrainz4::CFreeDBDisc *MusicBrainz4::CFreeDBDiscList::Item(int Item) const
{
	return dynamic_cast<CFreeDBDisc *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CFreeDBDiscList& FreeDBDiscList)
{
	os << "Disc list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&FreeDBDiscList;

	os << *Base << std::endl;

	for (int count=0;count<FreeDBDiscList.NumItems();count++)
	{
		MusicBrainz4::CFreeDBDisc *Item=FreeDBDiscList.Item(count);

		os << *Item;
	}

	return os;
}
