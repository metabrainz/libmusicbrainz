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

#ifndef _MUSICBRAINZ4_GENERIC_LIST_H
#define _MUSICBRAINZ4_GENERIC_LIST_H

#include "musicbrainz4/Entity.h"

#include "musicbrainz4/xmlParser.h"

#include <list>
#include <iostream>
#include <string>

namespace MusicBrainz4
{
	template <class T>
	class CGenericList: public CEntity
	{
	public:
		CGenericList(const XMLNode& Node=XMLNode::emptyNode())
		:	CEntity(),
			m_Offset(0),
			m_Count(0)
		{
			if (!Node.isEmpty())
			{
				//std::cout << "List node: " << std::endl << Node.createXMLString(true) << std::endl;

				Parse(Node);
			}
		}

		std::list<T> Items() const { return m_Items; }
		void push_back(T Item) { return m_Items.push_back(Item); }
		int Offset() const { return m_Offset; }
		int Count() const { return m_Count; }

	private:
		std::list<T> m_Items;
		int m_Offset;
		int m_Count;

		virtual bool ParseAttribute(const std::string& Name, const std::string& Value)
		{
			bool RetVal=true;

			if ("offset"==Name)
				ProcessItem(Value,m_Offset);
			else if ("count"==Name)
				ProcessItem(Value,m_Count);
			else
			{
				std::cerr << "Unrecognised list attribute: '" << Name << "'" << std::endl;
				RetVal=false;
			}

			return RetVal;
		}

		virtual bool ParseElement(const XMLNode& Node)
		{
			bool RetVal=true;

			T *Item=0;

			RetVal=ProcessItem(Node,Item);
			if (RetVal)
			{
				m_Items.push_back(*Item);
			}

			delete Item;

			return RetVal;
		}
	};
}

template <class T>
std::ostream& operator << (std::ostream& os, MusicBrainz4::CGenericList<T>& List)
{
	os << "List:" << std::endl;

	os << "Offset: " << List.Offset() << std::endl;
	os << "Count:  " << List.Count() << std::endl;

	std::list<T> Items=List.Items();
	typename std::list<T>::const_iterator ThisItem=Items.begin();
	while (ThisItem!=Items.end())
	{
		os << *ThisItem << std::endl;

		++ThisItem;
	}

	return os;
}

#endif
