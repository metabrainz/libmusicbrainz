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
:	m_d(new CAnnotationPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Annotation node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("type"))
			m_d->m_Type=Node.getAttribute("type");

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);
			std::string NodeName=ChildNode.getName();
			std::string NodeValue;
			if (ChildNode.getText())
				NodeValue=ChildNode.getText();

			if ("entity"==NodeName)
			{
				m_d->m_Entity=NodeValue;
			}
			else if ("name"==NodeName)
			{
				m_d->m_Name=NodeValue;
			}
			else if ("text"==NodeName)
			{
				m_d->m_Text=NodeValue;
			}
			else
			{
				std::cerr << "Unrecognised annotatio  node: '" << NodeName << "'" << std::endl;
			}
		}
	}
}

MusicBrainz4::CAnnotation::CAnnotation(const CAnnotation& Other)
:	m_d(new CAnnotationPrivate)
{
	*this=Other;
}

MusicBrainz4::CAnnotation& MusicBrainz4::CAnnotation::operator =(const CAnnotation& Other)
{
	if (this!=&Other)
	{
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

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CAnnotation& Annotation)
{
	os << "Annotation:" << std::endl;

	os << "\tType:    " << Annotation.Type() << std::endl;
	os << "\tEntity: " << Annotation.Entity() << std::endl;
	os << "\tName:   " << Annotation.Name() << std::endl;
	os << "\tText:   " << Annotation.Text() << std::endl;

	return os;
}
