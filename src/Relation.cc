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

#include "musicbrainz5/Relation.h"

#include "musicbrainz5/Artist.h"
#include "musicbrainz5/Release.h"
#include "musicbrainz5/ReleaseGroup.h"
#include "musicbrainz5/Recording.h"
#include "musicbrainz5/Label.h"
#include "musicbrainz5/Work.h"
#include "musicbrainz5/AttributeList.h"
#include "musicbrainz5/Attribute.h"

class MusicBrainz5::CRelationPrivate
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

MusicBrainz5::CRelation::CRelation(const XMLNode& Node)
:	CEntity(),
	m_d(new CRelationPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Relation node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CRelation::CRelation(const CRelation& Other)
:	CEntity(),
	m_d(new CRelationPrivate)
{
	*this=Other;
}

MusicBrainz5::CRelation& MusicBrainz5::CRelation::operator =(const CRelation& Other)
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

MusicBrainz5::CRelation::~CRelation()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CRelation::Cleanup()
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

MusicBrainz5::CRelation *MusicBrainz5::CRelation::Clone()
{
	return new CRelation(*this);
}

bool MusicBrainz5::CRelation::ParseAttribute(const std::string& Name, const std::string& Value)
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

bool MusicBrainz5::CRelation::ParseElement(const XMLNode& Node)
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

std::string MusicBrainz5::CRelation::GetElementName()
{
	return "relation";
}

std::string MusicBrainz5::CRelation::Type() const
{
	return m_d->m_Type;
}

std::string MusicBrainz5::CRelation::Target() const
{
	return m_d->m_Target;
}

std::string MusicBrainz5::CRelation::Direction() const
{
	return m_d->m_Direction;
}

MusicBrainz5::CAttributeList *MusicBrainz5::CRelation::AttributeList() const
{
	return m_d->m_AttributeList;
}

std::string MusicBrainz5::CRelation::Begin() const
{
	return m_d->m_Begin;
}

std::string MusicBrainz5::CRelation::End() const
{
	return m_d->m_End;
}

MusicBrainz5::CArtist *MusicBrainz5::CRelation::Artist() const
{
	return m_d->m_Artist;
}

MusicBrainz5::CRelease *MusicBrainz5::CRelation::Release() const
{
	return m_d->m_Release;
}

MusicBrainz5::CReleaseGroup *MusicBrainz5::CRelation::ReleaseGroup() const
{
	return m_d->m_ReleaseGroup;
}

MusicBrainz5::CRecording *MusicBrainz5::CRelation::Recording() const
{
	return m_d->m_Recording;
}

MusicBrainz5::CLabel *MusicBrainz5::CRelation::Label() const
{
	return m_d->m_Label;
}

MusicBrainz5::CWork *MusicBrainz5::CRelation::Work() const
{
	return m_d->m_Work;
}

std::ostream& MusicBrainz5::CRelation::Serialise(std::ostream& os) const
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
