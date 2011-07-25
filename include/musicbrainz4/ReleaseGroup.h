/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

#ifndef _MUSICBRAINZ4_RELEASE_GROUP_H
#define _MUSICBRAINZ4_RELEASE_GROUP_H

#include <string>
#include <iostream>

#include "musicbrainz4/Entity.h"
#include "musicbrainz4/GenericList.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CReleaseGroupPrivate;

	class CArtistCredit;
	class CRelease;
	class CRelation;
	class CTag;
	class CUserTag;
	class CRating;
	class CUserRating;

	class CReleaseGroup: public CEntity
	{
	public:
		CReleaseGroup(const XMLNode& Node=XMLNode::emptyNode());
		CReleaseGroup(const CReleaseGroup& Other);
		CReleaseGroup& operator =(const CReleaseGroup& Other);
		~CReleaseGroup();

		std::string ID() const;
		std::string Type() const;
		std::string Title() const;
		std::string Comment() const;
		std::string FirstReleaseDate() const;
		CArtistCredit *ArtistCredit() const;
		CGenericList<CRelease> *ReleaseList() const;
		CGenericList<CRelation> *RelationList() const;
		CGenericList<CTag> *TagList() const;
		CGenericList<CUserTag> *UserTagList() const;
		CRating *Rating() const;
		CUserRating *UserRating() const;
		std::string Disambiguation() const;

	private:
		void Cleanup();

		CReleaseGroupPrivate * const m_d;

		virtual bool ParseAttribute(const std::string& Name, const std::string& Value);
		virtual bool ParseElement(const XMLNode& Node);
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CReleaseGroup& ReleaseGroup);

#endif
