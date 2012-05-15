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

#include "musicbrainz5/Collection.h"

#include "musicbrainz5/ReleaseList.h"
#include "musicbrainz5/Release.h"

class MusicBrainz5::CCollectionPrivate
{
	public:
		CCollectionPrivate()
		:	 m_ReleaseList(0)
		{
		}

		std::string m_ID;
		std::string m_Name;
		std::string m_Editor;
		CReleaseList *m_ReleaseList;
};
MusicBrainz5::CCollection::CCollection(const XMLNode& Node)
:	CEntity(),
	m_d(new CCollectionPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Medium node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CCollection::CCollection(const CCollection& Other)
:	CEntity(),
	m_d(new CCollectionPrivate)
{
	*this=Other;
}

MusicBrainz5::CCollection& MusicBrainz5::CCollection::operator =(const CCollection& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Name=Other.m_d->m_Name;
		m_d->m_Editor=Other.m_d->m_Editor;

		if (Other.m_d->m_ReleaseList)
			m_d->m_ReleaseList=new CReleaseList(*Other.m_d->m_ReleaseList);
	}

	return *this;
}

MusicBrainz5::CCollection::~CCollection()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CCollection::Cleanup()
{
	delete m_d->m_ReleaseList;
	m_d->m_ReleaseList=0;
}

MusicBrainz5::CCollection *MusicBrainz5::CCollection::Clone()
{
	return new CCollection(*this);
}

bool MusicBrainz5::CCollection::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("id"==Name)
		m_d->m_ID=Value;
	else
	{
		std::cerr << "Unrecognised collection attribute: '" << Name << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

bool MusicBrainz5::CCollection::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("name"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Name);
	}
	else if ("editor"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Editor);
	}
	else if ("release-list"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_ReleaseList);
	}
	else
	{
		std::cerr << "Unrecognised collection element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}
	return RetVal;
}

std::string MusicBrainz5::CCollection::GetElementName()
{
	return "collection";
}

std::string MusicBrainz5::CCollection::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz5::CCollection::Name() const
{
	return m_d->m_Name;
}

std::string MusicBrainz5::CCollection::Editor() const
{
	return m_d->m_Editor;
}

MusicBrainz5::CReleaseList *MusicBrainz5::CCollection::ReleaseList() const
{
	return m_d->m_ReleaseList;
}

std::ostream& MusicBrainz5::CCollection::Serialise(std::ostream& os) const
{
	os << "Collection:" << std::endl;

	CEntity::Serialise(os);

	os << "\tID:     " << ID() << std::endl;
	os << "\tName:   " << Name() << std::endl;
	os << "\tEditor: " << Editor() << std::endl;

	if (ReleaseList())
		os << *ReleaseList() << std::endl;

	return os;
}
