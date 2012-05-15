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

#include "musicbrainz5/Artist.h"

#include "musicbrainz5/Lifespan.h"
#include "musicbrainz5/IPI.h"
#include "musicbrainz5/Rating.h"
#include "musicbrainz5/UserRating.h"
#include "musicbrainz5/AliasList.h"
#include "musicbrainz5/Alias.h"
#include "musicbrainz5/RecordingList.h"
#include "musicbrainz5/Recording.h"
#include "musicbrainz5/ReleaseList.h"
#include "musicbrainz5/Release.h"
#include "musicbrainz5/ReleaseGroupList.h"
#include "musicbrainz5/ReleaseGroup.h"
#include "musicbrainz5/LabelList.h"
#include "musicbrainz5/Label.h"
#include "musicbrainz5/WorkList.h"
#include "musicbrainz5/Work.h"
#include "musicbrainz5/RelationList.h"
#include "musicbrainz5/RelationListList.h"
#include "musicbrainz5/Relation.h"
#include "musicbrainz5/TagList.h"
#include "musicbrainz5/Tag.h"
#include "musicbrainz5/UserTagList.h"
#include "musicbrainz5/UserTag.h"

class MusicBrainz5::CArtistPrivate
{
	public:
		CArtistPrivate()
		:	m_IPIList(0),
			m_Lifespan(0),
			m_AliasList(0),
			m_RecordingList(0),
			m_ReleaseList(0),
			m_ReleaseGroupList(0),
			m_LabelList(0),
			m_WorkList(0),
			m_RelationListList(0),
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
		CIPIList *m_IPIList;
		CLifespan *m_Lifespan;
		CAliasList *m_AliasList;
		CRecordingList *m_RecordingList;
		CReleaseList *m_ReleaseList;
		CReleaseGroupList *m_ReleaseGroupList;
		CLabelList *m_LabelList;
		CWorkList *m_WorkList;
		CRelationListList *m_RelationListList;
		CTagList *m_TagList;
		CUserTagList *m_UserTagList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
};

MusicBrainz5::CArtist::CArtist(const XMLNode& Node)
:	CEntity(),
	m_d(new CArtistPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Artist node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CArtist::CArtist(const CArtist& Other)
:	CEntity(),
	m_d(new CArtistPrivate)
{
	*this=Other;
}

MusicBrainz5::CArtist& MusicBrainz5::CArtist::operator =(const CArtist& Other)
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

		if (Other.m_d->m_IPIList)
			m_d->m_IPIList=new CIPIList(*Other.m_d->m_IPIList);

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

MusicBrainz5::CArtist::~CArtist()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CArtist::Cleanup()
{
	delete m_d->m_IPIList;
	m_d->m_IPIList=0;

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

MusicBrainz5::CArtist *MusicBrainz5::CArtist::Clone()
{
	return new CArtist(*this);
}

bool MusicBrainz5::CArtist::ParseAttribute(const std::string& Name, const std::string& Value)
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

bool MusicBrainz5::CArtist::ParseElement(const XMLNode& Node)
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
	else if ("ipi"==NodeName)
	{
		//Ignore IPI
	}
	else if ("ipi-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_IPIList);
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
		std::cerr << "Unrecognised artist element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz5::CArtist::GetElementName()
{
	return "artist";
}

std::string MusicBrainz5::CArtist::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz5::CArtist::Type() const
{
	return m_d->m_Type;
}

std::string MusicBrainz5::CArtist::Name() const
{
	return m_d->m_Name;
}

std::string MusicBrainz5::CArtist::SortName() const
{
	return m_d->m_SortName;
}

std::string MusicBrainz5::CArtist::Gender() const
{
	return m_d->m_Gender;
}

std::string MusicBrainz5::CArtist::Country() const
{
	return m_d->m_Country;
}

std::string MusicBrainz5::CArtist::Disambiguation() const
{
	return m_d->m_Disambiguation;
}

MusicBrainz5::CIPIList *MusicBrainz5::CArtist::IPIList() const
{
	return m_d->m_IPIList;
}

MusicBrainz5::CLifespan *MusicBrainz5::CArtist::Lifespan() const
{
	return m_d->m_Lifespan;
}

MusicBrainz5::CAliasList *MusicBrainz5::CArtist::AliasList() const
{
	return m_d->m_AliasList;
}

MusicBrainz5::CRecordingList *MusicBrainz5::CArtist::RecordingList() const
{
	return m_d->m_RecordingList;
}

MusicBrainz5::CReleaseList *MusicBrainz5::CArtist::ReleaseList() const
{
	return m_d->m_ReleaseList;
}

MusicBrainz5::CReleaseGroupList *MusicBrainz5::CArtist::ReleaseGroupList() const
{
	return m_d->m_ReleaseGroupList;
}

MusicBrainz5::CLabelList *MusicBrainz5::CArtist::LabelList() const
{
	return m_d->m_LabelList;
}

MusicBrainz5::CWorkList *MusicBrainz5::CArtist::WorkList() const
{
	return m_d->m_WorkList;
}

MusicBrainz5::CRelationListList *MusicBrainz5::CArtist::RelationListList() const
{
	return m_d->m_RelationListList;
}

MusicBrainz5::CTagList *MusicBrainz5::CArtist::TagList() const
{
	return m_d->m_TagList;
}

MusicBrainz5::CUserTagList *MusicBrainz5::CArtist::UserTagList() const
{
	return m_d->m_UserTagList;
}

MusicBrainz5::CRating *MusicBrainz5::CArtist::Rating() const
{
	return m_d->m_Rating;
}

MusicBrainz5::CUserRating *MusicBrainz5::CArtist::UserRating() const
{
	return m_d->m_UserRating;
}

std::ostream& MusicBrainz5::CArtist::Serialise(std::ostream& os) const
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

	if (IPIList())
		os << *IPIList() << std::endl;

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

