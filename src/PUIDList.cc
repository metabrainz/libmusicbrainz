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

#include "musicbrainz4/PUIDList.h"

#include "musicbrainz4/PUID.h"

class MusicBrainz4::CPUIDListPrivate
{
	public:
};

MusicBrainz4::CPUIDList::CPUIDList(const XMLNode& Node)
:	CList(),
	m_d(new CPUIDListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "PUIDList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CPUIDList::CPUIDList(const CPUIDList& Other)
:	CList(),
	m_d(new CPUIDListPrivate)
{
	*this=Other;
}

MusicBrainz4::CPUIDList& MusicBrainz4::CPUIDList::operator =(const CPUIDList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CPUIDList::~CPUIDList()
{
	delete m_d;
}

MusicBrainz4::CPUIDList *MusicBrainz4::CPUIDList::Clone()
{
	return new CPUIDList(*this);
}

bool MusicBrainz4::CPUIDList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CPUIDList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("puid"==NodeName)
	{
		CPUID *Item=0;

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

std::string MusicBrainz4::CPUIDList::ElementName() const
{
	return "puid-list";
}

MusicBrainz4::CPUID *MusicBrainz4::CPUIDList::Item(int Item) const
{
	return dynamic_cast<CPUID *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CPUIDList& PUIDList)
{
	os << "PUID list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&PUIDList;

	os << *Base << std::endl;

	for (int count=0;count<PUIDList.NumItems();count++)
	{
		MusicBrainz4::CPUID *Item=PUIDList.Item(count);

		os << *Item;
	}

	return os;
}
