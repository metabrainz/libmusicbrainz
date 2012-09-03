/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

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

#include "musicbrainz5/RelationList.h"

#include "musicbrainz5/Relation.h"

class MusicBrainz5::CRelationListPrivate
{
	public:
		std::string m_TargetType;
};

MusicBrainz5::CRelationList::CRelationList(const XMLNode& Node)
:	CListImpl<CRelation>(),
	m_d(new CRelationListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "RelationList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CRelationList::CRelationList(const CRelationList& Other)
:	CListImpl<CRelation>(),
	m_d(new CRelationListPrivate)
{
	*this=Other;
}

MusicBrainz5::CRelationList& MusicBrainz5::CRelationList::operator =(const CRelationList& Other)
{
	if (this!=&Other)
	{
		CListImpl<CRelation>::operator =(Other);

		m_d->m_TargetType=Other.m_d->m_TargetType;
	}

	return *this;
}

MusicBrainz5::CRelationList::~CRelationList()
{
	delete m_d;
}

MusicBrainz5::CRelationList *MusicBrainz5::CRelationList::Clone()
{
	return new CRelationList(*this);
}

void MusicBrainz5::CRelationList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	if ("target-type"==Name)
		ProcessItem(Value,m_d->m_TargetType);
	else
		CListImpl<CRelation>::ParseAttribute(Name,Value);
}

void MusicBrainz5::CRelationList::ParseElement(const XMLNode& Node)
{
	CListImpl<CRelation>::ParseElement(Node);
}

std::string MusicBrainz5::CRelationList::GetElementName()
{
	return "relation-list";
}

std::string MusicBrainz5::CRelationList::TargetType() const
{
	return m_d->m_TargetType;
}

std::ostream& MusicBrainz5::CRelationList::Serialise(std::ostream& os) const
{
	os << "Relation list:" << std::endl;

	os << "\tTarget type: " << TargetType() << std::endl;

	CListImpl<CRelation>::Serialise(os);

	return os;
}
