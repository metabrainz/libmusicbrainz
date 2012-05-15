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

#include "musicbrainz5/FreeDBDisc.h"

#include "musicbrainz5/NonMBTrackList.h"
#include "musicbrainz5/NonMBTrack.h"

class MusicBrainz5::CFreeDBDiscPrivate
{
	public:
		CFreeDBDiscPrivate()
		:	m_NonMBTrackList(0)
		{
		}

		std::string m_ID;
		std::string m_Title;
		std::string m_Artist;
		std::string m_Category;
		std::string m_Year;
		CNonMBTrackList *m_NonMBTrackList;
};

MusicBrainz5::CFreeDBDisc::CFreeDBDisc(const XMLNode& Node)
:	CEntity(),
	m_d(new CFreeDBDiscPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "FreeDBDisc node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CFreeDBDisc::CFreeDBDisc(const CFreeDBDisc& Other)
:	CEntity(),
	m_d(new CFreeDBDiscPrivate)
{
	*this=Other;
}

MusicBrainz5::CFreeDBDisc& MusicBrainz5::CFreeDBDisc::operator =(const CFreeDBDisc& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Title=Other.m_d->m_Title;
		m_d->m_Artist=Other.m_d->m_Artist;
		m_d->m_Category=Other.m_d->m_Category;
		m_d->m_Year=Other.m_d->m_Year;

		if (Other.m_d->m_NonMBTrackList)
			m_d->m_NonMBTrackList=new CNonMBTrackList(*Other.m_d->m_NonMBTrackList);
	}

	return *this;
}

MusicBrainz5::CFreeDBDisc::~CFreeDBDisc()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CFreeDBDisc::Cleanup()
{
	delete m_d->m_NonMBTrackList;
	m_d->m_NonMBTrackList=0;
}

MusicBrainz5::CFreeDBDisc *MusicBrainz5::CFreeDBDisc::Clone()
{
	return new CFreeDBDisc(*this);
}

bool MusicBrainz5::CFreeDBDisc::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;


	if ("id"==Name)
		m_d->m_ID=Value;
	else
	{
		std::cerr << "Unrecognised freedb disc attribute: '" << Name << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

bool MusicBrainz5::CFreeDBDisc::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("title"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Title);
	}
	else if ("artist"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Artist);
	}
	else if ("category"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Category);
	}
	else if ("year"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Year);
	}
	else if ("nonmb-track-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_NonMBTrackList);
	}
	else
	{
		std::cerr << "Unrecognised freedb disc element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz5::CFreeDBDisc::GetElementName()
{
	return "freedb-disc";
}

std::string MusicBrainz5::CFreeDBDisc::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz5::CFreeDBDisc::Title() const
{
	return m_d->m_Title;
}

std::string MusicBrainz5::CFreeDBDisc::Artist() const
{
	return m_d->m_Artist;
}

std::string MusicBrainz5::CFreeDBDisc::Category() const
{
	return m_d->m_Category;
}

std::string MusicBrainz5::CFreeDBDisc::Year() const
{
	return m_d->m_Year;
}

MusicBrainz5::CNonMBTrackList *MusicBrainz5::CFreeDBDisc::NonMBTrackList() const
{
	return m_d->m_NonMBTrackList;
}

std::ostream& MusicBrainz5::CFreeDBDisc::Serialise(std::ostream& os) const
{
	os << "FreeDBDisc:" << std::endl;

	CEntity::Serialise(os);

	os << "\tID:       " << ID() << std::endl;
	os << "\tTitle:    " << Title() << std::endl;
	os << "\tArtist:   " << Artist() << std::endl;
	os << "\tCategory: " << Category() << std::endl;
	os << "\tYear:     " << Year() << std::endl;

	if (NonMBTrackList())
		os << *NonMBTrackList() << std::endl;

	return os;
}
