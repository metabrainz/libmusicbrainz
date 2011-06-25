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

#include "musicbrainz4/Metadata.h"

#include "musicbrainz4/Artist.h"
#include "musicbrainz4/Release.h"
#include "musicbrainz4/ReleaseGroup.h"
#include "musicbrainz4/Recording.h"
#include "musicbrainz4/Label.h"
#include "musicbrainz4/Work.h"
#include "musicbrainz4/PUID.h"
#include "musicbrainz4/ISRC.h"
#include "musicbrainz4/Disc.h"
#include "musicbrainz4/Rating.h"
#include "musicbrainz4/UserRating.h"
#include "musicbrainz4/Collection.h"
#include "musicbrainz4/Annotation.h"
#include "musicbrainz4/CDStub.h"
#include "musicbrainz4/FreeDBDisc.h"
#include "musicbrainz4/Tag.h"
#include "musicbrainz4/UserTag.h"
#include "musicbrainz4/LabelInfo.h"
#include "musicbrainz4/CDStub.h"
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
		CGenericList<CLabelInfo> *m_LabelInfoList;
		CRating *m_Rating;
		CUserRating *m_UserRating;
		CCollection *m_Collection;
		CGenericList<CArtist> *m_ArtistList;
		CGenericList<CRelease> *m_ReleaseList;
		CGenericList<CReleaseGroup> *m_ReleaseGroupList;
		CGenericList<CRecording> *m_RecordingList;
		CGenericList<CLabel> *m_LabelList;
		CGenericList<CWork> *m_WorkList;
		CGenericList<CISRC> *m_ISRCList;
		CGenericList<CAnnotation> *m_AnnotationList;
		CGenericList<CCDStub> *m_CDStubList;
		CGenericList<CFreeDBDisc> *m_FreeDBDiscList;
		CGenericList<CTag> *m_TagList;
		CGenericList<CUserTag> *m_UserTagList;
		CGenericList<CCollection> *m_CollectionList;
		CCDStub *m_CDStub;
		CMessage *m_Message;
};

MusicBrainz4::CMetadata::CMetadata(const XMLNode& Node)
:	m_d(new CMetadataPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Metadata node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("generator"))
			m_d->m_Generator=Node.getAttribute("generator");

		if (Node.isAttributeSet("created"))
			m_d->m_Created=Node.getAttribute("created");

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("artist"==NodeName)
			{
				m_d->m_Artist=new CArtist(ChildNode);
			}
			else if ("release"==NodeName)
			{
				m_d->m_Release=new CRelease(ChildNode);
			}
			else if ("release-group"==NodeName)
			{
				m_d->m_ReleaseGroup=new CReleaseGroup(ChildNode);
			}
			else if ("recording"==NodeName)
			{
				m_d->m_Recording=new CRecording(ChildNode);
			}
			else if ("label"==NodeName)
			{
				m_d->m_Label=new CLabel(ChildNode);
			}
			else if ("work"==NodeName)
			{
				m_d->m_Work=new CWork(ChildNode);
			}
			else if ("puid"==NodeName)
			{
				m_d->m_PUID=new CPUID(ChildNode);
			}
			else if ("isrc"==NodeName)
			{
				m_d->m_ISRC=new CISRC(ChildNode);
			}
			else if ("disc"==NodeName)
			{
				m_d->m_Disc=new CDisc(ChildNode);
			}
			else if ("rating"==NodeName)
			{
				m_d->m_Rating=new CRating(ChildNode);
			}
			else if ("user-rating"==NodeName)
			{
				m_d->m_UserRating=new CUserRating(ChildNode);
			}
			else if ("collection"==NodeName)
			{
				m_d->m_Collection=new CCollection(ChildNode);
			}
			else if ("artist-list"==NodeName)
			{
				m_d->m_ArtistList=new CGenericList<CArtist>(ChildNode,"artist");
			}
			else if ("release-list"==NodeName)
			{
				m_d->m_ReleaseList=new CGenericList<CRelease>(ChildNode,"release");
			}
			else if ("release-group-list"==NodeName)
			{
				m_d->m_ReleaseGroupList=new CGenericList<CReleaseGroup>(ChildNode,"release-group");
			}
			else if ("recording-list"==NodeName)
			{
				m_d->m_RecordingList=new CGenericList<CRecording>(ChildNode,"recording");
			}
			else if ("label-list"==NodeName)
			{
				m_d->m_LabelList=new CGenericList<CLabel>(ChildNode,"label");
			}
			else if ("work-list"==NodeName)
			{
				m_d->m_WorkList=new CGenericList<CWork>(ChildNode,"work");
			}
			else if ("isrc-list"==NodeName)
			{
				m_d->m_ISRCList=new CGenericList<CISRC>(ChildNode,"isrc");
			}
			else if ("annotation-list"==NodeName)
			{
				m_d->m_AnnotationList=new CGenericList<CAnnotation>(ChildNode,"annotation");
			}
			else if ("cdstub-list"==NodeName)
			{
				m_d->m_CDStubList=new CGenericList<CCDStub>(ChildNode,"ctstub");
			}
			else if ("freedb-disc-list"==NodeName)
			{
				m_d->m_FreeDBDiscList=new CGenericList<CFreeDBDisc>(ChildNode,"freedb-disc");
			}
			else if ("tag-list"==NodeName)
			{
				m_d->m_TagList=new CGenericList<CTag>(ChildNode,"tag");
			}
			else if ("user-tag-list"==NodeName)
			{
				m_d->m_UserTagList=new CGenericList<CUserTag>(ChildNode,"user-tag");
			}
			else if ("collection-list"==NodeName)
			{
				m_d->m_CollectionList=new CGenericList<CCollection>(ChildNode,"collection");
			}
			else if ("cdstub"==NodeName)
			{
				m_d->m_CDStub=new CCDStub(ChildNode);
			}
			else if ("message"==NodeName)
			{
				m_d->m_Message=new CMessage(ChildNode);
			}
			else
			{
				std::cerr << "Unrecognised metadata node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CMetadata::CMetadata(const CMetadata& Other)
:	m_d(new CMetadataPrivate)
{
	*this=Other;
}

MusicBrainz4::CMetadata& MusicBrainz4::CMetadata::operator =(const CMetadata& Other)
{
	if (this!=&Other)
	{
		Cleanup();

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
			m_d->m_LabelInfoList=new CGenericList<CLabelInfo>(*Other.m_d->m_LabelInfoList);

		if (Other.m_d->m_Rating)
			m_d->m_Rating=new CRating(*Other.m_d->m_Rating);

		if (Other.m_d->m_UserRating)
			m_d->m_UserRating=new CUserRating(*Other.m_d->m_UserRating);

		if (Other.m_d->m_Collection)
			m_d->m_Collection=new CCollection(*Other.m_d->m_Collection);

		if (Other.m_d->m_ArtistList)
			m_d->m_ArtistList=new CGenericList<CArtist>(*Other.m_d->m_ArtistList);

		if (Other.m_d->m_ReleaseList)
			m_d->m_ReleaseList=new CGenericList<CRelease>(*Other.m_d->m_ReleaseList);

		if (Other.m_d->m_ReleaseGroupList)
			m_d->m_ReleaseGroupList=new CGenericList<CReleaseGroup>(*Other.m_d->m_ReleaseGroupList);

		if (Other.m_d->m_RecordingList)
			m_d->m_RecordingList=new CGenericList<CRecording>(*Other.m_d->m_RecordingList);

		if (Other.m_d->m_LabelList)
			m_d->m_LabelList=new CGenericList<CLabel>(*Other.m_d->m_LabelList);

		if (Other.m_d->m_WorkList)
			m_d->m_WorkList=new CGenericList<CWork>(*Other.m_d->m_WorkList);

		if (Other.m_d->m_ISRCList)
			m_d->m_ISRCList=new CGenericList<CISRC>(*Other.m_d->m_ISRCList);

		if (Other.m_d->m_AnnotationList)
			m_d->m_AnnotationList=new CGenericList<CAnnotation>(*Other.m_d->m_AnnotationList);

		if (Other.m_d->m_CDStubList)
			m_d->m_CDStubList=new CGenericList<CCDStub>(*Other.m_d->m_CDStubList);

		if (Other.m_d->m_FreeDBDiscList)
			m_d->m_FreeDBDiscList=new CGenericList<CFreeDBDisc>(*Other.m_d->m_FreeDBDiscList);

		if (Other.m_d->m_TagList)
			m_d->m_TagList=new CGenericList<CTag>(*Other.m_d->m_TagList);

		if (Other.m_d->m_UserTagList)
			m_d->m_UserTagList=new CGenericList<CUserTag>(*Other.m_d->m_UserTagList);

		if (Other.m_d->m_CollectionList)
			m_d->m_CollectionList=new CGenericList<CCollection>(*Other.m_d->m_CollectionList);

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

MusicBrainz4::CGenericList<MusicBrainz4::CLabelInfo> *MusicBrainz4::CMetadata::LabelInfoList() const
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

MusicBrainz4::CGenericList<MusicBrainz4::CArtist> *MusicBrainz4::CMetadata::ArtistList() const
{
	return m_d->m_ArtistList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRelease> *MusicBrainz4::CMetadata::ReleaseList() const
{
	return m_d->m_ReleaseList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CReleaseGroup> *MusicBrainz4::CMetadata::ReleaseGroupList() const
{
	return m_d->m_ReleaseGroupList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRecording> *MusicBrainz4::CMetadata::RecordingList() const
{
	return m_d->m_RecordingList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CLabel> *MusicBrainz4::CMetadata::LabelList() const
{
	return m_d->m_LabelList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CWork> *MusicBrainz4::CMetadata::WorkList() const
{
	return m_d->m_WorkList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CISRC> *MusicBrainz4::CMetadata::ISRCList() const
{
	return m_d->m_ISRCList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CAnnotation> *MusicBrainz4::CMetadata::AnnotationList() const
{
	return m_d->m_AnnotationList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CCDStub> *MusicBrainz4::CMetadata::CDStubList() const
{
	return m_d->m_CDStubList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CFreeDBDisc> *MusicBrainz4::CMetadata::FreeDBDiscList() const
{
	return m_d->m_FreeDBDiscList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CTag> *MusicBrainz4::CMetadata::TagList() const
{
	return m_d->m_TagList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CUserTag> *MusicBrainz4::CMetadata::UserTagList() const
{
	return m_d->m_UserTagList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CCollection> *MusicBrainz4::CMetadata::CollectionList() const
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

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CMetadata& Metadata)
{
	os << "Metadata:" << std::endl;

	os << Metadata.Generator() << std::endl;
	os << Metadata.Created() << std::endl;

	if (Metadata.Artist())
		os << *Metadata.Artist() << std::endl;

	if (Metadata.Release())
		os << *Metadata.Release() << std::endl;

	if (Metadata.ReleaseGroup())
		os << *Metadata.ReleaseGroup() << std::endl;

	if (Metadata.Recording())
		os << *Metadata.Recording() << std::endl;

	if (Metadata.Label())
		os << *Metadata.Label() << std::endl;

	if (Metadata.Work())
		os << *Metadata.Work() << std::endl;

	if (Metadata.PUID())
		os << *Metadata.PUID() << std::endl;

	if (Metadata.ISRC())
		os << *Metadata.ISRC() << std::endl;

	if (Metadata.Disc())
		os << *Metadata.Disc() << std::endl;

	if (Metadata.LabelInfoList())
		os << *Metadata.LabelInfoList() << std::endl;

	if (Metadata.UserRating())
		os << *Metadata.UserRating() << std::endl;

	if (Metadata.Collection())
		os << *Metadata.Collection() << std::endl;

	if (Metadata.ArtistList())
		os << *Metadata.ArtistList() << std::endl;

	if (Metadata.ReleaseList())
		os << *Metadata.ReleaseList() << std::endl;

	if (Metadata.ReleaseGroupList())
		os << *Metadata.ReleaseGroupList() << std::endl;

	if (Metadata.RecordingList())
		os << *Metadata.RecordingList() << std::endl;

	if (Metadata.LabelList())
		os << *Metadata.LabelList() << std::endl;

	if (Metadata.WorkList())
		os << *Metadata.WorkList() << std::endl;

	if (Metadata.ISRCList())
		os << *Metadata.ISRCList() << std::endl;

	if (Metadata.AnnotationList())
		os << *Metadata.AnnotationList() << std::endl;

	if (Metadata.CDStubList())
		os << *Metadata.CDStubList() << std::endl;

	if (Metadata.FreeDBDiscList())
		os << *Metadata.FreeDBDiscList() << std::endl;

	if (Metadata.TagList())
		os << *Metadata.TagList() << std::endl;

	if (Metadata.UserTagList())
		os << *Metadata.UserTagList() << std::endl;

	if (Metadata.CollectionList())
		os << *Metadata.CollectionList() << std::endl;

	if (Metadata.CDStub())
		os << *Metadata.CDStub() << std::endl;

	if (Metadata.Message())
		os << *Metadata.Message() << std::endl;

	return os;
}

