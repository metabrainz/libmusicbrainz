/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2013 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

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

#include "musicbrainz5/TargetItem.h"

class MusicBrainz5::CTargetItemPrivate
{
	public:
		std::string m_ID;
		std::string m_Target;
};

MusicBrainz5::CTargetItem::CTargetItem(const XMLNode& Node)
:	CEntity(),
	m_d(new CTargetItemPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Target node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);

		if (Node.getText())
		{
			ProcessItem(Node,m_d->m_Target);
		}
	}
}

MusicBrainz5::CTargetItem::CTargetItem(const CTargetItem& Other)
:	CEntity(),
	m_d(new CTargetItemPrivate)
{
	*this=Other;
}

MusicBrainz5::CTargetItem& MusicBrainz5::CTargetItem::operator =(const CTargetItem& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_ID=Other.m_d->m_ID;
		m_d->m_Target=Other.m_d->m_Target;
	}

	return *this;
}

MusicBrainz5::CTargetItem::~CTargetItem()
{
	delete m_d;
}

MusicBrainz5::CTargetItem *MusicBrainz5::CTargetItem::Clone()
{
	return new CTargetItem(*this);
}

void MusicBrainz5::CTargetItem::ParseAttribute(const std::string& Name, const std::string& Value)
{
	if ("id"==Name)
		m_d->m_ID=Value;
#ifdef _MB5_DEBUG_
	else
	{
		std::cerr << "Unrecognised url attribute: '" << Name << "'" << std::endl;
	}
#endif
}

void MusicBrainz5::CTargetItem::ParseElement(const XMLNode& Node)
{
#ifdef _MB5_DEBUG_
	std::string NodeName=Node.getName();

	std::cerr << "Unrecognised url element: '" << NodeName << "'" << std::endl;
#else
	(void)Node;
#endif
}

std::string MusicBrainz5::CTargetItem::GetElementName()
{
	return "target";
}

std::string MusicBrainz5::CTargetItem::ID() const
{
	return m_d->m_ID;
}

std::string MusicBrainz5::CTargetItem::Target() const
{
	return m_d->m_Target;
}

std::ostream& MusicBrainz5::CTargetItem::Serialise(std::ostream& os) const
{
	os << "Target Item:" << std::endl;

	CEntity::Serialise(os);

	os << "ID:     " << ID() << std::endl;
	os << "Target: " << Target() << std::endl;

	return os;
}
