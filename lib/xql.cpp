/* --------------------------------------------------------------------------

   MusicBrainz -- The Internet music metadatabase

   Copyright (C) 2000 Robert Kaye
   
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
#include "xql.h"

XQL::XQL(bool useUTF8) :
      MBParse(useUTF8)
{
}

XQL::~XQL(void)
{
}

Error XQL::BeginElement(const string &oElement, AttrMap &oAttrMap)
{
    map<string, string>::iterator i;
    int                           j;
    string                        oKey;
    char                          szIndex[100];

    m_oPath += string("/") + oElement;  

    if (m_oNodeHist.find(m_oPath) == m_oNodeHist.end())
        m_oNodeHist[m_oPath] = 0;
    else
    {
        j = m_oNodeHist[m_oPath] + 1;
        m_oNodeHist[m_oPath] = j;
        sprintf(szIndex, "[%d]", j);
        m_oPath += string(szIndex);
    }

    for(i = oAttrMap.begin(); i != oAttrMap.end(); i++)
    {
        oKey = m_oPath + string("/@") + (*i).first; 
        m_oList[oKey] = (*i).second;
        //printf("parse: %s ==> '%s'\n", oKey.c_str(), (*i).second.c_str());
    }

    return kError_NoErr;
}

Error XQL::EndElement(const string &oElement)
{
    const char *pPtr;
    int         iOffset;  

    pPtr = strrchr(m_oPath.c_str(), '/');
    if (pPtr == NULL)
       return kError_NoErr;

    iOffset = pPtr - m_oPath.c_str();
    m_oPath.erase(iOffset, m_oPath.length() - iOffset); 

    return kError_NoErr;
}

Error XQL::PCData(const string &oData)
{
    //printf("parse: %s ==> '%s'\n", m_oPath.c_str(), oData.c_str());
    m_oList[m_oPath] += oData;

    return kError_NoErr;
}

const string &XQL::Query(const string &oKeyArg)
{
    string::size_type pos;
    string            oKey = oKeyArg;

    for(;;)
    {
        pos = oKey.find("[0]", 0);
        if (pos == string::npos)
           break;

        oKey.erase(pos, 3);
    }

    if (m_oList.find(oKey) == m_oList.end())
    {
        return m_oEmpty;
    }

    //printf("rq: '%s' => '%s'\n", oKeyArg.c_str(), m_oList[oKey].c_str()); 

    return m_oList[oKey];
}

#if 0
static char *query1 = "/TrackInfo/GeneralInfo/Title";
static char *query2 = "/TrackInfo/GeneralInfo/Artist/@ID";
static char *query3 = "/TrackInfo/ExtendedInfo/Lyrics/SyncLyrics/LyricEvent[]/Text";
static char *query4 = "/TrackInfo/ExtendedInfo/Lyrics/SyncLyrics/LyricEvent[]";

int main(void)
{
    XQL oList;
    string      oValue;
    Error       eRet;

    eRet = oList.ParseFile(string("tsample.xml"));
    if (eRet != kError_NoErr)
    {
        string oErr;

        oList.GetErrorString(oErr);
        printf("Parse error: %s\n", oErr.c_str()); 
        return 0;
    }
 
    printf("Query: %s ==> '%s'\n", query1, 
           oList.Query(string(query1), 0).c_str());

    printf("Query: %s ==> '%s'\n", query2, 
           oList.Query(string(query2), 0).c_str());

    printf("Query: %s ==> '%s'\n", query3, 
           oList.Query(string(query3), 2).c_str());

    printf("Query: %s ==> '%s'\n", query4, 
           oList.Query(string(query4), 3).c_str());

    return 0;
} 
#endif
