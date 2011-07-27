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

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include "musicbrainz4/UserTagList.h"

#include "musicbrainz4/UserTag.h"

class MusicBrainz4::CUserTagListPrivate
{
	public:
};

MusicBrainz4::CUserTagList::CUserTagList(const XMLNode& Node)
:	CList(),
	m_d(new CUserTagListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "UserTagList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CUserTagList::CUserTagList(const CUserTagList& Other)
:	CList(),
	m_d(new CUserTagListPrivate)
{
	*this=Other;
}

MusicBrainz4::CUserTagList& MusicBrainz4::CUserTagList::operator =(const CUserTagList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CUserTagList::~CUserTagList()
{
	delete m_d;
}

MusicBrainz4::CUserTagList *MusicBrainz4::CUserTagList::Clone()
{
	return new CUserTagList(*this);
}

bool MusicBrainz4::CUserTagList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CUserTagList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("user-tag"==NodeName)
	{
		CUserTag *Item=0;

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

std::string MusicBrainz4::CUserTagList::ElementName() const
{
	return "user-tag-list";
}

MusicBrainz4::CUserTag *MusicBrainz4::CUserTagList::Item(int Item) const
{
	return dynamic_cast<CUserTag *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CUserTagList& UserTagList)
{
	os << "UserTag list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&UserTagList;

	os << *Base << std::endl;

	for (int count=0;count<UserTagList.NumItems();count++)
	{
		MusicBrainz4::CUserTag *Item=UserTagList.Item(count);

		os << *Item;
	}

	return os;
}
