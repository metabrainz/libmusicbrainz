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

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#ifndef _MUSICBRAINZ4_METADATA_H
#define _MUSICBRAINZ4_METADATA_H

#include "musicbrainz4/Entity.h"

#include "musicbrainz4/xmlParser.h"

#include <string>

namespace MusicBrainz4
{
	class CMetadataPrivate;

	class CArtist;
	class CArtistList;
	class CRelease;
	class CReleaseList;
	class CReleaseGroup;
	class CRecording;
	class CLabel;
	class CWorkList;
	class CPUID;
	class CISRC;
	class CISRCList;
	class CDisc;
	class CLabelInfoList;
	class CRating;
	class CUserRating;
	class CCollection;
	class CArtist;
	class CReleaseGroupList;
	class CRecordingList;
	class CLabelList;
	class CWork;
	class CAnnotationList;
	class CCDStub;
	class CCDStubList;
	class CFreeDBDiscList;
	class CTagList;
	class CUserTagList;
	class CCollectionList;
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

		virtual std::string ElementName() const;

	protected:
		virtual bool ParseAttribute(const std::string& Name, const std::string& Value);
		virtual bool ParseElement(const XMLNode& Node);

	private:
		void Cleanup();

		CMetadataPrivate * const m_d;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CMetadata& Metadata);

#endif
