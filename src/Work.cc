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

#include "musicbrainz5/Work.h"

#include "musicbrainz5/ArtistCredit.h"
#include "musicbrainz5/AliasList.h"
#include "musicbrainz5/Alias.h"
#include "musicbrainz5/RelationList.h"
#include "musicbrainz5/RelationListList.h"
#include "musicbrainz5/TagList.h"
#include "musicbrainz5/Tag.h"
#include "musicbrainz5/UserTagList.h"
#include "musicbrainz5/UserTag.h"
#include "musicbrainz5/Rating.h"
#include "musicbrainz5/UserRating.h"
#include "musicbrainz5/ISWC.h"
#include "musicbrainz5/ISWCList.h"

class MusicBrainz5::CWorkPrivate
{
	public:
		CWorkPrivate()
		:	m_ArtistCredit(0),
			m_ISWCList(0),
			m_AliasList(0),
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
		CArtistCredit *m_ArtistCredit;
		CISWCList *m_ISWCList;
		std::string m_Disambiguation;
		CAliasList *m_AliasList;
		CRelationListList *m_RelationListList;
		CTagList *m_TagList;
		CUserTagList *m_UserTagList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
		std::string m_Language;
};

MusicBrainz5::CWork::CWork(const XMLNode& Node)
:	CEntity(),
	m_d(new CWorkPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Work node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CWork::CWork(const CWork& Other)
:	CEntity(),
	m_d(new CWorkPrivate)
{
	*this=Other;
}

MusicBrainz5::CWork& MusicBrainz5::CWork::operator =(const CWork& Other)
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

		if (Other.m_d->m_ISWCList)
			m_d->m_ISWCList=new CISWCList(*Other.m_d->m_ISWCList);

		m_d->m_Disambiguation=Other.m_d->m_Disambiguation;

		if (Other.m_d->m_AliasList)
			m_d->m_AliasList=new CAliasList(*Other.m_d->m_AliasList);

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

		m_d->m_Language=Other.m_d->m_Language;
	}

	return *this;
}

MusicBrainz5::CWork::~CWork()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CWork::Cleanup()
{
	delete m_d->m_ArtistCredit;
	m_d->m_ArtistCredit=0;

	delete m_d->m_ISWCList;
	m_d->m_ISWCList=0;

	delete m_d->m_AliasList;
	m_d->m_AliasList=0;

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

MusicBrainz5::CWork *MusicBrainz5::CWork::Clone()
{
	return new CWork(*this);
}

bool MusicBrainz5::CWork::ParseAttribute(const std::string& Name, const std::string& Value)
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

bool MusicBrainz5::CWork::ParseElement(const XMLNode& Node)
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
	else if ("iswc-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ISWCList);
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
	else if ("language"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Language);
	}
	else
	{
		std::cerr << "Unrecognised work element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz5::CWork::GetElementName()
{
	return "work";
}

std::string MusicBrainz5::CWork::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz5::CWork::Type() const
{
	return m_d->m_Type;
}

std::string MusicBrainz5::CWork::Title() const
{
	return m_d->m_Title;
}

MusicBrainz5::CArtistCredit *MusicBrainz5::CWork::ArtistCredit() const
{
	return m_d->m_ArtistCredit;
}

MusicBrainz5::CISWCList *MusicBrainz5::CWork::ISWCList() const
{
	return m_d->m_ISWCList;
}

std::string MusicBrainz5::CWork::Disambiguation() const
{
	return m_d->m_Disambiguation;
}

MusicBrainz5::CAliasList *MusicBrainz5::CWork::AliasList() const
{
	return m_d->m_AliasList;
}

MusicBrainz5::CRelationListList *MusicBrainz5::CWork::RelationListList() const
{
	return m_d->m_RelationListList;
}

MusicBrainz5::CTagList *MusicBrainz5::CWork::TagList() const
{
	return m_d->m_TagList;
}

MusicBrainz5::CUserTagList *MusicBrainz5::CWork::UserTagList() const
{
	return m_d->m_UserTagList;
}

MusicBrainz5::CRating *MusicBrainz5::CWork::Rating() const
{
	return m_d->m_Rating;
}

MusicBrainz5::CUserRating *MusicBrainz5::CWork::UserRating() const
{
	return m_d->m_UserRating;
}

std::string MusicBrainz5::CWork::Language() const
{
	return m_d->m_Language;
}

std::ostream& MusicBrainz5::CWork::Serialise(std::ostream& os) const
{
	os << "Work:" << std::endl;

	CEntity::Serialise(os);

	os << "\tID:             " << ID() << std::endl;
	os << "\tWork:           " << Type() << std::endl;
	os << "\tTitle:          " << Title() << std::endl;

	if (ArtistCredit())
		os << ArtistCredit() << std::endl;

	if (ISWCList())
		os << ISWCList() << std::endl;

	os << "\tDisambiguation: " << Disambiguation() << std::endl;

	if (AliasList())
		os << AliasList() << std::endl;

	if (RelationListList())
		os << RelationListList() << std::endl;

	if (TagList())
		os << TagList() << std::endl;

	if (UserTagList())
		os << UserTagList() << std::endl;

	if (Rating())
		os << Rating() << std::endl;

	if (UserRating())
		os << UserRating() << std::endl;

	os << "\tLanguage:       " << Language() << std::endl;

	return os;
}

