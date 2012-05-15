/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libmusicbrainz5 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include "config.h"
#include "musicbrainz5/defines.h"

#include "musicbrainz5/MediumList.h"

#include "musicbrainz5/Medium.h"

class MusicBrainz5::CMediumListPrivate
{
	public:
		CMediumListPrivate()
		:	m_TrackCount(0)
		{
		}

		int m_TrackCount;
};

MusicBrainz5::CMediumList::CMediumList(const XMLNode& Node)
:	CListImpl<CMedium>(),
	m_d(new CMediumListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "MediumList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CMediumList::CMediumList(const CMediumList& Other)
:	CListImpl<CMedium>(),
	m_d(new CMediumListPrivate)
{
	*this=Other;
}

MusicBrainz5::CMediumList& MusicBrainz5::CMediumList::operator =(const CMediumList& Other)
{
	if (this!=&Other)
	{
		CListImpl<CMedium>::operator =(Other);

		m_d->m_TrackCount=Other.m_d->m_TrackCount;
	}

	return *this;
}

MusicBrainz5::CMediumList::~CMediumList()
{
	delete m_d;
}

MusicBrainz5::CMediumList *MusicBrainz5::CMediumList::Clone()
{
	return new CMediumList(*this);
}

bool MusicBrainz5::CMediumList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CListImpl<CMedium>::ParseAttribute(Name,Value);
}

bool MusicBrainz5::CMediumList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("track-count"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_TrackCount);
	}
	else
	{
		RetVal=CListImpl<CMedium>::ParseElement(Node);
	}

	return RetVal;
}

std::string MusicBrainz5::CMediumList::GetElementName()
{
	return "medium-list";
}

int MusicBrainz5::CMediumList::TrackCount() const
{
	return m_d->m_TrackCount;
}

std::ostream& MusicBrainz5::CMediumList::Serialise(std::ostream& os) const
{
	os << "Medium list:" << std::endl;

	os << "\tTrack count: " << TrackCount() << std::endl;

	CListImpl<CMedium>::Serialise(os);

	return os;
}
