/* --------------------------------------------------------------------------

   MusicBrainz -- The Internet music metadatabase

   Copyright (C) 2000 Robert Kaye
   Portions Copyright (C) 2000 David Gray
   
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
#ifndef _MUSICBRAINZ_H_
#define _MUSICBRAINZ_H_

#include "errors.h"
#include "queries.h"

#include <string>
#include <vector>

using namespace std;

class XQL;

#if defined(_WIN32) && defined(MUSICBRAINZ_EXPORTS)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

class MusicBrainz
{
    public:

       EXPORT          MusicBrainz(void);
       EXPORT virtual ~MusicBrainz(void);

       EXPORT bool     SetServer      (const string &serverAddr, 
                                       short serverPort);
       EXPORT bool     SetProxy       (const string &proxyAddr, 
                                       short proxyPort);
       EXPORT bool     SetDevice      (const string &device);
       EXPORT void     UseUTF8        (bool bUse) { m_useUTF8 = bUse; };

       EXPORT bool     Query          (const string &xmlObject, 
                                       vector<string> *args = NULL);
       EXPORT void     GetQueryError  (string &ErrorText);
       EXPORT int      GetNumItems    (void);
       EXPORT bool     GetWebSubmitURL(string &url);

       EXPORT bool     Select         (const string &selectQuery);
       EXPORT bool     DoesResultExist(const string &resultName, 
                                       int Index = -1);
       EXPORT bool     GetResultData  (const string &resultName, int Index, 
                                string &data);
       EXPORT bool     GetResultRDF   (string &RDFObject);
       EXPORT bool     SetResultRDF   (string &RDFObject);

       EXPORT const string &Data      (const string &resultName, 
                                       int Index = -1);
       EXPORT int      DataInt        (const string &resultName, 
                                       int Index = -1);

    private:

       const string EscapeArg(const string &xml);
       void     SubstituteArgs(string &xml, vector<string> *args);
       void     SetError(Error ret);
       int      SplitResponse(const string &inputXml);

       int      GetNumXMLResults(void);
       bool     SelectXMLResult(int index);

       string          m_error, m_empty; 
       string          m_server, m_proxy;
       short           m_serverPort, m_proxyPort;
       string          m_device, m_selectQuery; 
       vector<string>  m_xmlList;
       int             m_xmlIndex, m_numItems;
       XQL            *m_xql;
       vector<int>     m_indexes;
       bool            m_useUTF8;
};

#endif
