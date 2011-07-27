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

#include "musicbrainz4/NonMBTrackList.h"

#include "musicbrainz4/NonMBTrack.h"

class MusicBrainz4::CNonMBTrackListPrivate
{
	public:
};

MusicBrainz4::CNonMBTrackList::CNonMBTrackList(const XMLNode& Node)
:	CList(),
	m_d(new CNonMBTrackListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "NonMBTrackList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CNonMBTrackList::CNonMBTrackList(const CNonMBTrackList& Other)
:	CList(),
	m_d(new CNonMBTrackListPrivate)
{
	*this=Other;
}

MusicBrainz4::CNonMBTrackList& MusicBrainz4::CNonMBTrackList::operator =(const CNonMBTrackList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CNonMBTrackList::~CNonMBTrackList()
{
	delete m_d;
}

MusicBrainz4::CNonMBTrackList *MusicBrainz4::CNonMBTrackList::Clone()
{
	return new CNonMBTrackList(*this);
}

bool MusicBrainz4::CNonMBTrackList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CNonMBTrackList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("track"==NodeName)
	{
		CNonMBTrack *Item=0;

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

std::string MusicBrainz4::CNonMBTrackList::ElementName() const
{
	return "track-list";
}

MusicBrainz4::CNonMBTrack *MusicBrainz4::CNonMBTrackList::Item(int Item) const
{
	return dynamic_cast<CNonMBTrack *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CNonMBTrackList& NonMBTrackList)
{
	os << "NonMBTrack list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&NonMBTrackList;

	os << *Base << std::endl;

	for (int count=0;count<NonMBTrackList.NumItems();count++)
	{
		MusicBrainz4::CNonMBTrack *Item=NonMBTrackList.Item(count);

		os << *Item;
	}

	return os;
}
