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
#include "musicbrainz4/defines.h"

#include "musicbrainz4/Label.h"

#include <iostream>

#include "musicbrainz4/Lifespan.h"
#include "musicbrainz4/IPI.h"
#include "musicbrainz4/Rating.h"
#include "musicbrainz4/UserRating.h"
#include "musicbrainz4/Alias.h"
#include "musicbrainz4/AliasList.h"
#include "musicbrainz4/Release.h"
#include "musicbrainz4/ReleaseList.h"
#include "musicbrainz4/Relation.h"
#include "musicbrainz4/RelationList.h"
#include "musicbrainz4/RelationListList.h"
#include "musicbrainz4/Tag.h"
#include "musicbrainz4/TagList.h"
#include "musicbrainz4/UserTag.h"
#include "musicbrainz4/UserTagList.h"

class MusicBrainz4::CLabelPrivate
{
	public:
		CLabelPrivate()
		:	m_LabelCode(0),
			m_IPIList(0),
			m_Lifespan(0),
			m_AliasList(0),
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
		std::string m_Name;
		std::string m_SortName;
		int m_LabelCode;
		std::string m_IPI;
		CIPIList *m_IPIList;
		std::string m_Disambiguation;
		std::string m_Country;
		CLifespan *m_Lifespan;
		CAliasList *m_AliasList;
		CReleaseList *m_ReleaseList;
		CRelationListList *m_RelationListList;
		CTagList *m_TagList;
		CUserTagList *m_UserTagList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
};

MusicBrainz4::CLabel::CLabel(const XMLNode& Node)
:	CEntity(),
	m_d(new CLabelPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Label node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CLabel::CLabel(const CLabel& Other)
:	CEntity(),
	m_d(new CLabelPrivate)
{
	*this=Other;
}

MusicBrainz4::CLabel& MusicBrainz4::CLabel::operator =(const CLabel& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Type=Other.m_d->m_Type;
		m_d->m_Name=Other.m_d->m_Name;
		m_d->m_SortName=Other.m_d->m_SortName;
		m_d->m_LabelCode=Other.m_d->m_LabelCode;
		m_d->m_IPI=Other.m_d->m_IPI;

		if (Other.m_d->m_IPIList)
			m_d->m_IPIList=new CIPIList(*Other.m_d->m_IPIList);

		m_d->m_Disambiguation=Other.m_d->m_Disambiguation;
		m_d->m_Country=Other.m_d->m_Country;

		if (Other.m_d->m_Lifespan)
			m_d->m_Lifespan=new CLifespan(*Other.m_d->m_Lifespan);

		if (Other.m_d->m_AliasList)
			m_d->m_AliasList=new CAliasList(*Other.m_d->m_AliasList);

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

MusicBrainz4::CLabel::~CLabel()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz4::CLabel::Cleanup()
{
	delete m_d->m_IPIList;
	m_d->m_IPIList=0;

	delete m_d->m_Lifespan;
	m_d->m_Lifespan=0;

	delete m_d->m_AliasList;
	m_d->m_AliasList=0;

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

MusicBrainz4::CLabel *MusicBrainz4::CLabel::Clone()
{
	return new CLabel(*this);
}

void MusicBrainz4::CLabel::ParseAttribute(const std::string& Name, const std::string& Value)
{
	if ("id"==Name)
		m_d->m_ID=Value;
	else if ("type"==Name)
		m_d->m_Type=Value;
	else
	{
		std::cerr << "Unrecognised label attribute: '" << Name << "'" << std::endl;
	}
}

void MusicBrainz4::CLabel::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	if ("name"==NodeName)
	{
		ProcessItem(Node,m_d->m_Name);
	}
	else if ("sort-name"==NodeName)
	{
		ProcessItem(Node,m_d->m_SortName);
	}
	else if ("label-code"==NodeName)
	{
		ProcessItem(Node,m_d->m_LabelCode);
	}
	else if ("ipi"==NodeName)
	{
		ProcessItem(Node,m_d->m_IPI);
	}
	else if ("ipi-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_IPIList);
	}
	else if ("disambiguation"==NodeName)
	{
		ProcessItem(Node,m_d->m_Disambiguation);
	}
	else if ("country"==NodeName)
	{
		ProcessItem(Node,m_d->m_Country);
	}
	else if ("life-span"==NodeName)
	{
		ProcessItem(Node,m_d->m_Lifespan);
	}
	else if ("alias-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_AliasList);
	}
	else if ("release-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_ReleaseList);
	}
	else if ("relation-list"==NodeName)
	{
		ProcessRelationList(Node,m_d->m_RelationListList);
	}
	else if ("tag-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_TagList);
	}
	else if ("user-tag-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_UserTagList);
	}
	else if ("rating"==NodeName)
	{
		ProcessItem(Node,m_d->m_Rating);
	}
	else if ("user-rating"==NodeName)
	{
		ProcessItem(Node,m_d->m_UserRating);
	}
	else
	{
		std::cerr << "Unrecognised label element: '" << NodeName << "'" << std::endl;
	}
}

std::string MusicBrainz4::CLabel::GetElementName()
{
	return "label";
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

std::string MusicBrainz4::CLabel::IPI() const
{
	return m_d->m_IPI;
}

MusicBrainz4::CIPIList *MusicBrainz4::CLabel::IPIList() const
{
	return m_d->m_IPIList;
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

MusicBrainz4::CAliasList *MusicBrainz4::CLabel::AliasList() const
{
	return m_d->m_AliasList;
}

MusicBrainz4::CReleaseList *MusicBrainz4::CLabel::ReleaseList() const
{
	return m_d->m_ReleaseList;
}

MusicBrainz4::CRelationList *MusicBrainz4::CLabel::RelationList() const
{
	return m_d->m_RelationListList?m_d->m_RelationListList->Item(m_d->m_RelationListList->NumItems()-1):0;
}

MusicBrainz4::CRelationListList *MusicBrainz4::CLabel::RelationListList() const
{
	return m_d->m_RelationListList;
}

MusicBrainz4::CTagList *MusicBrainz4::CLabel::TagList() const
{
	return m_d->m_TagList;
}

MusicBrainz4::CUserTagList *MusicBrainz4::CLabel::UserTagList() const
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

std::ostream& MusicBrainz4::CLabel::Serialise(std::ostream& os) const
{
	os << "Label:" << std::endl;

	CEntity::Serialise(os);

	os << "\tID:             " << ID() << std::endl;
	os << "\tType:           " << Type() << std::endl;
	os << "\tName:           " << Name() << std::endl;
	os << "\tSort name:      " << SortName() << std::endl;
	os << "\tLabel code:     " << LabelCode() << std::endl;

	if (IPIList())
		os << *IPIList() << std::endl;

	os << "\tDisambiguation: " << Disambiguation() << std::endl;
	os << "\tCountry:        " << Country() << std::endl;

	if (Lifespan())
		os << *Lifespan() << std::endl;

	if (AliasList())
		os << *AliasList() << std::endl;

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

