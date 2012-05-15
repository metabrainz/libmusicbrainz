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

#include "musicbrainz5/NonMBTrack.h"

class MusicBrainz5::CNonMBTrackPrivate
{
	public:
		CNonMBTrackPrivate()
		:	m_Length(0)
		{
		}

		std::string m_Title;
		std::string m_Artist;
		int m_Length;
};

MusicBrainz5::CNonMBTrack::CNonMBTrack(const XMLNode& Node)
:	CEntity(),
	m_d(new CNonMBTrackPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "NonMBTrack node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CNonMBTrack::CNonMBTrack(const CNonMBTrack& Other)
:	CEntity(),
	m_d(new CNonMBTrackPrivate)
{
	*this=Other;
}

MusicBrainz5::CNonMBTrack& MusicBrainz5::CNonMBTrack::operator =(const CNonMBTrack& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_Title=Other.m_d->m_Title;
		m_d->m_Artist=Other.m_d->m_Artist;
		m_d->m_Length=Other.m_d->m_Length;
	}

	return *this;
}

MusicBrainz5::CNonMBTrack::~CNonMBTrack()
{
	delete m_d;
}

MusicBrainz5::CNonMBTrack *MusicBrainz5::CNonMBTrack::Clone()
{
	return new CNonMBTrack(*this);
}

bool MusicBrainz5::CNonMBTrack::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	bool RetVal=true;

	std::cerr << "Unrecognised non MB track attribute: '" << Name << "'" << std::endl;
	RetVal=false;

	return RetVal;
}

bool MusicBrainz5::CNonMBTrack::ParseElement(const XMLNode& Node)
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
	else if ("length"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Length);
	}
	else
	{
		std::cerr << "Unrecognised non MB track element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz5::CNonMBTrack::GetElementName()
{
	return "track";
}

std::string MusicBrainz5::CNonMBTrack::Title() const
{
	return m_d->m_Title;
}

std::string MusicBrainz5::CNonMBTrack::Artist() const
{
	return m_d->m_Artist;
}

int MusicBrainz5::CNonMBTrack::Length() const
{
	return m_d->m_Length;
}

std::ostream& MusicBrainz5::CNonMBTrack::Serialise(std::ostream& os) const
{
	os << "NonMBTrack:" << std::endl;

	CEntity::Serialise(os);

	os << "\tTitle:  " << Title() << std::endl;
	os << "\tArtist: " << Artist() << std::endl;
	os << "\tLength: " << Length() << std::endl;

	return os;
}
