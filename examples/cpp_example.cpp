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
#include "musicbrainz.h"

int main(void)
{
    MusicBrainz o;
    string      error, data;
    bool        ret;
    int         numTracks, trackNum;

    // Set the server you want to use. Defaults to www.musicbrainz.org:80
    //o.SetServer(string("musicbrainz.eorbit.net"), 80);

    // Execute the GetCDInfo query, which pull the TOC from the 
    // audio CD in the cd-rom drive, calculate the disk id and the
    // request the data from the server
    ret = o.Query(string(MB_GetCDInfo));
    if (!ret)
    {
         o.GetQueryError(error);
         printf("Query failed: %s\n", error.c_str());
         return 0;
    }

    // Check to see how many items were returned from the server
    if (o.GetNumItems() == 0)
    {
        printf("This CD was not found.\n");
        return 0;
    }

    // Get the number of tracks
    numTracks = o.DataInt(MB_GetNumTracks);
    printf("NumTracks: %d\n", numTracks);

    // Now start the data extraction process.
    // Select the first item in the list of returned items
    o.Select(MB_SelectAlbum);

    // Now get and print the title of the cd
    printf("Title: '%s'\n", o.Data(MB_GetAlbumName).c_str());

    // Check to see if the GetArtist field exits. If it does, the returned
    // CD is a single artist CD. If it does not, the CD is a multiple
    // artist CD.
    if (o.DoesResultExist(MB_GetArtistName))
    {
         // Print out the artist and then print the titles of the tracks
         printf("Artist: '%s'\n", o.Data(MB_GetArtistName).c_str());
         o.Select(MB_SelectFirstTrack);
         for(int i = 0; i < numTracks; i++)
         {
             trackNum = o.DataInt(MB_GetTrackNum);
             printf("Track %d: '%s'\n", 
                 trackNum, o.Data(MB_GetTrackName).c_str());
             printf("Track id: '%s'\n", 
                 o.Data(MB_GetTrackID).c_str());

             // Now move on to the next track
             o.Select(MB_SelectNextTrack);
         }
    }
    else
    {
         // Now select the first track
         o.Select(MB_SelectFirstTrack);

         // For each track print out the artist and title
         for(int i = 0; i < numTracks; i++)
         {
             printf("Artist %d: '%s'\n", i+1, 
                    o.Data(MB_GetArtistName).c_str());
             printf(" Track %d: '%s'\n", i+1, 
                    o.Data(MB_GetTrackName).c_str());

             // Now move on to the next track
             o.Select(MB_SelectNextTrack);
         }
    }
    return 0;
}
