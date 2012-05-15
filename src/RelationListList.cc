/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

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

#include "musicbrainz5/RelationListList.h"

#include <vector>

#include "musicbrainz5/RelationList.h"
#include "musicbrainz5/Relation.h"

class MusicBrainz5::CRelationListListPrivate
{
	public:
		CRelationListListPrivate()
		:	m_ListGroup(0)
		{
		}

		std::vector<CRelationList *> *m_ListGroup;
};

MusicBrainz5::CRelationListList::CRelationListList()
:	m_d(new CRelationListListPrivate)
{
}

MusicBrainz5::CRelationListList::CRelationListList(const CRelationListList& Other)
:	m_d(new CRelationListListPrivate)
{
	*this=Other;
}

MusicBrainz5::CRelationListList& MusicBrainz5::CRelationListList::operator =(const CRelationListList& Other)
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

MusicBrainz5::CRelationListList::~CRelationListList()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CRelationListList::Cleanup()
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

void MusicBrainz5::CRelationListList::Add(CRelationList *RelationList)
{
	if (!m_d->m_ListGroup)
		m_d->m_ListGroup=new std::vector<CRelationList *>;

	m_d->m_ListGroup->push_back(new CRelationList(*RelationList));
}

int MusicBrainz5::CRelationListList::NumItems() const
{
	int Ret=0;

	if (m_d->m_ListGroup)
		Ret=m_d->m_ListGroup->size();

	return Ret;
}

MusicBrainz5::CRelationList *MusicBrainz5::CRelationListList::Item(int Item) const
{
	CRelationList *RelationList=0;

	if (m_d->m_ListGroup && Item<(int)m_d->m_ListGroup->size())
		RelationList=(*m_d->m_ListGroup)[Item];

	return RelationList;
}

std::ostream& MusicBrainz5::CRelationListList::Serialise(std::ostream& os) const
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

std::ostream& operator << (std::ostream& os, const MusicBrainz5::CRelationListList& RelationListList)
{
	return RelationListList.Serialise(os);
}

