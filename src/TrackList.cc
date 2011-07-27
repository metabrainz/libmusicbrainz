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

#include "musicbrainz4/TrackList.h"

#include "musicbrainz4/Track.h"

class MusicBrainz4::CTrackListPrivate
{
	public:
};

MusicBrainz4::CTrackList::CTrackList(const XMLNode& Node)
:	CList(),
	m_d(new CTrackListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "TrackList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CTrackList::CTrackList(const CTrackList& Other)
:	CList(),
	m_d(new CTrackListPrivate)
{
	*this=Other;
}

MusicBrainz4::CTrackList& MusicBrainz4::CTrackList::operator =(const CTrackList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CTrackList::~CTrackList()
{
	delete m_d;
}

MusicBrainz4::CTrackList *MusicBrainz4::CTrackList::Clone()
{
	return new CTrackList(*this);
}

bool MusicBrainz4::CTrackList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CTrackList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("track"==NodeName)
	{
		CTrack *Item=0;

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

std::string MusicBrainz4::CTrackList::ElementName() const
{
	return "track-list";
}

MusicBrainz4::CTrack *MusicBrainz4::CTrackList::Item(int Item) const
{
	return dynamic_cast<CTrack *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CTrackList& TrackList)
{
	os << "Track list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&TrackList;

	os << *Base << std::endl;

	for (int count=0;count<TrackList.NumItems();count++)
	{
		MusicBrainz4::CTrack *Item=TrackList.Item(count);

		os << *Item;
	}

	return os;
}
