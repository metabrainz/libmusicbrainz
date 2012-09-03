/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   libmusicbrainz5 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#ifndef _MUSICBRAINZ5_DEFINES_H
#define _MUSICBRAINZ5_DEFINES_H

#if defined(__GNUC__) && __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)

#define LIBMB5_DEPRECATED(f) __attribute__((deprecated("Use '" #f "' instead")))

#elif defined(__GNUC__) && __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1)

#define LIBMB5_DEPRECATED(f) __attribute__ ((deprecated))

#else

#define LIBMB5_DEPRECATED(f)

#endif

#endif
