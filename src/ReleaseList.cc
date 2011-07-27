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

#include "musicbrainz4/ReleaseList.h"

#include "musicbrainz4/Release.h"

class MusicBrainz4::CReleaseListPrivate
{
	public:
};

MusicBrainz4::CReleaseList::CReleaseList(const XMLNode& Node)
:	CList(),
	m_d(new CReleaseListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "ReleaseList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CReleaseList::CReleaseList(const CReleaseList& Other)
:	CList(),
	m_d(new CReleaseListPrivate)
{
	*this=Other;
}

MusicBrainz4::CReleaseList& MusicBrainz4::CReleaseList::operator =(const CReleaseList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CReleaseList::~CReleaseList()
{
	delete m_d;
}

MusicBrainz4::CReleaseList *MusicBrainz4::CReleaseList::Clone()
{
	return new CReleaseList(*this);
}

bool MusicBrainz4::CReleaseList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CReleaseList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("release"==NodeName)
	{
		CRelease *Item=0;

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

std::string MusicBrainz4::CReleaseList::ElementName() const
{
	return "release-list";
}

MusicBrainz4::CRelease *MusicBrainz4::CReleaseList::Item(int Item) const
{
	return dynamic_cast<CRelease *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CReleaseList& ReleaseList)
{
	os << "Release list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&ReleaseList;

	os << *Base << std::endl;

	for (int count=0;count<ReleaseList.NumItems();count++)
	{
		MusicBrainz4::CRelease *Item=ReleaseList.Item(count);

		os << *Item;
	}

	return os;
}
