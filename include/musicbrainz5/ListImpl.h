/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

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

#ifndef _MUSICBRAINZ5_LIST_IMPL_H
#define _MUSICBRAINZ5_LIST_IMPL_H

#include "musicbrainz5/List.h"

namespace MusicBrainz5
{
	template <class T>
	class CListImpl: public CList
	{
	public:
		CListImpl(const XMLNode& Node=XMLNode::emptyNode())
		:	CList()
		{
			if (!Node.isEmpty())
			{
				//std::cout << T::GetElementName() << " List node: " << std::endl << Node.createXMLString(true) << std::endl;

				Parse(Node);
			}
		}

		CListImpl(const CListImpl<T>& Other)
		:	CList()
		{
			*this=Other;
		}

		MusicBrainz5::CListImpl<T>& operator =(const CListImpl<T>& Other)
		{
			if (this!=&Other)
			{
				CList::operator =(Other);
			}

			return *this;
		}

		virtual ~CListImpl()
		{
		}

		CListImpl<T> *Clone()
		{
			return new CListImpl<T>(*this);
		}

		virtual std::ostream& Serialise(std::ostream& os) const
		{
			os << T::GetElementName() << " List (impl):" << std::endl;

			CList::Serialise(os);

			for (int count=0;count<NumItems();count++)
			{
				T *ThisItem=Item(count);

				os << *ThisItem << std::endl;
			}

			return os;
		}

		static std::string GetElementName()
		{
			return "";
		}

		T *Item(int Item) const
		{
			return dynamic_cast<T *>(CList::Item(Item));
		}

		void AddItem(T *Item)
		{
			CList::AddItem(Item);
		}

	protected:
		void ParseElement(const XMLNode& Node)
		{
			std::string NodeName=Node.getName();

			if (T::GetElementName()==NodeName)
			{
				T *Item=0;

				ProcessItem(Node,Item);
				AddItem(Item);
			}
			else
				CList::ParseElement(Node);
		}
	};
}

#endif
