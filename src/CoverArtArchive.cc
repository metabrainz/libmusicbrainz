/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2017 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

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

#include "musicbrainz5/CoverArtArchive.h"

#include "musicbrainz5/OffsetList.h"
#include "musicbrainz5/Offset.h"
#include "musicbrainz5/ReleaseList.h"
#include "musicbrainz5/Release.h"

class MusicBrainz5::CCoverArtArchivePrivate
{
	public:
		CCoverArtArchivePrivate()
		{
		}

		std::string m_Artwork;
		int m_Count;
		std::string m_Front;
		std::string m_Back;
		std::string m_Darkened;
};

MusicBrainz5::CCoverArtArchive::CCoverArtArchive(const XMLNode& Node)
:	CEntity(),
	m_d(new CCoverArtArchivePrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "CoverArtArchive node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CCoverArtArchive::CCoverArtArchive(const CCoverArtArchive& Other)
:	CEntity(),
	m_d(new CCoverArtArchivePrivate)
{
	*this=Other;
}

MusicBrainz5::CCoverArtArchive& MusicBrainz5::CCoverArtArchive::operator =(const CCoverArtArchive& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_Artwork=Other.m_d->m_Artwork;
		m_d->m_Count=Other.m_d->m_Count;
		m_d->m_Front=Other.m_d->m_Front;
		m_d->m_Back=Other.m_d->m_Back;
		m_d->m_Darkened=Other.m_d->m_Darkened;
	}

	return *this;
}

MusicBrainz5::CCoverArtArchive::~CCoverArtArchive()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CCoverArtArchive::Cleanup()
{
}

MusicBrainz5::CCoverArtArchive *MusicBrainz5::CCoverArtArchive::Clone()
{
	return new CCoverArtArchive(*this);
}

void MusicBrainz5::CCoverArtArchive::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
#ifdef _MB5_DEBUG_
	std::cerr << "Unrecognised CoverArtArchive attribute: '" << Name << "'" << std::endl;
#else
	(void)Name;
#endif
}

void MusicBrainz5::CCoverArtArchive::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	if ("artwork"==NodeName)
		ProcessItem(Node,m_d->m_Artwork);
	else if ("count"==NodeName)
		ProcessItem(Node,m_d->m_Count);
	else if ("front"==NodeName)
		ProcessItem(Node,m_d->m_Front);
	else if ("back"==NodeName)
		ProcessItem(Node,m_d->m_Back);
	else if ("darkened"==NodeName)
		ProcessItem(Node,m_d->m_Darkened);
	else
	{
#ifdef _MB5_DEBUG_
		std::cerr << "Unrecognised CoverArtArchive element: '" << NodeName << "'" << std::endl;
#endif
	}
}

std::string MusicBrainz5::CCoverArtArchive::GetElementName()
{
	return "cover-art-archive";
}

std::string MusicBrainz5::CCoverArtArchive::Artwork() const
{
	return m_d->m_Artwork;
}

int MusicBrainz5::CCoverArtArchive::Count() const
{
	return m_d->m_Count;
}

std::string MusicBrainz5::CCoverArtArchive::Front() const
{
	return m_d->m_Front;
}

std::string MusicBrainz5::CCoverArtArchive::Back() const
{
	return m_d->m_Back;
}

std::string MusicBrainz5::CCoverArtArchive::Darkened() const
{
	return m_d->m_Darkened;
}

std::ostream& MusicBrainz5::CCoverArtArchive::Serialise(std::ostream& os) const
{
	os << "CoverArtArchive:" << std::endl;

	CEntity::Serialise(os);

	os << "\tArtwork:  " << Artwork() << std::endl;
	os << "\tCount:    " << Count() << std::endl;
	os << "\tFront:    " << Front() << std::endl;
	os << "\tBack:     " << Back() << std::endl;
	os << "\tDarkened: " << Darkened() << std::endl;

	return os;
}

