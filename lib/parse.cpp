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
    string key, value;

    for(; *attr;)
    {
        if (((MBParse *)data)->UseUTF8())
        {
           key = string((char *)*(attr++));
           value = string((char *)*(attr++));
        }
        else
        {
           key = ConvertToISO((char *)*(attr++));
           value = ConvertToISO((char *)*(attr++));
        }
        oMap[key] = value;
    }

    ((MBParse *)data)->BeginElement(string(el), oMap);
}

void EndElement(void *data, const XML_Char *el)
{
    if (((MBParse *)data)->UseUTF8())
       ((MBParse *)data)->EndElement(string(el));
    else
       ((MBParse *)data)->EndElement(ConvertToISO((char *)el));
}

void PCData(void *data, const XML_Char *charData, int len)
{
    char *temp;

    temp = new char[len + 1];
    strncpy(temp, (char *)charData, len);
    temp[len] = 0;
    if (((MBParse *)data)->UseUTF8())
       ((MBParse *)data)->PCData(string(temp));
    else
       ((MBParse *)data)->PCData(ConvertToISO((char *)temp));
    delete temp;
}

MBParse::MBParse(bool useUTF8)
{
    m_useUTF8 = useUTF8;

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

const string ConvertToISO(const char *utf8)
{
   unsigned char *in;
   unsigned char *out, *end;
   string               ret;

   in = (unsigned char *)utf8;
   out = new unsigned char[strlen(utf8) + 1];
   end = in + strlen(utf8);
   for(;*in != 0x00 && in <= end; in++, out++)
   {
       if (*in < 0x80)
       {  /* lower 7-bits unchanged */
          *out = *in;
       }
       else
       if (*in > 0xC3)
       { /* discard anything above 0xFF */
          *out = '?';
       }
       else
       if (*in & 0xC0)
       { /* parse upper 7-bits */
          in++;
          if (in <= end)
            *out = 0;
          else
            *out = (*in) & 0x3F + 0x80;
       }
       else
       {
          *out = '?';  /* this should never happen */
       }
   }
   *out = 0x00; /* append null */

   ret = string((char *)out);

   delete out;

   return ret;
}
