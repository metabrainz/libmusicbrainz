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
 
#ifndef __MUSICBRAINZ3_MUSICBRAINZ_H__
#define __MUSICBRAINZ3_MUSICBRAINZ_H__

#include <exception>

#ifdef WIN32
  #ifdef MB_API_EXPORTS
    #define MB_API __declspec(dllexport)
  #else
    #define MB_API __declspec(dllimport)
  #endif
#else
  #ifdef GCC_HASCLASSVISIBILITY
    #define MB_API __attribute__ ((visibility("default")))
  #else
    #define MB_API
  #endif
#endif

#include <string>

/** 
 * Main libmusicbrainz namespace.
 */ 

namespace MusicBrainz
{ 
    
	class MB_API Exception : public std::exception
	{
	public:
		Exception(const std::string &msg = std::string()) : msg(msg) {}
		const char *what() const { return msg.c_str(); }
	private:
		std::string msg;
	};
	
	class MB_API ValueError : public Exception
	{
	public:
		ValueError(const std::string &msg = std::string()) : Exception(msg) {}
	};
	
    /**
     * MusicBrainz ID for "Various Artists" 
     */    
    static const std::string VARIOUS_ARTISTS_ID = "http://musicbrainz.org/artist/89ad4ac3-39f7-470e-963a-56509c546377";     

    /**
     * Namespace URI prefix for code MusicBrainz metadata 
     */    
    static const std::string NS_MMD_1 = "http://musicbrainz.org/ns/mmd-1.0#";
    
    /**
     * Namespace URI prefix for MusicBrainz relations 
     */    
    static const std::string NS_REL_1 = "http://musicbrainz.org/ns/rel-1.0#";
    
    /**
     * Namespace URI prefix for extensions to MusicBrainz metadata 
     */    
    static const std::string NS_EXT_1 = "http://musicbrainz.org/ns/ext-1.0#";     
    
}

#endif
