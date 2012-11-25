/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Christophe Fergeau

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
#ifndef _MUSICBRAINZ5_XMLPARSER_H
#define _MUSICBRAINZ5_XMLPARSER_H

#include <string>
#include <libxml/tree.h>

typedef xmlError XMLResults;

const int eXMLErrorNone = 0;

class XMLAttribute;
class XMLNode
{
    public:
        static XMLNode emptyNode();
        bool isEmpty() const;

        virtual ~XMLNode() {};

        const XMLAttribute getAttribute(const char *name = NULL) const;
        bool isAttributeSet(const char *name) const;

        XMLNode getChildNode(const char *name = NULL) const;
        XMLNode next() const;
        const char *getName() const;
        const char *getText() const;

        friend bool operator== (const XMLNode &lhs, const XMLNode &rhs);

    protected:
        XMLNode(xmlNodePtr node): mNode(node) {};

        xmlNodePtr mNode;

    private:
        xmlAttrPtr getAttributeRaw(const char *name) const;
};

inline bool operator== (const XMLNode &lhs, const XMLNode &rhs)
{
    return (lhs.mNode == rhs.mNode);
}

inline bool operator!= (const XMLNode &lhs, const XMLNode &rhs)
{
        return !(lhs == rhs);
}

class XMLRootNode: public XMLNode
{
    public:
        static XMLNode* parseString(std::string &xml, XMLResults *results);
        static XMLNode* parseFile(const std::string &filename, XMLResults *results);

        virtual ~XMLRootNode() { if (mDoc != NULL) xmlFreeDoc(mDoc); };

    private:
        XMLRootNode(xmlDocPtr doc);

        mutable xmlDocPtr mDoc;
};

class XMLAttribute
{
    public:
        bool isEmpty() const {
            return (mAttr == NULL);
        }

        std::string name() const {
            return std::string((const char *)mAttr->name);
        }

        std::string value() const {
            return std::string((const char *)mAttr->children->content);
        }
        const XMLAttribute next() const {
            return XMLAttribute(mAttr->next);
        }

        friend const XMLAttribute XMLNode::getAttribute(const char *name) const;

    private:
        XMLAttribute(xmlAttrPtr attr): mAttr(attr) {};
        xmlAttrPtr mAttr;
};

#endif
