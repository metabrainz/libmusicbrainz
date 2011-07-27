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

#include "musicbrainz4/CDStubList.h"

#include "musicbrainz4/CDStub.h"

class MusicBrainz4::CCDStubListPrivate
{
	public:
};

MusicBrainz4::CCDStubList::CCDStubList(const XMLNode& Node)
:	CList(),
	m_d(new CCDStubListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "CDStubList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CCDStubList::CCDStubList(const CCDStubList& Other)
:	CList(),
	m_d(new CCDStubListPrivate)
{
	*this=Other;
}

MusicBrainz4::CCDStubList& MusicBrainz4::CCDStubList::operator =(const CCDStubList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CCDStubList::~CCDStubList()
{
	delete m_d;
}

MusicBrainz4::CCDStubList *MusicBrainz4::CCDStubList::Clone()
{
	return new CCDStubList(*this);
}

bool MusicBrainz4::CCDStubList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CCDStubList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("cdstub"==NodeName)
	{
		CCDStub *Item=0;

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

std::string MusicBrainz4::CCDStubList::ElementName() const
{
	return "cdstub-list";
}

MusicBrainz4::CCDStub *MusicBrainz4::CCDStubList::Item(int Item) const
{
	return dynamic_cast<CCDStub *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CCDStubList& CDStubList)
{
	os << "CDStub list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&CDStubList;

	os << *Base << std::endl;

	for (int count=0;count<CDStubList.NumItems();count++)
	{
		MusicBrainz4::CCDStub *Item=CDStubList.Item(count);

		os << *Item;
	}

	return os;
}
