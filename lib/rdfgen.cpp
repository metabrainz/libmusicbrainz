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

   NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE

   This implementation of the RDF object generator is MINIMAL! It should
   be only used on very simple objects. Before this code gets adopted into
   more widespread use, it should be expanded to handle arbitarily complex
   rdf descriptions.

   NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE

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
#include "rdfgen.h"

RDFGenerator::RDFGenerator(void)
{
}

RDFGenerator::~RDFGenerator(void)
{
}

Error RDFGenerator::BeginElement(const string &oElement, AttrMap &oAttrMap)
{
    map<string, string>::iterator               i;
    map<pair<string, string>, string>::iterator k;
    int                           j;
    string                        oBasePath(m_oPath);
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
        printf("  parse: %s_@%s ==> '%s'\n", oBasePath.c_str(), 
                                          (*i).first.c_str(), 
                                          (*i).second.c_str());

        pair<string, string> oMapKey(oBasePath, string("@") + (*i).first); 
        k = m_oArgs.find(oMapKey);
        if (k != m_oArgs.end())
        {
            printf("replace: %s_%s ==> '%s'\n", 
                  (*k).first.first.c_str(),
                  (*k).first.second.c_str(),
                  (*k).second.c_str());
            oAttrMap[(*i).first] = (*k).second; 
        }
    }
    m_oOutput += string("<") + oElement.c_str();
    for(i = oAttrMap.begin(); i != oAttrMap.end(); i++)
    {
        m_oOutput += string(" ") + (*i).first.c_str() + string("=\"") +
                     (*i).second.c_str() + string("\"");
    }
    m_oOutput += string(">");

    printf("  Check: %s_%s\n", oBasePath.c_str(), oElement.c_str());
    pair<string, string> oMapKey(oBasePath, oElement);
    k = m_oArgs.find(oMapKey);
    if (k != m_oArgs.end())
    {
        m_oOutput += (*k).second;
    }

    return kError_NoErr;
}

Error RDFGenerator::EndElement(const string &oElement)
{
    map<string, string>::iterator i, k;
    char                          *pPtr;
    int                           iOffset;  

    m_oOutput += string("</") + oElement.c_str() + string(">");

    pPtr = strrchr(m_oPath.c_str(), '/');
    if (pPtr == NULL)
       return kError_NoErr;

    iOffset = pPtr - m_oPath.c_str();
    m_oPath.erase(iOffset, m_oPath.length() - iOffset); 

    return kError_NoErr;
}

Error RDFGenerator::PCData(const string &oData)
{
    //printf("parse: %s ==> '%s'\n", m_oPath.c_str(), oData.c_str());
    m_oOutput += oData;

    return kError_NoErr;
}

Error RDFGenerator::Select(const string &oSelect)
{
    m_oContext = oSelect;
    return kError_NoErr;
}

Error RDFGenerator::Insert(const string &oKey, const string &oValue)
{
    pair<string, string> oMapKey(m_oContext, oKey);;

    printf("    add: %s_%s\n", m_oContext.c_str(), oKey.c_str());
    m_oArgs[oMapKey] = oValue;
    return kError_NoErr;
}

Error RDFGenerator::Generate(const string        &oTemplate,
                            string              &oRDF)
{  
    Error err;

    m_oOutput = string("");
    err = ParseString(oTemplate);
    oRDF = string("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n");
    oRDF += m_oOutput;

    return err;
}

#if 0

const char *select1 = "/rdf:RDF/rdf:Description";
const char *select2 = "/rdf:RDF/rdf:Description/DC:Relation/rdf:Description";

const char *arg1 = "DC:Title";
const char *arg2 = "DC:Creator";
const char *arg3 = "@artistId";
const char *arg4 = "@albumId";

const char *value1 = "Shallow End";
const char *value2 = "Morcheeba";
const char *value3 = "MorcheebaID";
const char *value4 = "Fragments of Freedom";
const char *value5 = "MorcheebaAlbumID";

const char *cTemplate = 
"<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
"<rdf:RDF xmlns = \"http://w3.org/TR/1999/PR-rdf-syntax-19990105#\"\n"
"         xmlns:DC = \"http://purl.org/DC#\"\n"
"         xmlns:MM = \"http://musicbrainz.org/MM#\">\n\n"
"  <rdf:Description>\n"
"    <DC:Title></DC:Title>\n"
"    <DC:Creator></DC:Creator>\n"
"    <DC:Identifier artistId=\"\"/>\n"
"    <MM:TrackNum></MM:TrackNum>\n"
"    <DC:Relation type=\"\">\n"
"      <rdf:Description>\n"
"        <DC:Title></DC:Title>\n"
"        <DC:Identifier albumId=\"\"/>\n"
"      </rdf:Description>\n"
"    </DC:Relation>\n"
"  </rdf:Description>\n"
"</rdf:RDF>\n";

int main(void)
{
    RDFGenerator oList;
    string      oValue;
    Error       eRet;

    oList.Select(string(select1));
    oList.Insert(string(arg1), string(value1));
    oList.Insert(string(arg2), string(value2));
    oList.Insert(string(arg3), string(value3));
    oList.Select(string(select2));
    oList.Insert(string(arg1), string(value4));
    oList.Insert(string(arg4), string(value5));
    eRet = oList.Generate(string(cTemplate), oValue);
    if (eRet != kError_NoErr)
    {
        string oErr;

        oList.GetErrorString(oErr);
        printf("Generate error: %s\n", oErr.c_str()); 
        return 0;
    }
    printf("\n%s\n", oValue.c_str());
 
    return 0;
} 

#endif
