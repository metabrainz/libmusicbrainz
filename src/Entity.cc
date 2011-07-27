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

#include "musicbrainz4/Entity.h"

class MusicBrainz4::CEntityPrivate
{
	public:
		CEntityPrivate()
		{
		}

		std::map<std::string,std::string> m_ExtAttributes;
		std::map<std::string,std::string> m_ExtElements;
};

MusicBrainz4::CEntity::CEntity()
:	m_d(new CEntityPrivate)
{
}

MusicBrainz4::CEntity::CEntity(const CEntity& Other)
:	m_d(new CEntityPrivate)
{
	*this=Other;
}

MusicBrainz4::CEntity& MusicBrainz4::CEntity::operator =(const CEntity& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_d->m_ExtAttributes=Other.m_d->m_ExtAttributes;
		m_d->m_ExtElements=Other.m_d->m_ExtElements;
	}

	return *this;
}

MusicBrainz4::CEntity::~CEntity()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz4::CEntity::Cleanup()
{
}

bool MusicBrainz4::CEntity::Parse(const XMLNode& Node)
{
	bool RetVal=true;

	if (!Node.isEmpty())
	{
		for (int count=0;count<Node.nAttribute();count++)
		{
			std::string Name=Node.getAttributeName(count);
			std::string Value=Node.getAttributeValue(count);

			if ("ext:"==Name.substr(0,4))
			{
				m_d->m_ExtAttributes[Name.substr(4)]=Value;
			}
			else
				RetVal=RetVal && ParseAttribute(Name,Value);
		}

		//std::cout << "Node: " << std::endl << Node.createXMLString(true) << std::endl;

		for (int count=0;count<Node.nChildNode();count++)
		{
			XMLNode ChildNode=Node.getChildNode(count);

			std::string Name=ChildNode.getName();
			std::string Value;
			if (ChildNode.getText())
				Value=ChildNode.getText();

			if ("ext:"==Name.substr(0,4))
			{
				m_d->m_ExtElements[Name.substr(4)]=Value;
			}
			else
				RetVal=RetVal && ParseElement(ChildNode);
		}
	}

	return RetVal;
}

std::map<std::string,std::string> MusicBrainz4::CEntity::ExtAttributes() const
{
	return m_d->m_ExtAttributes;
}

std::map<std::string,std::string> MusicBrainz4::CEntity::ExtElements() const
{
	return m_d->m_ExtElements;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CEntity& Entity)
{
	if (!Entity.ExtAttributes().empty())
	{
		std::cout << "Ext attrs: " << std::endl;
		std::map<std::string,std::string> ExtAttrs=Entity.ExtAttributes();
		std::map<std::string,std::string>::const_iterator ThisExtAttr=ExtAttrs.begin();
		while (ThisExtAttr!=ExtAttrs.end())
		{
			os << (*ThisExtAttr).first << " = " << (*ThisExtAttr).second << std::endl;

			++ThisExtAttr;
		}
	}

	if (!Entity.ExtElements().empty())
	{
		std::cout << "Ext elements: " << std::endl;
		std::map<std::string,std::string> ExtElements=Entity.ExtElements();
		std::map<std::string,std::string>::const_iterator ThisExtElement=ExtElements.begin();
		while (ThisExtElement!=ExtElements.end())
		{
			os << (*ThisExtElement).first << " = " << (*ThisExtElement).second << std::endl;

			++ThisExtElement;
		}
	}

	return os;
}