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

const char *sampleRDF = 
"<rdf:RDF xmlns:rdf = \"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
"         xmlns:dc  = \"http://purl.org/dc/elements/1.1/\"\n"
"         xmlns:mq  = \"http://musicbrainz.org/mm/mq-1.0#\"\n"
"         xmlns:mm  = \"http://musicbrainz.org/mm/mm-2.0#\">\n"
"\n"
"  <mq:Result>\n"
"    <mq:status>OK</mq:status>\n"
"    <mm:albumList>\n"
"       <rdf:Seq>\n"
"          <rdf:li rdf:resource=\"http://musicbrainz.org/album/l1000\"/>\n"
"       </rdf:Seq>\n"
"    </mm:albumList>\n"
"  </mq:Result>\n"
"\n"
"  <mm:Album rdf:about=\"http://musicbrainz.org/album/l1000\">\n"
"    <dc:title>Dummy</dc:title>\n"
"    <dc:creator rdf:resource=\"http://musicbrainz.org/artist/a1000\"/>\n"
"    <mm:numTracks>2</mm:numTracks>\n"
"    <mm:trackList>\n"
"       <rdf:Seq>\n"
"          <rdf:li rdf:resource=\"http://musicbrainz.org/track/t1000\"/>\n"
"          <rdf:li rdf:resource=\"http://musicbrainz.org/track/t1001\"/>\n"
"       </rdf:Seq>\n"
"    </mm:trackList>\n"
"  </mm:Album>\n"
"\n"
"  <mm:Artist rdf:about=\"http://musicbrainz.org/artist/a1000\">\n"
"     <dc:title>Portishead</dc:title>\n"
"  </mm:Artist>\n"
"\n"
"  <mm:Track rdf:about=\"http://musicbrainz.org/track/t1000\">\n"
"    <dc:title>Mysterons</dc:title>\n"
"    <mm:trackNum>1</mm:trackNum>\n"
"    <dc:creator rdf:resource=\"http://musicbrainz.org/artist/a1000\"/>\n"
"  </mm:Track>\n"
"\n"
"  <mm:Track rdf:about=\"http://musicbrainz.org/track/t1001\">\n"
"    <dc:title>Sour Times</dc:title>\n"
"    <mm:trackNum>2</mm:trackNum>\n"
"    <dc:creator rdf:resource=\"http://musicbrainz.org/artist/a1000\"/>\n"
"  </mm:Track>\n"
"\n"
"</rdf:RDF>\n";


int main(void)
{
    MusicBrainz o;
    string      error, data;
    bool        ret;
    int         numTracks, trackNum;
 
    // Set the server you want to use. Defaults to www.musicbrainz.org:80
    //o.SetServer(string("musicbrainz.eorbit.net"), 80);

    // If you need to use a proxy, uncomment/edit the following line
    // as appropriate
    //o.SetProxy("proxy.mydomain.com", 80);

    // Tell the client library to return data in ISO8859-1 and not UTF-8
    o.UseUTF8(false);

    // Execute the GetCDInfo query, which pull the TOC from the 
    // audio CD in the cd-rom drive, calculate the disk id and the
    // request the data from the server
    //ret = o.Query(string(MBQ_GetCDInfo));
    ret = o.Query(string(sampleRDF));
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

    // Now start the data extraction process.

    // Select the first item in the list of returned items
    o.Select(MBS_SelectAlbum, 1);

    // Get the number of tracks
    numTracks = o.DataInt(MBE_GetNumTracks);
    printf(" NumTracks: %d\n", numTracks);

    // Now get and print the title of the cd
    printf("Album Name: '%s'\n", o.Data(MBE_GetAlbumName).c_str());
    o.GetIDFromURL(o.Data(MBE_GetAlbumID), data);
    printf("   AlbumID: '%s'\n\n", data.c_str());

    for(int i = 1; i <= numTracks; i++)
    {
        // Print out the artist and then print the titles of the tracks
        printf("    Artist: '%s'\n", o.Data(MBE_GetArtistName, i).c_str());

        trackNum = o.DataInt(MBE_GetTrackNum, i);
        printf("  Track %2d: '%s'\n", 
            trackNum, o.Data(MBE_GetTrackName, i).c_str());
        o.GetIDFromURL(o.Data(MBE_GetTrackID, i), data);
        printf("  Track id: '%s'\n\n", data.c_str());
    }
    return 0;
}

