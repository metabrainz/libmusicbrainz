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

#ifndef _MUSICBRAINZ5_METADATA_H
#define _MUSICBRAINZ5_METADATA_H

#include "musicbrainz5/Entity.h"
#include "musicbrainz5/ReleaseList.h"
#include "musicbrainz5/ArtistList.h"
#include "musicbrainz5/WorkList.h"
#include "musicbrainz5/ISRCList.h"
#include "musicbrainz5/LabelInfoList.h"
#include "musicbrainz5/ReleaseGroupList.h"
#include "musicbrainz5/RecordingList.h"
#include "musicbrainz5/LabelList.h"
#include "musicbrainz5/AnnotationList.h"
#include "musicbrainz5/CDStubList.h"
#include "musicbrainz5/FreeDBDiscList.h"
#include "musicbrainz5/TagList.h"
#include "musicbrainz5/UserTagList.h"
#include "musicbrainz5/CollectionList.h"

#include "musicbrainz5/xmlParser.h"

#include <string>

namespace MusicBrainz5
{
	class CMetadataPrivate;

	class CArtist;
	class CRelease;
	class CReleaseGroup;
	class CRecording;
	class CLabel;
	class CPUID;
	class CISRC;
	class CDisc;
	class CRating;
	class CUserRating;
	class CCollection;
	class CArtist;
	class CWork;
	class CCDStub;
	class CMessage;

	class CMetadata: public CEntity
	{
	public:
		CMetadata(const XMLNode& Node=XMLNode::emptyNode());
		CMetadata(const CMetadata& Other);
		CMetadata& operator =(const CMetadata& Other);
		virtual ~CMetadata();

		virtual CMetadata *Clone();

		std::string XMLNS() const;
		std::string XMLNSExt() const;
		std::string Generator() const;
		std::string Created() const;
		CArtist *Artist() const;
		CRelease *Release() const;
		CReleaseGroup *ReleaseGroup() const;
		CRecording *Recording() const;
		CLabel *Label() const;
		CWork *Work() const;
		CPUID *PUID() const;
		CISRC *ISRC() const;
		CDisc *Disc() const;
		CLabelInfoList *LabelInfoList() const;
		CRating *Rating() const;
		CUserRating *UserRating() const;
		CCollection *Collection() const;
		CArtistList *ArtistList() const;
		CReleaseList *ReleaseList() const;
		CReleaseGroupList *ReleaseGroupList() const;
		CRecordingList *RecordingList() const;
		CLabelList *LabelList() const;
		CWorkList *WorkList() const;
		CISRCList *ISRCList() const;
		CAnnotationList *AnnotationList() const;
		CCDStubList *CDStubList() const;
		CFreeDBDiscList *FreeDBDiscList() const;
		CTagList *TagList() const;
		CUserTagList *UserTagList() const;
		CCollectionList *CollectionList() const;
		CCDStub *CDStub() const;
		CMessage *Message() const;

		virtual std::ostream& Serialise(std::ostream& os) const;
		static std::string GetElementName();

	protected:
		virtual void ParseAttribute(const std::string& Name, const std::string& Value);
		virtual void ParseElement(const XMLNode& Node);

	private:
		void Cleanup();

		CMetadataPrivate * const m_d;
	};
}

#endif
