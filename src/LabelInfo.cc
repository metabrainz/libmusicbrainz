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

#include "musicbrainz4/LabelInfo.h"

#include "musicbrainz4/Label.h"

class MusicBrainz4::CLabelInfoPrivate
{
	public:
		CLabelInfoPrivate()
		:	m_Label(0)
		{
		}

		std::string m_CatalogNumber;
		CLabel *m_Label;
};

MusicBrainz4::CLabelInfo::CLabelInfo(const XMLNode& Node)
:	CEntity(),
	m_d(new CLabelInfoPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Label info node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CLabelInfo::CLabelInfo(const CLabelInfo& Other)
:	CEntity(),
	m_d(new CLabelInfoPrivate)
{
	*this=Other;
}

MusicBrainz4::CLabelInfo& MusicBrainz4::CLabelInfo::operator =(const CLabelInfo& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_d->m_CatalogNumber=Other.m_d->m_CatalogNumber;

		if (Other.m_d->m_Label)
			m_d->m_Label=new CLabel(*Other.m_d->m_Label);
	}

	return *this;
}

MusicBrainz4::CLabelInfo::~CLabelInfo()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz4::CLabelInfo::Cleanup()
{
	delete m_d->m_Label;
	m_d->m_Label=0;
}

bool MusicBrainz4::CLabelInfo::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	bool RetVal=true;

	std::cerr << "Unrecognised labelinfo attribute: '" << Name << "'" << std::endl;
	RetVal=false;

	return RetVal;
}

bool MusicBrainz4::CLabelInfo::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("catalog-number"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_CatalogNumber);
	}
	else if ("label"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Label);
	}
	else
	{
		std::cerr << "Unrecognised label info element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz4::CLabelInfo::CatalogNumber() const
{
	return m_d->m_CatalogNumber;
}

MusicBrainz4::CLabel *MusicBrainz4::CLabelInfo::Label() const
{
	return m_d->m_Label;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CLabelInfo& LabelInfo)
{
	os << "Label info:" << std::endl;

	MusicBrainz4::CEntity *Base=(MusicBrainz4::CEntity *)&LabelInfo;

	os << *Base << std::endl;

	os << "\tCatalog number: " << LabelInfo.CatalogNumber() << std::endl;

	if (LabelInfo.Label())
		os << *LabelInfo.Label() << std::endl;

	return os;
}

