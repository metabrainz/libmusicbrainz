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

#include "ParserUtils.h"

class MusicBrainz4::CLabelPrivate
{
	public:
		CLabelPrivate()
		:	m_LabelCode(0),
			m_Lifespan(0),
			m_AliasList(0),
			m_ReleaseList(0),
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
		int m_LabelCode;
		std::string m_Disambiguation;
		std::string m_Country;
		CLifespan *m_Lifespan;
		CGenericList<CAlias> *m_AliasList;
		CGenericList<CRelease> *m_ReleaseList;
		CGenericList<CRelation> *m_RelationList;
		CGenericList<CTag> *m_TagList;
		CGenericList<CUserTag> *m_UserTagList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
};
MusicBrainz4::CLabel::CLabel(const XMLNode& Node)
:	m_d(new CLabelPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Label node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("id"))
			m_d->m_ID=Node.getAttribute("id");

		if (Node.isAttributeSet("type"))
			m_d->m_Type=Node.getAttribute("type");

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("name"==NodeName)
			{
				m_d->m_Name=NodeValue;
			}
			else if ("sort-name"==NodeName)
			{
				m_d->m_SortName=NodeValue;
			}
			else if ("label-code"==NodeName)
			{
				ProcessItem(NodeValue,m_d->m_LabelCode);
			}
			else if ("disambiguation"==NodeName)
			{
				m_d->m_Disambiguation=NodeValue;
			}
			else if ("country"==NodeName)
			{
				m_d->m_Country=NodeValue;
			}
			else if ("life-span"==NodeName)
			{
				m_d->m_Lifespan=new CLifespan(ChildNode);
			}
			else if ("alias-list"==NodeName)
			{
				m_d->m_AliasList=new CGenericList<CAlias>(ChildNode,"alias");
			}
			else if ("release-list"==NodeName)
			{
				m_d->m_ReleaseList=new CGenericList<CRelease>(ChildNode,"release");
			}
			else if ("relation-list"==NodeName)
			{
				m_d->m_RelationList=new CGenericList<CRelation>(ChildNode,"relation");
			}
			else if ("tag-list"==NodeName)
			{
				m_d->m_TagList=new CGenericList<CTag>(ChildNode,"tag");
			}
			else if ("user-tag-list"==NodeName)
			{
				m_d->m_UserTagList=new CGenericList<CUserTag>(ChildNode,"user-tag");
			}
			else if ("rating"==NodeName)
			{
				m_d->m_Rating=new CRating(ChildNode);
			}
			else if ("user-rating"==NodeName)
			{
				m_d->m_UserRating=new CUserRating(ChildNode);
			}
			else
			{
				std::cerr << "Unrecognised label node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CLabel::CLabel(const CLabel& Other)
:	m_d(new CLabelPrivate)
{
	*this=Other;
}

MusicBrainz4::CLabel& MusicBrainz4::CLabel::operator =(const CLabel& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Type=Other.m_d->m_Type;
		m_d->m_Name=Other.m_d->m_Name;
		m_d->m_SortName=Other.m_d->m_SortName;
		m_d->m_LabelCode=Other.m_d->m_LabelCode;
		m_d->m_Disambiguation=Other.m_d->m_Disambiguation;
		m_d->m_Country=Other.m_d->m_Country;

		if (Other.m_d->m_Lifespan)
			m_d->m_Lifespan=new CLifespan(*Other.m_d->m_Lifespan);

		if (Other.m_d->m_AliasList)
			m_d->m_AliasList=new CGenericList<CAlias>(*Other.m_d->m_AliasList);

		if (Other.m_d->m_ReleaseList)
			m_d->m_ReleaseList=new CGenericList<CRelease>(*Other.m_d->m_ReleaseList);

		if (Other.m_d->m_RelationList)
			m_d->m_RelationList=new CGenericList<CRelation>(*Other.m_d->m_RelationList);

		if (Other.m_d->m_TagList)
			m_d->m_TagList=new CGenericList<CTag>(*Other.m_d->m_TagList);

		if (Other.m_d->m_UserTagList)
			m_d->m_UserTagList=new CGenericList<CUserTag>(*Other.m_d->m_UserTagList);

		if (Other.m_d->m_Rating)
			m_d->m_Rating=new CRating(*Other.m_d->m_Rating);

		if (Other.m_d->m_UserRating)
			m_d->m_UserRating=new CUserRating(*Other.m_d->m_UserRating);
	}

	return *this;
}

MusicBrainz4::CLabel::~CLabel()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz4::CLabel::Cleanup()
{
	delete m_d->m_Lifespan;
	m_d->m_Lifespan=0;

	delete m_d->m_AliasList;
	m_d->m_AliasList=0;

	delete m_d->m_ReleaseList;
	m_d->m_ReleaseList=0;

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

std::string MusicBrainz4::CLabel::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz4::CLabel::Type() const
{
	return m_d->m_Type;
}

std::string MusicBrainz4::CLabel::Name() const
{
	return m_d->m_Name;
}

std::string MusicBrainz4::CLabel::SortName() const
{
	return m_d->m_SortName;
}

int MusicBrainz4::CLabel::LabelCode() const
{
	return m_d->m_LabelCode;
}

std::string MusicBrainz4::CLabel::Disambiguation() const
{
	return m_d->m_Disambiguation;
}

std::string MusicBrainz4::CLabel::Country() const
{
	return m_d->m_Country;
}

MusicBrainz4::CLifespan *MusicBrainz4::CLabel::Lifespan() const
{
	return m_d->m_Lifespan;
}

MusicBrainz4::CGenericList<MusicBrainz4::CAlias> *MusicBrainz4::CLabel::AliasList() const
{
	return m_d->m_AliasList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRelease> *MusicBrainz4::CLabel::ReleaseList() const
{
	return m_d->m_ReleaseList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRelation> *MusicBrainz4::CLabel::RelationList() const
{
	return m_d->m_RelationList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CTag> *MusicBrainz4::CLabel::TagList() const
{
	return m_d->m_TagList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CUserTag> *MusicBrainz4::CLabel::UserTagList() const
{
	return m_d->m_UserTagList;
}

MusicBrainz4::CRating *MusicBrainz4::CLabel::Rating() const
{
	return m_d->m_Rating;
}

MusicBrainz4::CUserRating *MusicBrainz4::CLabel::UserRating() const
{
	return m_d->m_UserRating;
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

