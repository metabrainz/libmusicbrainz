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
#define MM_VERSION                 "2.0-pre1"

// Select queries -- these whitespace seperated list macros are a list of
// rdf predicates and/or ordinals (specified as []). These predicate lists
// specify a path to traverse through an RDF graph (comprised of statements,
// aka triples). Each select query starts at the top level resource and
// 'selects' another node in the rdf graph by moving through the graph
// as specified by the predicate list. The URI of the new node, will be
// saved as the 'selected context'. Once a context has been selected,
// you can use the MBE_ queries below to extract metadata out of a context.
#define MBS_Reset "[reset]"
#define MBS_SelectArtist           "http://musicbrainz.org/MM/artistList []"
#define MBS_SelectAlbum            "http://musicbrainz.org/mm/mm-2.0#albumList []"
#define MBS_SelectTrack            "http://musicbrainz.org/mm/mm-2.0#trackList []"
#define MBS_SelectGUID             "http://musicbrainz.org/MM/guidList []"
#define MBS_SelectLyrics           "http://musicbrainz.org/MM/lyricList []"

// local rdf queries
#define MBE_LocalGetId             "MQ:Args/@id"
#define MBE_LocalGetLastTrack      "MQ:Args[1]/@last"
#define MBE_LocalGetFirstTrack     "MQ:Args[1]/@first"
#define MBE_LocalGetTOC            "MQ:Args[1]/@toc"
#define MBE_LocalGetTrackLengths   "MQ:Args[2]/@trackLengths"

// mq:result queries
#define MBE_QuerySubject           "http://musicbrainz.org/mm/mq-1.0#Result"
#define MBE_GetError               "http://musicbrainz.org/mm/mq-1.0#error"
#define MBE_GetStatus              "http://musicbrainz.org/mm/mq-1.0#status"
#define MBE_NumItems               "http://musicbrainz.org/mm/mq-1.0#numItems"

// mm:albumList queries
#define MBE_GetNumAlbums           "http://musicbrainz.org/mm/mm-2.0#albumList [COUNT]"
#define MBE_GetAlbumName           "http://purl.org/dc/elements/1.1/title"
#define MBE_GetAlbumId             "" // yes, empty! 
#define MBE_GetNumTracks           "http://musicbrainz.org/mm/mm-2.0#trackList [COUNT]"
#define MBE_GetTrackId             "http://musicbrainz.org/mm/mm-2.0#trackList [] "
#define MBE_GetTrackNum            "http://musicbrainz.org/mm/mm-2.0#trackList [] http://musicbrainz.org/mm/mm-2.0#trackNum"
#define MBE_GetTrackName           "http://musicbrainz.org/mm/mm-2.0#trackList [] http://purl.org/dc/elements/1.1/title"
#define MBE_GetArtistName          "http://musicbrainz.org/mm/mm-2.0#trackList [] http://purl.org/dc/elements/1.1/creator http://purl.org/dc/elements/1.1/title"
#define MBE_GetArtistId            "http://musicbrainz.org/mm/mm-2.0#trackList [] http://purl.org/dc/elements/1.1/creator"

#define MBE_GetGUID                ""
#define MBE_GetFilename            ""
#define MBE_GetDuration            ""
#define MBE_GetYear                ""
#define MBE_GetGenre               ""
#define MBE_GetDescription         ""
#define MBE_GetSyncTextSubmittor   ""
#define MBE_GetSyncTextSubmitDate  ""
#define MBE_GetSyncTextType        ""
#define MBE_GetSyncTextText        ""
#define MBE_GetSyncTextTimestamp   ""

// Extract queries for the MBQ:GetCDTOC query
#define MBE_GetCDIndexId           "http://musicbrainz.org/mm/mm-2.0#cdindexId"
#define MBE_GetFirstTrack          "http://musicbrainz.org/mm/mm-2.0#firstTrack"
#define MBE_GetLastTrack           "http://musicbrainz.org/mm/mm-2.0#lastTrack"
#define MBE_GetTrackSectorOffset   "http://musicbrainz.org/mm/mm-2.0#toc [] http://musicbrainz.org/mm/mm-2.0#sectorOffset"
#define MBE_GetTrackNumSectors     "http://musicbrainz.org/mm/mm-2.0#toc [] http://musicbrainz.org/mm/mm-2.0#numSectors"

// local queries
#define MBQ_GetCDInfo              "@CDINFO@"
#define MBQ_GetCDTOC               "@LOCALCDINFO@"
#define MBQ_AssociateCD            "@CDINFOASSOCIATECD@"

// server queries
#define MBQ_GetCDInfoFromCDIndexId \
    "<mq:GetCDInfo>" \
    "   <mq:depth>@DEPTH@</mq:depth>" \
    "   <mm:cdindexId>@1@</mm:cdindexId>" \
    "</mq:GetCDInfo>" 

#define MBQ_FindArtistByName \
    "<mq:FindArtist>" \
    "   <mq:depth>@DEPTH@</mq:depth>" \
    "   <mq:artistName>@1@</mq:artistName>" \
    "</mq:FindArtist>" 

#define MBQ_FindAlbumByName \
    "<mq:FindAlbum>" \
    "   <mq:depth>@DEPTH@</mq:depth>" \
    "   <mq:artistName>@1@</mq:artistName>" \
    "   <mq:albumName>@2@</mq:albumName>" \
    "</mq:FindAlbum>" 

#define MBQ_FindTrackByName \
    "<mq:FindTrack>" \
    "   <mq:depth>@DEPTH@</mq:depth>" \
    "   <mq:artistName>@1@</mq:artistName>" \
    "   <mq:albumName>@2@</mq:albumName>" \
    "   <mq:trackName>@3@</mq:trackName>" \
    "</mq:FindTrack>" 

#define MBQ_FindDistinctTRMId \
    "<mq:FindDistinctTRMID>" \
    "   <mq:depth>@DEPTH@</mq:depth>" \
    "   <mq:artistName>@1@</mq:artistName>" \
    "   <mq:trackName>@2@</mq:trackName>" \
    "</mq:FindDistinctTRMID>" 

#define MBQ_GetArtistById \
    "http://@URL@/artist/@1@" 

#define MBQ_GetAlbumById \
    "http://@URL@/album/@1@" 

#define MBQ_GetTrackById \
    "http://@URL@/track/@1@" 

#define MBQ_GetTrackByTRMId \
    "http://@URL@/trmid/@1@" 

#define MBQ_GetSyncTextById \
    "http://@URL@/synctext/@1@" 

#define MBQ_ExchangeMetadata \
    "<mq:ExchangeMetadata>" \
    "   <mq:artistName>@1@</mq:artistName>" \
    "   <mq:albumName>@2@</mq:albumName>" \
    "   <mq:trackName>@3@</mq:trackName>" \
    "   <mm:trackNum>@4@</mm:trackNum>" \
    "   <mm:trmid>@5@</mm:trmid>" \
    "   <mm:fileName>@6@</mm:fileName>" \
    "   <mm:issued>@7@</mm:issued>" \
    "   <mm:genre>@8@</mm:genre>" \
    "   <dc:description>@9@</dc:description>" \
    "   <mm:bitprint>@10@</mm:bitprint>" \
    "   <mm:first20>@11@</mm:first20>" \
    "   <mm:fileSize>@12@</mm:fileSize>" \
    "   <mm:audioSha1>@13@</mm:audioSha1>" \
    "   <mm:duration>@14@<mm:duration>" \
    "   <mm:sampleRate>@15@</mm:sampleRate>" \
    "   <mm:bitRate>@16@</mm:bitRate>" \
    "   <mm:channels>@17@</mm:channels>" \
    "   <mm:vbr>@18@</mm:vbr>" \
    "</mq:ExchangeMetadata>" 

#define MBQ_SubmitTrack \
    "<mq:SubmitTrack>" \
    "   <mq:artistName>@1@</mq:artistName>" \
    "   <mq:albumName>@2@</mq:albumName>" \
    "   <mq:trackName>@3@</mq:trackName>" \
    "   <mm:trmid>@4@</mm:trmid>" \
    "   <mm:trackNum>@5@</mm:trackNum>" \
    "   <mm:duration>@6@</mm:duration>" \
    "   <mm:issued>@7@</mm:issued>" \
    "   <mm:genre>@8@</mm:genre>" \
    "   <dc:description>@9@</dc:description>" \
    "   <mm:link>@10@</mm:link>" \
    "</mq:SubmitTrack>" 

#endif
