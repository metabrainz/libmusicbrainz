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

#include "musicbrainz5/Recording.h"

#include "musicbrainz5/ArtistCredit.h"
#include "musicbrainz5/Rating.h"
#include "musicbrainz5/UserRating.h"
#include "musicbrainz5/ReleaseList.h"
#include "musicbrainz5/Release.h"
#include "musicbrainz5/PUIDList.h"
#include "musicbrainz5/PUID.h"
#include "musicbrainz5/ISRCList.h"
#include "musicbrainz5/ISRC.h"
#include "musicbrainz5/RelationListList.h"
#include "musicbrainz5/Relation.h"
#include "musicbrainz5/TagList.h"
#include "musicbrainz5/Tag.h"
#include "musicbrainz5/UserTagList.h"
#include "musicbrainz5/UserTag.h"

class MusicBrainz5::CRecordingPrivate
{
	public:
		CRecordingPrivate()
		:	m_Length(0),
			m_ArtistCredit(0),
			m_ReleaseList(0),
			m_PUIDList(0),
			m_ISRCList(0),
			m_RelationListList(0),
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
		CRelationListList *m_RelationListList;
		CTagList *m_TagList;
		CUserTagList *m_UserTagList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
};

MusicBrainz5::CRecording::CRecording(const XMLNode& Node)
:	CEntity(),
	m_d(new CRecordingPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Recording node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CRecording::CRecording(const CRecording& Other)
:	CEntity(),
	m_d(new CRecordingPrivate)
{
	*this=Other;
}

MusicBrainz5::CRecording& MusicBrainz5::CRecording::operator =(const CRecording& Other)
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

		if (Other.m_d->m_RelationListList)
			m_d->m_RelationListList=new CRelationListList(*Other.m_d->m_RelationListList);

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

MusicBrainz5::CRecording::~CRecording()
{
	Cleanup();

	delete m_d;
}

MusicBrainz5::CRecording *MusicBrainz5::CRecording::Clone()
{
	return new CRecording(*this);
}

bool MusicBrainz5::CRecording::ParseAttribute(const std::string& Name, const std::string& Value)
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

bool MusicBrainz5::CRecording::ParseElement(const XMLNode& Node)
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
		RetVal=ProcessRelationList(Node,m_d->m_RelationListList);
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

std::string MusicBrainz5::CRecording::GetElementName()
{
	return "recording";
}

void MusicBrainz5::CRecording::Cleanup()
{
	delete m_d->m_ArtistCredit;
	m_d->m_ArtistCredit=0;

	delete m_d->m_ReleaseList;
	m_d->m_ReleaseList=0;

	delete m_d->m_PUIDList;
	m_d->m_PUIDList=0;

	delete m_d->m_ISRCList;
	m_d->m_ISRCList=0;

	delete m_d->m_RelationListList;
	m_d->m_RelationListList=0;

	delete m_d->m_TagList;
	m_d->m_TagList=0;

	delete m_d->m_UserTagList;
	m_d->m_UserTagList=0;

	delete m_d->m_Rating;
	m_d->m_Rating=0;

	delete m_d->m_UserRating;
	m_d->m_UserRating=0;
}

std::string MusicBrainz5::CRecording::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz5::CRecording::Title() const
{
	return m_d->m_Title;
}

int MusicBrainz5::CRecording::Length() const
{
	return m_d->m_Length;
}

std::string MusicBrainz5::CRecording::Disambiguation() const
{
	return m_d->m_Disambiguation;
}

MusicBrainz5::CArtistCredit *MusicBrainz5::CRecording::ArtistCredit() const
{
	return m_d->m_ArtistCredit;
}

MusicBrainz5::CReleaseList *MusicBrainz5::CRecording::ReleaseList() const
{
	return m_d->m_ReleaseList;
}

MusicBrainz5::CPUIDList *MusicBrainz5::CRecording::PUIDList() const
{
	return m_d->m_PUIDList;
}

MusicBrainz5::CISRCList *MusicBrainz5::CRecording::ISRCList() const
{
	return m_d->m_ISRCList;
}

MusicBrainz5::CRelationListList *MusicBrainz5::CRecording::RelationListList() const
{
	return m_d->m_RelationListList;
}

MusicBrainz5::CTagList *MusicBrainz5::CRecording::TagList() const
{
	return m_d->m_TagList;
}

MusicBrainz5::CUserTagList *MusicBrainz5::CRecording::UserTagList() const
{
	return m_d->m_UserTagList;
}

MusicBrainz5::CRating *MusicBrainz5::CRecording::Rating() const
{
	return m_d->m_Rating;
}

MusicBrainz5::CUserRating *MusicBrainz5::CRecording::UserRating() const
{
	return m_d->m_UserRating;
}

std::ostream& MusicBrainz5::CRecording::Serialise(std::ostream& os) const
{
	os << "Recording:" << std::endl;

	CEntity::Serialise(os);

	os << "\tID:             " << ID() << std::endl;
	os << "\tTitle:          " << Title() << std::endl;
	os << "\tLength:         " << Length() << std::endl;
	os << "\tDisambiguation: " << Disambiguation() << std::endl;

	if (ArtistCredit())
		os << *ArtistCredit() << std::endl;

	if (ReleaseList())
		os << *ReleaseList() << std::endl;

	if (PUIDList())
		os << *PUIDList() << std::endl;

	if (ISRCList())
		os << *ISRCList() << std::endl;

	if (RelationListList())
		os << *RelationListList() << std::endl;

	if (TagList())
		os << *TagList() << std::endl;

	if (UserTagList())
		os << *UserTagList() << std::endl;

	if (Rating())
		os << *Rating() << std::endl;

	if (UserRating())
		os << *UserRating() << std::endl;

	return os;
}
