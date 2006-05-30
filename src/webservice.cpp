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
#include "utilspriv.h"

#include <ne_session.h>
#include <ne_request.h>
#include <ne_utils.h>
#include <ne_uri.h> 

using namespace std;
using namespace MusicBrainz;

void
WebService::init()
{
	ne_sock_init(); 
}

void
WebService::cleanup()
{
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

int
WebService::httpResponseReader(void *userdata, const char *buf, size_t len)
{
	string *str = (string *)userdata;
	str->append(buf, len);
	return 0;
}

string
uriEscape(string uri)
{
	char *esc_uri_str = ne_path_escape(uri.c_str());
	string esc_uri = string((const char *)esc_uri_str);
	free(esc_uri_str);
	return esc_uri;
}

string
WebService::get(const std::string &entity,
				const std::string &id,
				const IIncludes::IncludeList &include,
				const IFilter::ParameterList &filter,
				const std::string &version)
{
	ne_session *sess;
	ne_request *req;
	
#ifdef DEBUG	
	cout << endl << "Connecting to http://" << host << ":" << port << endl;
#endif
	
	sess = ne_session_create("http", host.c_str(), port);
	if (!sess) 
		throw WebServiceError("ne_session_create() failed.");

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

	string uri = pathPrefix + "/" + version + "/" + entity + "/" + id;
	
	bool first = true;	
	for (map<string, string>::iterator i = params.begin(); i != params.end(); i++) {
		string name = i->first;
		string value = i->second;
		if (value.empty())
			continue;
		uri += (first ? "?" : "&") + name + "=" + uriEscape(value);
		first = false;
	}

#ifdef DEBUG	
	cout << "GET " << uri << endl;
#endif
	
	string response;
	
	req = ne_request_create(sess, "GET", uri.c_str());	
	ne_add_response_body_reader(req, ne_accept_2xx, httpResponseReader, &response);		
	ne_request_dispatch(req);
	int status = ne_get_status(req)->code;
	ne_request_destroy(req); 
	
#ifdef DEBUG	
	cout << "Status: " << status << endl;
	cout << "Response:" << endl << response << endl;
#endif
	
	ne_session_destroy(sess);

	return response; 
}

void
WebService::post(const std::string &entity,
				 const std::string &id,
				 const std::string &data,
				 const std::string &version)
{
}

