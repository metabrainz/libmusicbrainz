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

struct _xmlNode;
typedef _xmlNode* xmlNodePtr;

struct _xmlDoc;
typedef _xmlDoc* xmlDocPtr;

struct _xmlAttr;
typedef _xmlAttr* xmlAttrPtr;

struct XMLResults
{
    std::string message;
    int line;
    int code;

    XMLResults();
};

const int eXMLErrorNone = 0;

class XMLAttribute;
class XMLNode
{
    public:
        static XMLNode emptyNode();
        bool isEmpty() const;

        virtual ~XMLNode();

        const XMLAttribute getAttribute(const char *name = NULL) const;
        bool isAttributeSet(const char *name) const;

        XMLNode getChildNode(const char *name = NULL) const;
        XMLNode next() const;
        const char *getName() const;
        const char *getText() const;

        bool operator ==(const XMLNode &rhs) const;

    protected:
        XMLNode(xmlNodePtr node);

        xmlNodePtr mNode;

    private:
        xmlAttrPtr getAttributeRaw(const char *name) const;
};

bool operator !=(const XMLNode &lhs, const XMLNode &rhs);

class XMLRootNode: public XMLNode
{
    public:
        static XMLNode* parseString(const std::string &xml, XMLResults *results);
        static XMLNode* parseFile(const std::string &filename, XMLResults *results);

        virtual ~XMLRootNode();

    private:
        XMLRootNode(xmlDocPtr doc);

        xmlDocPtr mDoc;
};

class XMLAttribute
{
    public:
        bool isEmpty() const;
        std::string name() const;
        std::string value() const;
        const XMLAttribute next() const;

        friend const XMLAttribute XMLNode::getAttribute(const char *name) const;

    private:
        XMLAttribute(xmlAttrPtr attr);
        xmlAttrPtr mAttr;
};

#endif
