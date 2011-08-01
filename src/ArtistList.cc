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

#include "musicbrainz4/ArtistList.h"

#include "musicbrainz4/Artist.h"

class MusicBrainz4::CArtistListPrivate
{
	public:
};

MusicBrainz4::CArtistList::CArtistList(const XMLNode& Node)
:	CList(),
	m_d(new CArtistListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "ArtistList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CArtistList::CArtistList(const CArtistList& Other)
:	CList(),
	m_d(new CArtistListPrivate)
{
	*this=Other;
}

MusicBrainz4::CArtistList& MusicBrainz4::CArtistList::operator =(const CArtistList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CArtistList::~CArtistList()
{
	delete m_d;
}

MusicBrainz4::CArtistList *MusicBrainz4::CArtistList::Clone()
{
	return new CArtistList(*this);
}

bool MusicBrainz4::CArtistList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CArtistList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("artist"==NodeName)
	{
		CArtist *Item=0;

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

std::string MusicBrainz4::CArtistList::GetElementName()
{
	return "artist-list";
}

MusicBrainz4::CArtist *MusicBrainz4::CArtistList::Item(int Item) const
{
	return dynamic_cast<CArtist *>(CList::Item(Item));
}

std::ostream& MusicBrainz4::CArtistList::Serialise(std::ostream& os) const
{
	os << "Artist list:" << std::endl;

	CList::Serialise(os);

	for (int count=0;count<NumItems();count++)
	{
		MusicBrainz4::CArtist *ThisItem=Item(count);

		os << *ThisItem;
	}

	return os;
}
