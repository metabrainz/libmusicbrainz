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

#ifndef _MUSICBRAINZ4_RECORDING_H
#define _MUSICBRAINZ4_RECORDING_H

#include <string>
#include <iostream>

namespace MusicBrainz4
{
	class CRecording;
}

#include "musicbrainz4/Entity.h"
#include "musicbrainz4/ReleaseList.h"
#include "musicbrainz4/PUIDList.h"
#include "musicbrainz4/ISRCList.h"
#include "musicbrainz4/RelationList.h"
#include "musicbrainz4/TagList.h"
#include "musicbrainz4/UserTagList.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
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

		/**
		 * @deprecated Returns the <b>last</b> relation list for this recording
		 *
		 * Returns the <b>last</b> relation list for this recording. To return all
		 * relation lists, see MusicBrainz4::CRecording::RelationListList
		 *
		 * <b>This method is deprecated, please use MusicBrainz4::CRecording::RelationListList</b>
		 *
		 * @return The <b>last</b> relation list for this recording
		 */

		CRelationList *RelationList() const LIBMB4_DEPRECATED;
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
