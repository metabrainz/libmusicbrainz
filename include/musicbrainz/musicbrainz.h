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
#include <list>

#include "encoder.h"
#include "errors.h"
#include "queries.h"

using namespace std;

class RDFExtract;

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

       EXPORT void     GetVersion       (int &major, int &minor, int &rev);
       EXPORT bool     SetServer        (const string &serverAddr, 
                                         short serverPort);
       EXPORT bool     SetProxy         (const string &proxyAddr, 
                                         short proxyPort);

       /** Sets the username and password for proxy authentication.
        * If a proxy server is needed and http authentication is required,
	* use this method to set the username and password for authorization.
	* Both Basic and MD5 hash authentication is supported.
	* @param proxyUsername - the username
	* @param proxyPassword - the password
	*/
       EXPORT bool     SetProxyCreds    (const string &proxyUsername, 
                                         const string &proxyPassword);
       EXPORT bool     Authenticate     (const string &userName,
                                         const string &password);

       EXPORT bool     SetDevice        (const string &device);
       EXPORT bool     SetDepth         (int depth);
       EXPORT bool     SetMaxItems      (int maxItems);

       /** Specifies which encoding to convert the data to.
        * This method is used to specify the character set encoding for
	* converting the metadata information. The default character set
	* that Musicbrainz converts to is ISO-8859-1.  To change it, call
	* this method with the desired character set name.  To perform
	* no character set conversions, just specify "UTF-8" as the character set.
	* @param encoding - The character set name.
	* @returns True if the character set is supported and will be used, false if
	* an error occurred.  Call GetQueryError() to get the ICU error code name.
	*/
       EXPORT bool     UseEncoding      (const char *encoding);

       /** Returns the current character set encoding that is being used for
        * displaying the metadata information.
        * @param encoding - The pointer that will have the character set name.
	* @returns True if the character set name was returned successfully, false if an error occurred.
	*/
       EXPORT bool   GetCurrentEncoding (string &encoding);

       /** Retrieves the list of character set encodings that are available to the
        * system.  This list contains only the character set names.
	* @param encodings - the string vector that will be filled with the character set names.
	* @returns True if the list was generated successfully, false if an error occurred.
	*/
       EXPORT bool     GetAvailableEncodings(vector<string> &encodings);

       /** Returns the number of available character set encodings
        * @returns the number of available character set encodings
        */
       EXPORT int      GetNumAvailableEncodings();

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
       EXPORT string   Data             (const string &resultName, 
                                         int Index = 0);
       EXPORT int      DataInt          (const string &resultName, 
                                         int Index = 0);

       EXPORT bool     GetResultRDF     (string &RDFObject);
       EXPORT bool     SetResultRDF     (string &RDFObject);

       EXPORT void     GetIDFromURL     (const string &url, string &id);
       EXPORT void     GetFragmentFromURL(const string &url, string &fragment);
       EXPORT int      GetOrdinalFromList(const string &resultList, const string &URI);

       /* These functions are helper functions that may be useful for clients */
       EXPORT bool     GetMP3Info       (const string &fileName, 
                                         int          &duration,
                                         int          &bitrate,
                                         int          &stereo,
                                         int          &samplerate);

#ifdef WIN32
       EXPORT void     WSAInit          (void);
       EXPORT void     WSAStop          (void);
#endif

       EXPORT void     SetDebug         (bool debug);

    private:

       const string EscapeArg(const string &xml);
       bool         SubstituteArgs(string &xml, vector<string> *args);
       void         ReplaceArg(string &rdf, const string &from, 
                               const string &to);
       void         ReplaceIntArg(string &rdf, const string &from, int to);
       void         SetError(Error ret);
       void         MakeRDFQuery(string &rdf);

       vector<string>  m_contextHistory;
       string          m_error, m_empty; 
       string          m_server, m_proxy, m_proxyUid, m_proxyPwd;
       string          m_sessionKey, m_sessionId, m_versionString;
       Encoder         m_encoder;          
       short           m_serverPort, m_proxyPort;
       string          m_device, m_currentURI, m_baseURI, m_response; 
       RDFExtract     *m_rdf;
       bool            m_debug;
       int             m_depth, m_maxItems;
};

#endif
