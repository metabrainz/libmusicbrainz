/* --------------------------------------------------------------------------

   MusicBrainz -- The Internet music metadatabase

   Copyright (C) 2000 Emusic.com
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/
// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <stdio.h>
#include <map>
#include <assert.h>
#include "parse.h"

void BeginElement(void *data, const XML_Char *el, const XML_Char **attr)
{
    map<string, string> oMap;

    for(; *attr;)
        oMap[string((char *)*(attr++))] = string((char *)*(attr++));

    ((MBParse *)data)->BeginElement(string(el), oMap);
}

void EndElement(void *data, const XML_Char *el)
{
    ((MBParse *)data)->EndElement(string(el));
}

void PCData(void *data, const XML_Char *charData, int len)
{
    char *temp;

    temp = new char[len + 1];
    strncpy(temp, (char *)charData, len);
    temp[len] = 0;
    ((MBParse *)data)->PCData(string(temp));
    delete temp;
}

MBParse::MBParse(void)
{
    m_pParser = (XML_Parser *)XML_ParserCreate(NULL);
    XML_SetUserData(m_pParser, this);
    XML_SetElementHandler(m_pParser, ::BeginElement, ::EndElement);
    XML_SetCharacterDataHandler(m_pParser, ::PCData);
}

MBParse::~MBParse(void)
{
    XML_ParserFree(m_pParser);
}

Error MBParse::ParseFile(const string &oFile)
{
    assert(0); 
    return kError_NoErr;
}

Error MBParse::ParseString(const string &oXML)
{
    return XML_Parse(m_pParser, oXML.c_str(), oXML.length(), 1) ? 
           kError_NoErr : kError_ParseError;
}

void MBParse::GetErrorString(string &oError)
{
    oError = string(XML_ErrorString(XML_GetErrorCode(m_pParser)));
}

int MBParse::GetErrorLine(void)
{
    return XML_GetCurrentLineNumber(m_pParser);
}
