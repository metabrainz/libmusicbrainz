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

#include "musicbrainz4/Recording.h"

#include "musicbrainz4/ArtistCredit.h"
#include "musicbrainz4/Rating.h"
#include "musicbrainz4/UserRating.h"
#include "musicbrainz4/Release.h"
#include "musicbrainz4/PUID.h"
#include "musicbrainz4/ISRC.h"
#include "musicbrainz4/Relation.h"
#include "musicbrainz4/Tag.h"
#include "musicbrainz4/UserTag.h"

MusicBrainz4::CRecording::CRecording(const XMLNode& Node)
:	m_ArtistCredit(0),
	m_ReleaseList(0),
	m_PUIDList(0),
	m_ISRCList(0),
	m_RelationList(0),
	m_TagList(0),
	m_UserTagList(0),
	m_Rating(0),
	m_UserRating(0)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Medium node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("id"))
			m_ID=Node.getAttribute("id");

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("title"==NodeName)
			{
				m_Title=NodeValue;
			}
			else if ("length"==NodeName)
			{
				m_Length=NodeValue;
			}
			else if ("disambiguation"==NodeName)
			{
				m_Disambiguation=NodeValue;
			}
			else if ("artist-credit"==NodeName)
			{
				m_ArtistCredit=new CArtistCredit(ChildNode);
			}
			else if ("release-list"==NodeName)
			{
				m_ReleaseList=new CGenericList<CRelease>(ChildNode,"release");
			}
			else if ("puid-list"==NodeName)
			{
				m_PUIDList=new CGenericList<CPUID>(ChildNode,"puid");
			}
			else if ("isrc-list"==NodeName)
			{
				m_ISRCList=new CGenericList<CISRC>(ChildNode,"isrc");
			}
			else if ("relation-list"==NodeName)
			{
				m_RelationList=new CGenericList<CRelation>(ChildNode,"relation");
			}
			else if ("tag-list"==NodeName)
			{
				m_TagList=new CGenericList<CTag>(ChildNode,"tag");
			}
			else if ("user-tag-list"==NodeName)
			{
				m_UserTagList=new CGenericList<CUserTag>(ChildNode,"user-tag");
			}
			else if ("rating"==NodeName)
			{
				m_Rating=new CRating(ChildNode);
			}
			else if ("user-rating"==NodeName)
			{
				m_UserRating=new CUserRating(ChildNode);
			}
			else
			{
				std::cerr << "Unrecognised recording node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CRecording::CRecording(const CRecording& Other)
:	m_ArtistCredit(0),
	m_ReleaseList(0),
	m_PUIDList(0),
	m_ISRCList(0),
	m_RelationList(0),
	m_TagList(0),
	m_UserTagList(0),
	m_Rating(0),
	m_UserRating(0)
{
	*this=Other;
}

MusicBrainz4::CRecording& MusicBrainz4::CRecording::operator =(const CRecording& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_ID=Other.m_ID;
		m_Title=Other.m_Title;
		m_Length=Other.m_Length;
		m_Disambiguation=Other.m_Disambiguation;

		if (Other.m_ArtistCredit)
			m_ArtistCredit=new CArtistCredit(*Other.m_ArtistCredit);

		if (Other.m_ReleaseList)
			m_ReleaseList=new CGenericList<CRelease>(*Other.m_ReleaseList);

		if (Other.m_PUIDList)
			m_PUIDList=new CGenericList<CPUID>(*Other.m_PUIDList);

		if (Other.m_ISRCList)
			m_ISRCList=new CGenericList<CISRC>(*Other.m_ISRCList);

		if (Other.m_RelationList)
			m_RelationList=new CGenericList<CRelation>(*Other.m_RelationList);

		if (Other.m_TagList)
			m_TagList=new CGenericList<CTag>(*Other.m_TagList);

		if (Other.m_UserTagList)
			m_UserTagList=new CGenericList<CUserTag>(*Other.m_UserTagList);

		if (Other.m_Rating)
			m_Rating=new CRating(*Other.m_Rating);

		if (Other.m_UserRating)
			m_UserRating=new CUserRating(*Other.m_UserRating);
	}

	return *this;
}

MusicBrainz4::CRecording::~CRecording()
{
	Cleanup();
}

void MusicBrainz4::CRecording::Cleanup()
{
	delete m_ArtistCredit;
	m_ArtistCredit=0;

	delete m_ReleaseList;
	m_ReleaseList=0;

	delete m_PUIDList;
	m_PUIDList=0;

	delete m_ISRCList;
	m_ISRCList=0;

	delete m_RelationList;
	m_RelationList=0;

	delete m_TagList;
	m_TagList=0;

	delete m_UserTagList;
	m_UserTagList=0;

	delete m_Rating;
	m_Rating=0;

	delete m_UserRating;
	m_UserRating=0;
}

std::string MusicBrainz4::CRecording::ID() const
{
	return m_ID;
}

std::string MusicBrainz4::CRecording::Title() const
{
	return m_Title;
}

std::string MusicBrainz4::CRecording::Length() const
{
	return m_Length;
}

std::string MusicBrainz4::CRecording::Disambiguation() const
{
	return m_Disambiguation;
}

MusicBrainz4::CArtistCredit *MusicBrainz4::CRecording::ArtistCredit() const
{
	return m_ArtistCredit;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRelease> *MusicBrainz4::CRecording::ReleaseList() const
{
	return m_ReleaseList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CPUID> *MusicBrainz4::CRecording::PUIDList() const
{
	return m_PUIDList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CISRC> *MusicBrainz4::CRecording::ISRCList() const
{
	return m_ISRCList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRelation> *MusicBrainz4::CRecording::RelationList() const
{
	return m_RelationList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CTag> *MusicBrainz4::CRecording::TagList() const
{
	return m_TagList;
}

MusicBrainz4::CGenericList<MusicBrainz4::CUserTag> *MusicBrainz4::CRecording::UserTagList() const
{
	return m_UserTagList;
}

MusicBrainz4::CRating *MusicBrainz4::CRecording::Rating() const
{
	return m_Rating;
}

MusicBrainz4::CUserRating *MusicBrainz4::CRecording::UserRating() const
{
	return m_UserRating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CRecording& Recording)
{
	os << "Recording:" << std::endl;

	os << "\tID:             " << Recording.ID() << std::endl;
	os << "\tTitle:          " << Recording.Title() << std::endl;
	os << "\tLength:         " << Recording.Length() << std::endl;
	os << "\tDisambiguation: " << Recording.Disambiguation() << std::endl;

	if (Recording.ArtistCredit())
		os << *Recording.ArtistCredit() << std::endl;

	if (Recording.ReleaseList())
		os << *Recording.ReleaseList() << std::endl;

	if (Recording.PUIDList())
		os << *Recording.PUIDList() << std::endl;

	if (Recording.ISRCList())
		os << *Recording.ISRCList() << std::endl;

	if (Recording.RelationList())
		os << *Recording.RelationList() << std::endl;

	if (Recording.TagList())
		os << *Recording.TagList() << std::endl;

	if (Recording.UserTagList())
		os << *Recording.UserTagList() << std::endl;

	if (Recording.Rating())
		os << *Recording.Rating() << std::endl;

	if (Recording.UserRating())
		os << *Recording.UserRating() << std::endl;

	return os;
}
