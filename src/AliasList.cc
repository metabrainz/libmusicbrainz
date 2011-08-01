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

#include "musicbrainz4/AliasList.h"

#include "musicbrainz4/Alias.h"

class MusicBrainz4::CAliasListPrivate
{
	public:
};

MusicBrainz4::CAliasList::CAliasList(const XMLNode& Node)
:	CList(),
	m_d(new CAliasListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "AliasList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CAliasList::CAliasList(const CAliasList& Other)
:	CList(),
	m_d(new CAliasListPrivate)
{
	*this=Other;
}

MusicBrainz4::CAliasList& MusicBrainz4::CAliasList::operator =(const CAliasList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CAliasList::~CAliasList()
{
	delete m_d;
}

MusicBrainz4::CAliasList *MusicBrainz4::CAliasList::Clone()
{
	return new CAliasList(*this);
}

bool MusicBrainz4::CAliasList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CAliasList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("alias"==NodeName)
	{
		CAlias *Item=0;

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

std::string MusicBrainz4::CAliasList::GetElementName()
{
	return "alias-list";
}

MusicBrainz4::CAlias *MusicBrainz4::CAliasList::Item(int Item) const
{
	return dynamic_cast<CAlias *>(CList::Item(Item));
}

std::ostream& MusicBrainz4::CAliasList::Serialise(std::ostream& os) const
{
	os << "Alias list:" << std::endl;

	CList::Serialise(os);

	for (int count=0;count<NumItems();count++)
	{
		MusicBrainz4::CAlias *ThisItem=Item(count);

		os << *ThisItem;
	}

	return os;
}
