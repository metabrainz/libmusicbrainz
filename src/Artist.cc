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

#include "musicbrainz4/Artist.h"

#include "musicbrainz4/Lifespan.h"
#include "musicbrainz4/Rating.h"
#include "musicbrainz4/UserRating.h"
#include "musicbrainz4/AliasList.h"
#include "musicbrainz4/RecordingList.h"
#include "musicbrainz4/ReleaseList.h"
#include "musicbrainz4/ReleaseGroupList.h"
#include "musicbrainz4/LabelList.h"
#include "musicbrainz4/WorkList.h"
#include "musicbrainz4/RelationList.h"
#include "musicbrainz4/TagList.h"
#include "musicbrainz4/UserTagList.h"

class MusicBrainz4::CArtistPrivate
{
	public:
		CArtistPrivate()
		:	m_Lifespan(0),
			m_AliasList(0),
			m_RecordingList(0),
			m_ReleaseList(0),
			m_ReleaseGroupList(0),
			m_LabelList(0),
			m_WorkList(0),
			m_RelationList(0),
			m_TagList(0),
			m_UserTagList(0),
			m_Rating(0),
			m_UserRating(0)
		{
		}

		std::string m_ID;
		std::string m_Type;
		std::string m_Name;
		std::string m_SortName;
		std::string m_Gender;
		std::string m_Country;
		std::string m_Disambiguation;
		CLifespan *m_Lifespan;
		CAliasList *m_AliasList;
		CRecordingList *m_RecordingList;
		CReleaseList *m_ReleaseList;
		CReleaseGroupList *m_ReleaseGroupList;
		CLabelList *m_LabelList;
		CWorkList *m_WorkList;
		CRelationList *m_RelationList;
		CTagList *m_TagList;
		CUserTagList *m_UserTagList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
};

MusicBrainz4::CArtist::CArtist(const XMLNode& Node)
:	CEntity(),
	m_d(new CArtistPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Artist node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CArtist::CArtist(const CArtist& Other)
:	CEntity(),
	m_d(new CArtistPrivate)
{
	*this=Other;
}

MusicBrainz4::CArtist& MusicBrainz4::CArtist::operator =(const CArtist& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Type=Other.m_d->m_Type;
		m_d->m_Name=Other.m_d->m_Name;
		m_d->m_SortName=Other.m_d->m_SortName;
		m_d->m_Gender=Other.m_d->m_Gender;
		m_d->m_Country=Other.m_d->m_Country;
		m_d->m_Disambiguation=Other.m_d->m_Disambiguation;

		if (Other.m_d->m_Lifespan)
			m_d->m_Lifespan=new CLifespan(*Other.m_d->m_Lifespan);

		if (Other.m_d->m_AliasList)
			m_d->m_AliasList=new CAliasList(*Other.m_d->m_AliasList);

		if (Other.m_d->m_RecordingList)
			m_d->m_RecordingList=new CRecordingList(*Other.m_d->m_RecordingList);

		if (Other.m_d->m_ReleaseList)
			m_d->m_ReleaseList=new CReleaseList(*Other.m_d->m_ReleaseList);

		if (Other.m_d->m_ReleaseGroupList)
			m_d->m_ReleaseGroupList=new CReleaseGroupList(*Other.m_d->m_ReleaseGroupList);

		if (Other.m_d->m_LabelList)
			m_d->m_LabelList=new CLabelList(*Other.m_d->m_LabelList);

		if (Other.m_d->m_WorkList)
			m_d->m_WorkList=new CWorkList(*Other.m_d->m_WorkList);

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

MusicBrainz4::CArtist::~CArtist()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz4::CArtist::Cleanup()
{
	delete m_d->m_Lifespan;
	m_d->m_Lifespan=0;

	delete m_d->m_AliasList;
	m_d->m_AliasList=0;

	delete m_d->m_RecordingList;
	m_d->m_RecordingList=0;

	delete m_d->m_ReleaseList;
	m_d->m_ReleaseList=0;

	delete m_d->m_ReleaseGroupList;
	m_d->m_ReleaseGroupList=0;

	delete m_d->m_LabelList;
	m_d->m_LabelList=0;

	delete m_d->m_WorkList;
	m_d->m_WorkList=0;

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

MusicBrainz4::CArtist *MusicBrainz4::CArtist::Clone()
{
	return new CArtist(*this);
}

bool MusicBrainz4::CArtist::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("id"==Name)
		m_d->m_ID=Value;
	else if ("type"==Name)
		m_d->m_Type=Value;
	else
	{
		std::cerr << "Unrecognised artist attribute: '" << Name << "'" << std::endl;
	}

	return RetVal;
}

bool MusicBrainz4::CArtist::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("name"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Name);
	}
	else if ("sort-name"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_SortName);
	}
	else if ("gender"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Gender);
	}
	else if ("country"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Country);
	}
	else if ("disambiguation"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Disambiguation);
	}
	else if ("life-span"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Lifespan);
	}
	else if ("alias-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_AliasList);
	}
	else if ("recording-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_RecordingList);
	}
	else if ("release-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ReleaseList);
	}
	else if ("release-group-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ReleaseGroupList);
	}
	else if ("label-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_LabelList);
	}
	else if ("work-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_WorkList);
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
		std::cerr << "Unrecognised artist element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz4::CArtist::GetElementName()
{
	return "artist";
}

std::string MusicBrainz4::CArtist::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz4::CArtist::Type() const
{
	return m_d->m_Type;
}

std::string MusicBrainz4::CArtist::Name() const
{
	return m_d->m_Name;
}

std::string MusicBrainz4::CArtist::SortName() const
{
	return m_d->m_SortName;
}

std::string MusicBrainz4::CArtist::Gender() const
{
	return m_d->m_Gender;
}

std::string MusicBrainz4::CArtist::Country() const
{
	return m_d->m_Country;
}

std::string MusicBrainz4::CArtist::Disambiguation() const
{
	return m_d->m_Disambiguation;
}

MusicBrainz4::CLifespan *MusicBrainz4::CArtist::Lifespan() const
{
	return m_d->m_Lifespan;
}

MusicBrainz4::CAliasList *MusicBrainz4::CArtist::AliasList() const
{
	return m_d->m_AliasList;
}

MusicBrainz4::CRecordingList *MusicBrainz4::CArtist::RecordingList() const
{
	return m_d->m_RecordingList;
}

MusicBrainz4::CReleaseList *MusicBrainz4::CArtist::ReleaseList() const
{
	return m_d->m_ReleaseList;
}

MusicBrainz4::CReleaseGroupList *MusicBrainz4::CArtist::ReleaseGroupList() const
{
	return m_d->m_ReleaseGroupList;
}

MusicBrainz4::CLabelList *MusicBrainz4::CArtist::LabelList() const
{
	return m_d->m_LabelList;
}

MusicBrainz4::CWorkList *MusicBrainz4::CArtist::WorkList() const
{
	return m_d->m_WorkList;
}

MusicBrainz4::CRelationList *MusicBrainz4::CArtist::RelationList() const
{
	return m_d->m_RelationList;
}

MusicBrainz4::CTagList *MusicBrainz4::CArtist::TagList() const
{
	return m_d->m_TagList;
}

MusicBrainz4::CUserTagList *MusicBrainz4::CArtist::UserTagList() const
{
	return m_d->m_UserTagList;
}

MusicBrainz4::CRating *MusicBrainz4::CArtist::Rating() const
{
	return m_d->m_Rating;
}

MusicBrainz4::CUserRating *MusicBrainz4::CArtist::UserRating() const
{
	return m_d->m_UserRating;
}

std::ostream& MusicBrainz4::CArtist::Serialise(std::ostream& os) const
{
	os << "Artist:" << std::endl;

	CEntity::Serialise(os);

	os << "\tID:             " << ID() << std::endl;
	os << "\tType:           " << Type() << std::endl;
	os << "\tName:           " << Name() << std::endl;
	os << "\tSort name:      " << SortName() << std::endl;
	os << "\tGender:         " << Gender() << std::endl;
	os << "\tCountry:        " << Country() << std::endl;
	os << "\tDisambiguation: " << Disambiguation() << std::endl;

	if (Lifespan())
		os << *Lifespan() << std::endl;

	if (AliasList())
		os << *AliasList() << std::endl;

	if (RecordingList())
		os << *RecordingList() << std::endl;

	if (ReleaseList())
		os << *ReleaseList() << std::endl;

	if (ReleaseGroupList())
		os << *ReleaseGroupList() << std::endl;

	if (LabelList())
		os << *LabelList() << std::endl;

	if (WorkList())
		os << *WorkList() << std::endl;

	if (RelationList())
		os << *RelationList() << std::endl;

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

