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

MusicBrainz4::CCollection::CCollection(const XMLNode& Node)
:	m_ReleaseList(0)
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

			if ("name"==NodeName)
			{
				m_Name=NodeValue;
			}
			else if ("editor"==NodeName)
			{
				m_Editor=NodeValue;
			}
			else if ("release-list"==NodeName)
			{
				m_ReleaseList=new CGenericList<CRelease>(ChildNode,"release");
			}
			else
			{
				std::cerr << "Unrecognised collection node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CCollection::CCollection(const CCollection& Other)
:	m_ReleaseList(0)
{
	*this=Other;
}

MusicBrainz4::CCollection& MusicBrainz4::CCollection::operator =(const CCollection& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_ID=Other.m_ID;
		m_Name=Other.m_Name;
		m_Editor=Other.m_Editor;

		if (Other.m_ReleaseList)
			m_ReleaseList=new CGenericList<CRelease>(*Other.m_ReleaseList);
	}

	return *this;
}

MusicBrainz4::CCollection::~CCollection()
{
	Cleanup();
}

void MusicBrainz4::CCollection::Cleanup()
{
	delete m_ReleaseList;
	m_ReleaseList=0;
}

std::string MusicBrainz4::CCollection::ID() const
{
	return m_ID;
}

std::string MusicBrainz4::CCollection::Name() const
{
	return m_Name;
}

std::string MusicBrainz4::CCollection::Editor() const
{
	return m_Editor;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRelease> *MusicBrainz4::CCollection::ReleaseList() const
{
	return m_ReleaseList;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CCollection& Collection)
{
	os << "Collection:" << std::endl;

	os << "\tID:  " << Collection.ID() << std::endl;
	os << "\tName: " << Collection.Name() << std::endl;
	os << "\tEditor: " << Collection.Editor() << std::endl;

	if (Collection.ReleaseList())
		os << *Collection.ReleaseList() << std::endl;

	return os;
}
