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

#include "musicbrainz4/LabelList.h"

#include "musicbrainz4/Label.h"

class MusicBrainz4::CLabelListPrivate
{
	public:
};

MusicBrainz4::CLabelList::CLabelList(const XMLNode& Node)
:	CList(),
	m_d(new CLabelListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "LabelList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CLabelList::CLabelList(const CLabelList& Other)
:	CList(),
	m_d(new CLabelListPrivate)
{
	*this=Other;
}

MusicBrainz4::CLabelList& MusicBrainz4::CLabelList::operator =(const CLabelList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CLabelList::~CLabelList()
{
	delete m_d;
}

MusicBrainz4::CLabelList *MusicBrainz4::CLabelList::Clone()
{
	return new CLabelList(*this);
}

bool MusicBrainz4::CLabelList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CLabelList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("label"==NodeName)
	{
		CLabel *Item=0;

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

std::string MusicBrainz4::CLabelList::ElementName() const
{
	return "label-list";
}

MusicBrainz4::CLabel *MusicBrainz4::CLabelList::Item(int Item) const
{
	return dynamic_cast<CLabel *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CLabelList& LabelList)
{
	os << "Label list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&LabelList;

	os << *Base << std::endl;

	for (int count=0;count<LabelList.NumItems();count++)
	{
		MusicBrainz4::CLabel *Item=LabelList.Item(count);

		os << *Item;
	}

	return os;
}
