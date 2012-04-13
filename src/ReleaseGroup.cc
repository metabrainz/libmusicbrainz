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

#include "config.h"

#include "musicbrainz4/ReleaseGroup.h"

#include "musicbrainz4/ArtistCredit.h"
#include "musicbrainz4/Rating.h"
#include "musicbrainz4/UserRating.h"
#include "musicbrainz4/ReleaseList.h"
#include "musicbrainz4/Release.h"
#include "musicbrainz4/RelationList.h"
#include "musicbrainz4/RelationListList.h"
#include "musicbrainz4/Relation.h"
#include "musicbrainz4/TagList.h"
#include "musicbrainz4/Tag.h"
#include "musicbrainz4/UserTagList.h"
#include "musicbrainz4/UserTag.h"

class MusicBrainz4::CReleaseGroupPrivate
{
	public:
		CReleaseGroupPrivate()
		:	m_ArtistCredit(0),
			m_ReleaseList(0),
			m_RelationListList(0),
			m_TagList(0),
			m_UserTagList(0),
			m_Rating(0),
			m_UserRating(0)
		{
		}

		std::string m_ID;
		std::string m_Type;
		std::string m_Title;
		std::string m_Disambiguation;
		std::string m_FirstReleaseDate;
		CArtistCredit *m_ArtistCredit;
		CReleaseList *m_ReleaseList;
		CRelationListList *m_RelationListList;
		CTagList *m_TagList;
		CUserTagList *m_UserTagList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
};

MusicBrainz4::CReleaseGroup::CReleaseGroup(const XMLNode& Node)
:	CEntity(),
	m_d(new CReleaseGroupPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Name credit node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CReleaseGroup::CReleaseGroup(const CReleaseGroup& Other)
:	CEntity(),
	m_d(new CReleaseGroupPrivate)
{
	*this=Other;
}

MusicBrainz4::CReleaseGroup& MusicBrainz4::CReleaseGroup::operator =(const CReleaseGroup& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Type=Other.m_d->m_Type;
		m_d->m_Title=Other.m_d->m_Title;
		m_d->m_Disambiguation=Other.m_d->m_Disambiguation;
		m_d->m_FirstReleaseDate=Other.m_d->m_FirstReleaseDate;

		if (Other.m_d->m_ArtistCredit)
			m_d->m_ArtistCredit=new CArtistCredit(*Other.m_d->m_ArtistCredit);

		if (Other.m_d->m_ReleaseList)
			m_d->m_ReleaseList=new CReleaseList(*Other.m_d->m_ReleaseList);

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

MusicBrainz4::CReleaseGroup::~CReleaseGroup()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz4::CReleaseGroup::Cleanup()
{
	delete m_d->m_ArtistCredit;
	m_d->m_ArtistCredit=0;

	delete m_d->m_ReleaseList;
	m_d->m_ReleaseList=0;

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

MusicBrainz4::CReleaseGroup *MusicBrainz4::CReleaseGroup::Clone()
{
	return new CReleaseGroup(*this);
}

bool MusicBrainz4::CReleaseGroup::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("id"==Name)
		m_d->m_ID=Value;
	else if ("type"==Name)
		m_d->m_Type=Value;
	else
	{
		std::cerr << "Unrecognised releasegroup attribute: '" << Name << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

bool MusicBrainz4::CReleaseGroup::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("title"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Title);
	}
	else if ("disambiguation"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Disambiguation);
	}
	else if ("first-release-date"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_FirstReleaseDate);
	}
	else if ("artist-credit"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ArtistCredit);
	}
	else if ("release-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ReleaseList);
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
		std::cerr << "Unrecognised release group element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz4::CReleaseGroup::GetElementName()
{
	return "release-group";
}

std::string MusicBrainz4::CReleaseGroup::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz4::CReleaseGroup::Type() const
{
	return m_d->m_Type;
}

std::string MusicBrainz4::CReleaseGroup::Title() const
{
	return m_d->m_Title;
}

std::string MusicBrainz4::CReleaseGroup::Disambiguation() const
{
	return m_d->m_Disambiguation;
}

std::string MusicBrainz4::CReleaseGroup::FirstReleaseDate() const
{
	return m_d->m_FirstReleaseDate;
}

MusicBrainz4::CArtistCredit *MusicBrainz4::CReleaseGroup::ArtistCredit() const
{
	return m_d->m_ArtistCredit;
}

MusicBrainz4::CReleaseList *MusicBrainz4::CReleaseGroup::ReleaseList() const
{
	return m_d->m_ReleaseList;
}

MusicBrainz4::CRelationList *MusicBrainz4::CReleaseGroup::RelationList() const
{
	return m_d->m_RelationListList?m_d->m_RelationListList->Item(m_d->m_RelationListList->NumItems()-1):0;
}

MusicBrainz4::CRelationListList *MusicBrainz4::CReleaseGroup::RelationListList() const
{
	return m_d->m_RelationListList;
}

MusicBrainz4::CTagList *MusicBrainz4::CReleaseGroup::TagList() const
{
	return m_d->m_TagList;
}

MusicBrainz4::CUserTagList *MusicBrainz4::CReleaseGroup::UserTagList() const
{
	return m_d->m_UserTagList;
}

MusicBrainz4::CRating *MusicBrainz4::CReleaseGroup::Rating() const
{
	return m_d->m_Rating;
}

MusicBrainz4::CUserRating *MusicBrainz4::CReleaseGroup::UserRating() const
{
	return m_d->m_UserRating;
}

std::ostream& MusicBrainz4::CReleaseGroup::Serialise(std::ostream& os) const
{
	os << "Release group:" << std::endl;

	CEntity::Serialise(os);

	os << "\tID:                 " << ID() << std::endl;
	os << "\tType:               " << Type() << std::endl;
	os << "\tTitle:              " << Title() << std::endl;
	os << "\tDisambiguation:     " << Disambiguation() << std::endl;
	os << "\tFirst release date: " << FirstReleaseDate() << std::endl;

	if (ArtistCredit())
		os << *ArtistCredit() << std::endl;

	if (ReleaseList())
		os << *ReleaseList() << std::endl;

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

