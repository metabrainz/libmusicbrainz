/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2013 Andrew Hawkins

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

#include "musicbrainz5/URL.h"

#include "musicbrainz5/RelationListList.h"

class MusicBrainz5::CURLPrivate
{
	public:
		CURLPrivate()
		:	m_RelationListList(0)
		{
		}

		std::string m_ID;
		std::string m_Resource;
		CRelationListList *m_RelationListList;
};

MusicBrainz5::CURL::CURL(const XMLNode& Node)
:	CEntity(),
	m_d(new CURLPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "URL node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CURL::CURL(const CURL& Other)
:	CEntity(),
	m_d(new CURLPrivate)
{
	*this=Other;
}

MusicBrainz5::CURL& MusicBrainz5::CURL::operator =(const CURL& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Resource=Other.m_d->m_Resource;

		if (Other.m_d->m_RelationListList)
			m_d->m_RelationListList=new CRelationListList(*Other.m_d->m_RelationListList);
	}

	return *this;
}

MusicBrainz5::CURL::~CURL()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CURL::Cleanup()
{
	delete m_d->m_RelationListList;
	m_d->m_RelationListList=0;
}

MusicBrainz5::CURL *MusicBrainz5::CURL::Clone()
{
	return new CURL(*this);
}

void MusicBrainz5::CURL::ParseAttribute(const std::string& Name, const std::string& Value)
{
	if ("id"==Name)
		m_d->m_ID=Value;
	else
	{
		std::cerr << "Unrecognised url attribute: '" << Name << "'" << std::endl;
	}
}

void MusicBrainz5::CURL::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	if ("resource"==NodeName)
	{
		ProcessItem(Node,m_d->m_Resource);
	}
	else if ("relation-list"==NodeName)
	{
		ProcessRelationList(Node,m_d->m_RelationListList);
	}
	else
	{
		std::cerr << "Unrecognised url element: '" << NodeName << "'" << std::endl;
	}
}

std::string MusicBrainz5::CURL::GetElementName()
{
	return "url";
}

std::string MusicBrainz5::CURL::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz5::CURL::Resource() const
{
	return m_d->m_Resource;
}

MusicBrainz5::CRelationListList *MusicBrainz5::CURL::RelationListList() const
{
	return m_d->m_RelationListList;
}

std::ostream& MusicBrainz5::CURL::Serialise(std::ostream& os) const
{
	os << "URL:" << std::endl;

	CEntity::Serialise(os);

	os << "ID:       " << ID() << std::endl;
	os << "Resource: " << Resource() << std::endl;

	if (RelationListList())
		os << *RelationListList() << std::endl;

	return os;
}

