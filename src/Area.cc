/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2017 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

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

#include "musicbrainz5/Area.h"

#include "musicbrainz5/ISO31661CodeList.h"
#include "musicbrainz5/ISO31662CodeList.h"
#include "musicbrainz5/ISO31663CodeList.h"
#include "musicbrainz5/Lifespan.h"
#include "musicbrainz5/Alias.h"
#include "musicbrainz5/AliasList.h"
#include "musicbrainz5/Relation.h"
#include "musicbrainz5/RelationList.h"
#include "musicbrainz5/Tag.h"
#include "musicbrainz5/TagList.h"
#include "musicbrainz5/UserTag.h"
#include "musicbrainz5/UserTagList.h"

class MusicBrainz5::CAreaPrivate
{
	public:
		CAreaPrivate()
		:	m_ISO31661CodeList(0),
			m_ISO31662CodeList(0),
			m_ISO31663CodeList(0),
			m_Lifespan(0),
			m_AliasList(0),
			m_RelationList(0),
			m_TagList(0),
			m_UserTagList(0)
		{
		}

		std::string m_ID;
		std::string m_Type;
		std::string m_TypeID;
		std::string m_Name;
		std::string m_SortName;
		std::string m_Disambiguation;
		CISO31661CodeList *m_ISO31661CodeList;
		CISO31662CodeList *m_ISO31662CodeList;
		CISO31663CodeList *m_ISO31663CodeList;
		std::string m_Annotation;
		CLifespan *m_Lifespan;
		CAliasList *m_AliasList;
		CRelationList *m_RelationList;
		CTagList *m_TagList;
		CUserTagList *m_UserTagList;
};

MusicBrainz5::CArea::CArea(const XMLNode& Node)
:	CEntity(),
	m_d(new CAreaPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Area node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CArea::CArea(const CArea& Other)
:	CEntity(),
	m_d(new CAreaPrivate)
{
	*this=Other;
}

MusicBrainz5::CArea& MusicBrainz5::CArea::operator =(const CArea& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Type=Other.m_d->m_Type;
		m_d->m_TypeID=Other.m_d->m_TypeID;
		m_d->m_Name=Other.m_d->m_Name;
		m_d->m_SortName=Other.m_d->m_SortName;
		m_d->m_Disambiguation=Other.m_d->m_Disambiguation;

		if (Other.m_d->m_ISO31661CodeList)
			m_d->m_ISO31661CodeList=new CISO31661CodeList(*Other.m_d->m_ISO31661CodeList);

		if (Other.m_d->m_ISO31662CodeList)
			m_d->m_ISO31662CodeList=new CISO31662CodeList(*Other.m_d->m_ISO31662CodeList);

		if (Other.m_d->m_ISO31663CodeList)
			m_d->m_ISO31663CodeList=new CISO31663CodeList(*Other.m_d->m_ISO31663CodeList);

		m_d->m_Annotation=Other.m_d->m_Annotation;

		if (Other.m_d->m_Lifespan)
			m_d->m_Lifespan=new CLifespan(*Other.m_d->m_Lifespan);

		if (Other.m_d->m_AliasList)
			m_d->m_AliasList=new CAliasList(*Other.m_d->m_AliasList);

		if (Other.m_d->m_RelationList)
			m_d->m_RelationList=new CRelationList(*Other.m_d->m_RelationList);

		if (Other.m_d->m_TagList)
			m_d->m_TagList=new CTagList(*Other.m_d->m_TagList);

		if (Other.m_d->m_UserTagList)
			m_d->m_UserTagList=new CUserTagList(*Other.m_d->m_UserTagList);
	}

	return *this;
}

MusicBrainz5::CArea::~CArea()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CArea::Cleanup()
{
	delete m_d->m_ISO31661CodeList;
	m_d->m_ISO31661CodeList=0;

	delete m_d->m_ISO31662CodeList;
	m_d->m_ISO31662CodeList=0;

	delete m_d->m_ISO31663CodeList;
	m_d->m_ISO31663CodeList=0;

	delete m_d->m_Lifespan;
	m_d->m_Lifespan=0;

	delete m_d->m_AliasList;
	m_d->m_AliasList=0;

	delete m_d->m_RelationList;
	m_d->m_RelationList=0;

	delete m_d->m_TagList;
	m_d->m_TagList=0;

	delete m_d->m_UserTagList;
	m_d->m_UserTagList=0;

}

MusicBrainz5::CArea *MusicBrainz5::CArea::Clone()
{
	return new CArea(*this);
}

void MusicBrainz5::CArea::ParseAttribute(const std::string& Name, const std::string& Value)
{
	if ("id"==Name)
		m_d->m_ID=Value;
	else
	{
#ifdef _MB5_DEBUG_
		std::cerr << "Unrecognised Area attribute: '" << Name << "'" << std::endl;
#endif
	}
}

void MusicBrainz5::CArea::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	if ("type"==NodeName)
	{
		ProcessItem(Node,m_d->m_Type);
	}
	else if ("type-id"==NodeName)
	{
		ProcessItem(Node,m_d->m_TypeID);
	}
	else if ("name"==NodeName)
	{
		ProcessItem(Node,m_d->m_Name);
	}
	else if ("sort-name"==NodeName)
	{
		ProcessItem(Node,m_d->m_SortName);
	}
	else if ("Disambiguation"==NodeName)
	{
		ProcessItem(Node,m_d->m_Disambiguation);
	}
	else if ("iso-3166-1-code-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_ISO31661CodeList);
	}
	else if ("iso-3166-2-code-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_ISO31662CodeList);
	}
	else if ("iso-3166-3-code-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_ISO31663CodeList);
	}
	else if ("annotation"==NodeName)
	{
		ProcessItem(Node,m_d->m_Annotation);
	}
	else if ("life-span"==NodeName)
	{
		ProcessItem(Node,m_d->m_Lifespan);
	}
	else if ("alias-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_AliasList);
	}
	else if ("relation-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_RelationList);
	}
	else if ("tag-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_TagList);
	}
	else if ("user-tag-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_UserTagList);
	}
	else
	{
#ifdef _MB5_DEBUG_
		std::cerr << "Unrecognised Area element: '" << NodeName << "'" << std::endl;
#endif
	}
}

std::string MusicBrainz5::CArea::GetElementName()
{
	return "Area";
}

std::string MusicBrainz5::CArea::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz5::CArea::Type() const
{
	return m_d->m_Type;
}

std::string MusicBrainz5::CArea::TypeID() const
{
	return m_d->m_TypeID;
}

std::string MusicBrainz5::CArea::Name() const
{
	return m_d->m_Name;
}

std::string MusicBrainz5::CArea::SortName() const
{
	return m_d->m_SortName;
}

std::string MusicBrainz5::CArea::Disambiguation() const
{
	return m_d->m_Disambiguation;
}

MusicBrainz5::CISO31661CodeList *MusicBrainz5::CArea::ISO31661CodeList() const
{
	return m_d->m_ISO31661CodeList;
}

MusicBrainz5::CISO31662CodeList *MusicBrainz5::CArea::ISO31662CodeList() const
{
	return m_d->m_ISO31662CodeList;
}

MusicBrainz5::CISO31663CodeList *MusicBrainz5::CArea::ISO31663CodeList() const
{
	return m_d->m_ISO31663CodeList;
}

std::string MusicBrainz5::CArea::Annotation() const
{
	return m_d->m_Annotation;
}

MusicBrainz5::CLifespan *MusicBrainz5::CArea::Lifespan() const
{
	return m_d->m_Lifespan;
}

MusicBrainz5::CAliasList *MusicBrainz5::CArea::AliasList() const
{
	return m_d->m_AliasList;
}

MusicBrainz5::CRelationList *MusicBrainz5::CArea::RelationList() const
{
	return m_d->m_RelationList;
}

MusicBrainz5::CTagList *MusicBrainz5::CArea::TagList() const
{
	return m_d->m_TagList;
}

MusicBrainz5::CUserTagList *MusicBrainz5::CArea::UserTagList() const
{
	return m_d->m_UserTagList;
}


std::ostream& MusicBrainz5::CArea::Serialise(std::ostream& os) const
{
	os << "Area:" << std::endl;

	CEntity::Serialise(os);

	os << "\tID:               " << ID() << std::endl;
	os << "\tType:             " << Type() << std::endl;
	os << "\tTypeID:           " << TypeID() << std::endl;
	os << "\tName:             " << Name() << std::endl;
	os << "\tSortName:         " << SortName() << std::endl;
	os << "\tDisambiguation:   " << Disambiguation() << std::endl;

	if (ISO31661CodeList())
		os << *ISO31661CodeList() << std::endl;

	if (ISO31662CodeList())
		os << *ISO31662CodeList() << std::endl;

	if (ISO31663CodeList())
		os << *ISO31663CodeList() << std::endl;

	os << "\tAnnotation:       " << Annotation() << std::endl;

	if (Lifespan())
		os << *Lifespan() << std::endl;

	if (AliasList())
		os << *AliasList() << std::endl;

	if (RelationList())
		os << *RelationList() << std::endl;

	if (TagList())
		os << *TagList() << std::endl;

	if (UserTagList())
		os << *UserTagList() << std::endl;

	return os;
}

