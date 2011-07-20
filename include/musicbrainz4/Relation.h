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

#ifndef _MUSICBRAINZ4_RELATION_H
#define _MUSICBRAINZ4_RELATION_H

#include <string>
#include <iostream>

#include "musicbrainz4/Entity.h"
#include "musicbrainz4/GenericList.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CRelationPrivate;

	class CAttribute;
	class CArtist;
	class CRelease;
	class CReleaseGroup;
	class CRecording;
	class CLabel;
	class CWork;

	class CRelation: public CEntity
	{
	public:
		CRelation(const XMLNode& Node=XMLNode::emptyNode());
		CRelation(const CRelation& Other);
		CRelation& operator =(const CRelation& Other);
		~CRelation();

		std::string Type() const;
		std::string Target() const;
		std::string Direction() const;
		CGenericList<CAttribute> *AttributeList() const;
		std::string Begin() const;
		std::string End() const;
		CArtist *Artist() const;
		CRelease *Release() const;
		CReleaseGroup *ReleaseGroup() const;
		CRecording *Recording() const;
		CLabel *Label() const;
		CWork *Work() const;

	private:
		void Cleanup();

		CRelationPrivate * const m_d;

		virtual bool ParseAttribute(const std::string& Name, const std::string& Value);
		virtual bool ParseElement(const XMLNode& Node);
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CRelation& Relation);

#endif
