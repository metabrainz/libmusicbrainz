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

#ifndef _MUSICBRAINZ5_AREA_H
#define _MUSICBRAINZ5_AREA_H

#include "musicbrainz5/Entity.h"

#include "musicbrainz5/ISO31661CodeList.h"
#include "musicbrainz5/ISO31662CodeList.h"
#include "musicbrainz5/ISO31663CodeList.h"
#include "musicbrainz5/AliasList.h"
#include "musicbrainz5/RelationList.h"
#include "musicbrainz5/TagList.h"
#include "musicbrainz5/UserTagList.h"

#include "musicbrainz5/xmlParser.h"

namespace MusicBrainz5
{
	class CAreaPrivate;

	class CLifespan;

	class CArea: public CEntity
	{
	public:
		CArea(const XMLNode& Node=XMLNode::emptyNode());
		CArea(const CArea& Other);
		CArea& operator =(const CArea& Other);
		virtual ~CArea();

		virtual CArea *Clone();

		std::string ID() const;
		std::string Type() const;
		std::string TypeID() const;
		std::string Name() const;
		std::string SortName() const;
		std::string Disambiguation() const;
		CISO31661CodeList *ISO31661CodeList() const;
		CISO31662CodeList *ISO31662CodeList() const;
		CISO31663CodeList *ISO31663CodeList() const;
		std::string Annotation() const;
		CLifespan *Lifespan() const;
		CAliasList *AliasList() const;
		CRelationList *RelationList() const;
		CTagList *TagList() const;
		CUserTagList *UserTagList() const;

		virtual std::ostream& Serialise(std::ostream& os) const;
		static std::string GetElementName();

	protected:
		virtual void ParseAttribute(const std::string& Name, const std::string& Value);
		virtual void ParseElement(const XMLNode& Node);

	private:
		void Cleanup();

		CAreaPrivate * const m_d;
	};
}

#endif
