/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

#include "musicbrainz4/HTTPFetch.h"

#include "ne_session.h"
#include "ne_string.h"
#include "ne_request.h"

#include "config.h"

class MusicBrainz4::CHTTPFetchPrivate
{
	public:
		std::string m_Host;
		int m_Port;
		std::vector<unsigned char> m_Data;
		int m_Result;
		int m_Status;
		std::string m_ErrorMessage;
};

MusicBrainz4::CHTTPFetch::CHTTPFetch(const std::string& Host, int Port)
:	m_d(new CHTTPFetchPrivate)
{
	m_d->m_Host=Host;
	m_d->m_Port=Port;
}

MusicBrainz4::CHTTPFetch::~CHTTPFetch()
{
	delete m_d;
}

int MusicBrainz4::CHTTPFetch::Fetch(const std::string& URL)
{
	int Ret=0;

	m_d->m_Data.clear();

	ne_sock_init();

	ne_session *sess=ne_session_create("http", m_d->m_Host.c_str(), m_d->m_Port);
	if (sess)
	{
		ne_set_useragent(sess, PACKAGE "/v" VERSION);

		ne_request *req = ne_request_create(sess, "GET", URL.c_str());
		ne_add_response_body_reader(req, ne_accept_2xx, httpResponseReader, &m_d->m_Data);

		m_d->m_Result = ne_request_dispatch(req);
		m_d->m_Status = ne_get_status(req)->code;

		Ret=m_d->m_Data.size();

		ne_request_destroy(req);

		m_d->m_ErrorMessage = ne_get_error(sess);

		ne_session_destroy(sess);
	}

	ne_sock_exit();

	return Ret;
}

int MusicBrainz4::CHTTPFetch::httpResponseReader(void *userdata, const char *buf, size_t len)
{
	std::vector<unsigned char> *buffer = reinterpret_cast<std::vector<unsigned char> *>(userdata);

	buffer->insert(buffer->end(),buf,buf+len);

	return 0;
}

std::vector<unsigned char> MusicBrainz4::CHTTPFetch::Data() const
{
	return m_d->m_Data;
}

int MusicBrainz4::CHTTPFetch::Result() const
{
	return m_d->m_Result;
}

int MusicBrainz4::CHTTPFetch::Status() const
{
	return m_d->m_Status;
}

std::string MusicBrainz4::CHTTPFetch::ErrorMessage() const
{
	return m_d->m_ErrorMessage;
}
