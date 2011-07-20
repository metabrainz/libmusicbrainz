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

#include "musicbrainz4/Collection.h"

#include "musicbrainz4/Release.h"

class MusicBrainz4::CCollectionPrivate
{
	public:
		CCollectionPrivate()
		:	 m_ReleaseList(0)
		{
		}

		std::string m_ID;
		std::string m_Name;
		std::string m_Editor;
		CGenericList<CRelease> *m_ReleaseList;
};
MusicBrainz4::CCollection::CCollection(const XMLNode& Node)
:	CEntity(),
	m_d(new CCollectionPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Medium node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CCollection::CCollection(const CCollection& Other)
:	CEntity(),
	m_d(new CCollectionPrivate)
{
	*this=Other;
}

MusicBrainz4::CCollection& MusicBrainz4::CCollection::operator =(const CCollection& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Name=Other.m_d->m_Name;
		m_d->m_Editor=Other.m_d->m_Editor;

		if (Other.m_d->m_ReleaseList)
			m_d->m_ReleaseList=new CGenericList<CRelease>(*Other.m_d->m_ReleaseList);
	}

	return *this;
}

MusicBrainz4::CCollection::~CCollection()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz4::CCollection::Cleanup()
{
	delete m_d->m_ReleaseList;
	m_d->m_ReleaseList=0;
}

bool MusicBrainz4::CCollection::ParseAttribute(const std::string& Name, const std::string& Value)
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

bool MusicBrainz4::CCollection::ParseElement(const XMLNode& Node)
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

std::string MusicBrainz4::CCollection::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz4::CCollection::Name() const
{
	return m_d->m_Name;
}

std::string MusicBrainz4::CCollection::Editor() const
{
	return m_d->m_Editor;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRelease> *MusicBrainz4::CCollection::ReleaseList() const
{
	return m_d->m_ReleaseList;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CCollection& Collection)
{
	os << "Collection:" << std::endl;

	MusicBrainz4::CEntity *Base=(MusicBrainz4::CEntity *)&Collection;

	os << *Base << std::endl;

	os << "\tID:  " << Collection.ID() << std::endl;
	os << "\tName: " << Collection.Name() << std::endl;
	os << "\tEditor: " << Collection.Editor() << std::endl;

	if (Collection.ReleaseList())
		os << *Collection.ReleaseList() << std::endl;

	return os;
}
