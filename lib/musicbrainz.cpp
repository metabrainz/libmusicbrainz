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
#include <assert.h>
#ifdef WIN32
#include <winsock.h>
#include "config_win32.h"
#endif
#include "musicbrainz.h"
#include "http.h"
#include "errors.h"
#include "diskid.h"
#include "xql.h"

extern "C"
{
   #include "sha1.h"
   #include "base64.h"
   #include "bitcollider.h"
}

const char *scriptUrl = "/cgi-bin/rquery.pl";
const char *localCDInfo = "@CDINFO@";
const char *localTOCInfo = "@LOCALCDINFO@";
const char *localAssociateCD = "@CDINFOASSOCIATECD@";
const char *defaultServer = "www.musicbrainz.org";
const short defaultPort = 80;
const char *rdfUTF8Encoding = "<?xml version=\"1.0\"?>\n";
const char *rdfISOEncoding = 
    "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n";
const char *rdfHeader = 
    "<rdf:RDF xmlns:rdf = \"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
    "         xmlns:DC = \"http://purl.org/DC#\"\n"
    "         xmlns:DCQ = \"http://purl.org/dc/qualifiers/1.0/\"\n"
    "         xmlns:MM = \"http://musicbrainz.org/MM#\"\n"
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
    m_proxy = "";
    m_xmlIndex = -1;
    m_numItems = 0;
    for(int i = 0; i < 50; i++)
       m_indexes.push_back(0);
    m_selectQuery = string(MB_SelectTopLevel);
    m_useUTF8 = true;
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

#ifdef WIN32
void MusicBrainz::WSAInit(void)
{
    WSADATA sGawdIHateMicrosoft;
    WSAStartup(0x0002,  &sGawdIHateMicrosoft);
}

void MusicBrainz::WSAStop(void)
{
    WSACleanup();
}
#endif

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
    url += string("/cdi/submit.html") + args;

    return true;
}

static const char* protocol = "file://";
static Error URLToFilePath(const char* url, char* path, uint32* length)
{
    Error result = kError_InvalidParam;

    assert(path);
    assert(url);
    assert(length);

    if(path && url && length && !strncasecmp(url, protocol, strlen(protocol)))
    {
        result = kError_BufferTooSmall;

        if(*length >= strlen(url) - strlen(protocol) + 1)
        {
            strcpy(path, url + strlen(protocol));
#ifdef WIN32
            if(strlen(path) > 1 && path[1] == '|')
            {
                path[1] = ':';
            }

            for(int32 index = strlen(path) - 1; index >=0; index--)
            {
                if(path[index] == '/')
                    path[index] = '\\';
            }
#endif
            result = kError_NoErr;
        }

        *length = strlen(url) - strlen(protocol) + 1;
    }

    return result;
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
        xml = (m_useUTF8 ? string(rdfUTF8Encoding) : string(rdfISOEncoding)) +
              string(rdfHeader) + 
              xml + 
              string("<MQ:Version>") + 
              string(MM_VERSION) + 
              string("</MQ:Version>\n") +
              string(rdfFooter);

        m_xql = new XQL(m_useUTF8);
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
    xml = (m_useUTF8 ? string(rdfUTF8Encoding) : string(rdfISOEncoding)) +
          string(rdfHeader) + 
          xml + 
          string("<MQ:Version>") + 
          string(MM_VERSION) + 
          string("</MQ:Version>\n") +
          string(rdfFooter);

    //printf("query: %s\n\n", xml.c_str());

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
    //printf("response: %s\n\n", retXml.c_str());

    numObjs = SplitResponse(retXml);
    if (numObjs == 0)
    { 
        m_error = string("Server response did not contain any XML objects");
        return false;
    }

    m_xql = new XQL(m_useUTF8);
    m_xmlIndex = 0;
    ret = m_xql->ParseString(m_xmlList[0]);
    if (IsError(ret))
    {
        string err;

        //printf("ret: [%s]\n", m_xmlList[0].c_str());

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
        m_xql = new XQL(m_useUTF8);
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

    return true;
}

bool MusicBrainz::SetResultRDF(string &rdf)
{
    int ret;

    if (m_xql)
       delete m_xql;

    m_xql = new XQL(m_useUTF8);
    ret = m_xql->ParseString(rdf);
    if (!IsError(ret))
    {
        m_xmlList.clear();
        m_xmlIndex = 0;
        m_xmlList[m_xmlIndex] = rdf;
        return true;
    }
    return false;
}

int MusicBrainz::GetNumXMLResults(void)
{
    return m_xmlList.size();
}

bool MusicBrainz::SelectXMLResult(int index)
{
    Error ret;

    if ((unsigned int)index > m_xmlList.size() - 1)
        return false;

    delete m_xql;
    m_xql = new XQL(m_useUTF8);
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

const string MusicBrainz::EscapeArg(const string &arg)
{
    string            text;
    string::size_type pos;

    text = arg;

    pos = text.find("&", 0);
    for(;;)
    {
       pos = text.find("&", pos);
       if (pos != string::npos)
           text.replace(pos, 1, string("&amp;"));
       else
           break;
       pos++;
    }

    pos = text.find("<", 0);
    for(;;)
    {
       pos = text.find("<", pos);
       if (pos != string::npos)
           text.replace(pos, 1, string("&lt;"));
       else
           break;
    }
    pos = text.find(">", 0);
    for(;;)
    {
       pos = text.find(">", pos);
       if (pos != string::npos)
           text.replace(pos, 1, string("&gt;"));
       else
           break;
    }

    return text;
}

void MusicBrainz::SubstituteArgs(string &xml, vector<string> *args)
{
    vector<string>::iterator i;
    string::size_type        pos;
    char                     replace[100];
    int                      j;
    string                   arg;

    if (args == NULL)
       return;

    for(i = args->begin(), j = 1; i != args->end(); i++, j++)
    {
        arg = EscapeArg(*i);
        sprintf(replace, "@%d@", j); 
        pos = xml.find(string(replace), 0);
        if (pos != string::npos)
        {
            xml.replace(pos, strlen(replace), arg);
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
       case kError_InvalidURL:
          m_error = string("Proxy or server URL is invalid.");
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

bool MusicBrainz::CalculateBitprint(const string &fileName, BitprintInfo *info) 
{
    BitcolliderSubmission *sub;

    sub = create_submission();
    if (sub == NULL)
       return false;

    if (!analyze_file(sub, fileName.c_str()))
       return false;

    strncpy(info->filename, fileName.c_str(), 255);
    strncpy(info->bitprint, get_attribute(sub, "bitprint"), MB_BITPRINTSIZE);
    strncpy(info->first20, 
            get_attribute(sub, "tag.file.first20"), MB_FIRST20SIZE);
    strncpy(info->audioSha1, 
            get_attribute(sub, "tag.mp3.audio_sha1"), MB_SHA1SIZE);
    info->length = atoi(get_attribute(sub, "tag.file.length"));
    info->duration = atoi(get_attribute(sub, "tag.mp3.duration"));
    info->samplerate = atoi(get_attribute(sub, "tag.mp3.samplerate"));
    info->bitrate = atoi(get_attribute(sub, "tag.mp3.bitrate"));
    info->stereo = strcmp(get_attribute(sub, "tag.mp3.stereo"), "y") == 0;
    if (get_attribute(sub, "tag.mp3.vbr"))
       info->vbr = strcmp(get_attribute(sub, "tag.mp3.vbr"), "y") == 0;
    else
       info->vbr = 0;

    delete_submission(sub);

    return true;
}
