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
#ifndef SHA_H
#define SHA_H

/* NIST Secure Hash Algorithm */
/* heavily modified by Uwe Hollerbach <uh@alumni.caltech edu> */
/* from Peter C. Gutmann's implementation as found in */
/* Applied Cryptography by Bruce Schneier */

/* This code is in the public domain */

/* Useful defines & typedefs */

typedef unsigned char BYTE;	/* 8-bit quantity */
typedef unsigned long LONG;	/* 32-or-more-bit quantity */

#define SHA_BLOCKSIZE		64
#define SHA_DIGESTSIZE		20

typedef struct {
    LONG digest[5];		/* message digest */
    LONG count_lo, count_hi;	/* 64-bit bit count */
    BYTE data[SHA_BLOCKSIZE];	/* SHA data buffer */
    int local;			/* unprocessed amount in data */
} SHA_INFO;

void sha_init(SHA_INFO *);
void sha_update(SHA_INFO *, BYTE *, int);
void sha_final(unsigned char [20], SHA_INFO *);

#include <stdlib.h>
#include <stdio.h>

void sha_stream(unsigned char [20], SHA_INFO *, FILE *);
void sha_print(unsigned char [20]);
char *sha_version(void);

#define SHA_VERSION 1

#ifndef WIN32 
#include "config.h"

#ifdef WORDS_BIGENDIAN
#  if SIZEOF_LONG == 4
#    define SHA_BYTE_ORDER  4321
#  elif SIZEOF_LONG == 8
#    define SHA_BYTE_ORDER  87654321
#  endif
#else
#  if SIZEOF_LONG == 4
#    define SHA_BYTE_ORDER  1234
#  elif SIZEOF_LONG == 8
#    define SHA_BYTE_ORDER  12345678
#  endif
#endif

#else

#define SHA_BYTE_ORDER 1234

#endif

#endif /* SHA_H */
