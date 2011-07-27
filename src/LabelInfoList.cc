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

#include "musicbrainz4/LabelInfoList.h"

#include "musicbrainz4/LabelInfo.h"

class MusicBrainz4::CLabelInfoListPrivate
{
	public:
};

MusicBrainz4::CLabelInfoList::CLabelInfoList(const XMLNode& Node)
:	CList(),
	m_d(new CLabelInfoListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "LabelInfoList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CLabelInfoList::CLabelInfoList(const CLabelInfoList& Other)
:	CList(),
	m_d(new CLabelInfoListPrivate)
{
	*this=Other;
}

MusicBrainz4::CLabelInfoList& MusicBrainz4::CLabelInfoList::operator =(const CLabelInfoList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CLabelInfoList::~CLabelInfoList()
{
	delete m_d;
}

MusicBrainz4::CLabelInfoList *MusicBrainz4::CLabelInfoList::Clone()
{
	return new CLabelInfoList(*this);
}

bool MusicBrainz4::CLabelInfoList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CLabelInfoList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("label-info"==NodeName)
	{
		CLabelInfo *Item=0;

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

std::string MusicBrainz4::CLabelInfoList::ElementName() const
{
	return "label-info-list";
}

MusicBrainz4::CLabelInfo *MusicBrainz4::CLabelInfoList::Item(int Item) const
{
	return dynamic_cast<CLabelInfo *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CLabelInfoList& LabelInfoList)
{
	os << "LabelInfo list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&LabelInfoList;

	os << *Base << std::endl;

	for (int count=0;count<LabelInfoList.NumItems();count++)
	{
		MusicBrainz4::CLabelInfo *Item=LabelInfoList.Item(count);

		os << *Item;
	}

	return os;
}
