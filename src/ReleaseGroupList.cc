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

#include "musicbrainz4/ReleaseGroupList.h"

#include "musicbrainz4/ReleaseGroup.h"

class MusicBrainz4::CReleaseGroupListPrivate
{
	public:
};

MusicBrainz4::CReleaseGroupList::CReleaseGroupList(const XMLNode& Node)
:	CList(),
	m_d(new CReleaseGroupListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "ReleaseGroupList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CReleaseGroupList::CReleaseGroupList(const CReleaseGroupList& Other)
:	CList(),
	m_d(new CReleaseGroupListPrivate)
{
	*this=Other;
}

MusicBrainz4::CReleaseGroupList& MusicBrainz4::CReleaseGroupList::operator =(const CReleaseGroupList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CReleaseGroupList::~CReleaseGroupList()
{
	delete m_d;
}

MusicBrainz4::CReleaseGroupList *MusicBrainz4::CReleaseGroupList::Clone()
{
	return new CReleaseGroupList(*this);
}

bool MusicBrainz4::CReleaseGroupList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CReleaseGroupList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("release-group"==NodeName)
	{
		CReleaseGroup *Item=0;

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

std::string MusicBrainz4::CReleaseGroupList::ElementName() const
{
	return "release-group-list";
}

MusicBrainz4::CReleaseGroup *MusicBrainz4::CReleaseGroupList::Item(int Item) const
{
	return dynamic_cast<CReleaseGroup *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CReleaseGroupList& ReleaseGroupList)
{
	os << "ReleaseGroup list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&ReleaseGroupList;

	os << *Base << std::endl;

	for (int count=0;count<ReleaseGroupList.NumItems();count++)
	{
		MusicBrainz4::CReleaseGroup *Item=ReleaseGroupList.Item(count);

		os << *Item;
	}

	return os;
}
