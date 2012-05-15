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

#include "musicbrainz5/LabelInfo.h"

#include "musicbrainz5/Label.h"

class MusicBrainz5::CLabelInfoPrivate
{
	public:
		CLabelInfoPrivate()
		:	m_Label(0)
		{
		}

		std::string m_CatalogNumber;
		CLabel *m_Label;
};

MusicBrainz5::CLabelInfo::CLabelInfo(const XMLNode& Node)
:	CEntity(),
	m_d(new CLabelInfoPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Label info node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz5::CLabelInfo::CLabelInfo(const CLabelInfo& Other)
:	CEntity(),
	m_d(new CLabelInfoPrivate)
{
	*this=Other;
}

MusicBrainz5::CLabelInfo& MusicBrainz5::CLabelInfo::operator =(const CLabelInfo& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_CatalogNumber=Other.m_d->m_CatalogNumber;

		if (Other.m_d->m_Label)
			m_d->m_Label=new CLabel(*Other.m_d->m_Label);
	}

	return *this;
}

MusicBrainz5::CLabelInfo::~CLabelInfo()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CLabelInfo::Cleanup()
{
	delete m_d->m_Label;
	m_d->m_Label=0;
}

MusicBrainz5::CLabelInfo *MusicBrainz5::CLabelInfo::Clone()
{
	return new CLabelInfo(*this);
}

bool MusicBrainz5::CLabelInfo::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	bool RetVal=true;

	std::cerr << "Unrecognised labelinfo attribute: '" << Name << "'" << std::endl;
	RetVal=false;

	return RetVal;
}

bool MusicBrainz5::CLabelInfo::ParseElement(const XMLNode& Node)
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

std::string MusicBrainz5::CLabelInfo::GetElementName()
{
	return "label-info";
}

std::string MusicBrainz5::CLabelInfo::CatalogNumber() const
{
	return m_d->m_CatalogNumber;
}

MusicBrainz5::CLabel *MusicBrainz5::CLabelInfo::Label() const
{
	return m_d->m_Label;
}

std::ostream& MusicBrainz5::CLabelInfo::Serialise(std::ostream& os) const
{
	os << "Label info:" << std::endl;

	CEntity::Serialise(os);

	os << "\tCatalog number: " << CatalogNumber() << std::endl;

	if (Label())
		os << *Label() << std::endl;

	return os;
}

