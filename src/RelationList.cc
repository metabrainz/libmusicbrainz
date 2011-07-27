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

#include "musicbrainz4/RelationList.h"

#include "musicbrainz4/Relation.h"

class MusicBrainz4::CRelationListPrivate
{
	public:
		std::string m_TargetType;
};

MusicBrainz4::CRelationList::CRelationList(const XMLNode& Node)
:	CList(),
	m_d(new CRelationListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "RelationList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CRelationList::CRelationList(const CRelationList& Other)
:	CList(),
	m_d(new CRelationListPrivate)
{
	*this=Other;
}

MusicBrainz4::CRelationList& MusicBrainz4::CRelationList::operator =(const CRelationList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);

		m_d->m_TargetType=Other.m_d->m_TargetType;
	}

	return *this;
}

MusicBrainz4::CRelationList::~CRelationList()
{
	delete m_d;
}

MusicBrainz4::CRelationList *MusicBrainz4::CRelationList::Clone()
{
	return new CRelationList(*this);
}

bool MusicBrainz4::CRelationList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("target-type"==Name)
		RetVal=ProcessItem(Name,m_d->m_TargetType);
	else
		RetVal=CList::ParseAttribute(Name,Value);

	return RetVal;
}

bool MusicBrainz4::CRelationList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("relation"==NodeName)
	{
		CRelation *Item=0;

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

std::string MusicBrainz4::CRelationList::ElementName() const
{
	return "relation-list";
}

std::string MusicBrainz4::CRelationList::TargetType() const
{
	return m_d->m_TargetType;
}

MusicBrainz4::CRelation *MusicBrainz4::CRelationList::Item(int Item) const
{
	return dynamic_cast<CRelation *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CRelationList& RelationList)
{
	os << "Relation list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&RelationList;

	os << *Base << std::endl;

	os << "\tTarget type: " << RelationList.TargetType() << std::endl;

	for (int count=0;count<RelationList.NumItems();count++)
	{
		MusicBrainz4::CRelation *Item=RelationList.Item(count);

		os << *Item;
	}

	return os;
}
