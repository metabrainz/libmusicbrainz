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

#include "musicbrainz4/Label.h"

#include <iostream>

#include "musicbrainz4/Lifespan.h"
#include "musicbrainz4/Rating.h"
#include "musicbrainz4/UserRating.h"
#include "musicbrainz4/Alias.h"
#include "musicbrainz4/Release.h"
#include "musicbrainz4/Relation.h"
#include "musicbrainz4/Tag.h"
#include "musicbrainz4/UserTag.h"

MusicBrainz4::CLabel::CLabel(const XMLNode& Node)
:	m_Lifespan(0),
	m_AliasList(0),
	m_ReleaseList(0),
	m_RelationList(0),
	m_TagList(0),
	m_UserTagList(0),
	m_Rating(0),
	m_UserRating(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Label node: " << std::endl << Node.createXMLString(true) << std::endl;

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
			else if ("label-code"==NodeName)
			{
				m_LabelCode=NodeValue;
			}
			else if ("disambiguation"==NodeName)
			{
				m_Disambiguation=NodeValue;
			}
			else if ("country"==NodeName)
			{
				m_Country=NodeValue;
			}
			else if ("life-span"==NodeName)
			{
				m_Lifespan=new CLifespan(ChildNode);
			}
			else if ("alias-list"==NodeName)
			{
				m_AliasList=new CGenericList<CAlias>(ChildNode,"alias");
			}
			else if ("release-list"==NodeName)
			{
				m_ReleaseList=new CGenericList<CRelease>(ChildNode,"release");
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
				std::cerr << "Unrecognised label node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CLabel::CLabel(const CLabel& Other)
:	m_Lifespan(0),
	m_AliasList(0),
	m_ReleaseList(0),
	m_RelationList(0),
	m_TagList(0),
	m_UserTagList(0),
	m_Rating(0),
	m_UserRating(0)
{
	*this=Other;
}

MusicBrainz4::CLabel& MusicBrainz4::CLabel::operator =(const CLabel& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_ID=Other.m_ID;
		m_Type=Other.m_Type;
		m_Name=Other.m_Name;
		m_SortName=Other.m_SortName;
		m_LabelCode=Other.m_LabelCode;
		m_Disambiguation=Other.m_Disambiguation;
		m_Country=Other.m_Country;

		if (Other.m_Lifespan)
			m_Lifespan=new CLifespan(*Other.m_Lifespan);

		if (Other.m_AliasList)
			m_AliasList=new CGenericList<CAlias>(*Other.m_AliasList);

		if (Other.m_ReleaseList)
			m_ReleaseList=new CGenericList<CRelease>(*Other.m_ReleaseList);

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

MusicBrainz4::CLabel::~CLabel()
{
	Cleanup();
}

void MusicBrainz4::CLabel::Cleanup()
{
	delete m_Lifespan;
	m_Lifespan=0;

	delete m_AliasList;
	m_AliasList=0;

	delete m_ReleaseList;
	m_ReleaseList=0;

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

std::string MusicBrainz4::CLabel::ID() const
{
	return m_ID;
}

std::string MusicBrainz4::CLabel::Type() const
{
	return m_Type;
}

std::string MusicBrainz4::CLabel::Name() const
{
	return m_Name;
}

std::string MusicBrainz4::CLabel::SortName() const
{
	return m_SortName;
}

std::string MusicBrainz4::CLabel::LabelCode() const
{
	return m_LabelCode;
}

std::string MusicBrainz4::CLabel::Disambiguation() const
{
	return m_Disambiguation;
}

std::string MusicBrainz4::CLabel::Country() const
{
	return m_Country;
}

MusicBrainz4::CLifespan *MusicBrainz4::CLabel::Lifespan() const
{
	return m_Lifespan;
}

MusicBrainz4::CGenericList<MusicBrainz4::CAlias> *MusicBrainz4::CLabel::AliasList() const
{
	return m_AliasList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRelease> *MusicBrainz4::CLabel::ReleaseList() const
{
	return m_ReleaseList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRelation> *MusicBrainz4::CLabel::RelationList() const
{
	return m_RelationList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CTag> *MusicBrainz4::CLabel::TagList() const
{
	return m_TagList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CUserTag> *MusicBrainz4::CLabel::UserTagList() const
{
	return m_UserTagList;
}

MusicBrainz4::CRating *MusicBrainz4::CLabel::Rating() const
{
	return m_Rating;
}

MusicBrainz4::CUserRating *MusicBrainz4::CLabel::UserRating() const
{
	return m_UserRating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CLabel& Label)
{
	os << "Label:" << std::endl;

	os << "\tID:             " << Label.ID() << std::endl;
	os << "\tType:           " << Label.Type() << std::endl;
	os << "\tName:           " << Label.Name() << std::endl;
	os << "\tSort name:      " << Label.SortName() << std::endl;
	os << "\tLabel code:     " << Label.LabelCode() << std::endl;
	os << "\tDisambiguation: " << Label.Disambiguation() << std::endl;
	os << "\tCountry:        " << Label.Country() << std::endl;

	if (Label.Lifespan())
		os << *Label.Lifespan() << std::endl;

	if (Label.AliasList())
		os << *Label.AliasList() << std::endl;

	if (Label.ReleaseList())
		os << *Label.ReleaseList() << std::endl;

	if (Label.RelationList())
		os << *Label.RelationList() << std::endl;

	if (Label.TagList())
		os << *Label.TagList() << std::endl;

	if (Label.UserTagList())
		os << *Label.UserTagList() << std::endl;

	if (Label.Rating())
		os << *Label.Rating() << std::endl;

	if (Label.UserRating())
		os << *Label.UserRating() << std::endl;

	return os;
}

