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

#include "musicbrainz4/NameCreditList.h"

#include "musicbrainz4/NameCredit.h"

class MusicBrainz4::CNameCreditListPrivate
{
	public:
};

MusicBrainz4::CNameCreditList::CNameCreditList(const XMLNode& Node)
:	CList(),
	m_d(new CNameCreditListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "NameCreditList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CNameCreditList::CNameCreditList(const CNameCreditList& Other)
:	CList(),
	m_d(new CNameCreditListPrivate)
{
	*this=Other;
}

MusicBrainz4::CNameCreditList& MusicBrainz4::CNameCreditList::operator =(const CNameCreditList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CNameCreditList::~CNameCreditList()
{
	delete m_d;
}

MusicBrainz4::CNameCreditList *MusicBrainz4::CNameCreditList::Clone()
{
	return new CNameCreditList(*this);
}

bool MusicBrainz4::CNameCreditList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CNameCreditList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("name-credit"==NodeName)
	{
		CNameCredit *Item=0;

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

std::string MusicBrainz4::CNameCreditList::ElementName() const
{
	return "name-credit-list";
}

MusicBrainz4::CNameCredit *MusicBrainz4::CNameCreditList::Item(int Item) const
{
	return dynamic_cast<CNameCredit *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CNameCreditList& NameCreditList)
{
	os << "NameCredit list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&NameCreditList;

	os << *Base << std::endl;

	for (int count=0;count<NameCreditList.NumItems();count++)
	{
		MusicBrainz4::CNameCredit *Item=NameCreditList.Item(count);

		os << *Item;
	}

	return os;
}
