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

#include "musicbrainz4/TagList.h"

#include "musicbrainz4/Tag.h"

class MusicBrainz4::CTagListPrivate
{
	public:
};

MusicBrainz4::CTagList::CTagList(const XMLNode& Node)
:	CList(),
	m_d(new CTagListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "TagList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CTagList::CTagList(const CTagList& Other)
:	CList(),
	m_d(new CTagListPrivate)
{
	*this=Other;
}

MusicBrainz4::CTagList& MusicBrainz4::CTagList::operator =(const CTagList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CTagList::~CTagList()
{
	delete m_d;
}

MusicBrainz4::CTagList *MusicBrainz4::CTagList::Clone()
{
	return new CTagList(*this);
}

bool MusicBrainz4::CTagList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CTagList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("tag"==NodeName)
	{
		CTag *Item=0;

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

std::string MusicBrainz4::CTagList::ElementName() const
{
	return "tag-list";
}

MusicBrainz4::CTag *MusicBrainz4::CTagList::Item(int Item) const
{
	return dynamic_cast<CTag *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CTagList& TagList)
{
	os << "Tag list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&TagList;

	os << *Base << std::endl;

	for (int count=0;count<TagList.NumItems();count++)
	{
		MusicBrainz4::CTag *Item=TagList.Item(count);

		os << *Item;
	}

	return os;
}
