/* --------------------------------------------------------------------------

   MusicBrainz -- The Intenet music metadatabase

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

const char *SUBMIT_LYRICS_QUERY=
"   <MQ:Query>SubmitTrack</MQ:Query>\n"
"    <DC:Title>Big Time</DC:Title>\n"
"    <DC:Creator>Peter Gabriel</DC:Creator>\n"
"    <MM:Album>So</MM:Album>\n"
"    <DC:Relation track=\"7\"/>\n"
"    <MM:SyncEvents>\n"
//"       <rdf:Description about=\"http://usenet4free.com?grp=alt.music.lyrics&art=26819\">\n"
"       <rdf:Description>\n"
"         <DC:Contributor>Red Hot Lyrics Man</DC:Contributor>\n"
"         <DC:Type type=\"lyrics\"/>\n"
"         <DC:Date>2000-07-27</DC:Date>\n"
"         <rdf:Seq>\n"
"            <rdf:li>\n"
"               <rdf:Description>\n"
"                  <MM:SyncText ts=\"00:02.451\">Hello World</MM:SyncText>\n"
"               </rdf:Description>\n"
"            </rdf:li>\n"
"            <rdf:li>\n"
"               <rdf:Description>\n"
"                  <MM:SyncText ts=\"00:06.882\">Sing along</MM:SyncText>\n"
"               </rdf:Description>\n"
"            </rdf:li>\n"
"            <rdf:li>\n"
"               <rdf:Description>\n"
"                  <MM:SyncText ts=\"01:03.096\">Make</MM:SyncText>\n"
"               </rdf:Description>\n"
"            </rdf:li>\n"
"            <rdf:li>\n"
"               <rdf:Description>\n"
"                  <MM:SyncText ts=\"01:09.478\">it</MM:SyncText>\n"
"               </rdf:Description>\n"
"            </rdf:li>\n"
"            <rdf:li>\n"
"               <rdf:Description>\n"
"                  <MM:SyncText ts=\"01:13.516\">all</MM:SyncText>\n"
"               </rdf:Description>\n"
"            </rdf:li>\n"
"            <rdf:li>\n"
"               <rdf:Description>\n"
"                  <MM:SyncText ts=\"01:41.744\">clear.</MM:SyncText>\n"
"               </rdf:Description>\n"
"            </rdf:li>\n"
"         </rdf:Seq>\n"
"       </rdf:Description>\n"
"    </MM:SyncEvents>\n";

Queries queries[] = 
{
    { "GetCDInfoFromCDIndexId", MB_GetCDInfoFromCDIndexID, 
      1, "CD Index ID", "", "", "" }, 
    { "FindArtist",             MB_FindArtistByName,
      1, "Artist Name", "", "", "" },
    { "FindTrack",              MB_FindTrackByName,
      3, "Track Name", "Album Name", "Artist Name", "" },
    { "FindAlbumsByArtist",     MB_FindAlbumsByArtistName,
      1, "Artist Name", "", "", "" },
    { "FindAlbum",              MB_FindAlbumByName,
      1, "Album Name", "", "", "" },
    { "FindDistinctGUID",       MB_FindDistinctGUID,
      2, "Track Name", "Artist Name", "", "" },
    { "GetArtist",              MB_GetArtistById ,
      1, "Artist ID", "", "", "" },
    { "GetAlbum",               MB_GetAlbumById ,
      1, "Album ID", "", "", "" },
    { "GetAlbumsByArtist",      MB_GetAlbumsByArtistId ,
      1, "Artist ID", "", "", "" },
    { "GetTrack",               MB_GetTrackById ,
      1, "Track ID", "", "", "" },
    { "GetLyrics",              MB_GetLyricsById ,
      1, "Track ID", "", "", "" },
    { "GetCDInfo",              MB_GetCDInfo ,
      0, "", "", "", "" },
    { "GetCDTOC",               MB_GetCDTOC ,
      0, "", "", "", "" },
    { "AssociateCD",            MB_AssociateCD ,
      0, "", "", "", "" },
    { "\0",                     "\0", 0, "", "", "", "" }
}; 

int main(void)
{
    MusicBrainz    o;
    string         error, data;
    bool           ret, info;
    int            numTracks, i;
    Queries        *p;
    char           szLine[256], *szCmd, *ptr, szLast[100];
    string         xml, qarg, query;
    vector<string> args;

    // Set the server you want to use. Defaults to www.musicbrainz.org:80
    o.SetServer(string("musicbrainz.eorbit.net"), 80);

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
        printf("Query ok. Items returned: %d\n", o.GetNumItems());

        o.GetResultRDF(xml);
        printf("Returned RDF object:\n\n%s\n", xml.c_str());
    }

    return 0;
}
