/*
 * MusicBrainz -- The Internet music metadatabase
 *
 * Copyright (C) 2006 Lukas Lalinsky
 *  
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
 
#include <string>
#include <map>
#include <iostream>
#include <string.h>
#ifdef WIN32
#include <winsock.h>
#endif
#include <musicbrainz3/webservice.h>
#include <musicbrainz3/artist.h>
#include "http/http.h"

using namespace std;
using namespace MusicBrainz;

void
WebService::init()
{
#ifdef WIN32
    WSADATA d;
    WSAStartup(0x0002,  &d);
#endif
}

void
WebService::cleanup()
{
#ifdef WIN32
    WSACleanup();
#endif
}

WebService::WebService(const std::string host, const int port, const std::string pathPrefix,
                       const std::string username, const std::string password,
                       const std::string realm)
{
    this->host = host;
    this->port = port;
    this->pathPrefix = pathPrefix;
    this->username = username;
    this->password = password;
    this->realm = realm;
}

string
WebService::get(string entity, string id, string version)
{
    MBHttp http;
    
    string url = "http://" + host;
    if (port != 80) {
        char temp[32];
        sprintf(temp, ":%d", port);
        url += temp; 
    }
    url += pathPrefix + "/" + version + "/" + entity + "/" + id;

    map<string, string> params;
    params["type"] = "xml";
    
    for (map<string, string>::iterator i = params.begin(); i != params.end(); i++) {
        string name = i->first;
        // FIXME: escape the value
        string value = i->second; 
        url += (i == params.begin() ? "?" : "&") + name + "=" + value;  
    }

#ifdef DEBUG    
    cout << "GET " << url << endl;
#endif
    
    string response;
    string data = "";
    
    Error error = http.DownloadToString(url, data, response);
    
#ifdef DEBUG    
    cout << "Response:" << endl << response << endl;
#endif
    
    return response; 
}

