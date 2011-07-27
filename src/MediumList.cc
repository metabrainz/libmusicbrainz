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

#include "musicbrainz4/MediumList.h"

#include "musicbrainz4/Medium.h"

class MusicBrainz4::CMediumListPrivate
{
	public:
		CMediumListPrivate()
		:	m_TrackCount(0)
		{
		}

		int m_TrackCount;
};

MusicBrainz4::CMediumList::CMediumList(const XMLNode& Node)
:	CList(),
	m_d(new CMediumListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "MediumList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CMediumList::CMediumList(const CMediumList& Other)
:	CList(),
	m_d(new CMediumListPrivate)
{
	*this=Other;
}

MusicBrainz4::CMediumList& MusicBrainz4::CMediumList::operator =(const CMediumList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);

		m_d->m_TrackCount=Other.m_d->m_TrackCount;
	}

	return *this;
}

MusicBrainz4::CMediumList::~CMediumList()
{
	delete m_d;
}

MusicBrainz4::CMediumList *MusicBrainz4::CMediumList::Clone()
{
	return new CMediumList(*this);
}

bool MusicBrainz4::CMediumList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CMediumList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("track-count"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_TrackCount);
	}
	else if ("medium"==NodeName)
	{
		CMedium *Item=0;

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

std::string MusicBrainz4::CMediumList::ElementName() const
{
	return "medium-list";
}

int MusicBrainz4::CMediumList::TrackCount() const
{
	return m_d->m_TrackCount;
}

MusicBrainz4::CMedium *MusicBrainz4::CMediumList::Item(int Item) const
{
	return dynamic_cast<CMedium *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CMediumList& MediumList)
{
	os << "Medium list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&MediumList;

	os << *Base << std::endl;

	os << "\tTrack count: " << MediumList.TrackCount() << std::endl;

	for (int count=0;count<MediumList.NumItems();count++)
	{
		MusicBrainz4::CMedium *Item=MediumList.Item(count);

		os << *Item;
	}

	return os;
}
