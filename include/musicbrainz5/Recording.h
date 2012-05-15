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

#ifndef _MUSICBRAINZ5_RECORDING_H
#define _MUSICBRAINZ5_RECORDING_H

#include <string>
#include <iostream>

namespace MusicBrainz5
{
	class CRecording;
}

#include "musicbrainz5/Entity.h"
#include "musicbrainz5/ReleaseList.h"
#include "musicbrainz5/PUIDList.h"
#include "musicbrainz5/ISRCList.h"
#include "musicbrainz5/RelationList.h"
#include "musicbrainz5/TagList.h"
#include "musicbrainz5/UserTagList.h"

#include "musicbrainz5/xmlParser.h"

namespace MusicBrainz5
{
	class CRecordingPrivate;

	class CArtistCredit;
	class CRating;
	class CUserRating;

	class CRecording: public CEntity
	{
	public:
		CRecording(const XMLNode& Node=XMLNode::emptyNode());
		CRecording(const CRecording& Other);
		CRecording& operator =(const CRecording& Other);
		virtual ~CRecording();

		virtual CRecording *Clone();

		std::string ID() const;
		std::string Title() const;
		int Length() const;
		std::string Disambiguation() const;
		CArtistCredit *ArtistCredit() const;
		CReleaseList *ReleaseList() const;
		CPUIDList *PUIDList() const;
		CISRCList *ISRCList() const;
		CRelationListList *RelationListList() const;
		CTagList *TagList() const;
		CUserTagList *UserTagList() const;
		CRating *Rating() const;
		CUserRating *UserRating() const;

		virtual std::ostream& Serialise(std::ostream& os) const;
		static std::string GetElementName();

	protected:
		virtual bool ParseAttribute(const std::string& Name, const std::string& Value);
		virtual bool ParseElement(const XMLNode& Node);

	private:
		void Cleanup();

		CRecordingPrivate * const m_d;
	};
}

#endif
