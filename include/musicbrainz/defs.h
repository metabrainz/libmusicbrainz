/* --------------------------------------------------------------------------

   MusicBrainz -- The Internet music metadatabase

   Copyright (C) 2000 Robert Kaye
   Portions Copyright (C) 2000 David Gray
   
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
#ifndef _DEFS_H_
#define _DEFS_H_

/**
 * The length of a CD Index id in characters
 */
#define MB_CDINDEX_ID_LEN 28

/**
 * The length of a Artist/Album/Track id in characters
 */
#define MB_ID_LEN 36

/**
 * Basic C abstraction for the MusicBrainz Object 
 */
typedef void * musicbrainz_t;

/**
 * Basic C abstraction for the TRM Object 
 */
typedef void * trm_t;
//
//  cdinfo struct 
//
typedef struct 
{
    unsigned char FirstTrack;        // The first track on CD : normally 1
    unsigned char LastTrack;         // The last track on CD: max number 99
    
    unsigned long FrameOffset[100];  // Track 2 is TrackFrameOffset[2] etc.
                                     // Leadout Track will be TrackFrameOffset[0]

} cdtoc_t;

#endif
