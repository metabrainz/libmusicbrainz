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
#include <stdio.h>
#include "musicbrainz.h"
#include "http.h"
#include "errors.h"
#include "diskid.h"
#include "xql.h"

const char *scriptUrl = "/cgi-bin/rquery.pl";
const char *localCDInfo = "@CDINFO@";
const char *localTOCInfo = "@LOCALCDINFO@";
const char *localAssociateCD = "@CDINFOASSOCIATECD@";
const char *defaultServer = "www.musicbrainz.org";
const short defaultPort = 80;
const char *rdfHeader = 
    "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n"
    "<rdf:RDF xmlns = \"http://w3.org/TR/1999/PR-rdf-syntax-19990105#\"\n"
    "         xmlns:DC = \"http://purl.org/DC#\"\n"
    "         xmlns:MM = \"http://musicbrainz.org/MM#\">\n"
    "         xmlns:MQ = \"http://musicbrainz.org/MQ#\">\n\n"
    "<rdf:Description>\n";

const char *rdfFooter = 
    "</rdf:Description>\n" 
    "</rdf:RDF>\n";

#define DB printf("%s:%d\n",  __FILE__, __LINE__);

MusicBrainz::MusicBrainz(void)
{
    m_xql = NULL;
    m_server = string(defaultServer);
    m_serverPort = defaultPort;
    m_xmlIndex = -1;
    m_numItems = 0;
    m_downmixBuffer = NULL;
    m_storeBuffer = NULL;
    for(int i = 0; i < 50; i++)
       m_indexes.push_back(0);
}

MusicBrainz::~MusicBrainz(void)
{
    delete m_xql; 
}

bool MusicBrainz::SetServer(const string &serverAddr, short serverPort)
{
    m_server = serverAddr;
    m_serverPort = serverPort;

    return true;
}

bool MusicBrainz::SetProxy(const string &proxyAddr, short proxyPort)
{
    m_proxy = proxyAddr;
    m_proxyPort = proxyPort;

    return true;
}

bool MusicBrainz::SetDevice(const string &device)
{
    m_device = device;
    return true;
}

bool MusicBrainz::GetWebSubmitURL(string &url)
{
    DiskId id;
    string args;
    Error  ret;

    ret = id.GetWebSubmitURLArgs(m_device, args);
    if (ret != kError_NoErr)
        return false;

    url = string("http://") + string(m_server);
    if (m_serverPort != defaultPort)
    {
       char port[10];

       sprintf(port, ":%d", m_serverPort);
       url += string(port);
    }
    url += string("/cgi-bin/cdi/submit.pl") + args;

    return true;
}

bool MusicBrainz::Query(const string &xmlObject, vector<string> *args)
{
    MBHttp   http;
    char   port[20];
    string xml = xmlObject, url, retXml, firstXml, secondXml, value;
    Error  ret;
    int    numObjs;

    if (xml == string(localCDInfo) ||
        xml == string(localAssociateCD))
    {
        DiskId id;

        ret = id.GenerateDiskIdQueryRDF(m_device, xml, 
                        xml == string(localAssociateCD));
        if (IsError(ret))
        {
            id.GetLastError(m_error);
            return false;
        }
    }
    if (xml == string(localTOCInfo))
    {
        DiskId id;

        ret = id.GenerateDiskIdQueryRDF(m_device, xml, 0);
        if (IsError(ret))
        {
            id.GetLastError(m_error);
            return false;
        }
        xml = string(rdfHeader) + xml + string(rdfFooter);

        m_xql = new XQL();
        ret = m_xql->ParseString(xml);
        if (IsError(ret))
        {
            m_error = string("Internal error.");
            return false;
        }
        m_xmlList.clear();
        m_xmlList.push_back(xml);
        m_xmlIndex = 0;
        return true;
    }

    SubstituteArgs(xml, args);
    xml = string(rdfHeader) + xml + string(rdfFooter);

    //printf("output query: %s\n\n", xml.c_str());

    if (m_proxy.length() > 0)
    {
       sprintf(port, ":%d", m_proxyPort);   
       http.SetProxyURL(string("http://") + m_proxy + string(port));
    }
    sprintf(port, ":%d", m_serverPort);   
    url = string("http://") + m_server + string(port) + string(scriptUrl);
    ret = http.DownloadToString(url, xml, retXml); 
    if (IsError(ret))
    { 
        SetError(ret);
        return false;
    }

    numObjs = SplitResponse(retXml);
    if (numObjs == 0)
    { 
        m_error = string("Server response did not contain any XML objects");
        return false;
    }

    m_xql = new XQL();
    ret = m_xql->ParseString(m_xmlList[0]);
    if (IsError(ret))
    {
        string err;

        printf("ret: [%s]\n", m_xmlList[0].c_str());

        m_xql->GetErrorString(err);
        m_error = string("The server sent an invalid response. (") +
                  err + string(")");
        return false;
    }

    value = m_xql->Query(string("/rdf:RDF/rdf:Description/MQ:Error"));
    if (value.length() > 0)
    {
        m_error = value;
        return false;
    }

    value = m_xql->Query(string("/rdf:RDF/rdf:Description/MQ:Status"));
    if (value.length() == 0)
    {    
        m_error = string("Could not determine the result of the query");
        return false;
    }
    if (value != string("OK") && value != string("Fuzzy"))
    {    
        m_error = value;
        return false;
    }
    value = m_xql->Query(string("/rdf:RDF/rdf:Description/MQ:Status/@items"));
    if (value.length() == 0)
    {    
        m_error = string("Could not determine the number of items returned");
        return false;
    }
    m_numItems = atoi(value.c_str());

    if (numObjs > 1)
    {
        delete m_xql;
        m_xql = new XQL();
        xml = m_xmlList[1];
        ret = m_xql->ParseString(xml);
        if (IsError(ret))
        {
            m_error = string("The server sent an invalid response");
            delete m_xql;
            m_xql = NULL;
            return false;
        }
        m_xmlIndex = 1;
    }
    else
        m_xmlIndex = 0;

    return true;
}

void MusicBrainz::GetQueryError(string &ErrorText)
{
    ErrorText = m_error;
}

int MusicBrainz::GetNumItems(void)
{
    return m_numItems;
}

const string &MusicBrainz::Data(const string &resultName, int Index)
{
    string query;

    query = m_selectQuery + string("/") + resultName;
    //printf("Query: '%s'\n", query.c_str());
    if (!m_xql)
    {
       m_error = string("The server returned no valid data");
       return m_empty;
    }
    return m_xql->Query(query);
}

int MusicBrainz::DataInt(const string &resultName, int Index)
{
    string query;

    query = m_selectQuery + string("/") + resultName;
    //printf("Query: '%s'\n", query.c_str());
    if (!m_xql)
    {
       m_error = string("The server returned no valid data");
       return 0;
    }
    return atoi(m_xql->Query(query).c_str());
}

bool MusicBrainz::GetResultData(const string &resultName, int Index, string &data)
{
    string query;

    if (!m_xql)
    {
       m_error = string("The server returned no valid data");
       return false;
    }

    query = m_selectQuery + string("/") + resultName;
    data = m_xql->Query(query);
    if (data.length() > 0)
        return true;

    m_error = "No data was returned.";
    return false;
}

bool MusicBrainz::DoesResultExist(const string &resultName, int Index)
{
    string data;
    string query;

    if (!m_xql)
       return false;

    query = m_selectQuery + string("/") + resultName;
    data = m_xql->Query(query);
    return data.length() > 0;
}

bool MusicBrainz::Select(const string &selectQueryArg)
{
    string::size_type pos;
    string            newQuery, index, selectQuery;
    int               i, newIndex = 0;
    char              temp[20];

    selectQuery = selectQueryArg;

    for(i = 0;; i++)
    {
       pos = selectQuery.find("[", 0);
       if (pos == string::npos)
       {
           newQuery += selectQuery;
           break;
       }
       newQuery += selectQuery.substr(0, pos);
       selectQuery.erase(0, pos);

       pos = selectQuery.find("]", 0);
       if (pos == string::npos)
           return false;

       index = selectQuery.substr(0, pos);
       selectQuery.erase(0, pos);

       if (index.length() == 1)
           newIndex = m_indexes[i];
       else
       {
           if (index[1] == '+')
              newIndex = m_indexes[i] + atoi(index.c_str() + 2);
           else
           if (index[1] == '-')
              newIndex = m_indexes[i] - atoi(index.c_str() + 2);
           else
              newIndex = atoi(index.c_str() + 1);

           m_indexes[i] = newIndex;
       }
       sprintf(temp, "[%d", newIndex);
       newQuery += string(temp);
    }
    m_selectQuery = newQuery;

    return true;
}

bool MusicBrainz::GetResultRDF(string &RDFObject)
{
    if (m_xmlList[m_xmlIndex].length() == 0)
       return false;

    RDFObject = m_xmlList[m_xmlIndex];

    return false;
}

int MusicBrainz::GetNumXMLResults(void)
{
    return m_xmlList.size();
}

bool MusicBrainz::SelectXMLResult(int index)
{
    Error ret;

    if (index > m_xmlList.size() - 1)
        return false;

    delete m_xql;
    m_xql = new XQL();
    ret = m_xql->ParseString(m_xmlList[index]);
    if (IsError(ret))
    {
        m_error = string("The server sent an invalid xml response");
        delete m_xql;
        m_xql = NULL;
        return false;
    }
    m_xmlIndex = index;

    return true;
}

void MusicBrainz::SubstituteArgs(string &xml, vector<string> *args)
{
    vector<string>::iterator i;
    string::size_type        pos;
    char                     replace[100];
    int                      j;

    if (args == NULL)
       return;

    for(i = args->begin(), j = 1; i != args->end(); i++, j++)
    {
        sprintf(replace, "@%d@", j); 
        pos = xml.find(string(replace), 0);
        if (pos != string::npos)
        {
            xml.replace(pos, strlen(replace), *i);
        }
    }
    for(;; j++)
    {
        sprintf(replace, "@%d@", j); 
        pos = xml.find(string(replace), 0);
        if (pos != string::npos)
        {
            xml.replace(pos, strlen(replace), "");
        }
        else
            break;
    }
}

void MusicBrainz::SetError(Error ret)
{
    switch(ret)
    {
       case kError_CantFindHost:
          m_error = string("Cannot find server: ") + m_server;
          break;
       case kError_ConnectFailed:
          m_error = string("Cannot connect to server: ") + m_server;
          break;
       case kError_IOError:
          m_error = string("Cannot send/receive to/from server.");
          break;
       case kError_WriteFile:
          m_error = string("Cannot write to disk. Disk full?");
          break;
       case kError_HTTPFileNotFound:
          m_error = string("Cannot find musicbrainz pages on server. Check "
                           "your server name and port settings.");
          break;
       case kError_UnknownServerError:
          m_error = string("The server encountered an error processing this "
                           "query.");
          break;
       default:
          char num[10];
          sprintf(num, "%d", ret);
          m_error = string("Internal error: ") + string(num);
          break;
    }
}

int MusicBrainz::SplitResponse(const string &inXML)
{
    string            xml = inXML, temp;
    string::size_type pos1, pos2;
    int               i;

    m_xmlList.clear();

    for(i = 0;; i++)
    {
        pos1 = xml.find("<?xml", 0);
        if (pos1 == string::npos)
           return 0;

        pos2 = xml.find("<?xml", pos1 + 1);
        if (pos2 == string::npos)
        {
           m_xmlList.push_back(xml);
           return i + 1;
        }
    
        temp = xml.substr(pos1, pos2 - pos1); 
        m_xmlList.push_back(temp);

        xml.erase(0, pos2); 
    }

    return 0;
}

#if 0

#include "queries.h"

int main(void)
{
    MusicBrainz o;
    vector<string> args;
    string         error, data, url;
    bool           ret;

    o.SetServer(string("localhost"), 80);
    ret = o.Query(string(localCDInfo), &args);
    if (!ret)
    {
         o.GetQueryError(error);
         printf("Query failed: %s\n", error.c_str());
    
         ret = o.GetWebSubmitURL(url);
         if (ret)
             printf("submit url: %s\n", url.c_str());

         return 0;
    }

    o.GetResultRDF(data);
    printf("XML: '%s'\n", data.c_str());

    ret = o.GetResultData(string(GetTitle), 0, data);
    if (!ret)
    {
         o.GetQueryError(error);
         printf("Get result failed: %s\n", error.c_str());
         return 0;
    }
    printf("Title: '%s'\n", data.c_str());
    
    ret = o.GetResultData(string(GetArtist), 0, data);
    if (!ret)
    {
         o.GetQueryError(error);
         printf("Get result failed: %s\n", error.c_str());
         return 0;
    }
    printf("Artist: '%s'\n", data.c_str());

    ret = o.DoesResultExist(string(GetFuzzyMatchAlbumId));
    if (ret)
    {
        printf("Fuzzy match!\n");

        o.GetResultData(string(GetFuzzyMatchAlbumId), 0, data);
        args.clear();
        args.push_back(data);
        ret = o.Query(string(AssociateCD), &args);
        if (!ret)
        {
             o.GetQueryError(error);
             printf("Associate Query failed: %s\n", error.c_str());
             return 0;
        }
        printf("Associate query ok\n");
    }


    return 0;
}
#endif
