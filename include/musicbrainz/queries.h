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
#ifndef _QUERIES_H_
#define _QUERIES_H_

// The following define should match the version number of the MM spec
// that is implemented by the defines in this file
#define MM_VERSION                "1.0-pre4"

// local query names
#define MB_GetCDInfo              "@CDINFO@"
#define MB_GetCDTOC               "@LOCALCDINFO@"
#define MB_AssociateCD            "@CDINFOASSOCIATECD@"

// local query xql queries
#define MB_LocalGetId             "MQ:Args/@id"
#define MB_LocalGetLastTrack      "MQ:Args[1]/@last"
#define MB_LocalGetFirstTrack     "MQ:Args[1]/@first"
#define MB_LocalGetTOC            "MQ:Args[1]/@toc"
#define MB_LocalGetTrackLengths   "MQ:Args[2]/@trackLengths"

// description context queries
#define MB_GetArtistName          "DC:Creator"
#define MB_GetArtistID            "DC:Identifier/@artistId"

#define MB_GetAlbumName           "DC:Title"
#define MB_GetAlbumID             "DC:Identifier/@albumId"

#define MB_GetTrackID             "DC:Identifier/@trackId"
#define MB_GetTrackNum            "DC:Relation/@track"
#define MB_GetTrackName           "DC:Title"
#define MB_GetNumTracks           "MM:Collection/@numParts"

#define MB_GetGUID                "DC:Identifier/@guid"
#define MB_GetFilename            "MQ:Filename"
#define MB_GetDuration            "DC:Format/@duration"
#define MB_GetYear                "DC:Date/@issued"
#define MB_GetGenre               "MM:Genre"
#define MB_GetDescription         "DC:Description"
#define MB_GetSyncTextSubmittor   "DC:Contributor"
#define MB_GetSyncTextSubmitDate  "DC:Date"
#define MB_GetSyncTextType        "DC:Type/@type"
#define MB_GetSyncTextText        "MM:SyncText"
#define MB_GetSyncTextTimestamp   "MM:SyncText/@ts"

// Select the local query 
#define MB_SelectTopLevel         "/rdf:RDF/rdf:Description"

// Select Album information
#define MB_SelectAlbum            "/rdf:RDF/rdf:Description/MM:Collection/rdf:Description"
#define MB_SelectFirstTrack       "/rdf:RDF/rdf:Description/MM:Collection/rdf:Description/rdf:Seq/rdf:li[0]/rdf:Description"
#define MB_SelectNextTrack        "/rdf:RDF/rdf:Description/MM:Collection/rdf:Description/rdf:Seq/rdf:li[+1]/rdf:Description"

// Item selectors for queries that return a list of items
#define MB_SelectFirstItem        "/rdf:RDF/rdf:Description/MM:Collection/rdf:Bag/rdf:li[0]/rdf:Description"
#define MB_SelectNextItem         "/rdf:RDF/rdf:Description/MM:Collection/rdf:Bag/rdf:li[+1]/rdf:Description"

// Item selectors for queries that return a list of items
#define MB_SelectExchangedData    "/rdf:RDF/rdf:Description"
#define MB_SelectExchangedAlbum   "/rdf:RDF/rdf:Description/DC:Relation/rdf:Description"

// Item selectors for SyncText queries
#define MB_SelectTrackInfo        "/rdf:RDF/rdf:Description"
#define MB_SelectSyncTextAlbum    "/rdf:RDF/rdf:Description/DC:Relation[ @type = 'album' ]/rdf:Description"
#define MB_SelectFirstSyncText    "/rdf:RDF/rdf:Description/MM:SyncEvents/rdf:Seq/rdf:li[0]/rdf:Description"
#define MB_SelectNextSyncText     "/rdf:RDF/rdf:Description/MM:SyncEvents/rdf:Seq/rdf:li[+1]/rdf:Description"
#define MB_SelectFirstSyncEvent   "/rdf:RDF/rdf:Description/MM:SyncEvents/rdf:Seq/rdf:li[]/rdf:Description/rdf:Seq/rdf:li[0]/rdf:Description"
#define MB_SelectNextSyncEvent    "/rdf:RDF/rdf:Description/MM:SyncEvents/rdf:Seq/rdf:li[]/rdf:Description/rdf:Seq/rdf:li[+1]/rdf:Description"

// GUID selectors for queries that return a list of GUIDS
#define MB_SelectFirstGUID        "/rdf:RDF/rdf:Description/MM:Collection/rdf:Bag/rdf:li[0]/rdf:Description"
#define MB_SelectNextGUID         "/rdf:RDF/rdf:Description/MM:Collection/rdf:Bag/rdf:li[+1]/rdf:Description"

// Lookup queries
#define MB_GetCDInfoFromCDIndexID "<MQ:Query>GetCDInfoFromId</MQ:Query>\n"     \
                                  "<MQ:Args id=\"@1@\"/>\n"
#define MB_FindArtistByName       "<MQ:Query>FindArtistByName</MQ:Query>\n"    \
                                  "<MQ:Args artist=\"@1@\"/>\n"
#define MB_FindAlbumByName        "<MQ:Query>FindAlbumByName</MQ:Query>\n"     \
                                  "<MQ:Args album=\"@1@\" artist=\"@2@\"/>\n"
#define MB_FindAlbumsByArtistName "<MQ:Query>FindAlbumsByArtistName</MQ:Query>\n"\
                                  "<MQ:Args artist=\"@1@\"/>"      
#define MB_FindTrackByName        "<MQ:Query>FindTrackByName</MQ:Query>\n"     \
                                  "<MQ:Args album=\"@3@\" artist=\"@2@\"\n"    \
                                  "         track=\"@1@\"/>\n"
#define MB_FindDistinctGUID       "<MQ:Query>FindDistinctGUID</MQ:Query>\n"    \
                                  "<MQ:Args artist=\"@2@\"\n"    \
                                  "         track=\"@1@\"/>\n"
#define MB_GetArtistById          "<MQ:Query>GetArtistById</MQ:Query>\n"       \
                                  "<MQ:Args id=\"@1@\"/>\n"
#define MB_GetAlbumById           "<MQ:Query>GetAlbumById</MQ:Query>\n"        \
                                  "<MQ:Args id=\"@1@\"/>\n"
#define MB_GetAlbumsByArtistId    "<MQ:Query>GetAlbumsByArtistId</MQ:Query>\n" \
                                  "<MQ:Args id=\"@1@\"/>\n"
#define MB_GetTrackById           "<MQ:Query>GetTrackById</MQ:Query>\n"        \
                                  "<MQ:Args id=\"@1@\"/>\n"
#define MB_GetTrackByGUID         "<MQ:Query>GetTrackByGUID</MQ:Query>\n"      \
                                  "<MQ:Args id=\"@1@\"/>\n"
#define MB_ExchangeMetadata       "<MQ:Query>ExchangeMetadata</MQ:Query>\n"    \
                                  "<DC:Title>@1@</DC:Title>\n"                 \
                                  "<DC:Identifier guid=\"@2@\"/>\n"            \
                                  "<MQ:Filename>@3@</MQ:Filename>\n"           \
                                  "<DC:Creator>@4@</DC:Creator>\n"             \
                                  "<DC:Relation>\n"                            \
                                  "  <rdf:Description>\n"                      \
                                  "    <DC:Title>@5@</DC:Title>\n"             \
                                  "  </rdf:Description>\n"                     \
                                  "</DC:Relation>\n"                           \
                                  "<MM:TrackNum>@6@</MM:TrackNum>\n"           \
                                  "<DC:Format duration=\"@7@\"/>\n"            \
                                  "<DC:Date issued=\"@8@\"/>\n"                \
                                  "<MM:Genre>@9@</MM:Genre>\n"                 \
                                  "<DC:Description>@10@</DC:Description>\n"    \
                                  "<DC:Identifier bitprint=\"@11@\"/>\n"       \
                                  "<DC:Identifier first20=\"@12@\"/>\n"        \
                                  "<DC:Identifier length=\"@13@\"/>\n"         \
                                  "<DC:Identifier audioSha1=\"@14@\"/>\n"      \
                                  "<DC:Identifier duration=\"@15@\"/>\n"       \
                                  "<DC:Identifier sampleRate=\"@16@\"/>\n"     \
                                  "<DC:Identifier bitRate=\"@17@\"/>\n"        \
                                  "<DC:Identifier stereo=\"@18@\"/>\n"         \
                                  "<DC:Identifier vbr=\"@19@\"/>\n"            
#define MB_GetSyncTextById        "<MQ:Query>GetSyncTextById</MQ:Query>\n"     \
                                  "<MQ:Args id=\"@1@\"/>\n"
#define MB_SubmitTrack            "<MQ:Query>SubmitTrack</MQ:Query>\n"         \
                                  "<DC:Title>@1@</DC:Title>\n"                 \
                                  "<DC:Identifier guid=\"@2@\"/>\n"            \
                                  "<DC:Creator>@3@</DC:Creator>\n"             \
                                  "<DC:Relation>\n"                            \
                                  "  <rdf:Description>\n"                      \
                                  "    <DC:Title>@4@</DC:Title>\n"             \
                                  "  </rdf:Description>\n"                     \
                                  "</DC:Relation>\n"                           \
                                  "<DC:Relation track=\"@5@\"/>\n"             \
                                  "<MM:TrackNum>@6@</MM:TrackNum>\n"           \
                                  "<DC:Date issued=\"@7@\"/>\n"                \
                                  "<MM:Genre>@8@</MM:Genre>\n"                 \
                                  "<DC:Description>@9@</DC:Description>\n"
                                  

#endif

