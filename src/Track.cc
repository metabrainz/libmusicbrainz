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

#include "musicbrainz5/Track.h"

#include "musicbrainz5/Recording.h"
#include "musicbrainz5/ArtistCredit.h"

class MusicBrainz5::CTrackPrivate
{
	public:
		CTrackPrivate()
		:	m_Position(0),
			m_Recording(0),
			m_Length(0),
			m_ArtistCredit(0)
		{
		}

		int m_Position;
		std::string m_Title;
		CRecording *m_Recording;
		int m_Length;
		CArtistCredit *m_ArtistCredit;
		std::string m_Number;
};

MusicBrainz5::CTrack::CTrack(const XMLNode& Node)
:	CEntity(),
	m_d(new CTrackPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Track node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CTrack::CTrack(const CTrack& Other)
:	CEntity(),
	m_d(new CTrackPrivate)
{
	*this=Other;
}

MusicBrainz5::CTrack& MusicBrainz5::CTrack::operator =(const CTrack& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_Position=Other.m_d->m_Position;
		m_d->m_Title=Other.m_d->m_Title;

		if (Other.m_d->m_Recording)
			m_d->m_Recording=new CRecording(*Other.m_d->m_Recording);

		m_d->m_Length=Other.m_d->m_Length;

		if (Other.m_d->m_ArtistCredit)
			m_d->m_ArtistCredit=new CArtistCredit(*Other.m_d->m_ArtistCredit);

		m_d->m_Number=Other.m_d->m_Number;
	}

	return *this;
}

MusicBrainz5::CTrack::~CTrack()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CTrack::Cleanup()
{
	delete m_d->m_Recording;
	m_d->m_Recording=0;

	delete m_d->m_ArtistCredit;
	m_d->m_ArtistCredit=0;
}

MusicBrainz5::CTrack *MusicBrainz5::CTrack::Clone()
{
	return new CTrack(*this);
}

bool MusicBrainz5::CTrack::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	bool RetVal=true;

	std::cerr << "Unrecognised track attribute: '" << Name << "'" << std::endl;
	RetVal=false;

	return RetVal;
}

bool MusicBrainz5::CTrack::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("position"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Position);
	}
	else if ("title"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Title);
	}
	else if ("recording"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Recording);
	}
	else if ("length"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Length);
	}
	else if ("artist-credit"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ArtistCredit);
	}
	else if ("number"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Number);
	}
	else
	{
		std::cerr << "Unrecognised track element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz5::CTrack::GetElementName()
{
	return "track";
}

int MusicBrainz5::CTrack::Position() const
{
	return m_d->m_Position;
}

std::string MusicBrainz5::CTrack::Title() const
{
	return m_d->m_Title;
}

MusicBrainz5::CRecording *MusicBrainz5::CTrack::Recording() const
{
	return m_d->m_Recording;
}

int MusicBrainz5::CTrack::Length() const
{
	return m_d->m_Length;
}

MusicBrainz5::CArtistCredit *MusicBrainz5::CTrack::ArtistCredit() const
{
	return m_d->m_ArtistCredit;
}

std::string MusicBrainz5::CTrack::Number() const
{
	return m_d->m_Number;
}

std::ostream& MusicBrainz5::CTrack::Serialise(std::ostream& os) const
{
	os << "Track:" << std::endl;

	CEntity::Serialise(os);

	os << "\tPosition: " << Position() << std::endl;
	os << "\tTitle:    " << Title() << std::endl;

	if (Recording())
		os << *Recording() << std::endl;

	os << "\tLength:   " << Length() << std::endl;

	if (ArtistCredit())
		os << *ArtistCredit() << std::endl;

	os << "\tNumber:   " << Number() << std::endl;

	return os;
}
