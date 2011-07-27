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

#include "musicbrainz4/AttributeList.h"

#include "musicbrainz4/Attribute.h"

class MusicBrainz4::CAttributeListPrivate
{
	public:
};

MusicBrainz4::CAttributeList::CAttributeList(const XMLNode& Node)
:	CList(),
	m_d(new CAttributeListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "AttributeList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CAttributeList::CAttributeList(const CAttributeList& Other)
:	CList(),
	m_d(new CAttributeListPrivate)
{
	*this=Other;
}

MusicBrainz4::CAttributeList& MusicBrainz4::CAttributeList::operator =(const CAttributeList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CAttributeList::~CAttributeList()
{
	delete m_d;
}

MusicBrainz4::CAttributeList *MusicBrainz4::CAttributeList::Clone()
{
	return new CAttributeList(*this);
}

bool MusicBrainz4::CAttributeList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CAttributeList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("attribute"==NodeName)
	{
		CAttribute *Item=0;

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

std::string MusicBrainz4::CAttributeList::ElementName() const
{
	return "attribute-list";
}

MusicBrainz4::CAttribute *MusicBrainz4::CAttributeList::Item(int Item) const
{
	return dynamic_cast<CAttribute *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CAttributeList& AttributeList)
{
	os << "Attribute list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&AttributeList;

	os << *Base << std::endl;

	for (int count=0;count<AttributeList.NumItems();count++)
	{
		MusicBrainz4::CAttribute *Item=AttributeList.Item(count);

		os << *Item;
	}

	return os;
}
