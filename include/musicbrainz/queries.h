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
#ifndef _QUERIES_H_
#define _QUERIES_H_

#define MUSICBRAINZ_VERSION "musicbrainz_client/1.0.0-pre1"

// local query names
#define GetCDInfo              "@CDINFO@"
#define GetCDTOC               "@LOCALCDINFO@"
#define AssociateCD            "@CDINFOASSOCIATECD@"

// local query xql queries
#define LocalGetId             "/rdf:RDF/MQ:Args/@id"
#define LocalGetLastTrack      "/rdf:RDF/MQ:Args/@last"
#define LocalGetFirstTrack     "/rdf:RDF/MQ:Args/@first"

// description context queries
#define GetArtistName          "DC:Creator"
#define GetArtistID            "DC:Identifier/@artistId"

#define GetAlbumName           "MM:Album"
#define GetAlbumID             "DC:Identifier/@albumId"

#define GetTrackID             "DC:Identifier/@trackId"
#define GetTrackNum            "DC:Relation/@track"
#define GetTrackName           "DC:Title"
#define GetNumTracks           "MM:Album/@numTracks"

#define GetGUID                "DC:Identifier/@guid"
#define GetFilename            "DC:Identifier/@fileName"
#define GetDuration            "DC:Format/@duration"
#define GetYear                "DC:Date/@issued"
#define GetGenre               "MM:Genre"
#define GetDescription         "DC:Description"
#define GetLyricSubmittor      "DC:Contributor"
#define GetLyricSubmitDate     "DC:Date"
#define GetLyricType           "DC:Type/@type"
#define GetLyricText           "MM:SyncText"
#define GetLyricTimestamp      "MM:SyncText/@ts"

// Track selectors for queries that return an album
#define SelectFirstTrack       "/rdf:RDF/rdf:Description/MC:Collection/rdf:Bag/rdf:li[]/rdf:Description/rdf:Seq/rdf:li[0]/rdf:Description"
#define SelectNextTrack       "/rdf:RDF/rdf:Description/MC:Collection/rdf:Bag/rdf:li[]/rdf:Description/rdf:Seq/rdf:li[+1]/rdf:Description"

// Item selectors for queries that return a list of items
#define SelectFirstItem       "/rdf:RDF/rdf:Description/MC:Collection/rdf:Bag/rdf:li[0]/rdf:Description"
#define SelectNextItem        "/rdf:RDF/rdf:Description/MC:Collection/rdf:Bag/rdf:li[+1]/rdf:Description"

// Item selectors for queries that return a list of items
#define SelectExchangedData   "/rdf:RDF/rdf:Description"

// Item selectors for lyric queries
#define SelectTrackInfo       "/rdf:RDF/rdf:Description"
#define SelectLyricInfo       "/rdf:RDF/rdf:Description/MM:SyncEvents/rdf:Description"
#define SelectFirstSyncEvent  "/rdf:RDF/rdf:Description/MM:SyncEvents/rdf:Description/rdf:Seq/rdf:li[0]/rdf:Description"
#define SelectNextSyncEvent  "/rdf:RDF/rdf:Description/MM:SyncEvents/rdf:Description/rdf:Seq/rdf:li[+1]/rdf:Description"

// GUID selectors for queries that return a list of GUIDS
#define SelectFirstGUID       "/rdf:RDF/rdf:Description/MC:Collection/rdf:Bag/rdf:li[0]/rdf:Description/DC:Identifier/@guid"
#define SelectNextGUID        "/rdf:RDF/rdf:Description/MC:Collection/rdf:Bag/rdf:li[+1]/rdf:Description/DC:Identifier/@guid"

// Lookup queries
#define GetCDInfoFromCDIndexID "<MQ:Query>GetCDInfoFromId</MQ:Query>\n"     \
                               "<MQ:Args id=\"@1@\"/>\n"
#define FindArtistByName       "<MQ:Query>FindArtistByName</MQ:Query>\n"    \
                               "<MQ:Args artist=\"@1@\"/>\n"
#define FindAlbumByName        "<MQ:Query>FindAlbumByName</MQ:Query>\n"     \
                               "<MQ:Args album=\"@1@\" artist=\"@2@\"/>\n"
#define FindAlbumsByArtistName "<MQ:Query>FindAlbumsByArtistName</MQ:Query>\n"\
                               "<MQ:Args artist=\"@1@\"/>"      
#define FindTrackByName        "<MQ:Query>FindTrackByName</MQ:Query>\n"     \
                               "<MQ:Args album=\"@3@\" artist=\"@2@\"\n"    \
                               "         track=\"@1@\"/>\n"
#define FindDistinctGUID       "<MQ:Query>FindDistinctGUID</MQ:Query>\n"    \
                               "<MQ:Args artist=\"@2@\"\n"    \
                               "         track=\"@1@\"/>\n"
#define GetArtistById          "<MQ:Query>GetArtistById</MQ:Query>\n"       \
                               "<MQ:Args id=\"@1@\"/>\n"
#define GetAlbumById           "<MQ:Query>GetAlbumById</MQ:Query>\n"        \
                               "<MQ:Args id=\"@1@\"/>\n"
#define GetAlbumsByArtistId    "<MQ:Query>GetAlbumsByArtistId</MQ:Query>\n" \
                               "<MQ:Args id=\"@1@\"/>\n"
#define GetTrackById           "<MQ:Query>GetTrackById</MQ:Query>\n"        \
                               "<MQ:Args id=\"@1@\"/>\n"
#define ExchangeMetadata       "<MQ:Query>ExchangeMetadata</MQ:Query>\n"    \
                               "<DC:Title>@1@</DC:Title>\n"                 \
                               "<DC:Identifier guid=\"@2@\" \n"             \
                               "               fileName=\"@3@\"/>\n"        \
                               "<DC:Creator>@4@</DC:Creator>\n"             \
                               "<MM:Album>@5@</MM:Album>\n"                 \
                               "<DC:Relation track=\"@6@\"/>\n"             \
                               "<DC:Format duration=\"@7@\"/>\n"            \
                               "<DC:Date issued=\"@8@\"/>\n"                \
                               "<MM:Genre>@9@</MM:Genre>\n"                 \
                               "<DC:Description>@10</DC:Description>\n"    
#define GetLyricsById          "<MQ:Query>GetLyricsById</MQ:Query>\n"       \
                               "<MQ:Args id=\"@1@\"/>\n"

#endif

