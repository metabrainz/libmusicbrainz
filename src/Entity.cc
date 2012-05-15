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

#include "musicbrainz5/Entity.h"

#include "musicbrainz5/RelationList.h"
#include "musicbrainz5/RelationListList.h"

class MusicBrainz5::CEntityPrivate
{
	public:
		CEntityPrivate()
		{
		}

		std::map<std::string,std::string> m_ExtAttributes;
		std::map<std::string,std::string> m_ExtElements;
};

MusicBrainz5::CEntity::CEntity()
:	m_d(new CEntityPrivate)
{
}

MusicBrainz5::CEntity::CEntity(const CEntity& Other)
:	m_d(new CEntityPrivate)
{
	*this=Other;
}

MusicBrainz5::CEntity& MusicBrainz5::CEntity::operator =(const CEntity& Other)
{
	if (this!=&Other)
	{
		Cleanup();

		m_d->m_ExtAttributes=Other.m_d->m_ExtAttributes;
		m_d->m_ExtElements=Other.m_d->m_ExtElements;
	}

	return *this;
}

MusicBrainz5::CEntity::~CEntity()
{
	Cleanup();

	delete m_d;
}

void MusicBrainz5::CEntity::Cleanup()
{
}

bool MusicBrainz5::CEntity::Parse(const XMLNode& Node)
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

std::map<std::string,std::string> MusicBrainz5::CEntity::ExtAttributes() const
{
	return m_d->m_ExtAttributes;
}

std::map<std::string,std::string> MusicBrainz5::CEntity::ExtElements() const
{
	return m_d->m_ExtElements;
}

bool MusicBrainz5::CEntity::ProcessRelationList(const XMLNode& Node, CRelationListList* & RetVal)
{
	if (0==RetVal)
		RetVal=new CRelationListList;

	CRelationList *RelationList=0;
	ProcessItem(Node,RelationList);
	RetVal->Add(RelationList);
	delete RelationList;

	return true;
}
std::ostream& MusicBrainz5::CEntity::Serialise(std::ostream& os) const
{
	if (!ExtAttributes().empty())
	{
		os << "Ext attrs: " << std::endl;
		std::map<std::string,std::string> ExtAttrs=ExtAttributes();
		std::map<std::string,std::string>::const_iterator ThisExtAttr=ExtAttrs.begin();
		while (ThisExtAttr!=ExtAttrs.end())
		{
			os << (*ThisExtAttr).first << " = " << (*ThisExtAttr).second << std::endl;

			++ThisExtAttr;
		}
	}

	if (!ExtElements().empty())
	{
		os << "Ext elements: " << std::endl;
		std::map<std::string,std::string> ExtElems=ExtElements();
		std::map<std::string,std::string>::const_iterator ThisExtElement=ExtElems.begin();
		while (ThisExtElement!=ExtElems.end())
		{
			os << (*ThisExtElement).first << " = " << (*ThisExtElement).second << std::endl;

			++ThisExtElement;
		}
	}

	return os;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz5::CEntity& Entity)
{
	return Entity.Serialise(os);
}

