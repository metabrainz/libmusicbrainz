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

#include <string>
#include <vector>

#include "errors.h"
#include "queries.h"
#include "bitprint.h"
#include "rdfextract.h"

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

       EXPORT bool     SetServer        (const string &serverAddr, 
                                         short serverPort);
       EXPORT bool     SetProxy         (const string &proxyAddr, 
                                         short proxyPort);

       EXPORT bool     SetDevice        (const string &device);
       EXPORT bool     SetDepth         (int depth);
       EXPORT void     UseUTF8          (bool bUse) { m_useUTF8 = bUse; };

       EXPORT bool     Query            (const string &rdfObject, 
                                         vector<string> *args = NULL);
       EXPORT void     GetQueryError    (string &ErrorText);
       EXPORT bool     GetWebSubmitURL  (string &url);
  
       EXPORT bool     Select           (const string &selectQuery,
                                         int           ordinal = 0);
       EXPORT bool     Select           (const string &selectQuery,
                                         list<int>    *ordinalList);

       EXPORT bool     DoesResultExist  (const string &resultName, 
                                         int Index = 0);
       EXPORT bool     GetResultData    (const string &resultName, 
                                         int Index, 
                                         string &data);
       EXPORT const string &Data        (const string &resultName, 
                                         int Index = 0);
       EXPORT int      DataInt          (const string &resultName, 
                                         int Index = 0);

       EXPORT bool     GetResultRDF     (string &RDFObject);
       EXPORT bool     SetResultRDF     (string &RDFObject);

       EXPORT void     GetIDFromURL     (const string &url, string &id);
       EXPORT bool     CalculateBitprint(const string &fileName,
                                         BitprintInfo *info);
#ifdef WIN32
       EXPORT void     WSAInit          (void);
       EXPORT void     WSAStop          (void);
#endif

       EXPORT void     SetDebug         (bool debug);

    private:

       const string EscapeArg(const string &xml);
       void         SubstituteArgs(string &xml, vector<string> *args);
       void         SetError(Error ret);
       void         MakeRDFQuery(string &rdf);

       vector<string>  m_contextHistory;
       string          m_error, m_empty; 
       string          m_server, m_proxy;
       short           m_serverPort, m_proxyPort;
       string          m_device, m_currentURI, m_baseURI, m_response; 
       RDFExtract     *m_rdf;
       bool            m_useUTF8, m_debug;
       int             m_depth;
};

#endif
