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
#include "queries.h"

struct Queries
{
    char *name, *value;
    int   numArgs;
    char *arg1, *arg2, *arg3, *arg4;
};

const char *SUBMIT_LYRICS_QUERY= "";

Queries queries[] = 
{
    { "GetCDInfoFromCDIndexId", MBQ_GetCDInfoFromCDIndexId, 
      1, "CD Index ID", "", "", "" }, 
    { "FindArtist",             MBQ_FindArtistByName,
      1, "Artist Name", "", "", "" },
    { "FindTrack",              MBQ_FindTrackByName,
      3, "Artist Name", "Album Name", "Track Name", "" },
    { "FindAlbum",              MBQ_FindAlbumByName,
      1, "Artist Name", "Album name", "", "" },
    { "FindDistinctGUID",       MBQ_FindDistinctTRMId,
      2, "Artist Name", "Track Name", "", "" },
    { "GetArtist",              MBQ_GetArtistById ,
      1, "Artist ID", "", "", "" },
    { "GetAlbum",               MBQ_GetAlbumById ,
      1, "Album ID", "", "", "" },
    { "GetTrack",               MBQ_GetTrackById ,
      1, "Track ID", "", "", "" },
    { "GetTrackTRMId",           MBQ_GetTrackByTRMId ,
      1, "Track TRM Id", "", "", "" },
    { "GetSyncText",            MBQ_GetSyncTextById ,
      1, "Track ID", "", "", "" },
    { "GetCDInfo",              MBQ_GetCDInfo ,
      0, "", "", "", "" },
    { "GetCDTOC",               MBQ_GetCDTOC ,
      0, "", "", "", "" },
    { "AssociateCD",            MBQ_AssociateCD ,
      0, "", "", "", "" },
    { "SubmitTRMId",       MBQ_SubmitTrackTRMId,
      2, "Track GID", "TRM ID", "", "" },
    { "\0",                     "\0", 0, "", "", "", "" }
}; 

#ifdef WIN32
#define strcasecmp stricmp
#endif

int main(void)
{
    MusicBrainz    o;
    string         error, data;
    bool           ret;
    Queries        *p;
    char           szLine[256], *szCmd, *ptr, szLast[100];
    string         xml, qarg, query, server;
    vector<string> args;

    // Set the server you want to use. Defaults to www.musicbrainz.org:80
    server = string("www.musicbrainz.org");
    o.SetServer(server, 80);

    // Tell the client library to return data in ISO8859-1 and not UTF-8
    o.UseUTF8(0);

    // If you need to use a proxy, uncomment/edit the following line
    // as appropriate
    //o.SetProxy("proxy.mydomain.com", 80);

    for(;;)
    {
        query = "";
        printf("query> ");
        fflush(stdout);

        if (fgets(szLine, 255, stdin) < 0)
           break;

        if (strncmp(szLine, "!!", 2) == 0)
        {
            printf("%s\n", szLast);
            strcpy(szLine, szLast);
        }
        else
            strcpy(szLast, szLine);

        szLine[strlen(szLine) - 1] = 0;
        szCmd = strtok(szLine, " ");

        if (szCmd == NULL)
           continue;

        args.clear();
        for(;;)
        {
            ptr = strtok(NULL, " ");
            if (!ptr)
               break;

            if (*ptr == '\"' &&  !(*(ptr + strlen(ptr) - 1) == '\"'))
            {
               qarg = string(ptr + 1);
               for(;;)
               {
                   ptr = strtok(NULL, " ");
                   if (!ptr)
                      break;

                   if (*(ptr + strlen(ptr) - 1) == '\"')
                   {
                       *(ptr + strlen(ptr) - 1) = 0;
                       qarg += string(" ") + string(ptr);
                       ptr = (char *)qarg.c_str();
                       break;
                   }
                   qarg += string(" ") + string(ptr);
               }
               if (!ptr)
               {
                   continue;
               }
            }

            if (*ptr == '\"' &&  *(ptr + strlen(ptr) - 1) == '\"')
            {
               *(ptr + strlen(ptr) - 1) = 0;
               args.push_back(string(ptr + 1));
            }
            else
            {
               if (strcmp(ptr, "\"\"") == 0)
                  *ptr = 0;
   
               args.push_back(string(ptr));
            }
        }
         

        if (strncmp(szCmd, "bye", 3) == 0 ||
            strncmp(szCmd, "quit", 4) == 0 ||
            strncmp(szCmd, "exit", 4) == 0)
        {
            break;
        }

        if (strncmp(szCmd, "help", 4) == 0)
        {
            printf("Available commands:                Arguments:\n\n");
            for(p = queries; *p->name; p++)
            {
                printf("%-34s ", p->name);
                if (strlen(p->arg1))
                   printf("<%s> ", p->arg1); 
                if (strlen(p->arg2))
                   printf("<%s> ", p->arg2); 
                if (strlen(p->arg3))
                   printf("<%s> ", p->arg3); 
                if (strlen(p->arg4))
                   printf("<%s> ", p->arg4); 

                printf("\n");
            }
            printf("exit/quit/bye                      [quit]\n");
            printf("submit                             [get web submit URL]\n");
            printf("info                               [help on a command]\n");
            continue;
        }

        if (strncmp(szCmd, "lyrics", 6) == 0)
        {
            query = string(SUBMIT_LYRICS_QUERY);
        }

        if (strncmp(szCmd, "submit", 6) == 0)
        {
            string url;

            ret = o.GetWebSubmitURL(url);
            if (ret)
               printf("URL: %s\n", url.c_str());
            else
               printf("Could not determine web submit url.\n");

            continue;
        }

        if (strncmp(szCmd, "info", 4) == 0)
        {
            for(p = queries; p->name; p++)
            {
                if (strcasecmp(szCmd + 5, p->name) == 0)
                {
                   printf("usage: %s ", p->name);
                   if (strlen(p->arg1))
                      printf("<%s> ", p->arg1); 
                   if (strlen(p->arg2))
                      printf("<%s> ", p->arg2); 
                   if (strlen(p->arg3))
                      printf("<%s> ", p->arg3); 
                   if (strlen(p->arg4))
                      printf("<%s> ", p->arg4); 

                   printf("\n");
                   break;
                }
            }
            if (p->name == NULL)
               printf("No info available for %s\n", szCmd + 5);
            continue;
        }

        if (query.length() == 0)
        {
           for(p = queries; p->name; p++)
           {
               if (strcasecmp(szCmd, p->name) == 0)
                  break;
           }
           if (p->name == NULL)
           {
               printf("Unknown query.\n");
               continue;
           }
           query = string(p->value);
        }

        ret = o.Query(query, &args);
        if (!ret)
        {
             o.GetQueryError(error);
             printf("Query failed: %s\n", error.c_str());
             continue; 
        }
        printf("Query ok.\n");

        o.GetResultRDF(xml);
        printf("Returned RDF object:\n\n%s\n", xml.c_str());
    }

    return 0;
}
