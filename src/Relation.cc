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

#include "musicbrainz4/Relation.h"

#include "musicbrainz4/Artist.h"
#include "musicbrainz4/Release.h"
#include "musicbrainz4/ReleaseGroup.h"
#include "musicbrainz4/Recording.h"
#include "musicbrainz4/Label.h"
#include "musicbrainz4/Work.h"
#include "musicbrainz4/Attribute.h"

class MusicBrainz4::CRelationPrivate
{
	public:
		CRelationPrivate()
		:	m_AttributeList(0),
			m_Artist(0),
			m_Release(0),
			m_ReleaseGroup(0),
			m_Recording(0),
			m_Label(0),
			m_Work(0)
		{
		}
		
		std::string m_Type;
		std::string m_Target;
		std::string m_Direction;
		CGenericList<CAttribute> *m_AttributeList;
		std::string m_Begin;
		std::string m_End;
		CArtist *m_Artist;
		CRelease *m_Release;
		CReleaseGroup *m_ReleaseGroup;
		CRecording *m_Recording;
		CLabel *m_Label;
		CWork *m_Work;
};

MusicBrainz4::CRelation::CRelation(const XMLNode& Node)
:	m_d(new CRelationPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Relation node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("type"))
			m_d->m_Type=Node.getAttribute("type");

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("target"==NodeName)
			{
				m_d->m_Target=NodeValue;
			}
			else if ("direction"==NodeName)
			{
				m_d->m_Direction=NodeValue;
			}
			else if ("attribute-list"==NodeName)
			{
				m_d->m_AttributeList=new CGenericList<CAttribute>(ChildNode,"attribute");
			}
			else if ("begin"==NodeName)
			{
				m_d->m_Begin=NodeValue;
			}
			else if ("end"==NodeName)
			{
				m_d->m_End=NodeValue;
			}
			else if ("artist"==NodeName)
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
			else
			{
				std::cerr << "Unrecognised relation node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CRelation::CRelation(const CRelation& Other)
:	m_d(new CRelationPrivate)
{
	*this=Other;
}

MusicBrainz4::CRelation& MusicBrainz4::CRelation::operator =(const CRelation& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_d->m_Type=Other.m_d->m_Type;
		m_d->m_Target=Other.m_d->m_Target;
		m_d->m_Direction=Other.m_d->m_Direction;

		if (Other.m_d->m_AttributeList)
			m_d->m_AttributeList=new CGenericList<CAttribute>(*Other.m_d->m_AttributeList);

		m_d->m_Begin=Other.m_d->m_Begin;
		m_d->m_End=Other.m_d->m_End;

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
	}

	return *this;
}

MusicBrainz4::CRelation::~CRelation()
{
	Cleanup();
	
	delete m_d;
}

void MusicBrainz4::CRelation::Cleanup()
{
	delete m_d->m_AttributeList;
	m_d->m_AttributeList=0;

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
}

std::string MusicBrainz4::CRelation::Type() const
{
	return m_d->m_Type;
}

std::string MusicBrainz4::CRelation::Target() const
{
	return m_d->m_Target;
}

std::string MusicBrainz4::CRelation::Direction() const
{
	return m_d->m_Direction;
}

MusicBrainz4::CGenericList<MusicBrainz4::CAttribute> *MusicBrainz4::CRelation::AttributeList() const
{
	return m_d->m_AttributeList;
}

std::string MusicBrainz4::CRelation::Begin() const
{
	return m_d->m_Begin;
}

std::string MusicBrainz4::CRelation::End() const
{
	return m_d->m_End;
}

MusicBrainz4::CArtist *MusicBrainz4::CRelation::Artist() const
{
	return m_d->m_Artist;
}

MusicBrainz4::CRelease *MusicBrainz4::CRelation::Release() const
{
	return m_d->m_Release;
}

MusicBrainz4::CReleaseGroup *MusicBrainz4::CRelation::ReleaseGroup() const
{
	return m_d->m_ReleaseGroup;
}

MusicBrainz4::CRecording *MusicBrainz4::CRelation::Recording() const
{
	return m_d->m_Recording;
}

MusicBrainz4::CLabel *MusicBrainz4::CRelation::Label() const
{
	return m_d->m_Label;
}

MusicBrainz4::CWork *MusicBrainz4::CRelation::Work() const
{
	return m_d->m_Work;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CRelation& Relation)
{
	os << "Relation:" << std::endl;

	os << "\tType:      " << Relation.Type() << std::endl;
	os << "\tTarget:    " << Relation.Target() << std::endl;
	os << "\tDirection: " << Relation.Direction() << std::endl;
	os << Relation.AttributeList() << std::endl;
	os << "\tBegin:     " << Relation.Begin() << std::endl;
	os << "\tEnd:       " << Relation.End() << std::endl;

	if (Relation.Artist())
		os << *Relation.Artist() << std::endl;

	if (Relation.Release())
		os << *Relation.Release() << std::endl;

	if (Relation.ReleaseGroup())
		os << *Relation.ReleaseGroup() << std::endl;

	if (Relation.Recording())
		os << *Relation.Recording() << std::endl;

	if (Relation.Label())
		os << *Relation.Label() << std::endl;

	if (Relation.Work())
		os << *Relation.Work() << std::endl;

	return os;
}
