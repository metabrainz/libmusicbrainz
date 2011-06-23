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

#include "musicbrainz4/xmlParser.h"

#include <list>
#include <iostream>
#include <string>

namespace MusicBrainz4
{
	template <class T>
	class CGenericList
	{
	public:
		CGenericList(const XMLNode& Node=XMLNode::emptyNode(), const std::string& SubNodeName="")
		:	m_SubNodeName(SubNodeName)
		{
			if (!Node.isEmpty())
			{
				/* std::cout << m_SubNodeName << " node: " << std::endl << Node.createXMLString(true) << std::endl; */

				int nItems=Node.nChildNode(SubNodeName.c_str());

				for (int count=0;count<nItems;count++)
				{
					XMLNode ItemNode=Node.getChildNode(SubNodeName.c_str(),count);
					m_Items.push_back(T(ItemNode));
				}
			}
		}

		std::string SubNodeName() const { return m_SubNodeName; }
		std::list<T> Items() const { return m_Items; }
		void push_back(T Item) { return m_Items.push_back(Item); }

	private:
		std::string m_SubNodeName;
		std::list<T> m_Items;
	};
}

template <class T>
std::ostream& operator << (std::ostream& os, MusicBrainz4::CGenericList<T>& List)
{
	os << List.SubNodeName() << " list:" << std::endl;

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
