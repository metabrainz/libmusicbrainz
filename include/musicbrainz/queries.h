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
#define MBS_SelectArtist           "http://musicbrainz.org/mm/mm-2.0#artistList []"
#define MBS_SelectAlbum            "http://musicbrainz.org/mm/mm-2.0#albumList []"
#define MBS_SelectTrack            "http://musicbrainz.org/mm/mm-2.0#trackList []"
#define MBS_SelectLyrics           "http://musicbrainz.org/mm/mm-2.0#lyricList []"

// General top level queries
#define MBE_QuerySubject           "http://musicbrainz.org/mm/mq-1.0#Result"
#define MBE_GetError               "http://musicbrainz.org/mm/mq-1.0#error"
#define MBE_GetStatus              "http://musicbrainz.org/mm/mq-1.0#status"
#define MBE_NumItems               "http://musicbrainz.org/mm/mq-1.0#numItems"

// albumList queries
#define MBE_AlbumGetNumAlbums      "http://musicbrainz.org/mm/mm-2.0#albumList [COUNT]"
#define MBE_AlbumGetAlbumName      "http://purl.org/dc/elements/1.1/title"
#define MBE_AlbumGetAlbumId        "" // yes, empty! 
#define MBE_AlbumGetNumTracks      "http://musicbrainz.org/mm/mm-2.0#trackList [COUNT]"
#define MBE_AlbumGetTrackId        "http://musicbrainz.org/mm/mm-2.0#trackList [] "
#define MBE_AlbumGetTrackNum       "http://musicbrainz.org/mm/mm-2.0#trackList [] http://musicbrainz.org/mm/mm-2.0#trackNum"
#define MBE_AlbumGetTrackName      "http://musicbrainz.org/mm/mm-2.0#trackList [] http://purl.org/dc/elements/1.1/title"
#define MBE_AlbumGetArtistName     "http://musicbrainz.org/mm/mm-2.0#trackList [] http://purl.org/dc/elements/1.1/creator http://purl.org/dc/elements/1.1/title"
#define MBE_AlbumGetArtistId       "http://musicbrainz.org/mm/mm-2.0#trackList [] http://purl.org/dc/elements/1.1/creator"

// artistList queries TBC!
// trackList queries TBC!

// ExchangeMetadata queries
#define MBE_MEGetArtistName        "http://musicbrainz.org/mm/mq-1.0#artistName"
#define MBE_MEGetAlbumName         "http://musicbrainz.org/mm/mq-1.0#albumName"
#define MBE_MEGetTrackName         "http://musicbrainz.org/mm/mq-1.0#trackName"
#define MBE_MEGetTrackNum          "http://musicbrainz.org/mm/mm-2.0#trackNum"
#define MBE_MEGetTRMId             "http://musicbrainz.org/mm/mm-2.0#trmid"
#define MBE_MEGetDuration          "http://musicbrainz.org/mm/mm-2.0#duration"
#define MBE_MEGetYear              "http://musicbrainz.org/mm/mm-2.0#issued"
#define MBE_MEGetGenre             "http://musicbrainz.org/mm/mm-2.0#genre"
#define MBE_MEGetDescription       "http://purl.org/dc/elements/1.1/description"

// Extract queries for the MBQ_GetCDTOC query
#define MBE_TOCGetCDIndexId           "http://musicbrainz.org/mm/mm-2.0#cdindexId"
#define MBE_TOCGetFirstTrack          "http://musicbrainz.org/mm/mm-2.0#firstTrack"
#define MBE_TOCGetLastTrack           "http://musicbrainz.org/mm/mm-2.0#lastTrack"
#define MBE_TOCGetTrackSectorOffset   "http://musicbrainz.org/mm/mm-2.0#toc [] http://musicbrainz.org/mm/mm-2.0#sectorOffset"
#define MBE_TOCGetTrackNumSectors     "http://musicbrainz.org/mm/mm-2.0#toc [] http://musicbrainz.org/mm/mm-2.0#numSectors"

// local queries
#define MBQ_GetCDInfo              "@CDINFO@"
#define MBQ_GetCDTOC               "@LOCALCDINFO@"
#define MBQ_AssociateCD            "@CDINFOASSOCIATECD@"

// server queries
#define MBQ_GetCDInfoFromCDIndexId \
    "<mq:GetCDInfo>\n" \
    "   <mq:depth>@DEPTH@</mq:depth>\n" \
    "   <mm:cdindexId>@1@</mm:cdindexId>\n" \
    "</mq:GetCDInfo>\n" 

#define MBQ_FindArtistByName \
    "<mq:FindArtist>\n" \
    "   <mq:depth>@DEPTH@</mq:depth>\n" \
    "   <mq:artistName>@1@</mq:artistName>\n" \
    "</mq:FindArtist>\n" 

#define MBQ_FindAlbumByName \
    "<mq:FindAlbum>\n" \
    "   <mq:depth>@DEPTH@</mq:depth>\n" \
    "   <mq:artistName>@1@</mq:artistName>\n" \
    "   <mq:albumName>@2@</mq:albumName>\n" \
    "</mq:FindAlbum>\n" 

#define MBQ_FindTrackByName \
    "<mq:FindTrack>\n" \
    "   <mq:depth>@DEPTH@</mq:depth>\n" \
    "   <mq:artistName>@1@</mq:artistName>\n" \
    "   <mq:albumName>@2@</mq:albumName>\n" \
    "   <mq:trackName>@3@</mq:trackName>\n" \
    "</mq:FindTrack>\n" 

#define MBQ_FindDistinctTRMId \
    "<mq:FindDistinctTRMID>\n" \
    "   <mq:depth>@DEPTH@</mq:depth>\n" \
    "   <mq:artistName>@1@</mq:artistName>\n" \
    "   <mq:trackName>@2@</mq:trackName>\n" \
    "</mq:FindDistinctTRMID>\n" 

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
    "<mq:ExchangeMetadata>\n" \
    "   <mq:artistName>@1@</mq:artistName>\n" \
    "   <mq:albumName>@2@</mq:albumName>\n" \
    "   <mq:trackName>@3@</mq:trackName>\n" \
    "   <mm:trackNum>@4@</mm:trackNum>\n" \
    "   <mm:trmid>@5@</mm:trmid>\n" \
    "   <mm:fileName>@6@</mm:fileName>\n" \
    "   <mm:issued>@7@</mm:issued>\n" \
    "   <mm:genre>@8@</mm:genre>\n" \
    "   <dc:description>@9@</dc:description>\n" \
    "   <mm:bitprint>@10@</mm:bitprint>\n" \
    "   <mm:first20>@11@</mm:first20>\n" \
    "   <mm:fileSize>@12@</mm:fileSize>\n" \
    "   <mm:audioSha1>@13@</mm:audioSha1>\n" \
    "   <mm:duration>@14@</mm:duration>\n" \
    "   <mm:sampleRate>@15@</mm:sampleRate>\n" \
    "   <mm:bitRate>@16@</mm:bitRate>\n" \
    "   <mm:channels>@17@</mm:channels>\n" \
    "   <mm:vbr>@18@</mm:vbr>\n" \
    "</mq:ExchangeMetadata>\n" 

#define MBQ_SubmitTrack \
    "<mq:SubmitTrack>\n" \
    "   <mq:artistName>@1@</mq:artistName>\n" \
    "   <mq:albumName>@2@</mq:albumName>\n" \
    "   <mq:trackName>@3@</mq:trackName>\n" \
    "   <mm:trmid>@4@</mm:trmid>\n" \
    "   <mm:trackNum>@5@</mm:trackNum>\n" \
    "   <mm:duration>@6@</mm:duration>\n" \
    "   <mm:issued>@7@</mm:issued>\n" \
    "   <mm:genre>@8@</mm:genre>\n" \
    "   <dc:description>@9@</dc:description>\n" \
    "   <mm:link>@10@</mm:link>\n" \
    "</mq:SubmitTrack>\n" 

#endif
