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

#ifndef _MUSICBRAINZ4_LABEL_H
#define _MUSICBRAINZ4_LABEL_H

#include <string>
#include <iostream>

#include "musicbrainz4/GenericList.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CLifespan;
	class CAlias;
	class CRelease;
	class CRelation;
	class CTag;
	class CUserTag;
	class CRating;
	class CUserRating;

	class CLabel
	{
	public:
		CLabel(const XMLNode& Node=XMLNode::emptyNode());
		CLabel(const CLabel& Other);
		CLabel& operator =(const CLabel& Other);
		~CLabel();

		std::string ID() const;
		std::string Type() const;
		std::string Name() const;
		std::string SortName() const;
		std::string LabelCode() const;
		std::string Disambiguation() const;
		std::string Country() const;
		CLifespan *Lifespan() const;
		CGenericList<CAlias> *AliasList() const;
		CGenericList<CRelease> *ReleaseList() const;
		CGenericList<CRelation> *RelationList() const;
		CGenericList<CTag> *TagList() const;
		CGenericList<CUserTag> *UserTagList() const;
		CRating *Rating() const;
		CUserRating *UserRating() const;

	private:
		void Cleanup();

		std::string m_ID;
		std::string m_Type;
		std::string m_Name;
		std::string m_SortName;
		std::string m_LabelCode;
		std::string m_Disambiguation;
		std::string m_Country;
		CLifespan *m_Lifespan;
		CGenericList<CAlias> *m_AliasList;
		CGenericList<CRelease> *m_ReleaseList;
		CGenericList<CRelation> *m_RelationList;
		CGenericList<CTag> *m_TagList;
		CGenericList<CUserTag> *m_UserTagList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CLabel& Label);

#endif
