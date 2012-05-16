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

#include "config.h"
#include "musicbrainz4/defines.h"

#include "musicbrainz4/Metadata.h"

#include "musicbrainz4/Artist.h"
#include "musicbrainz4/ArtistList.h"
#include "musicbrainz4/Release.h"
#include "musicbrainz4/ReleaseList.h"
#include "musicbrainz4/ReleaseGroup.h"
#include "musicbrainz4/ReleaseGroupList.h"
#include "musicbrainz4/Recording.h"
#include "musicbrainz4/RecordingList.h"
#include "musicbrainz4/Label.h"
#include "musicbrainz4/LabelList.h"
#include "musicbrainz4/Work.h"
#include "musicbrainz4/WorkList.h"
#include "musicbrainz4/PUID.h"
#include "musicbrainz4/ISRC.h"
#include "musicbrainz4/ISRCList.h"
#include "musicbrainz4/Disc.h"
#include "musicbrainz4/Rating.h"
#include "musicbrainz4/UserRating.h"
#include "musicbrainz4/Collection.h"
#include "musicbrainz4/CollectionList.h"
#include "musicbrainz4/Annotation.h"
#include "musicbrainz4/AnnotationList.h"
#include "musicbrainz4/CDStub.h"
#include "musicbrainz4/CDStubList.h"
#include "musicbrainz4/FreeDBDisc.h"
#include "musicbrainz4/FreeDBDiscList.h"
#include "musicbrainz4/Tag.h"
#include "musicbrainz4/TagList.h"
#include "musicbrainz4/UserTag.h"
#include "musicbrainz4/UserTagList.h"
#include "musicbrainz4/LabelInfo.h"
#include "musicbrainz4/LabelInfoList.h"
#include "musicbrainz4/Message.h"

class MusicBrainz4::CMetadataPrivate
{
	public:
		CMetadataPrivate()
		:	m_Artist(0),
			m_Release(0),
			m_ReleaseGroup(0),
			m_Recording(0),
			m_Label(0),
			m_Work(0),
			m_PUID(0),
			m_ISRC(0),
			m_Disc(0),
			m_LabelInfoList(0),
			m_Rating(0),
			m_UserRating(0),
			m_Collection(0),
			m_ArtistList(0),
			m_ReleaseList(0),
			m_ReleaseGroupList(0),
			m_RecordingList(0),
			m_LabelList(0),
			m_WorkList(0),
			m_ISRCList(0),
			m_AnnotationList(0),
			m_CDStubList(0),
			m_FreeDBDiscList(0),
			m_TagList(0),
			m_UserTagList(0),
			m_CollectionList(0),
			m_CDStub(0),
			m_Message(0)
		{
		}

		std::string m_XMLNS;
		std::string m_XMLNSExt;
		std::string m_Generator;
		std::string m_Created;
		CArtist *m_Artist;
		CRelease *m_Release;
		CReleaseGroup *m_ReleaseGroup;
		CRecording *m_Recording;
		CLabel *m_Label;
		CWork *m_Work;
		CPUID *m_PUID;
		CISRC *m_ISRC;
		CDisc *m_Disc;
		CLabelInfoList *m_LabelInfoList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
		CCollection *m_Collection;
		CArtistList *m_ArtistList;
		CReleaseList *m_ReleaseList;
		CReleaseGroupList *m_ReleaseGroupList;
		CRecordingList *m_RecordingList;
		CLabelList *m_LabelList;
		CWorkList *m_WorkList;
		CISRCList *m_ISRCList;
		CAnnotationList *m_AnnotationList;
		CCDStubList *m_CDStubList;
		CFreeDBDiscList *m_FreeDBDiscList;
		CTagList *m_TagList;
		CUserTagList *m_UserTagList;
		CCollectionList *m_CollectionList;
		CCDStub *m_CDStub;
		CMessage *m_Message;
};

MusicBrainz4::CMetadata::CMetadata(const XMLNode& Node)
:	CEntity(),
	m_d(new CMetadataPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Metadata node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CMetadata::CMetadata(const CMetadata& Other)
:	CEntity(),
	m_d(new CMetadataPrivate)
{
	*this=Other;
}

MusicBrainz4::CMetadata& MusicBrainz4::CMetadata::operator =(const CMetadata& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_XMLNS=Other.m_d->m_XMLNS;
		m_d->m_XMLNSExt=Other.m_d->m_XMLNSExt;
		m_d->m_Generator=Other.m_d->m_Generator;
		m_d->m_Created=Other.m_d->m_Created;

		if (Other.m_d->m_Artist)
			m_d->m_Artist=new CArtist(*Other.m_d->m_Artist);

		if (Other.m_d->m_Release)
			m_d->m_Release=new CRelease(*Other.m_d->m_Release);

		if (Other.m_d->m_ReleaseGroup)
			m_d->m_ReleaseGroup=new CReleaseGroup(*Other.m_d->m_ReleaseGroup);

		if (Other.m_d->m_Recording)
			m_d->m_Recording=new CRecording(*Other.m_d->m_Recording);

		if (Other.m_d->m_Label)
			m_d->m_Label=new CLabel(*Other.m_d->m_Label);

		if (Other.m_d->m_Work)
			m_d->m_Work=new CWork(*Other.m_d->m_Work);

		if (Other.m_d->m_PUID)
			m_d->m_PUID=new CPUID(*Other.m_d->m_PUID);

		if (Other.m_d->m_ISRC)
			m_d->m_ISRC=new CISRC(*Other.m_d->m_ISRC);

		if (Other.m_d->m_Disc)
			m_d->m_Disc=new CDisc(*Other.m_d->m_Disc);

		if (Other.m_d->m_LabelInfoList)
			m_d->m_LabelInfoList=new CLabelInfoList(*Other.m_d->m_LabelInfoList);

		if (Other.m_d->m_Rating)
			m_d->m_Rating=new CRating(*Other.m_d->m_Rating);

		if (Other.m_d->m_UserRating)
			m_d->m_UserRating=new CUserRating(*Other.m_d->m_UserRating);

		if (Other.m_d->m_Collection)
			m_d->m_Collection=new CCollection(*Other.m_d->m_Collection);

		if (Other.m_d->m_ArtistList)
			m_d->m_ArtistList=new CArtistList(*Other.m_d->m_ArtistList);

		if (Other.m_d->m_ReleaseList)
			m_d->m_ReleaseList=new CReleaseList(*Other.m_d->m_ReleaseList);

		if (Other.m_d->m_ReleaseGroupList)
			m_d->m_ReleaseGroupList=new CReleaseGroupList(*Other.m_d->m_ReleaseGroupList);

		if (Other.m_d->m_RecordingList)
			m_d->m_RecordingList=new CRecordingList(*Other.m_d->m_RecordingList);

		if (Other.m_d->m_LabelList)
			m_d->m_LabelList=new CLabelList(*Other.m_d->m_LabelList);

		if (Other.m_d->m_WorkList)
			m_d->m_WorkList=new CWorkList(*Other.m_d->m_WorkList);

		if (Other.m_d->m_ISRCList)
			m_d->m_ISRCList=new CISRCList(*Other.m_d->m_ISRCList);

		if (Other.m_d->m_AnnotationList)
			m_d->m_AnnotationList=new CAnnotationList(*Other.m_d->m_AnnotationList);

		if (Other.m_d->m_CDStubList)
			m_d->m_CDStubList=new CCDStubList(*Other.m_d->m_CDStubList);

		if (Other.m_d->m_FreeDBDiscList)
			m_d->m_FreeDBDiscList=new CFreeDBDiscList(*Other.m_d->m_FreeDBDiscList);

		if (Other.m_d->m_TagList)
			m_d->m_TagList=new CTagList(*Other.m_d->m_TagList);

		if (Other.m_d->m_UserTagList)
			m_d->m_UserTagList=new CUserTagList(*Other.m_d->m_UserTagList);

		if (Other.m_d->m_CollectionList)
			m_d->m_CollectionList=new CCollectionList(*Other.m_d->m_CollectionList);

		if (Other.m_d->m_CDStub)
			m_d->m_CDStub=new CCDStub(*Other.m_d->m_CDStub);

		if (Other.m_d->m_Message)
			m_d->m_Message=new CMessage(*Other.m_d->m_Message);
	}

	return *this;
}

MusicBrainz4::CMetadata::~CMetadata()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz4::CMetadata::Cleanup()
{
	delete m_d->m_Artist;
	m_d->m_Artist=0;

	delete m_d->m_Release;
	m_d->m_Release=0;

	delete m_d->m_ReleaseGroup;
	m_d->m_ReleaseGroup=0;

	delete m_d->m_Recording;
	m_d->m_Recording=0;

	delete m_d->m_Label;
	m_d->m_Label=0;

	delete m_d->m_Work;
	m_d->m_Work=0;

	delete m_d->m_PUID;
	m_d->m_PUID=0;

	delete m_d->m_ISRC;
	m_d->m_ISRC=0;

	delete m_d->m_Disc;
	m_d->m_Disc=0;

	delete m_d->m_LabelInfoList;
	m_d->m_LabelInfoList=0;

	delete m_d->m_Rating;
	m_d->m_Rating=0;

	delete m_d->m_UserRating;
	m_d->m_UserRating=0;

	delete m_d->m_Collection;
	m_d->m_Collection=0;

	delete m_d->m_ArtistList;
	m_d->m_ArtistList=0;

	delete m_d->m_ReleaseList;
	m_d->m_ReleaseList=0;

	delete m_d->m_ReleaseGroupList;
	m_d->m_ReleaseGroupList=0;

	delete m_d->m_RecordingList;
	m_d->m_RecordingList=0;

	delete m_d->m_LabelList;
	m_d->m_LabelList=0;

	delete m_d->m_WorkList;
	m_d->m_WorkList=0;

	delete m_d->m_ISRCList;
	m_d->m_ISRCList=0;

	delete m_d->m_AnnotationList;
	m_d->m_AnnotationList=0;

	delete m_d->m_CDStubList;
	m_d->m_CDStubList=0;

	delete m_d->m_FreeDBDiscList;
	m_d->m_FreeDBDiscList=0;

	delete m_d->m_TagList;
	m_d->m_TagList=0;

	delete m_d->m_UserTagList;
	m_d->m_UserTagList=0;

	delete m_d->m_CollectionList;
	m_d->m_CollectionList=0;

	delete m_d->m_CDStub;
	m_d->m_CDStub=0;

	delete m_d->m_Message;
	m_d->m_Message=0;
}

MusicBrainz4::CMetadata *MusicBrainz4::CMetadata::Clone()
{
	return new CMetadata(*this);
}

void MusicBrainz4::CMetadata::ParseAttribute(const std::string& Name, const std::string& Value)
{
	if ("xmlns"==Name)
		m_d->m_XMLNS=Value;
	else if ("xmlns:ext"==Name)
		m_d->m_XMLNSExt=Value;
	else if ("generator"==Name)
		m_d->m_Generator=Value;
	else if ("created"==Name)
		m_d->m_Created=Value;
	else
	{
		std::cerr << "Unrecognised metadata attribute: '" << Name << "'" << std::endl;
	}
}

void MusicBrainz4::CMetadata::ParseElement(const XMLNode& Node)
{
	std::string NodeName=Node.getName();

	if ("artist"==NodeName)
	{
		ProcessItem(Node,m_d->m_Artist);
	}
	else if ("release"==NodeName)
	{
		ProcessItem(Node,m_d->m_Release);
	}
	else if ("release-group"==NodeName)
	{
		ProcessItem(Node,m_d->m_ReleaseGroup);
	}
	else if ("recording"==NodeName)
	{
		ProcessItem(Node,m_d->m_Recording);
	}
	else if ("label"==NodeName)
	{
		ProcessItem(Node,m_d->m_Label);
	}
	else if ("work"==NodeName)
	{
		ProcessItem(Node,m_d->m_Work);
	}
	else if ("puid"==NodeName)
	{
		ProcessItem(Node,m_d->m_PUID);
	}
	else if ("isrc"==NodeName)
	{
		ProcessItem(Node,m_d->m_ISRC);
	}
	else if ("disc"==NodeName)
	{
		ProcessItem(Node,m_d->m_Disc);
	}
	else if ("rating"==NodeName)
	{
		ProcessItem(Node,m_d->m_Rating);
	}
	else if ("user-rating"==NodeName)
	{
		ProcessItem(Node,m_d->m_UserRating);
	}
	else if ("collection"==NodeName)
	{
		ProcessItem(Node,m_d->m_Collection);
	}
	else if ("artist-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_ArtistList);
	}
	else if ("release-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_ReleaseList);
	}
	else if ("release-group-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_ReleaseGroupList);
	}
	else if ("recording-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_RecordingList);
	}
	else if ("label-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_LabelList);
	}
	else if ("work-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_WorkList);
	}
	else if ("isrc-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_ISRCList);
	}
	else if ("annotation-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_AnnotationList);
	}
	else if ("cdstub-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_CDStubList);
	}
	else if ("freedb-disc-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_FreeDBDiscList);
	}
	else if ("tag-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_TagList);
	}
	else if ("user-tag-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_UserTagList);
	}
	else if ("collection-list"==NodeName)
	{
		ProcessItem(Node,m_d->m_CollectionList);
	}
	else if ("cdstub"==NodeName)
	{
		ProcessItem(Node,m_d->m_CDStub);
	}
	else if ("message"==NodeName)
	{
		ProcessItem(Node,m_d->m_Message);
	}
	else
	{
		std::cerr << "Unrecognised metadata element: '" << NodeName << "'" << std::endl;
	}
}

std::string MusicBrainz4::CMetadata::GetElementName()
{
	return "metadata";
}

std::string MusicBrainz4::CMetadata::XMLNS() const
{
	return m_d->m_XMLNS;
}

std::string MusicBrainz4::CMetadata::XMLNSExt() const
{
	return m_d->m_XMLNSExt;
}

std::string MusicBrainz4::CMetadata::Generator() const
{
	return m_d->m_Generator;
}

std::string MusicBrainz4::CMetadata::Created() const
{
	return m_d->m_Created;
}

MusicBrainz4::CArtist *MusicBrainz4::CMetadata::Artist() const
{
	return m_d->m_Artist;
}

MusicBrainz4::CRelease *MusicBrainz4::CMetadata::Release() const
{
	return m_d->m_Release;
}

MusicBrainz4::CReleaseGroup *MusicBrainz4::CMetadata::ReleaseGroup() const
{
	return m_d->m_ReleaseGroup;
}

MusicBrainz4::CRecording *MusicBrainz4::CMetadata::Recording() const
{
	return m_d->m_Recording;
}

MusicBrainz4::CLabel *MusicBrainz4::CMetadata::Label() const
{
	return m_d->m_Label;
}

MusicBrainz4::CWork *MusicBrainz4::CMetadata::Work() const
{
	return m_d->m_Work;
}

MusicBrainz4::CPUID *MusicBrainz4::CMetadata::PUID() const
{
	return m_d->m_PUID;
}

MusicBrainz4::CISRC *MusicBrainz4::CMetadata::ISRC() const
{
	return m_d->m_ISRC;
}

MusicBrainz4::CDisc *MusicBrainz4::CMetadata::Disc() const
{
	return m_d->m_Disc;
}

MusicBrainz4::CLabelInfoList *MusicBrainz4::CMetadata::LabelInfoList() const
{
	return m_d->m_LabelInfoList;
}

MusicBrainz4::CRating *MusicBrainz4::CMetadata::Rating() const
{
	return m_d->m_Rating;
}

MusicBrainz4::CUserRating *MusicBrainz4::CMetadata::UserRating() const
{
	return m_d->m_UserRating;
}

MusicBrainz4::CCollection *MusicBrainz4::CMetadata::Collection() const
{
	return m_d->m_Collection;
}

MusicBrainz4::CArtistList *MusicBrainz4::CMetadata::ArtistList() const
{
	return m_d->m_ArtistList;
}

MusicBrainz4::CReleaseList *MusicBrainz4::CMetadata::ReleaseList() const
{
	return m_d->m_ReleaseList;
}

MusicBrainz4::CReleaseGroupList *MusicBrainz4::CMetadata::ReleaseGroupList() const
{
	return m_d->m_ReleaseGroupList;
}

MusicBrainz4::CRecordingList *MusicBrainz4::CMetadata::RecordingList() const
{
	return m_d->m_RecordingList;
}

MusicBrainz4::CLabelList *MusicBrainz4::CMetadata::LabelList() const
{
	return m_d->m_LabelList;
}

MusicBrainz4::CWorkList *MusicBrainz4::CMetadata::WorkList() const
{
	return m_d->m_WorkList;
}

MusicBrainz4::CISRCList *MusicBrainz4::CMetadata::ISRCList() const
{
	return m_d->m_ISRCList;
}

MusicBrainz4::CAnnotationList *MusicBrainz4::CMetadata::AnnotationList() const
{
	return m_d->m_AnnotationList;
}

MusicBrainz4::CCDStubList *MusicBrainz4::CMetadata::CDStubList() const
{
	return m_d->m_CDStubList;
}

MusicBrainz4::CFreeDBDiscList *MusicBrainz4::CMetadata::FreeDBDiscList() const
{
	return m_d->m_FreeDBDiscList;
}

MusicBrainz4::CTagList *MusicBrainz4::CMetadata::TagList() const
{
	return m_d->m_TagList;
}

MusicBrainz4::CUserTagList *MusicBrainz4::CMetadata::UserTagList() const
{
	return m_d->m_UserTagList;
}

MusicBrainz4::CCollectionList *MusicBrainz4::CMetadata::CollectionList() const
{
	return m_d->m_CollectionList;
}

MusicBrainz4::CCDStub *MusicBrainz4::CMetadata::CDStub() const
{
	return m_d->m_CDStub;
}

MusicBrainz4::CMessage *MusicBrainz4::CMetadata::Message() const
{
	return m_d->m_Message;
}

std::ostream& MusicBrainz4::CMetadata::Serialise(std::ostream& os) const
{
	os << "Metadata:" << std::endl;

	CEntity::Serialise(os);

	os << "XMLNS:     " << XMLNS() << std::endl;
	os << "XMLNS-Ext: " << XMLNSExt() << std::endl;
	os << "Generator: " << Generator() << std::endl;
	os << "Created:   " << Created() << std::endl;

	if (Artist())
		os << *Artist() << std::endl;

	if (Release())
		os << *Release() << std::endl;

	if (ReleaseGroup())
		os << *ReleaseGroup() << std::endl;

	if (Recording())
		os << *Recording() << std::endl;

	if (Label())
		os << *Label() << std::endl;

	if (Work())
		os << *Work() << std::endl;

	if (PUID())
		os << *PUID() << std::endl;

	if (ISRC())
		os << *ISRC() << std::endl;

	if (Disc())
		os << *Disc() << std::endl;

	if (LabelInfoList())
		os << *LabelInfoList() << std::endl;

	if (UserRating())
		os << *UserRating() << std::endl;

	if (Collection())
		os << *Collection() << std::endl;

	if (ArtistList())
		os << *ArtistList() << std::endl;

	if (ReleaseList())
		os << *ReleaseList() << std::endl;

	if (ReleaseGroupList())
		os << *ReleaseGroupList() << std::endl;

	if (RecordingList())
		os << *RecordingList() << std::endl;

	if (LabelList())
		os << *LabelList() << std::endl;

	if (WorkList())
		os << *WorkList() << std::endl;

	if (ISRCList())
		os << *ISRCList() << std::endl;

	if (AnnotationList())
		os << *AnnotationList() << std::endl;

	if (CDStubList())
		os << *CDStubList() << std::endl;

	if (FreeDBDiscList())
		os << *FreeDBDiscList() << std::endl;

	if (TagList())
		os << *TagList() << std::endl;

	if (UserTagList())
		os << *UserTagList() << std::endl;

	if (CollectionList())
		os << *CollectionList() << std::endl;

	if (CDStub())
		os << *CDStub() << std::endl;

	if (Message())
		os << *Message() << std::endl;

	return os;
}

