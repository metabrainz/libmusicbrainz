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
}
#if 0
    musicbrainz_t o;
    char          error[256], data[256];
    int           ret, numTracks, i;

    // Create the cdi object, which will be needed for subsequent calls
    o = mb_New();

    // Tell the client library to return data in ISO8859-1 and not UTF-8
    //mb_UseUTF8(o, 0);

    // Set the server you want to use. Defaults to www.musicbrainz.org:80
    //mb_SetServer(o, "musicbrainz.eorbit.net", 80);

    // If you need to use a proxy, uncomment/edit the following line
    // as appropriate
    //mb_SetProxy("proxy.mydomain.com", 80);

    // Execute the MB_GetCDInfo query, which pull the TOC from the
    // audio CD in the cd-rom drive, calculate the disk id and the
    // request the data from the server
    ret = mb_Query(o, MB_GetCDInfo);
    if (!ret)
    {
         mb_GetQueryError(o, error, 256);
         printf("Query failed: %s\n", error);
         return 0;
    }

    // Check to see how many items were returned from the server
    if (mb_GetNumItems(o) == 0)
    {
        printf("This CD was not found.\n");
        return 0;
    }  

    // Select the top level (default context)
    mb_Select(o, MB_SelectTopLevel);  

    // Get the number of tracks
    mb_GetResultData(o, MB_GetNumTracks, data, 256);
    numTracks = atoi(data);
    printf("NumTracks: %d\n", numTracks);

    // Now start the data extraction process.
    // Select the album context first
    mb_Select(o, MB_SelectAlbum);  

    // Now get and print the title of the cd
    mb_GetResultData(o, MB_GetAlbumName, data, 256);
    printf("Title: '%s'\n", data);

    // Check to see if the GetArtist field exits. If it does, the returned
    // CD is a single artist CD. If it does not, the CD is a multiple
    // artist CD.
    if (mb_DoesResultExist(o, MB_GetArtistName))
    {
        // Print out the artist and then print the titles of the tracks 
        mb_GetResultData(o, MB_GetArtistName, data, 256);
        printf("Artist: '%s'\n", data);

        // Select the first track and then get info for this track
        mb_Select(o, MB_SelectFirstTrack);
        for(i = 0; i < numTracks; i++)
        {
            mb_GetResultData(o, MB_GetTrackName, data, 256);
            printf("Track %d: '%s'\n", i+1, data);

            // Done with this track, move on to next
            mb_Select(o, MB_SelectNextTrack);
        }
    }
    else
    {
        // Select the first track and then get info for this track
        mb_Select(o, MB_SelectFirstTrack);

        // For each track print out the artist and title
        for(i = 0; i < numTracks; i++)
        {
            mb_GetResultData(o, MB_GetArtistName, data, 256);
            printf("Artist %d: '%s'\n", i+1, data);
            mb_GetResultData(o, MB_GetTrackName, data, 256);
            printf(" Track %d: '%s'\n", i+1, data);

            // Done with this track, move on to next
            mb_Select(o, MB_SelectNextTrack);
        }
    }

    // and clean up the cdi object
    mb_Delete(o);

    return 0;
}
#endif
