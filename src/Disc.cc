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

#include "musicbrainz4/Disc.h"

#include "musicbrainz4/Release.h"

class MusicBrainz4::CDiscPrivate
{
	public:
		CDiscPrivate()
		:	m_ReleaseList(0)
		{
		}
		
		std::string m_ID;
		std::string m_Sectors;
		CGenericList<CRelease> *m_ReleaseList;
};

MusicBrainz4::CDisc::CDisc(const XMLNode& Node)
:	m_d(new CDiscPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Disc node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("id"))
			m_d->m_ID=Node.getAttribute("id");

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("sectors"==NodeName)
			{
				m_d->m_Sectors=NodeValue;
			}
			else if ("release-list"==NodeName)
			{
				m_d->m_ReleaseList=new CGenericList<CRelease>(ChildNode,"release");
			}
			else
			{
				std::cerr << "Unrecognised disc node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CDisc::CDisc(const CDisc& Other)
:	m_d(new CDiscPrivate)
{
	*this=Other;
}

MusicBrainz4::CDisc& MusicBrainz4::CDisc::operator =(const CDisc& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Sectors=Other.m_d->m_Sectors;

		if (Other.m_d->m_ReleaseList)
			m_d->m_ReleaseList=new CGenericList<CRelease>(*Other.m_d->m_ReleaseList);
	}

	return *this;
}

MusicBrainz4::CDisc::~CDisc()
{
	Cleanup();
	
	delete m_d;
}

void MusicBrainz4::CDisc::Cleanup()
{
	delete m_d->m_ReleaseList;
	m_d->m_ReleaseList=0;
}

std::string MusicBrainz4::CDisc::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz4::CDisc::Sectors() const
{
	return m_d->m_Sectors;
}

MusicBrainz4::CGenericList<MusicBrainz4::CRelease> *MusicBrainz4::CDisc::ReleaseList() const
{
	return m_d->m_ReleaseList;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CDisc& Disc)
{
	os << "Disc:" << std::endl;

	os << "\tID:      " << Disc.ID() << std::endl;
	os << "\tSectors: " << Disc.Sectors() << std::endl;

	if (Disc.ReleaseList())
		os << *Disc.ReleaseList() << std::endl;

	return os;
}

