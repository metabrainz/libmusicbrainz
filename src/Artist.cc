/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

#include "musicbrainz4/Artist.h"

#include "musicbrainz4/Lifespan.h"
#include "musicbrainz4/Rating.h"
#include "musicbrainz4/UserRating.h"
#include "musicbrainz4/Alias.h"
#include "musicbrainz4/Recording.h"
#include "musicbrainz4/Release.h"
#include "musicbrainz4/ReleaseGroup.h"
#include "musicbrainz4/Label.h"
#include "musicbrainz4/Work.h"
#include "musicbrainz4/Relation.h"
#include "musicbrainz4/Tag.h"
#include "musicbrainz4/UserTag.h"

MusicBrainz4::CArtist::CArtist(const XMLNode& Node)
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
	if (!Node.isEmpty())
	{
		//std::cout << "Artist node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("id"))
			m_ID=Node.getAttribute("id");

		if (Node.isAttributeSet("type"))
			m_Type=Node.getAttribute("type");

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("name"==NodeName)
			{
				m_Name=NodeValue;
			}
			else if ("sort-name"==NodeName)
			{
				m_SortName=NodeValue;
			}
			else if ("gender"==NodeName)
			{
				m_Gender=NodeValue;
			}
			else if ("country"==NodeName)
			{
				m_Country=NodeValue;
			}
			else if ("disambiguation"==NodeName)
			{
				m_Disambiguation=NodeValue;
			}
			else if ("life-span"==NodeName)
			{
				m_Lifespan=new CLifespan(ChildNode);
			}
			else if ("alias-list"==NodeName)
			{
				m_AliasList=new CGenericList<CAlias>(ChildNode,"alias");
			}
			else if ("recording-list"==NodeName)
			{
				m_RecordingList=new CGenericList<CRecording>(ChildNode,"recording");
			}
			else if ("release-list"==NodeName)
			{
				m_ReleaseList=new CGenericList<CRelease>(ChildNode,"release");
			}
			else if ("release-group-list"==NodeName)
			{
				m_ReleaseGroupList=new CGenericList<CReleaseGroup>(ChildNode,"release");
			}
			else if ("label-list"==NodeName)
			{
				m_LabelList=new CGenericList<CLabel>(ChildNode,"label");
			}
			else if ("work-list"==NodeName)
			{
				m_WorkList=new CGenericList<CWork>(ChildNode,"work");
			}
			else if ("relation-list"==NodeName)
			{
				m_RelationList=new CGenericList<CRelation>(ChildNode,"relation");
			}
			else if ("tag-list"==NodeName)
			{
				m_TagList=new CGenericList<CTag>(ChildNode,"tag");
			}
			else if ("user-tag-list"==NodeName)
			{
				m_UserTagList=new CGenericList<CUserTag>(ChildNode,"user-tag");
			}
			else if ("rating"==NodeName)
			{
				m_Rating=new CRating(ChildNode);
			}
			else if ("user-rating"==NodeName)
			{
				m_UserRating=new CUserRating(ChildNode);
			}
			else
			{
				std::cerr << "Unrecognised artist node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CArtist::CArtist(const CArtist& Other)
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
	*this=Other;
}

MusicBrainz4::CArtist::CArtist& MusicBrainz4::CArtist::operator =(const CArtist& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_ID=Other.m_ID;
		m_Type=Other.m_Type;
		m_Name=Other.m_Name;
		m_SortName=Other.m_SortName;
		m_Gender=Other.m_Gender;
		m_Country=Other.m_Country;
		m_Disambiguation=Other.m_Disambiguation;

		if (Other.m_Lifespan)
			m_Lifespan=new CLifespan(*Other.m_Lifespan);

		if (Other.m_AliasList)
			m_AliasList=new CGenericList<CAlias>(*Other.m_AliasList);

		if (Other.m_RecordingList)
			m_RecordingList=new CGenericList<CRecording>(*Other.m_RecordingList);

		if (Other.m_ReleaseList)
			m_ReleaseList=new CGenericList<CRelease>(*Other.m_ReleaseList);

		if (Other.m_ReleaseGroupList)
			m_ReleaseGroupList=new CGenericList<CReleaseGroup>(*Other.m_ReleaseGroupList);

		if (Other.m_LabelList)
			m_LabelList=new CGenericList<CLabel>(*Other.m_LabelList);

		if (Other.m_WorkList)
			m_WorkList=new CGenericList<CWork>(*Other.m_WorkList);

		if (Other.m_RelationList)
			m_RelationList=new CGenericList<CRelation>(*Other.m_RelationList);

		if (Other.m_TagList)
			m_TagList=new CGenericList<CTag>(*Other.m_TagList);

		if (Other.m_UserTagList)
			m_UserTagList=new CGenericList<CUserTag>(*Other.m_UserTagList);

		if (Other.m_Rating)
			m_Rating=new CRating(*Other.m_Rating);

		if (Other.m_UserRating)
			m_UserRating=new CUserRating(*Other.m_UserRating);
	}

	return *this;
}

MusicBrainz4::CArtist::~CArtist()
{
	Cleanup();
}

void MusicBrainz4::CArtist::Cleanup()
{
	delete m_Lifespan;
	m_Lifespan=0;

	delete m_AliasList;
	m_AliasList=0;

	delete m_RecordingList;
	m_RecordingList=0;

	delete m_ReleaseList;
	m_ReleaseList=0;

	delete m_ReleaseGroupList;
	m_ReleaseGroupList=0;

	delete m_LabelList;
	m_LabelList=0;

	delete m_WorkList;
	m_WorkList=0;

	delete m_RelationList;
	m_RelationList=0;

	delete m_TagList;
	m_TagList=0;

	delete m_UserTagList;
	m_UserTagList=0;

	delete m_Rating;
	m_Rating=0;

	delete m_UserRating;
	m_UserRating=0;
}

std::string MusicBrainz4::CArtist::ID() const
{
	return m_ID;
}

std::string MusicBrainz4::CArtist::Type() const
{
	return m_Type;
}

std::string MusicBrainz4::CArtist::Name() const
{
	return m_Name;
}

std::string MusicBrainz4::CArtist::SortName() const
{
	return m_SortName;
}

std::string MusicBrainz4::CArtist::Gender() const
{
	return m_Gender;
}

std::string MusicBrainz4::CArtist::Country() const
{
	return m_Country;
}

std::string MusicBrainz4::CArtist::Disambiguation() const
{
	return m_Disambiguation;
}

MusicBrainz4::CLifespan *MusicBrainz4::CArtist::Lifespan() const
{
	return m_Lifespan;
}

MusicBrainz4::CGenericList<MusicBrainz4::CAlias> *MusicBrainz4::CArtist::AliasList() const
{
	return m_AliasList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRecording> *MusicBrainz4::CArtist::RecordingList() const
{
	return m_RecordingList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRelease> *MusicBrainz4::CArtist::ReleaseList() const
{
	return m_ReleaseList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CReleaseGroup> *MusicBrainz4::CArtist::ReleaseGroupList() const
{
	return m_ReleaseGroupList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CLabel> *MusicBrainz4::CArtist::LabelList() const
{
	return m_LabelList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CWork> *MusicBrainz4::CArtist::WorkList() const
{
	return m_WorkList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRelation> *MusicBrainz4::CArtist::RelationList() const
{
	return m_RelationList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CTag> *MusicBrainz4::CArtist::TagList() const
{
	return m_TagList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CUserTag> *MusicBrainz4::CArtist::UserTagList() const
{
	return m_UserTagList;
}

MusicBrainz4::CRating *MusicBrainz4::CArtist::Rating() const
{
	return m_Rating;
}

MusicBrainz4::CUserRating *MusicBrainz4::CArtist::UserRating() const
{
	return m_UserRating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CArtist& Artist)
{
	os << "Artist:" << std::endl;

	os << "\tID:             " << Artist.ID() << std::endl;
	os << "\tType:           " << Artist.Type() << std::endl;
	os << "\tName:           " << Artist.Name() << std::endl;
	os << "\tSort name:      " << Artist.SortName() << std::endl;
	os << "\tGender:         " << Artist.Gender() << std::endl;
	os << "\tCountry:        " << Artist.Country() << std::endl;
	os << "\tDisambiguation: " << Artist.Disambiguation() << std::endl;

	if (Artist.Lifespan())
		os << *Artist.Lifespan() << std::endl;

	if (Artist.AliasList())
		os << *Artist.AliasList() << std::endl;

	if (Artist.RecordingList())
		os << *Artist.RecordingList() << std::endl;

	if (Artist.ReleaseList())
		os << *Artist.ReleaseList() << std::endl;

	if (Artist.ReleaseGroupList())
		os << *Artist.ReleaseGroupList() << std::endl;

	if (Artist.LabelList())
		os << *Artist.LabelList() << std::endl;

	if (Artist.WorkList())
		os << *Artist.WorkList() << std::endl;

	if (Artist.RelationList())
		os << *Artist.RelationList() << std::endl;

	if (Artist.TagList())
		os << *Artist.TagList() << std::endl;

	if (Artist.UserTagList())
		os << *Artist.UserTagList() << std::endl;

	if (Artist.Rating())
		os << *Artist.Rating() << std::endl;

	if (Artist.UserRating())
		os << *Artist.UserRating() << std::endl;

	return os;
}

