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
#define MBE_GetAlbumName           "http://purl.org/dc/elements/1.1/title"
#define MBE_GetAlbumID             "" // yes, empty! 
#define MBE_GetNumTracks           "http://musicbrainz.org/mm/mm-2.0#numTracks"
#define MBE_GetTrackID             "http://musicbrainz.org/mm/mm-2.0#trackList [] "
#define MBE_GetTrackNum            "http://musicbrainz.org/mm/mm-2.0#trackList [] http://musicbrainz.org/mm/mm-2.0#trackNum"
#define MBE_GetTrackName           "http://musicbrainz.org/mm/mm-2.0#trackList [] http://purl.org/dc/elements/1.1/title"
#define MBE_GetArtistName          "http://musicbrainz.org/mm/mm-2.0#trackList [] http://purl.org/dc/elements/1.1/creator http://purl.org/dc/elements/1.1/title"
#define MBE_GetArtistID            "http://musicbrainz.org/mm/mm-2.0#trackList [] http://purl.org/dc/elements/1.1/creator"

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
#define MBQ_GetCDInfoFromCDIndexID \
    "<mq:GetCDInfoFromId>" \
    "   <mm:cdindexId>@1@</mm:cdindexId>" \
    "</mq:GetCDInfoFromId>" 

#define MB_FindArtistByName \
    "<mq:FindArtistByName>" \
    "   <mm:artist>@1@</mm:artist>" \
    "</mq:FindArtistByName>" 

#define MB_FindAlbumByName \
    "<mq:FindAlbumByName>" \
    "   <mm:album>@1@</mm:album>" \
    "</mq:FindAlbumByName>" 

#define MB_FindAlbumsByArtistName \
    "<mq:FindAlbumsByArtistName>" \
    "   <mm:artist>@1@</mm:artist>" \
    "</mq:FindAlbumsByArtistName>" 

#define MB_FindTrackByName \
    "<mq:FindTrackByName>" \
    "   <mm:artist>@1@</mm:artist>" \
    "   <mm:album>@2@</mm:album>" \
    "   <mm:track>@3@</mm:track>" \
    "</mq:FindTrackByName>" 

#define MB_FindDistinctGUID \
    "<mq:FindDistinctGUID>" \
    "   <mm:artist>@1@</mm:artist>" \
    "   <mm:track>@2@</mm:track>" \
    "</mq:FindDistinctGUID>" 

#define MB_GetArtistById \
    "http://@URL@/rdf?artist=@1@" 

#define MB_GetAlbumById \
    "http://@URL@/rdf?album=@1@" 

#define MB_GetTrackById \
    "http://@URL@/rdf?track=@1@" 

#define MB_GetAlbumsByArtistId \
    "http://@URL@/rdf?albumsbyartist=@1@" 

#define MB_GetTrackByGUID \
    "http://@URL@/rdf?guid=@1@" 

#define MB_GetSyncTextById \
    "http://@URL@/rdf?synctext=@1@" 

#define MB_ExchangeMetadata \
    "<mq:ExchangeMetadata>" \
    "   <dc:title>@1@</dc:title>" \
    "   <mm:artist>@2@</mm:artist>" \
    "   <mm:album>@3@</mm:album>" \
    "   <mm:trackNum>@4@</mm:trackNum>" \
    "   <mm:guid>@5@</mm:guid>" \
    "   <mm:fileName>@6@</mm:fileName>" \
    "   <dc:date>@7@</dc:date>" \
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

#define MB_SubmitTrack \
    "<mq:SubmitTrack>" \
    "   <dc:Title>@1@</dc:Title>" \
    "   <mm:guid>@2@</mm:guid>" \
    "   <dc:creator>@3@</dc:creator>" \
    "   <mm:album>@4@</mm:Title>" \
    "   <mm:trackNum>@5@</mm:trackNum>" \
    "   <mm:duration>@6@</mm:duration>" \
    "   <dc:date>@7@</dc:date>" \
    "   <mm:genre>@8@</mm:genre>" \
    "   <dc:description>@9@</dc:description>" \
    "</mq:SubmitTrack>" 

#endif
