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

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include "musicbrainz4/AnnotationList.h"

#include "musicbrainz4/Annotation.h"

class MusicBrainz4::CAnnotationListPrivate
{
	public:
};

MusicBrainz4::CAnnotationList::CAnnotationList(const XMLNode& Node)
:	CList(),
	m_d(new CAnnotationListPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "AnnotationList node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);
	}
}

MusicBrainz4::CAnnotationList::CAnnotationList(const CAnnotationList& Other)
:	CList(),
	m_d(new CAnnotationListPrivate)
{
	*this=Other;
}

MusicBrainz4::CAnnotationList& MusicBrainz4::CAnnotationList::operator =(const CAnnotationList& Other)
{
	if (this!=&Other)
	{
		CList::operator =(Other);
	}

	return *this;
}

MusicBrainz4::CAnnotationList::~CAnnotationList()
{
	delete m_d;
}

MusicBrainz4::CAnnotationList *MusicBrainz4::CAnnotationList::Clone()
{
	return new CAnnotationList(*this);
}

bool MusicBrainz4::CAnnotationList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	return CList::ParseAttribute(Name,Value);
}

bool MusicBrainz4::CAnnotationList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	if ("annotation"==NodeName)
	{
		CAnnotation *Item=0;

		RetVal=ProcessItem(Node,Item);
		if (RetVal)
			AddItem(Item);
	}
	else
	{
		RetVal=CList::ParseElement(Node);
	}

	return RetVal;
}

std::string MusicBrainz4::CAnnotationList::ElementName() const
{
	return "annotation-list";
}

MusicBrainz4::CAnnotation *MusicBrainz4::CAnnotationList::Item(int Item) const
{
	return dynamic_cast<CAnnotation *>(CList::Item(Item));
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CAnnotationList& AnnotationList)
{
	os << "Annotation list:" << std::endl;

	MusicBrainz4::CList *Base=(MusicBrainz4::CList *)&AnnotationList;

	os << *Base << std::endl;

	for (int count=0;count<AnnotationList.NumItems();count++)
	{
		MusicBrainz4::CAnnotation *Item=AnnotationList.Item(count);

		os << *Item;
	}

	return os;
}
