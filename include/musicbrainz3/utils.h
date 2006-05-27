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
 
#ifndef __MUSICBRAINZ3_UTILS_H__
#define __MUSICBRAINZ3_UTILS_H__

#include <string>
#include <musicbrainz3/musicbrainz.h>

namespace MusicBrainz
{ 

	/**
	 * Extract the fragment part from a URI.
	 *
	 * If \a uriStr no absolute URI, then it is returned unchanged.
	 *
	 * @param uriStr a string containing an absolute URI
	 *
	 * @return a string containing the fragment
	 */
	MB_API std::string extractFragment(const std::string &uriStr);    

	/**
	 * Extract the UUID part from a MusicBrainz identifier.
	 *
	 * This function takes a MusicBrainz ID (an absolute URI) as the input
	 * and returns the UUID part of the URI, thus turning it into a relative
	 * URI. If \a uriStr is empty or a relative URI, then it is returned
	 * unchanged.
	 */
	MB_API std::string extractUuid(const std::string &uriStr);    
}

#endif
