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

int GetChoice(int maxChoice)
{
    char buffer[20];
    int  choice, ret;

    for(;;)
    {
        printf("> ");
        fflush(stdout);
        fgets(buffer, 20, stdin);
        ret = sscanf(buffer, " %d", &choice);
        if (ret < 1 || choice < 0 || choice > maxChoice)
            printf("\nInvalid choice.\n");
        else
            break;
    }
    return choice;
}

int HandleArtistList(musicbrainz_t o, Metadata *mdata)
{
    int  i, choice, rel;
    char artistName[256], sortName[256];

    printf("Select the appropriate artist:\n");
    for(i = 1;; i++)
    {
        mb_Select(o, MBS_Rewind);
        if (!mb_Select1(o, MBS_SelectLookupResult, i))
            break;
        rel = mb_GetResultInt(o, MBE_LookupGetRelevance);

        mb_Select(o, MBS_SelectLookupResultArtist);
        mb_GetResultData(o, MBE_ArtistGetArtistName, artistName, 256);
        mb_GetResultData(o, MBE_ArtistGetArtistSortName, sortName, 256);

        printf("%2d. %s (%d%% relevance, Sortname: %s)\n", i, artistName, rel, sortName);
    }

    printf("\n 0. (to cancel lookup)\n");
    choice = GetChoice(i);
    if (choice == 0)
       return 1;

    mb_Select(o, MBS_Rewind);
    mb_Select1(o, MBS_SelectLookupResult, choice);

    mb_GetResultData(o, MBE_LookupGetArtistId, artistName, 256);
    mb_GetIDFromURL(o, artistName, mdata->artistId, 40);

    return 0;
}

int HandleAlbumList(musicbrainz_t o, Metadata *mdata)
{
    int  i, choice, numIds, rel, numTracks;
    char albumName[256];

    printf("Select the appropriate album:\n");
    for(i = 1;; i++)
    {
        mb_Select(o, MBS_Rewind);
        if (!mb_Select1(o, MBS_SelectLookupResult, i))
            break;
        rel = mb_GetResultInt(o, MBE_LookupGetRelevance);

        mb_Select(o, MBS_SelectLookupResultAlbum);
        mb_GetResultData(o, MBE_AlbumGetAlbumName, albumName, 256);
        numIds = mb_GetResultInt(o, MBE_AlbumGetNumCdindexIds);
        numTracks = mb_GetResultInt(o, MBE_AlbumGetNumTracks);
        printf("%2d. %s (%d%% relevance, %d tracks, %d cdindex ids)\n", 
                  i, albumName, rel, numTracks, numIds);
    }

    printf("\n 0. (to stop and exit)\n");
    choice = GetChoice(i);
    if (choice == 0)
       return 1;

    mb_Select(o, MBS_Rewind);
    mb_Select1(o, MBS_SelectLookupResult, choice);

    mb_GetResultData(o, MBE_LookupGetAlbumId, albumName, 256);
    mb_GetIDFromURL(o, albumName, mdata->albumId, 40);

    return 0;
}

int HandleAlbumTrackList(musicbrainz_t o, Metadata *mdata)
{
    int  i, choice, numIds, numTracks, rel;
    char albumName[256], trackName[256], artistName[256];

    printf("Select the appropriate album/track:\n");
    for(i = 1;; i++)
    {
        mb_Select(o, MBS_Rewind);
        if (!mb_Select1(o, MBS_SelectLookupResult, i))
            break;
        rel = mb_GetResultInt(o, MBE_LookupGetRelevance);

        mb_Select(o, MBS_SelectLookupResultTrack);
        mb_GetResultData(o, MBE_TrackGetTrackName, trackName, 256);

        mb_Select(o, MBS_Back);
        mb_Select(o, MBS_SelectLookupResultAlbum);
        mb_GetResultData(o, MBE_AlbumGetAlbumName, albumName, 256);
        numIds = mb_GetResultInt(o, MBE_AlbumGetNumCdindexIds);
        numTracks = mb_GetResultInt(o, MBE_AlbumGetNumTracks);
        printf("%2d. %s on %s (%d%% relevance, %d tracks, %d cdindex ids)\n", 
                  i, trackName, albumName, rel, numTracks, numIds);
    }

    printf("\n 0. (to stop and exit)\n");
    choice = GetChoice(i);
    if (choice == 0)
       return 1;

    mb_Select(o, MBS_Rewind);
    mb_Select1(o, MBS_SelectLookupResult, choice);

    mb_GetResultData(o, MBE_LookupGetAlbumId, albumName, 256);
    mb_GetIDFromURL(o, albumName, mdata->albumId, 40);
    mb_GetResultData(o, MBE_LookupGetTrackId, trackName, 256);
    mb_GetIDFromURL(o, trackName, mdata->trackId, 40);

    mb_GetResultData(o, MBE_LookupGetTrackArtistId, artistName, 256);
    mb_GetIDFromURL(o, artistName, mdata->artistId, 40);

    return 0;
}

void PrintResult(musicbrainz_t o)
{
    char name[256], id[40], trackURI[256];
    int trackNum, duration;

    mb_Select(o, MBS_Rewind);
    if (mb_DoesResultExist(o, MBE_LookupGetArtistId))
    {
        mb_Select(o, MBS_SelectLookupResultArtist);
        mb_GetResultData(o, MBE_ArtistGetArtistName, name, 256);
        printf("    Artist: %s ", name);
        mb_GetResultData(o, MBE_ArtistGetArtistSortName, name, 256);
        printf("(%s)\n", name);
        mb_GetResultData(o, MBE_ArtistGetArtistId, name, 256);
        mb_GetIDFromURL(o, name, id, 40);
        printf("  ArtistId: %s\n", id);
    }
    mb_Select(o, MBS_Rewind);
    if (mb_DoesResultExist(o, MBE_LookupGetTrackId))
    {
        mb_Select(o, MBS_SelectLookupResultTrack);
        mb_GetResultData(o, MBE_TrackGetTrackName, name, 256);
        printf("     Track: %s\n", name);
        mb_GetResultData(o, MBE_TrackGetTrackId, name, 256);
        strcpy(trackURI, name);
        mb_GetIDFromURL(o, name, id, 40);
        printf("   TrackId: %s\n", id);
        duration = mb_GetResultInt(o, MBE_TrackGetTrackDuration);
        if (duration > 0)
            printf("  Duration: %d ms\n", duration);
            
    }
    mb_Select(o, MBS_Rewind);
    if (mb_DoesResultExist(o, MBE_LookupGetAlbumId))
    {
        mb_Select(o, MBS_SelectLookupResultAlbum);
        mb_GetResultData(o, MBE_AlbumGetAlbumId, name, 256);
        mb_GetIDFromURL(o, name, id, 40);
        mb_GetResultData(o, MBE_AlbumGetAlbumName, name, 256);

        // Extract the track number
        trackNum = mb_GetOrdinalFromList(o, MBE_AlbumGetTrackList, trackURI);
        if (trackNum > 0 && trackNum < 100)
           printf("  TrackNum: %d\n", trackNum);

        printf("     Album: %s\n", name);
        printf("   AlbumId: %s\n", id);
    }
}

int main(int argc, char *argv[])
{
    musicbrainz_t o;
    Metadata      mdata;
    FILE         *p;
    char          error[256], data[256], temp[256], *args[11], cmd[256], trmdata[6][256];
    int           ret, isDone = 0, i;
    int           argi;
    if (argc < 2)
    {
        printf("Usage: tagger <mp3 file>\n");
        exit(0);
    }

    for( argi=1; argi < argc; argi++ ){

      printf("File: %s\n", argv[argi]);

    memset(&mdata, 0, sizeof(Metadata));

    // Here we cheat -- big time. We require that the trm program be installed
    // and thus we call it to generate the TRM and extract the id3 data.
      sprintf(cmd, "trm -i \"%s\"", argv[argi]);
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
    }
    pclose(p);

    strcpy(mdata.trmid, trmdata[0]);
    strcpy(mdata.artistName, trmdata[1]);
    strcpy(mdata.albumName, trmdata[2]);
    strcpy(mdata.trackName, trmdata[3]);
    strcpy(mdata.trackNum, trmdata[4]);
    strcpy(mdata.duration, trmdata[5]);
      strcpy(mdata.fileName, argv[argi]);

    // For debug only
    //strcpy(mdata.trmid, "");
    //strcpy(mdata.artistName, "guns");
    //strcpy(mdata.albumName, "gnr lies");
    //strcpy(mdata.trackName, "used to love hir");
    //strcpy(mdata.trackNum, "");
    //strcpy(mdata.duration, "");
    //strcpy(mdata.fileName, "");

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
            PrintResult(o);
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

    }

    return 0;
}
