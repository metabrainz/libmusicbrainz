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

#ifndef _MUSICBRAINZ5_RELATIONLIST_GROUP_H
#define _MUSICBRAINZ5_RELATIONLIST_GROUP_H

#include <iostream>

#include "musicbrainz5/xmlParser.h"

namespace MusicBrainz5
{
	class CRelationListListPrivate;

	class CRelationList;

	class CRelationListList
	{
	public:
		CRelationListList();
		CRelationListList(const CRelationListList& Other);
		CRelationListList& operator =(const CRelationListList& Other);
		virtual ~CRelationListList();

		void Add(CRelationList *RelationList);
		int NumItems() const;
		CRelationList *Item(int Item) const;
		int Offset() const { return 0; }
		int Count() const { return NumItems(); }

		std::ostream& Serialise(std::ostream& os) const;

	private:
		void Cleanup();

		CRelationListListPrivate * const m_d;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz5::CRelationListList& RelationListList);

#endif
