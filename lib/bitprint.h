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
#ifndef _BITPRINT_H_
#define _BITPRINT_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MB_BITPRINTSIZE 89
#define MB_FIRST20SIZE  41
#define MB_SHA1SIZE     41

/**
 * The structure used to return Bitzi bitprint information for a file.
 */
typedef struct _BitprintInfo
{
    char     filename[255];
    char     bitprint[MB_BITPRINTSIZE];
    char     first20[MB_FIRST20SIZE];
    char     audioSha1[MB_SHA1SIZE];
    unsigned length;
    unsigned duration;
    unsigned samplerate;
    unsigned bitrate;
    char     stereo;
    char     vbr;
} BitprintInfo;

#ifdef __cplusplus
}
#endif

#endif
