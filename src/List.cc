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

#include "musicbrainz5/List.h"

#include <vector>

class MusicBrainz5::CListPrivate
{
public:
	CListPrivate()
	:	m_Offset(0),
		m_Count(0)
	{
	}

	int m_Offset;
	int m_Count;
	std::vector<CEntity *> m_Items;
};

MusicBrainz5::CList::CList()
:	CEntity(),
	m_d(new CListPrivate)
{
}

MusicBrainz5::CList::CList(const CList& Other)
:	CEntity(),
	m_d(new CListPrivate)
{
	*this=Other;
}

MusicBrainz5::CList& MusicBrainz5::CList::operator =(const CList& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		CEntity::operator =(Other);

		m_d->m_Offset=Other.m_d->m_Offset;
		m_d->m_Count=Other.m_d->m_Count;

		std::vector<CEntity *>::const_iterator ThisItem=Other.m_d->m_Items.begin();
		while (ThisItem!=Other.m_d->m_Items.end())
		{
			CEntity *Item=(*ThisItem);
			m_d->m_Items.push_back(Item->Clone());
			++ThisItem;
		}
	}

	return *this;
}

MusicBrainz5::CList::~CList()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CList::Cleanup()
{
	while (!m_d->m_Items.empty())
	{
		delete m_d->m_Items.back();
		m_d->m_Items.pop_back();
	}
}

MusicBrainz5::CList *MusicBrainz5::CList::Clone()
{
	return new CList(*this);
}

bool MusicBrainz5::CList::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("offset"==Name)
		ProcessItem(Value,m_d->m_Offset);
	else if ("count"==Name)
		ProcessItem(Value,m_d->m_Count);
	else
	{
		std::cerr << "Unrecognised list attribute: '" << Name << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

bool MusicBrainz5::CList::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	std::cerr << "Unrecognised list element: '" << NodeName << "'" << std::endl;
	RetVal=false;

	return RetVal;
}

std::string MusicBrainz5::CList::GetElementName()
{
	return "";
}

void MusicBrainz5::CList::AddItem(CEntity *Item)
{
	m_d->m_Items.push_back(Item);
}

int MusicBrainz5::CList::NumItems() const
{
	return m_d->m_Items.size();
}

MusicBrainz5::CEntity *MusicBrainz5::CList::Item(int Item) const
{
	CEntity *Ret=0;

	if (Item<NumItems())
		Ret=m_d->m_Items[Item];

	return Ret;
}

int MusicBrainz5::CList::Offset() const
{
	return m_d->m_Offset;
}

int MusicBrainz5::CList::Count() const
{
	return m_d->m_Count;
}

std::ostream& MusicBrainz5::CList::Serialise(std::ostream& os) const
{
	os << "List: " << std::endl;
	os << "Offset: " << Offset() << std::endl;
	os << "Count:  " << Count() << std::endl;

	return os;
}

