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

#include "config.h"
#include "musicbrainz5/defines.h"

#include "musicbrainz5/xmlParser.h"

#include <cstring>

XMLNode XMLNode::emptyNode()
{
    return XMLNode(NULL);
}

XMLNode *XMLRootNode::parseFile(const std::string &filename, xmlErrorPtr results)
{
    xmlDocPtr doc;

    doc = xmlParseFile(filename.c_str());
    if ((doc == NULL) && (results != NULL)) {
        xmlCopyError(xmlGetLastError(), results);
    }

    return new XMLRootNode(doc);
}

XMLNode *XMLRootNode::parseString(std::string &xml, xmlErrorPtr results)
{
    xmlDocPtr doc;

    doc = xmlParseMemory(xml.c_str(), xml.length());
    if ((doc == NULL) && (results != NULL)) {
        xmlCopyError(xmlGetLastError(), results);
    }

    return new XMLRootNode(doc);
}

const char *XMLNode::getName() const
{
    return (char *)mNode->name;
}

const char *XMLNode::getText() const
{
    if (mNode->children == NULL)
        return NULL;
    if (!xmlNodeIsText(mNode->children))
        return NULL;

    return (char*)mNode->children->content;
}

xmlAttrPtr XMLNode::getAttributeRaw(const char *name) const
{
    xmlAttrPtr attr;

    for (attr = mNode->properties; attr != NULL; attr = attr->next)
        if (strcmp(name, (char *)attr->name) == 0)
            return attr;

    return NULL;
}

const XMLAttribute XMLNode::getAttribute(const char *name) const
{
    xmlAttrPtr attr;

    if (name == NULL)
        return XMLAttribute(mNode->properties);

    attr = this->getAttributeRaw(name);
    if (attr != NULL)
        return XMLAttribute(attr);

    return XMLAttribute(NULL);
}

bool XMLNode::isAttributeSet(const char *name) const
{
    return (this->getAttributeRaw(name) != NULL);
}

XMLRootNode::XMLRootNode(xmlDocPtr doc): XMLNode(xmlDocGetRootElement(doc)),
                                         mDoc(doc)
{
}

static xmlNodePtr skipTextNodes(xmlNodePtr node)
{
    xmlNodePtr it = node;

    while ((it != NULL) && xmlNodeIsText(it))
        it = it->next;

    return it;
}

XMLNode XMLNode::next() const
{
    return XMLNode(skipTextNodes(mNode->next));
}

XMLNode XMLNode::getChildNode(const char *name) const
{
    xmlNodePtr it;
    if (name == NULL)
        return XMLNode(skipTextNodes(mNode->children));

    for (it = mNode->children; it != NULL; it = it->next) {
        if (xmlNodeIsText(it))
            continue;
        if (strcmp(name, (char *)it->name) == 0)
            return XMLNode(it);
    }

    return emptyNode();
}

bool XMLNode::isEmpty() const
{
    return mNode == NULL;
}


