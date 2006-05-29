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
#include "utilspriv.h"

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

WebService::WebService(const std::string &host,
					   const int port,
					   const std::string &pathPrefix,
                       const std::string &username,
					   const std::string &password,
                       const std::string &realm)
	: host(host),
	  port(port),
	  pathPrefix(pathPrefix),
	  username(username),
	  password(password),
	  realm(realm)
{
}

string
WebService::get(const std::string &entity,
				const std::string &id,
				const IIncludes::IncludeList &include,
				const IFilter::ParameterList &filter,
				const std::string &version)
{
    MBHttp http;
    
    string url = "http://" + host;
    if (port != 80) 
		url += ":" + intToString(port);
    url += pathPrefix + "/" + version + "/" + entity + "/" + id;

    map<string, string> params;
    params["type"] = "xml";
    
	string inc;
	for (IIncludes::IncludeList::const_iterator i = include.begin(); i != include.end(); i++) {
		if (!inc.empty())
			inc += " ";
		inc += *i;
	}
	params["inc"] = inc;
	
	for (IFilter::ParameterList::const_iterator i = filter.begin(); i != filter.end(); i++) {
		params[i->first] = i->second;	
	}

	bool first = true;	
    for (map<string, string>::iterator i = params.begin(); i != params.end(); i++) {
        string name = i->first;
        string value = i->second;
		if (value.empty())
			continue;
		MBHttp::EncodeURI(value);
        url += (first ? "?" : "&") + name + "=" + value;
		first = false;
    }

#ifdef DEBUG    
    cout << endl << "Request:" << endl << url << endl;
#endif
    
    string response;
    string data = "";
    
    Error error = http.DownloadToString(url, data, response);
    
#ifdef DEBUG    
    cout << endl << "Response:" << endl << response << endl;
#endif
    
    return response; 
}

void
WebService::post(const std::string &entity,
			     const std::string &id,
				 const std::string &data,
				 const std::string &version)
{
}

