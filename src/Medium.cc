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

#include "musicbrainz5/Medium.h"

#include "musicbrainz5/Disc.h"
#include "musicbrainz5/DiscList.h"
#include "musicbrainz5/Track.h"
#include "musicbrainz5/TrackList.h"

class MusicBrainz5::CMediumPrivate
{
	public:
		CMediumPrivate()
		:	m_Position(0),
			m_DiscList(0),
			m_TrackList(0)
		{
		}

		std::string m_Title;
		int m_Position;
		std::string m_Format;
		CDiscList *m_DiscList;
		CTrackList *m_TrackList;
};

MusicBrainz5::CMedium::CMedium(const XMLNode& Node)
:	CEntity(),
	m_d(new CMediumPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Medium node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CMedium::CMedium(const CMedium& Other)
:	CEntity(),
	m_d(new CMediumPrivate)
{
	*this=Other;
}

MusicBrainz5::CMedium& MusicBrainz5::CMedium::operator =(const CMedium& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_Title=Other.m_d->m_Title;
		m_d->m_Position=Other.m_d->m_Position;
		m_d->m_Format=Other.m_d->m_Format;

		if (Other.m_d->m_DiscList)
			m_d->m_DiscList=new CDiscList(*Other.m_d->m_DiscList);

		if (Other.m_d->m_TrackList)
			m_d->m_TrackList=new CTrackList(*Other.m_d->m_TrackList);
	}

	return *this;
}

MusicBrainz5::CMedium::~CMedium()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CMedium::Cleanup()
{
	delete m_d->m_DiscList;
	m_d->m_DiscList=0;

	delete m_d->m_TrackList;
	m_d->m_TrackList=0;
}

MusicBrainz5::CMedium *MusicBrainz5::CMedium::Clone()
{
	return new CMedium(*this);
}

bool MusicBrainz5::CMedium::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	bool RetVal=true;

	std::cerr << "Unrecognised medium attribute: '" << Name << "'" << std::endl;
	RetVal=false;

	return RetVal;
}

bool MusicBrainz5::CMedium::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("title"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Title);
	}
	else if ("position"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Position);
	}
	else if ("format"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Format);
	}
	else if ("disc-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_DiscList);
	}
	else if ("track-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_TrackList);
	}
	else
	{
		std::cerr << "Unrecognised medium element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz5::CMedium::GetElementName()
{
	return "medium";
}

std::string MusicBrainz5::CMedium::Title() const
{
	return m_d->m_Title;
}

int MusicBrainz5::CMedium::Position() const
{
	return m_d->m_Position;
}

std::string MusicBrainz5::CMedium::Format() const
{
	return m_d->m_Format;
}

MusicBrainz5::CDiscList *MusicBrainz5::CMedium::DiscList() const
{
	return m_d->m_DiscList;
}

MusicBrainz5::CTrackList *MusicBrainz5::CMedium::TrackList() const
{
	return m_d->m_TrackList;
}

bool MusicBrainz5::CMedium::ContainsDiscID(const std::string& DiscID) const
{
	bool RetVal=false;

	if (m_d->m_DiscList)
	{
		for (int count=0;!RetVal && count<m_d->m_DiscList->NumItems();count++)
		{
			CDisc *Disc=m_d->m_DiscList->Item(count);

			if (Disc->ID()==DiscID)
				RetVal=true;
		}
	}

	return RetVal;
}

std::ostream& MusicBrainz5::CMedium::Serialise(std::ostream& os) const
{
	os << "Medium:" << std::endl;

	CEntity::Serialise(os);

	os << "\tTitle:    " << Title() << std::endl;
	os << "\tPosition: " << Position() << std::endl;
	os << "\tFormat:   " << Format() << std::endl;

	if (DiscList())
		os << *DiscList() << std::endl;

	if (TrackList())
		os << *TrackList() << std::endl;

	return os;
}
