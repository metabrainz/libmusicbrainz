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

#include "musicbrainz4/Work.h"

#include "musicbrainz4/ArtistCredit.h"
#include "musicbrainz4/AliasList.h"
#include "musicbrainz4/Alias.h"
#include "musicbrainz4/RelationList.h"
#include "musicbrainz4/TagList.h"
#include "musicbrainz4/Tag.h"
#include "musicbrainz4/UserTagList.h"
#include "musicbrainz4/UserTag.h"
#include "musicbrainz4/Rating.h"
#include "musicbrainz4/UserRating.h"

class MusicBrainz4::CWorkPrivate
{
	public:
		CWorkPrivate()
		:	m_ArtistCredit(0),
			m_AliasList(0),
			m_RelationList(0),
			m_TagList(0),
			m_UserTagList(0),
			m_Rating(0),
			m_UserRating(0)
		{
		}

		std::string m_ID;
		std::string m_Type;
		std::string m_Title;
		CArtistCredit *m_ArtistCredit;
		std::string m_ISWC;
		std::string m_Disambiguation;
		CAliasList *m_AliasList;
		CRelationList *m_RelationList;
		CTagList *m_TagList;
		CUserTagList *m_UserTagList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
};

MusicBrainz4::CWork::CWork(const XMLNode& Node)
:	CEntity(),
	m_d(new CWorkPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Work node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CWork::CWork(const CWork& Other)
:	CEntity(),
	m_d(new CWorkPrivate)
{
	*this=Other;
}

MusicBrainz4::CWork& MusicBrainz4::CWork::operator =(const CWork& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Type=Other.m_d->m_Type;
		m_d->m_Title=Other.m_d->m_Title;

		if (Other.m_d->m_ArtistCredit)
			m_d->m_ArtistCredit=new CArtistCredit(*Other.m_d->m_ArtistCredit);

		m_d->m_ISWC=Other.m_d->m_ISWC;
		m_d->m_Disambiguation=Other.m_d->m_Disambiguation;

		if (Other.m_d->m_AliasList)
			m_d->m_AliasList=new CAliasList(*Other.m_d->m_AliasList);

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

MusicBrainz4::CWork::~CWork()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz4::CWork::Cleanup()
{
	delete m_d->m_ArtistCredit;
	m_d->m_ArtistCredit=0;

	delete m_d->m_AliasList;
	m_d->m_AliasList=0;

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

MusicBrainz4::CWork *MusicBrainz4::CWork::Clone()
{
	return new CWork(*this);
}

bool MusicBrainz4::CWork::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("id"==Name)
		m_d->m_ID=Value;
	else if ("type"==Name)
		m_d->m_Type=Value;
	else
	{
		std::cerr << "Unrecognised work attribute: '" << Name << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

bool MusicBrainz4::CWork::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("title"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Title);
	}
	else if ("artist-credit"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ArtistCredit);
	}
	else if ("iswc"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ISWC);
	}
	else if ("disambiguation"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Disambiguation);
	}
	else if ("alias-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_AliasList);
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
		std::cerr << "Unrecognised work element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz4::CWork::GetElementName()
{
	return "work";
}

std::string MusicBrainz4::CWork::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz4::CWork::Type() const
{
	return m_d->m_Type;
}

std::string MusicBrainz4::CWork::Title() const
{
	return m_d->m_Title;
}

MusicBrainz4::CArtistCredit *MusicBrainz4::CWork::ArtistCredit() const
{
	return m_d->m_ArtistCredit;
}

std::string MusicBrainz4::CWork::ISWC() const
{
	return m_d->m_ISWC;
}

std::string MusicBrainz4::CWork::Disambiguation() const
{
	return m_d->m_Disambiguation;
}

MusicBrainz4::CAliasList *MusicBrainz4::CWork::AliasList() const
{
	return m_d->m_AliasList;
}

MusicBrainz4::CRelationList *MusicBrainz4::CWork::RelationList() const
{
	return m_d->m_RelationList;
}

MusicBrainz4::CTagList *MusicBrainz4::CWork::TagList() const
{
	return m_d->m_TagList;
}

MusicBrainz4::CUserTagList *MusicBrainz4::CWork::UserTagList() const
{
	return m_d->m_UserTagList;
}

MusicBrainz4::CRating *MusicBrainz4::CWork::Rating() const
{
	return m_d->m_Rating;
}

MusicBrainz4::CUserRating *MusicBrainz4::CWork::UserRating() const
{
	return m_d->m_UserRating;
}

std::ostream& MusicBrainz4::CWork::Serialise(std::ostream& os) const
{
	os << "Work:" << std::endl;

	CEntity::Serialise(os);

	os << "\tID:             " << ID() << std::endl;
	os << "\tWork:           " << Type() << std::endl;
	os << "\tTitle:          " << Title() << std::endl;

	if (ArtistCredit())
		os << ArtistCredit() << std::endl;

	os << "\tISWC:           " << ISWC() << std::endl;
	os << "\tDisambiguation: " << Disambiguation() << std::endl;

	if (AliasList())
		os << AliasList() << std::endl;

	if (RelationList())
		os << RelationList() << std::endl;

	if (TagList())
		os << TagList() << std::endl;

	if (UserTagList())
		os << UserTagList() << std::endl;

	if (Rating())
		os << Rating() << std::endl;

	if (UserRating())
		os << UserRating() << std::endl;

	return os;
}

