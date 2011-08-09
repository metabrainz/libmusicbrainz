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

#include "musicbrainz4/Annotation.h"

class MusicBrainz4::CAnnotationPrivate
{
public:
		std::string m_Type;
		std::string m_Entity;
		std::string m_Name;
		std::string m_Text;
};

MusicBrainz4::CAnnotation::CAnnotation(const XMLNode& Node)
:	CEntity(),
	m_d(new CAnnotationPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Annotation node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CAnnotation::CAnnotation(const CAnnotation& Other)
:	CEntity(),
	m_d(new CAnnotationPrivate)
{
	*this=Other;
}

MusicBrainz4::CAnnotation& MusicBrainz4::CAnnotation::operator =(const CAnnotation& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_Type=Other.m_d->m_Type;
		m_d->m_Entity=Other.m_d->m_Entity;
		m_d->m_Name=Other.m_d->m_Name;
		m_d->m_Text=Other.m_d->m_Text;
	}

	return *this;
}

MusicBrainz4::CAnnotation::~CAnnotation()
{
	delete m_d;
}

MusicBrainz4::CAnnotation *MusicBrainz4::CAnnotation::Clone()
{
	return new CAnnotation(*this);
}

bool MusicBrainz4::CAnnotation::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("type"==Name)
		m_d->m_Type=Value;
	else
	{
		std::cerr << "Unrecognised annotation attribute: '" << Name << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

bool MusicBrainz4::CAnnotation::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("entity"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Entity);
	}
	else if ("name"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Name);
	}
	else if ("text"==NodeName)
	{
		RetVal=ProcessItem(Node,m_d->m_Text);
	}
	else
	{
		std::cerr << "Unrecognised annotation element: '" << NodeName << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

std::string MusicBrainz4::CAnnotation::GetElementName()
{
	return "annotation";
}

std::string MusicBrainz4::CAnnotation::Type() const
{
	return m_d->m_Type;
}

std::string MusicBrainz4::CAnnotation::Entity() const
{
	return m_d->m_Entity;
}

std::string MusicBrainz4::CAnnotation::Name() const
{
	return m_d->m_Name;
}

std::string MusicBrainz4::CAnnotation::Text() const
{
	return m_d->m_Text;
}

std::ostream& MusicBrainz4::CAnnotation::Serialise(std::ostream& os) const
{
	os << "Annotation:" << std::endl;

	CEntity::Serialise(os);

	os << "\tType:   " << Type() << std::endl;
	os << "\tEntity: " << Entity() << std::endl;
	os << "\tName:   " << Name() << std::endl;
	os << "\tText:   " << Text() << std::endl;

	return os;
}
