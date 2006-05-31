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
 *
 * $Id$
 */
 
#ifndef __MUSICBRAINZ3_DEFINES_H__
#define __MUSICBRAINZ3_DEFINES_H__

#ifdef _MSC_VER
#	pragma warning (disable : 4251) 
#endif

#ifdef WIN32
#	ifdef MB_API_EXPORTS
#		define MB_API __declspec(dllexport)
#	else
#		define MB_API __declspec(dllimport)
#	endif
#else
#	define MB_EXPIMP_TEMPLATE
#	ifdef GCC_HASCLASSVISIBILITY
#		define MB_API __attribute__ ((visibility("default")))
#	else
#		define MB_API
#	endif
#endif

#endif
