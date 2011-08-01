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

#include "musicbrainz4/CollectionList.h"

#include "musicbrainz4/Collection.h"

class MusicBrainz4::CCollectionListPrivate
{
	public:
};

MusicBrainz4::CCollectionList::CCollectionList(const XMLNode& Node)
:	CList(),
	m_d(new CCollectionListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "CollectionList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CCollectionList::CCollectionList(const CCollectionList& Other)
:	CList(),
	m_d(new CCollectionListPrivate)
{
	*this=Other;
}

MusicBrainz4::CCollectionList& MusicBrainz4::CCollectionList::operator =(const CCollectionList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CCollectionList::~CCollectionList()
{
	delete m_d;
}

MusicBrainz4::CCollectionList *MusicBrainz4::CCollectionList::Clone()
{
	return new CCollectionList(*this);
}

bool MusicBrainz4::CCollectionList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CCollectionList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("collection"==NodeName)
	{
		CCollection *Item=0;

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

std::string MusicBrainz4::CCollectionList::GetElementName()
{
	return "collection-list";
}

MusicBrainz4::CCollection *MusicBrainz4::CCollectionList::Item(int Item) const
{
	return dynamic_cast<CCollection *>(CList::Item(Item));
}

std::ostream& MusicBrainz4::CCollectionList::Serialise(std::ostream& os) const
{
	os << "Collection list:" << std::endl;

	CList::Serialise(os);

	for (int count=0;count<NumItems();count++)
	{
		MusicBrainz4::CCollection *ThisItem=Item(count);

		os << *ThisItem;
	}

	return os;
}
