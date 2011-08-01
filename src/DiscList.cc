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

#include "musicbrainz4/DiscList.h"

#include "musicbrainz4/Disc.h"

class MusicBrainz4::CDiscListPrivate
{
	public:
};

MusicBrainz4::CDiscList::CDiscList(const XMLNode& Node)
:	CList(),
	m_d(new CDiscListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "DiscList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CDiscList::CDiscList(const CDiscList& Other)
:	CList(),
	m_d(new CDiscListPrivate)
{
	*this=Other;
}

MusicBrainz4::CDiscList& MusicBrainz4::CDiscList::operator =(const CDiscList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CDiscList::~CDiscList()
{
	delete m_d;
}

MusicBrainz4::CDiscList *MusicBrainz4::CDiscList::Clone()
{
	return new CDiscList(*this);
}

bool MusicBrainz4::CDiscList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CDiscList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("disc"==NodeName)
	{
		CDisc *Item=0;

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

std::string MusicBrainz4::CDiscList::GetElementName()
{
	return "disc-list";
}

MusicBrainz4::CDisc *MusicBrainz4::CDiscList::Item(int Item) const
{
	return dynamic_cast<CDisc *>(CList::Item(Item));
}

std::ostream& MusicBrainz4::CDiscList::Serialise(std::ostream& os) const
{
	os << "Disc list:" << std::endl;

	CList::Serialise(os);

	for (int count=0;count<NumItems();count++)
	{
		MusicBrainz4::CDisc *ThisItem=Item(count);

		os << *ThisItem;
	}

	return os;
}
