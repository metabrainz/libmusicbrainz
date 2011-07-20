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

#ifndef _MUSICBRAINZ4_METADATA_H
#define _MUSICBRAINZ4_METADATA_H

#include "musicbrainz4/GenericList.h"
#include "musicbrainz4/Entity.h"

#include "musicbrainz4/xmlParser.h"

#include <string>

namespace MusicBrainz4
{
	class CMetadataPrivate;

	class CArtist;
	class CRelease;
	class CReleaseGroup;
	class CRecording;
	class CLabel;
	class CWork;
	class CPUID;
	class CISRC;
	class CDisc;
	class CLabelInfo;
	class CRating;
	class CUserRating;
	class CCollection;
	class CArtist;
	class CRelease;
	class CReleaseGroup;
	class CRecording;
	class CLabel;
	class CWork;
	class CAnnotation;
	class CCDStub;
	class CFreeDBDisc;
	class CTag;
	class CUserTag;
	class CCollection;
	class CCDStub;
	class CMessage;

	class CMetadata: public CEntity
	{
	public:
		CMetadata(const XMLNode& Node=XMLNode::emptyNode());
		CMetadata(const CMetadata& Other);
		CMetadata& operator =(const CMetadata& Other);
		~CMetadata();

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
		CGenericList<CLabelInfo> *LabelInfoList() const;
		CRating *Rating() const;
		CUserRating *UserRating() const;
		CCollection *Collection() const;
		CGenericList<CArtist> *ArtistList() const;
		CGenericList<CRelease> *ReleaseList() const;
		CGenericList<CReleaseGroup> *ReleaseGroupList() const;
		CGenericList<CRecording> *RecordingList() const;
		CGenericList<CLabel> *LabelList() const;
		CGenericList<CWork> *WorkList() const;
		CGenericList<CISRC> *ISRCList() const;
		CGenericList<CAnnotation> *AnnotationList() const;
		CGenericList<CCDStub> *CDStubList() const;
		CGenericList<CFreeDBDisc> *FreeDBDiscList() const;
		CGenericList<CTag> *TagList() const;
		CGenericList<CUserTag> *UserTagList() const;
		CGenericList<CCollection> *CollectionList() const;
		CCDStub *CDStub() const;
		CMessage *Message() const;

	private:
		void Cleanup();

		CMetadataPrivate * const m_d;

		virtual bool ParseAttribute(const std::string& Name, const std::string& Value);
		virtual bool ParseElement(const XMLNode& Node);
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CMetadata& Metadata);

#endif
