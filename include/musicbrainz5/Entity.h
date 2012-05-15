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

#ifndef _MUSICBRAINZ5_ENTITY_H
#define _MUSICBRAINZ5_ENTITY_H

#include <iostream>
#include <string>
#include <sstream>
#include <map>

#include "musicbrainz5/xmlParser.h"

namespace MusicBrainz5
{
	class CEntityPrivate;

	class CRelationListList;

	class CEntity
	{
	public:
		CEntity();
		CEntity(const CEntity& Other);
		CEntity& operator =(const CEntity& Other);
		virtual ~CEntity();

		virtual CEntity *Clone()=0;

		bool Parse(const XMLNode& Node);

		std::map<std::string,std::string> ExtAttributes() const;
		std::map<std::string,std::string> ExtElements() const;

		virtual std::ostream& Serialise(std::ostream& os) const;
		static std::string GetElementName();

	protected:
		bool ProcessRelationList(const XMLNode& Node, CRelationListList* & RetVal);

		template<typename T>
		bool ProcessItem(const XMLNode& Node, T* & RetVal)
		{
			RetVal=new T(Node);

			return true;
		}

		template<class T>
		bool ProcessItem(const XMLNode& Node, T& RetVal)
		{
			bool Ret=true;

			std::stringstream os;
			if (Node.getText())
				os << (const char *)Node.getText();

			os >> RetVal;
			if (os.fail())
			{
				Ret=false;
				std::cerr << "Error parsing value '";
				if (Node.getText())
					std::cerr << Node.getText();
				std::cerr << "'" << std::endl;
			}

			return Ret;
		}

		template<typename T>
		bool ProcessItem(const std::string& Text, T& RetVal)
		{
			bool Ret=true;

			std::stringstream os;
			os << Text;

			os >> RetVal;
			if (os.fail())
			{
				Ret=false;
				std::cerr << "Error parsing value '" << Text << "'" << std::endl;
			}

			return Ret;
		}

		bool ProcessItem(const XMLNode& Node, std::string& RetVal)
		{
			if (Node.getText())
				RetVal=Node.getText();

			return true;

		}

		virtual bool ParseAttribute(const std::string& Name, const std::string& Value)=0;
		virtual bool ParseElement(const XMLNode& Node)=0;

	private:
		CEntityPrivate *m_d;

		void Cleanup();

	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz5::CEntity& Entity);

#endif
