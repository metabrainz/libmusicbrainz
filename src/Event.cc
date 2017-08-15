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

#include "musicbrainz5/Event.h"

#include "musicbrainz5/Lifespan.h"
#include "musicbrainz5/Alias.h"
#include "musicbrainz5/AliasList.h"
#include "musicbrainz5/Relation.h"
#include "musicbrainz5/RelationList.h"
#include "musicbrainz5/Tag.h"
#include "musicbrainz5/TagList.h"
#include "musicbrainz5/UserTag.h"
#include "musicbrainz5/UserTagList.h"
#include "musicbrainz5/Rating.h"
#include "musicbrainz5/UserRating.h"

class MusicBrainz5::CEventPrivate
{
	public:
		CEventPrivate()
		:	m_Lifespan(0),
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
		std::string m_TypeID;
		std::string m_Name;
		std::string m_Disambiguation;
		std::string m_Cancelled;
		CLifespan *m_Lifespan;
		std::string m_Time;
		std::string m_Setlist;
		std::string m_Annotation;
		CAliasList *m_AliasList;
		CRelationList *m_RelationList;
		CTagList *m_TagList;
		CUserTagList *m_UserTagList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
};

MusicBrainz5::CEvent::CEvent(const XMLNode& Node)
:	CEntity(),
	m_d(new CEventPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Event node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CEvent::CEvent(const CEvent& Other)
:	CEntity(),
	m_d(new CEventPrivate)
{
	*this=Other;
}

MusicBrainz5::CEvent& MusicBrainz5::CEvent::operator =(const CEvent& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Type=Other.m_d->m_Type;
		m_d->m_TypeID=Other.m_d->m_TypeID;
		m_d->m_Name=Other.m_d->m_Name;
		m_d->m_Disambiguation=Other.m_d->m_Disambiguation;
		m_d->m_Cancelled=Other.m_d->m_Cancelled;

		if (Other.m_d->m_Lifespan)
			m_d->m_Lifespan=new CLifespan(*Other.m_d->m_Lifespan);

		m_d->m_Time=Other.m_d->m_Time;
		m_d->m_Setlist=Other.m_d->m_Setlist;
		m_d->m_Annotation=Other.m_d->m_Annotation;

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

MusicBrainz5::CEvent::~CEvent()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CEvent::Cleanup()
{
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

	delete m_d->m_Rating;
	m_d->m_Rating=0;

	delete m_d->m_UserRating;
	m_d->m_UserRating=0;
}

MusicBrainz5::CEvent *MusicBrainz5::CEvent::Clone()
{
	return new CEvent(*this);
}

void MusicBrainz5::CEvent::ParseAttribute(const std::string& Name, const std::string& Value)
{
	if ("id"==Name)
		m_d->m_ID=Value;
	else if ("type"==Name)
		m_d->m_Type=Value;
	else if ("type-id"==Name)
		m_d->m_TypeID=Value;
	else
	{
#ifdef _MB5_DEBUG_
		std::cerr << "Unrecognised event attribute: '" << Name << "'" << std::endl;
#endif
	}
}

void MusicBrainz5::CEvent::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	if ("name"==NodeName)
	{
		ProcessItem(Node,m_d->m_Name);
	}
	else if ("disambiguation"==NodeName)
	{
		ProcessItem(Node,m_d->m_Disambiguation);
	}
	else if ("cancelled"==NodeName)
	{
		ProcessItem(Node,m_d->m_Cancelled);
	}
	else if ("life-span"==NodeName)
	{
		ProcessItem(Node,m_d->m_Lifespan);
	}
	else if ("time"==NodeName)
	{
		ProcessItem(Node,m_d->m_Time);
	}
	else if ("setlist"==NodeName)
	{
		ProcessItem(Node,m_d->m_Setlist);
	}
	else if ("annotation"==NodeName)
	{
		ProcessItem(Node,m_d->m_Annotation);
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
#ifdef _MB5_DEBUG_
		std::cerr << "Unrecognised event element: '" << NodeName << "'" << std::endl;
#endif
	}
}

std::string MusicBrainz5::CEvent::GetElementName()
{
	return "event";
}

std::string MusicBrainz5::CEvent::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz5::CEvent::Type() const
{
	return m_d->m_Type;
}

std::string MusicBrainz5::CEvent::TypeID() const
{
	return m_d->m_TypeID;
}

std::string MusicBrainz5::CEvent::Name() const
{
	return m_d->m_Name;
}

std::string MusicBrainz5::CEvent::Disambiguation() const
{
	return m_d->m_Disambiguation;
}

std::string MusicBrainz5::CEvent::Cancelled() const
{
	return m_d->m_Cancelled;
}

MusicBrainz5::CLifespan *MusicBrainz5::CEvent::Lifespan() const
{
	return m_d->m_Lifespan;
}

std::string MusicBrainz5::CEvent::Time() const
{
	return m_d->m_Time;
}

std::string MusicBrainz5::CEvent::Setlist() const
{
	return m_d->m_Setlist;
}

std::string MusicBrainz5::CEvent::Annotation() const
{
	return m_d->m_Annotation;
}

MusicBrainz5::CAliasList *MusicBrainz5::CEvent::AliasList() const
{
	return m_d->m_AliasList;
}

MusicBrainz5::CRelationList *MusicBrainz5::CEvent::RelationList() const
{
	return m_d->m_RelationList;
}

MusicBrainz5::CTagList *MusicBrainz5::CEvent::TagList() const
{
	return m_d->m_TagList;
}

MusicBrainz5::CUserTagList *MusicBrainz5::CEvent::UserTagList() const
{
	return m_d->m_UserTagList;
}

MusicBrainz5::CRating *MusicBrainz5::CEvent::Rating() const
{
	return m_d->m_Rating;
}

MusicBrainz5::CUserRating *MusicBrainz5::CEvent::UserRating() const
{
	return m_d->m_UserRating;
}

std::ostream& MusicBrainz5::CEvent::Serialise(std::ostream& os) const
{
	os << "Artist:" << std::endl;

	CEntity::Serialise(os);

	os << "\tID:             " << ID() << std::endl;
	os << "\tType:           " << Type() << std::endl;
	os << "\tTypeID:         " << TypeID() << std::endl;
	os << "\tName:           " << Name() << std::endl;
	os << "\tDisambiguation: " << Disambiguation() << std::endl;
	os << "\tCancelled:      " << Cancelled() << std::endl;

	if (Lifespan())
		os << *Lifespan() << std::endl;

	os << "\tTime:           " << Time() << std::endl;
	os << "\tSetlist:        " << Setlist() << std::endl;
	os << "\tAnnotation:     " << Annotation() << std::endl;

	if (AliasList())
		os << *AliasList() << std::endl;

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

