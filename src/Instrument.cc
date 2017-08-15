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

#include "musicbrainz5/Instrument.h"

#include "musicbrainz5/Alias.h"
#include "musicbrainz5/AliasList.h"
#include "musicbrainz5/Relation.h"
#include "musicbrainz5/RelationList.h"
#include "musicbrainz5/Tag.h"
#include "musicbrainz5/TagList.h"
#include "musicbrainz5/UserTag.h"
#include "musicbrainz5/UserTagList.h"

class MusicBrainz5::CInstrumentPrivate
{
	public:
		CInstrumentPrivate()
		:	m_AliasList(0),
			m_RelationList(0),
			m_TagList(0),
			m_UserTagList(0)
		{
		}

		std::string m_ID;
		std::string m_Type;
		std::string m_TypeID;
		std::string m_Name;
		std::string m_Disambiguation;
		std::string m_Description;
		std::string m_Annotation;
		CAliasList *m_AliasList;
		CRelationList *m_RelationList;
		CTagList *m_TagList;
		CUserTagList *m_UserTagList;
};

MusicBrainz5::CInstrument::CInstrument(const XMLNode& Node)
:	CEntity(),
	m_d(new CInstrumentPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Instrument node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CInstrument::CInstrument(const CInstrument& Other)
:	CEntity(),
	m_d(new CInstrumentPrivate)
{
	*this=Other;
}

MusicBrainz5::CInstrument& MusicBrainz5::CInstrument::operator =(const CInstrument& Other)
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
		m_d->m_Description=Other.m_d->m_Description;
		m_d->m_Annotation=Other.m_d->m_Annotation;

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

MusicBrainz5::CInstrument::~CInstrument()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CInstrument::Cleanup()
{
	delete m_d->m_AliasList;
	m_d->m_AliasList=0;

	delete m_d->m_RelationList;
	m_d->m_RelationList=0;

	delete m_d->m_TagList;
	m_d->m_TagList=0;

	delete m_d->m_UserTagList;
	m_d->m_UserTagList=0;
}

MusicBrainz5::CInstrument *MusicBrainz5::CInstrument::Clone()
{
	return new CInstrument(*this);
}

void MusicBrainz5::CInstrument::ParseAttribute(const std::string& Name, const std::string& Value)
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
		std::cerr << "Unrecognised instrument attribute: '" << Name << "'" << std::endl;
#endif
	}
}

void MusicBrainz5::CInstrument::ParseElement(const XMLNode& Node)
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
	else if ("description"==NodeName)
	{
		ProcessItem(Node,m_d->m_Description);
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
	else
	{
#ifdef _MB5_DEBUG_
		std::cerr << "Unrecognised instrument element: '" << NodeName << "'" << std::endl;
#endif
	}
}

std::string MusicBrainz5::CInstrument::GetElementName()
{
	return "instrument";
}

std::string MusicBrainz5::CInstrument::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz5::CInstrument::Type() const
{
	return m_d->m_Type;
}

std::string MusicBrainz5::CInstrument::TypeID() const
{
	return m_d->m_TypeID;
}

std::string MusicBrainz5::CInstrument::Name() const
{
	return m_d->m_Name;
}

std::string MusicBrainz5::CInstrument::Disambiguation() const
{
	return m_d->m_Disambiguation;
}

std::string MusicBrainz5::CInstrument::Description() const
{
	return m_d->m_Description;
}

std::string MusicBrainz5::CInstrument::Annotation() const
{
	return m_d->m_Annotation;
}

MusicBrainz5::CAliasList *MusicBrainz5::CInstrument::AliasList() const
{
	return m_d->m_AliasList;
}

MusicBrainz5::CRelationList *MusicBrainz5::CInstrument::RelationList() const
{
	return m_d->m_RelationList;
}

MusicBrainz5::CTagList *MusicBrainz5::CInstrument::TagList() const
{
	return m_d->m_TagList;
}

MusicBrainz5::CUserTagList *MusicBrainz5::CInstrument::UserTagList() const
{
	return m_d->m_UserTagList;
}

std::ostream& MusicBrainz5::CInstrument::Serialise(std::ostream& os) const
{
	os << "Instrument:" << std::endl;

	CEntity::Serialise(os);

	os << "\tID:             " << ID() << std::endl;
	os << "\tType:           " << Type() << std::endl;
	os << "\tTypeID:         " << TypeID() << std::endl;
	os << "\tName:           " << Name() << std::endl;
	os << "\tDisambiguation: " << Disambiguation() << std::endl;
	os << "\tDescription:    " << Description() << std::endl;
	os << "\tAnnotation:     " << Annotation() << std::endl;

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

