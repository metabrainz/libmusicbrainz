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

#ifndef _MUSICBRAINZ5_WORK_H
#define _MUSICBRAINZ5_WORK_H

#include <string>

#include "musicbrainz5/Entity.h"
#include "musicbrainz5/AliasList.h"
#include "musicbrainz5/RelationList.h"
#include "musicbrainz5/TagList.h"
#include "musicbrainz5/UserTagList.h"
#include "musicbrainz5/ISWCList.h"

#include "musicbrainz5/xmlParser.h"

namespace MusicBrainz5
{
	class CWorkPrivate;

	class CArtistCredit;
	class CISWC;
	class CRating;
	class CUserRating;

	class MB_API CWork: public CEntity
	{
	public:
		CWork(const XMLNode& Node=XMLNode::emptyNode());
		CWork(const CWork& Other);
		CWork& operator =(const CWork& Other);
		virtual ~CWork();

		virtual CWork *Clone();

		std::string ID() const;
		std::string Type() const;
		std::string Title() const;
		CArtistCredit *ArtistCredit() const;
		CISWCList *ISWCList() const;
		std::string Disambiguation() const;
		CAliasList *AliasList() const;
		CRelationListList *RelationListList() const;
		CTagList *TagList() const;
		CUserTagList *UserTagList() const;
		CRating *Rating() const;
		CUserRating *UserRating() const;
		std::string Language() const;

		virtual std::ostream& Serialise(std::ostream& os) const;
		static std::string GetElementName();

	protected:
		virtual void ParseAttribute(const std::string& Name, const std::string& Value);
		virtual void ParseElement(const XMLNode& Node);

	private:
		void Cleanup();

		CWorkPrivate * const m_d;
	};
}

#endif

