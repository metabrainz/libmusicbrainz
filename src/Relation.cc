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

#include "musicbrainz4/Relation.h"

#include "musicbrainz4/Artist.h"
#include "musicbrainz4/Release.h"
#include "musicbrainz4/ReleaseGroup.h"
#include "musicbrainz4/Recording.h"
#include "musicbrainz4/Label.h"
#include "musicbrainz4/Work.h"
#include "musicbrainz4/AttributeList.h"
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
		CAttributeList *m_AttributeList;
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
:	CEntity(),
	m_d(new CRelationPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Relation node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CRelation::CRelation(const CRelation& Other)
:	CEntity(),
	m_d(new CRelationPrivate)
{
	*this=Other;
}

MusicBrainz4::CRelation& MusicBrainz4::CRelation::operator =(const CRelation& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_Type=Other.m_d->m_Type;
		m_d->m_Target=Other.m_d->m_Target;
		m_d->m_Direction=Other.m_d->m_Direction;

		if (Other.m_d->m_AttributeList)
			m_d->m_AttributeList=new CAttributeList(*Other.m_d->m_AttributeList);

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

MusicBrainz4::CRelation *MusicBrainz4::CRelation::Clone()
{
	return new CRelation(*this);
}

bool MusicBrainz4::CRelation::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("type"==Name)
		m_d->m_Type=Value;
	else
	{
		std::cerr << "Unrecognised relation attribute: '" << Name << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

bool MusicBrainz4::CRelation::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("target"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Target);
	}
	else if ("direction"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Direction);
	}
	else if ("attribute-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_AttributeList);
	}
	else if ("begin"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Begin);
	}
	else if ("end"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_End);
	}
	else if ("artist"==NodeName)
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
	else
	{
		std::cerr << "Unrecognised relation element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz4::CRelation::GetElementName()
{
	return "relation";
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

MusicBrainz4::CAttributeList *MusicBrainz4::CRelation::AttributeList() const
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

std::ostream& MusicBrainz4::CRelation::Serialise(std::ostream& os) const
{
	os << "Relation:" << std::endl;

	CEntity::Serialise(os);

	os << "\tType:      " << Type() << std::endl;
	os << "\tTarget:    " << Target() << std::endl;
	os << "\tDirection: " << Direction() << std::endl;

	if (AttributeList())
		os << AttributeList() << std::endl;

	os << "\tBegin:     " << Begin() << std::endl;
	os << "\tEnd:       " << End() << std::endl;

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

	return os;
}
