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

#include "musicbrainz4/Recording.h"

#include "musicbrainz4/ArtistCredit.h"
#include "musicbrainz4/Rating.h"
#include "musicbrainz4/UserRating.h"
#include "musicbrainz4/ReleaseList.h"
#include "musicbrainz4/PUIDList.h"
#include "musicbrainz4/ISRCList.h"
#include "musicbrainz4/RelationList.h"
#include "musicbrainz4/TagList.h"
#include "musicbrainz4/UserTagList.h"

class MusicBrainz4::CRecordingPrivate
{
	public:
		CRecordingPrivate()
		:	m_Length(0),
			m_ArtistCredit(0),
			m_ReleaseList(0),
			m_PUIDList(0),
			m_ISRCList(0),
			m_RelationList(0),
			m_TagList(0),
			m_UserTagList(0),
			m_Rating(0),
			m_UserRating(0)
		{
		}

		std::string m_ID;
		std::string m_Title;
		int m_Length;
		std::string m_Disambiguation;
		CArtistCredit *m_ArtistCredit;
		CReleaseList *m_ReleaseList;
		CPUIDList *m_PUIDList;
		CISRCList *m_ISRCList;
		CRelationList *m_RelationList;
		CTagList *m_TagList;
		CUserTagList *m_UserTagList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
};

MusicBrainz4::CRecording::CRecording(const XMLNode& Node)
:	CEntity(),
	m_d(new CRecordingPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Metadata node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CRecording::CRecording(const CRecording& Other)
:	CEntity(),
	m_d(new CRecordingPrivate)
{
	*this=Other;
}

MusicBrainz4::CRecording& MusicBrainz4::CRecording::operator =(const CRecording& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Title=Other.m_d->m_Title;
		m_d->m_Length=Other.m_d->m_Length;
		m_d->m_Disambiguation=Other.m_d->m_Disambiguation;

		if (Other.m_d->m_ArtistCredit)
			m_d->m_ArtistCredit=new CArtistCredit(*Other.m_d->m_ArtistCredit);

		if (Other.m_d->m_ReleaseList)
			m_d->m_ReleaseList=new CReleaseList(*Other.m_d->m_ReleaseList);

		if (Other.m_d->m_PUIDList)
			m_d->m_PUIDList=new CPUIDList(*Other.m_d->m_PUIDList);

		if (Other.m_d->m_ISRCList)
			m_d->m_ISRCList=new CISRCList(*Other.m_d->m_ISRCList);

		if (Other.m_d->m_RelationList)
			m_d->m_RelationList=new CRelationList(*Other.m_d->m_RelationList);

		if (Other.m_d->m_TagList)
			m_d->m_TagList=new CTagList(*Other.m_d->m_TagList);

		if (Other.m_d->m_UserTagList)
			m_d->m_UserTagList=new CUserTagList(*Other.m_d->m_UserTagList);

		if (Other.m_d->m_Rating)
			m_d->m_Rating=new CRating(*Other.m_d->m_Rating);

		if (Other.m_d->m_UserRating)
			m_d->m_UserRating=new CUserRating(*Other.m_d->m_UserRating);
	}

	return *this;
}

MusicBrainz4::CRecording::~CRecording()
{
	Cleanup();

	delete m_d;
}

MusicBrainz4::CRecording *MusicBrainz4::CRecording::Clone()
{
	return new CRecording(*this);
}

bool MusicBrainz4::CRecording::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("id"==Name)
		m_d->m_ID=Value;
	else
	{
		std::cerr << "Unrecognised recording attribute: '" << Name << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

bool MusicBrainz4::CRecording::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("title"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Title);
	}
	else if ("length"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Length);
	}
	else if ("disambiguation"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Disambiguation);
	}
	else if ("artist-credit"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ArtistCredit);
	}
	else if ("release-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ReleaseList);
	}
	else if ("puid-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_PUIDList);
	}
	else if ("isrc-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ISRCList);
	}
	else if ("relation-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_RelationList);
	}
	else if ("tag-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_TagList);
	}
	else if ("user-tag-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_UserTagList);
	}
	else if ("rating"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Rating);
	}
	else if ("user-rating"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_UserRating);
	}
	else
	{
		std::cerr << "Unrecognised recording element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz4::CRecording::ElementName() const
{
	return "recording";
}

void MusicBrainz4::CRecording::Cleanup()
{
	delete m_d->m_ArtistCredit;
	m_d->m_ArtistCredit=0;

	delete m_d->m_ReleaseList;
	m_d->m_ReleaseList=0;

	delete m_d->m_PUIDList;
	m_d->m_PUIDList=0;

	delete m_d->m_ISRCList;
	m_d->m_ISRCList=0;

	delete m_d->m_RelationList;
	m_d->m_RelationList=0;

	delete m_d->m_TagList;
	m_d->m_TagList=0;

	delete m_d->m_UserTagList;
	m_d->m_UserTagList=0;

	delete m_d->m_Rating;
	m_d->m_Rating=0;

	delete m_d->m_UserRating;
	m_d->m_UserRating=0;
}

std::string MusicBrainz4::CRecording::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz4::CRecording::Title() const
{
	return m_d->m_Title;
}

int MusicBrainz4::CRecording::Length() const
{
	return m_d->m_Length;
}

std::string MusicBrainz4::CRecording::Disambiguation() const
{
	return m_d->m_Disambiguation;
}

MusicBrainz4::CArtistCredit *MusicBrainz4::CRecording::ArtistCredit() const
{
	return m_d->m_ArtistCredit;
}

MusicBrainz4::CReleaseList *MusicBrainz4::CRecording::ReleaseList() const
{
	return m_d->m_ReleaseList;
}

MusicBrainz4::CPUIDList *MusicBrainz4::CRecording::PUIDList() const
{
	return m_d->m_PUIDList;
}

MusicBrainz4::CISRCList *MusicBrainz4::CRecording::ISRCList() const
{
	return m_d->m_ISRCList;
}

MusicBrainz4::CRelationList *MusicBrainz4::CRecording::RelationList() const
{
	return m_d->m_RelationList;
}

MusicBrainz4::CTagList *MusicBrainz4::CRecording::TagList() const
{
	return m_d->m_TagList;
}

MusicBrainz4::CUserTagList *MusicBrainz4::CRecording::UserTagList() const
{
	return m_d->m_UserTagList;
}

MusicBrainz4::CRating *MusicBrainz4::CRecording::Rating() const
{
	return m_d->m_Rating;
}

MusicBrainz4::CUserRating *MusicBrainz4::CRecording::UserRating() const
{
	return m_d->m_UserRating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CRecording& Recording)
{
	os << "Recording:" << std::endl;

	MusicBrainz4::CEntity *Base=(MusicBrainz4::CEntity *)&Recording;

	os << *Base << std::endl;

	os << "\tID:             " << Recording.ID() << std::endl;
	os << "\tTitle:          " << Recording.Title() << std::endl;
	os << "\tLength:         " << Recording.Length() << std::endl;
	os << "\tDisambiguation: " << Recording.Disambiguation() << std::endl;

	if (Recording.ArtistCredit())
		os << *Recording.ArtistCredit() << std::endl;

	if (Recording.ReleaseList())
		os << *Recording.ReleaseList() << std::endl;

	if (Recording.PUIDList())
		os << *Recording.PUIDList() << std::endl;

	if (Recording.ISRCList())
		os << *Recording.ISRCList() << std::endl;

	if (Recording.RelationList())
		os << *Recording.RelationList() << std::endl;

	if (Recording.TagList())
		os << *Recording.TagList() << std::endl;

	if (Recording.UserTagList())
		os << *Recording.UserTagList() << std::endl;

	if (Recording.Rating())
		os << *Recording.Rating() << std::endl;

	if (Recording.UserRating())
		os << *Recording.UserRating() << std::endl;

	return os;
}
