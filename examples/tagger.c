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
#include <string.h>
#include "mb_c.h"

#define DB printf("%s:%d\n", __FILE__, __LINE__);

typedef struct _Metadata
{
    char trmid[40];
    char artistName[256];
    char albumName[256];
    char trackName[256];
    char trackNum[10];
    char duration[14];
    char fileName[256];
    char artistId[40];
    char albumId[40];
    char trackId[40];
} Metadata;

int HandleArtistList(musicbrainz_t o, Metadata *mdata)
{
    int  i, choice;
    char artistName[256], sortName[256];

    printf("Select the correct artist:\n");
    for(i = 1;; i++)
    {
        mb_Select(o, MBS_Rewind);
        if (!mb_Select1(o, MBS_SelectLookupResult, i))
            break;

        mb_GetResultData(o, "http://musicbrainz.org/mm/mq-1.1#artist "
                            "http://purl.org/dc/elements/1.1/title", artistName, 256);
        mb_GetResultData(o, "http://musicbrainz.org/mm/mq-1.1#artist "
                            "http://musicbrainz.org/mm/mm-2.1#sortName", sortName, 256);

        printf("%2d. %s (%s)\n", i, artistName, sortName);
    }

    printf("\n 0. (to stop and exit)\n");
    for(;;)
    {
        printf("> ");
        fflush(stdout);
        scanf(" %d", &choice);
        if (choice < 0 || choice > i)
            printf("\nInvalid choice.\n");
        else
            break;
    }
    if (choice == 0)
       return 1;

    mb_Select(o, MBS_Rewind);
    mb_Select1(o, MBS_SelectLookupResult, choice);

    mb_GetResultData(o, "http://musicbrainz.org/mm/mq-1.1#artist", artistName, 256);
    mb_GetIDFromURL(o, artistName, mdata->artistId, 40);

    return 0;
}

int HandleAlbumList(musicbrainz_t o, Metadata *mdata)
{
    int  i, choice;
    char albumName[256];

    printf("Select the correct album:\n");
    for(i = 1;; i++)
    {
        mb_Select(o, MBS_Rewind);
        if (!mb_Select1(o, MBS_SelectLookupResult, i))
            break;

        mb_GetResultData(o, "http://musicbrainz.org/mm/mq-1.1#album "
                            "http://purl.org/dc/elements/1.1/title", albumName, 256);

        printf("%2d. %s\n", i, albumName);
    }

    printf("\n 0. (to stop and exit)\n");
    for(;;)
    {
        printf("> ");
        fflush(stdout);
        scanf(" %d", &choice);
        if (choice < 0 || choice > i)
            printf("\nInvalid choice.\n");
        else
            break;
    }
    if (choice == 0)
       return 1;

    mb_Select(o, MBS_Rewind);
    mb_Select1(o, MBS_SelectLookupResult, choice);

    mb_GetResultData(o, "http://musicbrainz.org/mm/mq-1.1#album", albumName, 256);
    mb_GetIDFromURL(o, albumName, mdata->albumId, 40);

    return 0;
}

int HandleAlbumTrackList(musicbrainz_t o, Metadata *mdata)
{
    printf("AlbumTrack result\n");

    return 1;
}

int main(int argc, char *argv[])
{
    musicbrainz_t o;
    Metadata      mdata;
    FILE         *p;
    char          error[256], data[256], temp[256], *args[11], cmd[256], trmdata[6][256];
    int           ret, numTracks, trackNum, i, isMultipleArtist = 0, isDone = 0;

    if (argc < 2)
    {
        printf("Usage: tagger <mp3 file>\n");
        exit(0);
    }

    memset(&mdata, 0, sizeof(Metadata));
#if 0
    // Here we cheap -- big time. We require that the trm program be installed
    // and thus we call it to generate the TRM and extract the id3 data.
    sprintf(cmd, "trm -i %s", argv[1]);
    p = popen(cmd, "r");
    if (p == NULL)
    {
       fprintf(stderr, "You need to have the trm command line utility installed\n"
                       "in order for this program to work right. Download the\n"
                       "TRM utility from: http://musicbrainz.org/download/html\n");
       exit(0);
    }

    for(i = 0; i < 6; i++)
    {
        fgets(trmdata[i], 255, p);
        trmdata[i][strlen(trmdata[i]) - 1] = 0;
        printf("data[%d]: %s\n", i, trmdata[i]);
    }
    pclose(p);

    strcpy(mdata.trmid, trmdata[0]);
    strcpy(mdata.artistName, trmdata[1]);
    strcpy(mdata.albumName, trmdata[2]);
    strcpy(mdata.trackName, trmdata[3]);
    strcpy(mdata.trackNum, trmdata[4]);
    strcpy(mdata.duration, trmdata[5]);
    strcpy(mdata.fileName, argv[1]);
#endif

    strcpy(mdata.trmid, "");
    strcpy(mdata.artistName, "portishead");
    strcpy(mdata.albumName, "flummy");
    strcpy(mdata.trackName, "");
    strcpy(mdata.trackNum, "");
    strcpy(mdata.duration, "");
    strcpy(mdata.fileName, "");

    // Create the musicbrainz object, which will be needed for subsequent calls
    o = mb_New();

#ifdef WIN32
    mb_WSAInit(o);
#endif

    // Tell the client library to return data in ISO8859-1 and not UTF-8
    mb_UseUTF8(o, 0);

    // Set the proper server to use. Defaults to mm.musicbrainz.org:80
    if (getenv("MB_SERVER"))
        mb_SetServer(o, getenv("MB_SERVER"), 80);

    // Check to see if the debug env var has been set 
    if (getenv("MB_DEBUG"))
        mb_SetDebug(o, atoi(getenv("MB_DEBUG")));

    isDone = 0;
    for(; !isDone;)
    {
        // Set up the args for the find album query
        args[0] = mdata.trmid;
        args[1] = mdata.artistName;
        args[2] = mdata.albumName;
        args[3] = mdata.trackName;
        args[4] = mdata.trackNum;
        args[5] = mdata.duration;
        args[6] = mdata.fileName;
        args[7] = mdata.artistId;
        args[8] = mdata.albumId;
        args[9] = mdata.trackId;
        args[10] = NULL;

        ret = mb_QueryWithArgs(o, MBQ_FileInfoLookup, args);
        if (!ret)
        {
            mb_GetQueryError(o, error, 256);
            printf("Query failed: %s\n", error);
            isDone = 1;
            break;
        }

        if (!mb_Select1(o, MBS_SelectLookupResult, 1))
        {
            printf("Lookup returned no matches. Lookup might be done.\n");
            // PrintResult();
            isDone = 1;
            break;
        }

        if (!mb_GetResultData(o, MBE_LookupGetType, data, 256))
        {
            printf("Could not determine the type of lookup result.\n");
            isDone = 1;
            break;
        }  

        mb_GetFragmentFromURL(o, data, temp, 256);
        if (strcmp(temp, "ArtistResult") == 0)
        {
            isDone = HandleArtistList(o, &mdata);
        }
        else
        if (strcmp(temp, "AlbumResult") == 0)
        {
            isDone = HandleAlbumList(o, &mdata);
        }
        else
        if (strcmp(temp, "AlbumTrackResult") == 0)
        {
            isDone = HandleAlbumTrackList(o, &mdata);
        }
        else
        {
            printf("Unknown query response.\n");
            isDone = 1;
        }
    }

#ifdef WIN32
    mb_WSAStop(o);
#endif

    // and clean up the musicbrainz object
    mb_Delete(o);

    return 0;
}
