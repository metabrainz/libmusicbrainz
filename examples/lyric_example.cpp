/* --------------------------------------------------------------------------

   MusicBrainz -- The Internet music metadatabase

   Copyright (C) 2000 Robert Kaye, Johan Pouwelse
   
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
    MusicBrainz    o;
    string         error, data;
    bool           ret;
    vector<string> args;

    // Set the server you want to use. Defaults to www.musicbrainz.org:80
    //o.SetServer(string("localhost"), 80);

    // Tell the client library to return data in ISO8859-1 and not UTF-8
    o.UseUTF8(false);

    // The string below needs to be a valid track id for this example
    // to work!
    args.push_back("00000005@camry@39FBE6D0");

    // Execute the GetCDInfo query, which pull the TOC from the 
    // audio CD in the cd-rom drive, calculate the disk id and the
    // request the data from the server
    ret = o.Query(string(MB_GetSyncTextById), &args);
    if (!ret)
    {
         o.GetQueryError(error);
         printf("Query failed: %s\n", error.c_str());
         return 0;
    }

    // Check to see how many items were returned from the server
    if (o.GetNumItems() == 0)
    {
        printf("No lyrics found for this track..\n");
        return 0;
    }

    // Now start the data extraction process.
    o.Select(MB_SelectTrackInfo);

    // Print out the artist and then print the title of this track
    printf("Artist: '%s'\n", o.Data(MB_GetArtistName).c_str());
    printf("Title: '%s'\n", o.Data(MB_GetTrackName).c_str());

    o.Select(MB_SelectSyncTextAlbum);
    printf("Album: '%s'\n", o.Data(MB_GetAlbumName).c_str());

    // Now select the lyric information
    o.Select(MB_SelectFirstSyncText);
    while(1) {
       if (!o.DoesResultExist(MB_GetSyncTextType))
          break;
       // Now get and print the title of the cd
       printf("Submitted By: '%s'\n", o.Data(MB_GetSyncTextSubmittor).c_str());
       printf("Submitted Date: '%s'\n", o.Data(MB_GetSyncTextSubmitDate).c_str());
       printf("Submitted Type: '%s'\n", o.Data(MB_GetSyncTextType).c_str());

       // Now select the first sync event data item
       o.Select(MB_SelectFirstSyncEvent);
       while(1) {
          if (!o.DoesResultExist(MB_GetSyncTextText))
             break;

          printf("@ %d: '%s'\n", 
             o.DataInt(MB_GetSyncTextTimestamp),
             o.Data(MB_GetSyncTextText).c_str());

          // Now move on to the next track
          o.Select(MB_SelectNextSyncEvent);
       }
       o.Select(MB_SelectNextSyncText);
    }
    return 0;
}
