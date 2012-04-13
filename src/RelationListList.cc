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

#include "musicbrainz4/RelationListList.h"

#include <vector>

#include "musicbrainz4/RelationList.h"
#include "musicbrainz4/Relation.h"

class MusicBrainz4::CRelationListListPrivate
{
	public:
		CRelationListListPrivate()
		:	m_ListGroup(0)
		{
		}

		std::vector<CRelationList *> *m_ListGroup;
};

MusicBrainz4::CRelationListList::CRelationListList()
:	m_d(new CRelationListListPrivate)
{
}

MusicBrainz4::CRelationListList::CRelationListList(const CRelationListList& Other)
:	m_d(new CRelationListListPrivate)
{
	*this=Other;
}

MusicBrainz4::CRelationListList& MusicBrainz4::CRelationListList::operator =(const CRelationListList& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		if (Other.m_d->m_ListGroup)
		{
			m_d->m_ListGroup=new std::vector<CRelationList *>;

			for (std::vector<CRelationList *>::const_iterator ThisRelationList=Other.m_d->m_ListGroup->begin();ThisRelationList!=Other.m_d->m_ListGroup->end();++ThisRelationList)
			{
				CRelationList *RelationList=*ThisRelationList;
				m_d->m_ListGroup->push_back(new CRelationList(*RelationList));
			}
		}
	}

	return *this;
}

MusicBrainz4::CRelationListList::~CRelationListList()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz4::CRelationListList::Cleanup()
{
	if (m_d->m_ListGroup)
	{
		for (std::vector<CRelationList *>::const_iterator ThisRelationList=m_d->m_ListGroup->begin();ThisRelationList!=m_d->m_ListGroup->end();++ThisRelationList)
		{
			CRelationList *RelationList=*ThisRelationList;

			delete RelationList;
		}
	}

	delete m_d->m_ListGroup;
	m_d->m_ListGroup=0;
}

void MusicBrainz4::CRelationListList::Add(CRelationList *RelationList)
{
	if (!m_d->m_ListGroup)
		m_d->m_ListGroup=new std::vector<CRelationList *>;

	m_d->m_ListGroup->push_back(new CRelationList(*RelationList));
}

int MusicBrainz4::CRelationListList::NumItems() const
{
	int Ret=0;

	if (m_d->m_ListGroup)
		Ret=m_d->m_ListGroup->size();

	return Ret;
}

MusicBrainz4::CRelationList *MusicBrainz4::CRelationListList::Item(int Item) const
{
	CRelationList *RelationList=0;

	if (m_d->m_ListGroup && Item<(int)m_d->m_ListGroup->size())
		RelationList=(*m_d->m_ListGroup)[Item];

	return RelationList;
}

std::ostream& MusicBrainz4::CRelationListList::Serialise(std::ostream& os) const
{
	if (m_d->m_ListGroup && m_d->m_ListGroup->size()!=0)
	{
		os << "RelationLists:" << std::endl;

		for (int count=0;count<NumItems();count++)
		{
			os << *Item(count) << std::endl;
		}
	}

	return os;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CRelationListList& RelationListList)
{
	return RelationListList.Serialise(os);
}

