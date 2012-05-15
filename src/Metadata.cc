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

#include "config.h"
#include "musicbrainz5/defines.h"

#include "musicbrainz5/Metadata.h"

#include "musicbrainz5/Artist.h"
#include "musicbrainz5/ArtistList.h"
#include "musicbrainz5/Release.h"
#include "musicbrainz5/ReleaseList.h"
#include "musicbrainz5/ReleaseGroup.h"
#include "musicbrainz5/ReleaseGroupList.h"
#include "musicbrainz5/Recording.h"
#include "musicbrainz5/RecordingList.h"
#include "musicbrainz5/Label.h"
#include "musicbrainz5/LabelList.h"
#include "musicbrainz5/Work.h"
#include "musicbrainz5/WorkList.h"
#include "musicbrainz5/PUID.h"
#include "musicbrainz5/ISRC.h"
#include "musicbrainz5/ISRCList.h"
#include "musicbrainz5/Disc.h"
#include "musicbrainz5/Rating.h"
#include "musicbrainz5/UserRating.h"
#include "musicbrainz5/Collection.h"
#include "musicbrainz5/CollectionList.h"
#include "musicbrainz5/Annotation.h"
#include "musicbrainz5/AnnotationList.h"
#include "musicbrainz5/CDStub.h"
#include "musicbrainz5/CDStubList.h"
#include "musicbrainz5/FreeDBDisc.h"
#include "musicbrainz5/FreeDBDiscList.h"
#include "musicbrainz5/Tag.h"
#include "musicbrainz5/TagList.h"
#include "musicbrainz5/UserTag.h"
#include "musicbrainz5/UserTagList.h"
#include "musicbrainz5/LabelInfo.h"
#include "musicbrainz5/LabelInfoList.h"
#include "musicbrainz5/Message.h"

class MusicBrainz5::CMetadataPrivate
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

MusicBrainz5::CMetadata::CMetadata(const XMLNode& Node)
:	CEntity(),
	m_d(new CMetadataPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Metadata node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CMetadata::CMetadata(const CMetadata& Other)
:	CEntity(),
	m_d(new CMetadataPrivate)
{
	*this=Other;
}

MusicBrainz5::CMetadata& MusicBrainz5::CMetadata::operator =(const CMetadata& Other)
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

MusicBrainz5::CMetadata::~CMetadata()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CMetadata::Cleanup()
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

MusicBrainz5::CMetadata *MusicBrainz5::CMetadata::Clone()
{
	return new CMetadata(*this);
}

bool MusicBrainz5::CMetadata::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

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
		RetVal=false;
	}

	return RetVal;
}

bool MusicBrainz5::CMetadata::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("artist"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Artist);
	}
	else if ("release"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Release);
	}
	else if ("release-group"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ReleaseGroup);
	}
	else if ("recording"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Recording);
	}
	else if ("label"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Label);
	}
	else if ("work"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Work);
	}
	else if ("puid"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_PUID);
	}
	else if ("isrc"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ISRC);
	}
	else if ("disc"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Disc);
	}
	else if ("rating"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Rating);
	}
	else if ("user-rating"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_UserRating);
	}
	else if ("collection"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Collection);
	}
	else if ("artist-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ArtistList);
	}
	else if ("release-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ReleaseList);
	}
	else if ("release-group-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ReleaseGroupList);
	}
	else if ("recording-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_RecordingList);
	}
	else if ("label-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_LabelList);
	}
	else if ("work-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_WorkList);
	}
	else if ("isrc-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ISRCList);
	}
	else if ("annotation-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_AnnotationList);
	}
	else if ("cdstub-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_CDStubList);
	}
	else if ("freedb-disc-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_FreeDBDiscList);
	}
	else if ("tag-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_TagList);
	}
	else if ("user-tag-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_UserTagList);
	}
	else if ("collection-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_CollectionList);
	}
	else if ("cdstub"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_CDStub);
	}
	else if ("message"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Message);
	}
	else
	{
		std::cerr << "Unrecognised metadata element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz5::CMetadata::GetElementName()
{
	return "metadata";
}

std::string MusicBrainz5::CMetadata::XMLNS() const
{
	return m_d->m_XMLNS;
}

std::string MusicBrainz5::CMetadata::XMLNSExt() const
{
	return m_d->m_XMLNSExt;
}

std::string MusicBrainz5::CMetadata::Generator() const
{
	return m_d->m_Generator;
}

std::string MusicBrainz5::CMetadata::Created() const
{
	return m_d->m_Created;
}

MusicBrainz5::CArtist *MusicBrainz5::CMetadata::Artist() const
{
	return m_d->m_Artist;
}

MusicBrainz5::CRelease *MusicBrainz5::CMetadata::Release() const
{
	return m_d->m_Release;
}

MusicBrainz5::CReleaseGroup *MusicBrainz5::CMetadata::ReleaseGroup() const
{
	return m_d->m_ReleaseGroup;
}

MusicBrainz5::CRecording *MusicBrainz5::CMetadata::Recording() const
{
	return m_d->m_Recording;
}

MusicBrainz5::CLabel *MusicBrainz5::CMetadata::Label() const
{
	return m_d->m_Label;
}

MusicBrainz5::CWork *MusicBrainz5::CMetadata::Work() const
{
	return m_d->m_Work;
}

MusicBrainz5::CPUID *MusicBrainz5::CMetadata::PUID() const
{
	return m_d->m_PUID;
}

MusicBrainz5::CISRC *MusicBrainz5::CMetadata::ISRC() const
{
	return m_d->m_ISRC;
}

MusicBrainz5::CDisc *MusicBrainz5::CMetadata::Disc() const
{
	return m_d->m_Disc;
}

MusicBrainz5::CLabelInfoList *MusicBrainz5::CMetadata::LabelInfoList() const
{
	return m_d->m_LabelInfoList;
}

MusicBrainz5::CRating *MusicBrainz5::CMetadata::Rating() const
{
	return m_d->m_Rating;
}

MusicBrainz5::CUserRating *MusicBrainz5::CMetadata::UserRating() const
{
	return m_d->m_UserRating;
}

MusicBrainz5::CCollection *MusicBrainz5::CMetadata::Collection() const
{
	return m_d->m_Collection;
}

MusicBrainz5::CArtistList *MusicBrainz5::CMetadata::ArtistList() const
{
	return m_d->m_ArtistList;
}

MusicBrainz5::CReleaseList *MusicBrainz5::CMetadata::ReleaseList() const
{
	return m_d->m_ReleaseList;
}

MusicBrainz5::CReleaseGroupList *MusicBrainz5::CMetadata::ReleaseGroupList() const
{
	return m_d->m_ReleaseGroupList;
}

MusicBrainz5::CRecordingList *MusicBrainz5::CMetadata::RecordingList() const
{
	return m_d->m_RecordingList;
}

MusicBrainz5::CLabelList *MusicBrainz5::CMetadata::LabelList() const
{
	return m_d->m_LabelList;
}

MusicBrainz5::CWorkList *MusicBrainz5::CMetadata::WorkList() const
{
	return m_d->m_WorkList;
}

MusicBrainz5::CISRCList *MusicBrainz5::CMetadata::ISRCList() const
{
	return m_d->m_ISRCList;
}

MusicBrainz5::CAnnotationList *MusicBrainz5::CMetadata::AnnotationList() const
{
	return m_d->m_AnnotationList;
}

MusicBrainz5::CCDStubList *MusicBrainz5::CMetadata::CDStubList() const
{
	return m_d->m_CDStubList;
}

MusicBrainz5::CFreeDBDiscList *MusicBrainz5::CMetadata::FreeDBDiscList() const
{
	return m_d->m_FreeDBDiscList;
}

MusicBrainz5::CTagList *MusicBrainz5::CMetadata::TagList() const
{
	return m_d->m_TagList;
}

MusicBrainz5::CUserTagList *MusicBrainz5::CMetadata::UserTagList() const
{
	return m_d->m_UserTagList;
}

MusicBrainz5::CCollectionList *MusicBrainz5::CMetadata::CollectionList() const
{
	return m_d->m_CollectionList;
}

MusicBrainz5::CCDStub *MusicBrainz5::CMetadata::CDStub() const
{
	return m_d->m_CDStub;
}

MusicBrainz5::CMessage *MusicBrainz5::CMetadata::Message() const
{
	return m_d->m_Message;
}

std::ostream& MusicBrainz5::CMetadata::Serialise(std::ostream& os) const
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

