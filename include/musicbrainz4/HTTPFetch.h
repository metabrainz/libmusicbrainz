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

#ifndef _MUSICBRAINZ4_HTTP_FETCH_
#define _MUSICBRAINZ4_HTTP_FETCH_

#include <string>
#include <vector>

namespace MusicBrainz4
{
	class CHTTPFetchPrivate;
	
	class CHTTPFetch
	{
	public:
		CHTTPFetch(const std::string& Host, int Port=80);
		~CHTTPFetch();
	
		int Fetch(const std::string& URL);
		std::vector<unsigned char> Data() const;
		int Result() const;
		int Status() const;
		std::string ErrorMessage() const;
		
	private:
		CHTTPFetchPrivate * const m_d;
		
		static int httpResponseReader(void *userdata, const char *buf, size_t len);
	};
}

#endif
