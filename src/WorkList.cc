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

#include "musicbrainz4/WorkList.h"

#include "musicbrainz4/Work.h"

class MusicBrainz4::CWorkListPrivate
{
	public:
};

MusicBrainz4::CWorkList::CWorkList(const XMLNode& Node)
:	CList(),
	m_d(new CWorkListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "WorkList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CWorkList::CWorkList(const CWorkList& Other)
:	CList(),
	m_d(new CWorkListPrivate)
{
	*this=Other;
}

MusicBrainz4::CWorkList& MusicBrainz4::CWorkList::operator =(const CWorkList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CWorkList::~CWorkList()
{
	delete m_d;
}

MusicBrainz4::CWorkList *MusicBrainz4::CWorkList::Clone()
{
	return new CWorkList(*this);
}

bool MusicBrainz4::CWorkList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CWorkList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("work"==NodeName)
	{
		CWork *Item=0;

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

std::string MusicBrainz4::CWorkList::ElementName() const
{
	return "work-list";
}

MusicBrainz4::CWork *MusicBrainz4::CWorkList::Item(int Item) const
{
	return dynamic_cast<CWork *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CWorkList& WorkList)
{
	os << "Work list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&WorkList;

	os << *Base << std::endl;

	for (int count=0;count<WorkList.NumItems();count++)
	{
		MusicBrainz4::CWork *Item=WorkList.Item(count);

		os << *Item;
	}

	return os;
}
