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
#include <stdio.h>
#include <stdlib.h>
#include "mb_c.h"

int main(void)
{
    musicbrainz_t o;
    char          error[256], data[256], temp[256];
    int           ret, numTracks, i;

    // Create the musicbrainz object, which will be needed for subsequent calls
    o = mb_New();

    // Tell the client library to return data in ISO8859-1 and not UTF-8
    mb_UseUTF8(o, 0);

    // Set the proper server to use. Defaults to www.musicbrainz.org:80
    if (getenv("MB_SERVER"))
        mb_SetServer(o, getenv("MB_SERVER"), 80);

    // If you need to use a proxy, uncomment/edit the following line
    // as appropriate
    //mb_SetProxy("proxy.mydomain.com", 80);

    // Execute the MB_GetCDInfo query, which pulls the TOC from the
    // audio CD in the cd-rom drive, calculates the disk id and
    // requests the CD info from the server
    ret = mb_Query(o, MBQ_GetCDInfo);
    if (!ret)
    {
         mb_GetQueryError(o, error, 256);
         printf("Query failed: %s\n", error);
         return 0;
    }

    // Check to see how many items were returned from the server
    if (mb_GetResultInt(o, MBE_GetNumAlbums) < 1)
    {
        printf("This CD was not found.\n");
        return 0;
    }  

    // Select the first album
    mb_Select1(o, MBS_SelectAlbum, 1);  

    // Get the number of tracks
    numTracks = mb_GetResultInt(o, MBE_AlbumGetNumTracks);
    printf(" NumTracks: %d\n", numTracks);

    // Now get and print the title of the cd
    mb_GetResultData(o, MBE_AlbumGetAlbumName, data, 256);
    printf("Album Name: '%s'\n", data);

    // Get the album ID URL
    mb_GetResultData(o, MBE_AlbumGetAlbumId, data, 256);
    // Extract the actual ID from the URL
    mb_GetIDFromURL(o, data, temp, 256);
    printf("   AlbumId: '%s'\n\n", temp);

    for(i = 1; i <= numTracks; i++)
    {
        // Extract the artist name from the ith track
        mb_GetResultData1(o, MBE_AlbumGetArtistName, data, 256, i);
        printf("    Artist: '%s'\n", data);

        // Extract the track number from the ith track
        mb_GetResultData1(o, MBE_AlbumGetTrackName, data, 256, i);
        printf("  Track %2d: '%s'\n", mb_GetResultInt1(o, 
               MBE_AlbumGetTrackNum, i), data);

        // Extract the track nqme from the ith track
        mb_GetResultData1(o, MBE_AlbumGetTrackId, data, 256, i);
        mb_GetIDFromURL(o, data, temp, 256);
        printf("   TrackId: '%s'\n\n", temp);
            
    }

    // and clean up the musicbrainz object
    mb_Delete(o);

    return 0;
}
