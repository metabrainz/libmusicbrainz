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

#include "musicbrainz4/RecordingList.h"

#include "musicbrainz4/Recording.h"

class MusicBrainz4::CRecordingListPrivate
{
	public:
};

MusicBrainz4::CRecordingList::CRecordingList(const XMLNode& Node)
:	CList(),
	m_d(new CRecordingListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "RecordingList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CRecordingList::CRecordingList(const CRecordingList& Other)
:	CList(),
	m_d(new CRecordingListPrivate)
{
	*this=Other;
}

MusicBrainz4::CRecordingList& MusicBrainz4::CRecordingList::operator =(const CRecordingList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CRecordingList::~CRecordingList()
{
	delete m_d;
}

MusicBrainz4::CRecordingList *MusicBrainz4::CRecordingList::Clone()
{
	return new CRecordingList(*this);
}

bool MusicBrainz4::CRecordingList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CRecordingList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("recording"==NodeName)
	{
		CRecording *Item=0;

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

std::string MusicBrainz4::CRecordingList::ElementName() const
{
	return "recording-list";
}

MusicBrainz4::CRecording *MusicBrainz4::CRecordingList::Item(int Item) const
{
	return dynamic_cast<CRecording *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CRecordingList& RecordingList)
{
	os << "Recording list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&RecordingList;

	os << *Base << std::endl;

	for (int count=0;count<RecordingList.NumItems();count++)
	{
		MusicBrainz4::CRecording *Item=RecordingList.Item(count);

		os << *Item;
	}

	return os;
}
