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

/* -------------------------------------------------------------------------
 * Select queries -- these whitespace seperated list macros are a list of
 * rdf predicates and/or ordinals (specified as []). These predicate lists
 * specify a path to traverse through an RDF graph (comprised of statements,
 * aka triples). Each select query starts at the top level resource and
 * 'selects' another node in the rdf graph by moving through the graph
 * as specified by the predicate list. The URI of the new node, will be
 * saved as the 'selected context'. Once a context has been selected,
 * you can use the MBE_ queries below to extract metadata out of a context.
 * -------------------------------------------------------------------------
 */

/**
 * Use this query to reset the current context back to the top level of
 * the response.
 */
#define MBS_Rewind           \
        "[REWIND]"

/**
 * Use this query to change the current context back one level.
 */
#define MBS_Back           \
        "[BACK]"

/**
 * Use this Select Query to select an artist from an query that returns
 * a list of artists. Giving the argument 1 for the ordinal selects 
 * the first artist in the list, 2 the second and so on. Use 
 * MBE_ArtistXXXXXX queries to extract data after the select.
 * @param ordinal This select requires one ordinal argument
 */
#define MBS_SelectArtist           \
        "http://musicbrainz.org/mm/mm-2.0#artistList []"

/**
 * Use this Select Query to select an album from an query that returns
 * a list of albums. Giving the argument 1 for the ordinal selects 
 * the first album in the list, 2 the second and so on. Use
 * MBE_AlbumXXXXXX queries to extract data after the select.
 * @param ordinal This select requires one ordinal argument
 */
#define MBS_SelectAlbum            \
        "http://musicbrainz.org/mm/mm-2.0#albumList []"

/**
 * Use this Select Query to select a track from an query that returns
 * a list of tracks. Giving the argument 1 for the ordinal selects 
 * the first track in the list, 2 the second and so on. Use
 * MBE_TrackXXXXXX queries to extract data after the select.
 * @param ordinal This select requires one ordinal argument
 */
#define MBS_SelectTrack            \
        "http://musicbrainz.org/mm/mm-2.0#trackList []"

/**
 * Use this Select Query to select an the corresponding artist from a track 
 * context. MBE_ArtistXXXXXX queries to extract data after the select.
 * @param ordinal 
 */
#define MBS_SelectTrackArtist      \
        "http://purl.org/dc/elements/1.1/creator"

/**
 * Use this Select Query to select a set of lyrics from an query that returns
 * a list of lyrics. Giving the argument 1 for the ordinal selects 
 * the first lyric in the list, 2 the second and so on. Use
 * MBE_LyricsXXXXXX queries to extract data after the select.
 * @param ordinal This select requires one ordinal argument
 */
#define MBS_SelectLyrics           \
        "http://musicbrainz.org/mm/mm-2.0#lyricList []"

/**
 * Use this Select Query to select a trmid from the list. 
 * @param ordinal This select requires one ordinal argument
 */
#define MBS_SelectTrmid           \
        "http://musicbrainz.org/mm/mm-2.0#trmidList []"

/* -------------------------------------------------------------------------
 * General top level queries -- Internal use only.
 * -------------------------------------------------------------------------
 */
/** 
 * Internal use only.
 */
#define MBE_QuerySubject           \
        "http://musicbrainz.org/mm/mq-1.0#Result"
/** 
 * Internal use only.
 */
#define MBE_GetError               \
        "http://musicbrainz.org/mm/mq-1.0#error"
/** 
 * Internal use only.
 */
#define MBE_GetStatus              \
        "http://musicbrainz.org/mm/mq-1.0#status"


/* -------------------------------------------------------------------------
 * Queries used to determine the number of items returned
 * by a query.
 * -------------------------------------------------------------------------
 */
/**
 * Return the number of artist returned in this query.
 */
#define MBE_GetNumArtists     \
        "http://musicbrainz.org/mm/mm-2.0#artistList [COUNT]"

/**
 * Return the number of albums returned in this query.
 */
#define MBE_GetNumAlbums      \
        "http://musicbrainz.org/mm/mm-2.0#albumList [COUNT]"

/**
 * Return the number of tracks returned in this query.
 */
#define MBE_GetNumTracks      \
        "http://musicbrainz.org/mm/mm-2.0#trackList [COUNT]"

/**
 * Return the number of lyrics returned in this query.
 */
#define MBE_GetNumLyrics      \
        "http://musicbrainz.org/mm/mm-2.0#trackList [COUNT]"

/**
 * Return the number of trmids returned in this query.
 */
#define MBE_GetNumTrmids      \
        "http://musicbrainz.org/mm/mm-2.0#trmidList [COUNT]"

/* -------------------------------------------------------------------------
 * artistList queries
 * -------------------------------------------------------------------------
 */

/**
 * Return the name of the currently selected Album
 */
#define MBE_ArtistGetArtistName      \
        "http://purl.org/dc/elements/1.1/title"

/**
 * Return the name of the currently selected Album
 */
#define MBE_ArtistGetArtistSortName      \
        "http://musicbrainz.org/mm/mm-2.0#sortName"

/**
 * Return the ID of the currently selected Album. The value of this
 * query is indeed empty!
 */
#define MBE_ArtistGetArtistId        \
        "" // yes, empty! 

/**
 * Return the name of the nth album. Requires an ordinal argument to select
 * an album from a list of albums in the current artist
 * @param ordinal This select requires one ordinal argument to select an album
 */
#define MBE_ArtistGetAlbumName      \
        "http://musicbrainz.org/mm/mm-2.0#albumList [] http://purl.org/dc/elements/1.1/title"

/**
 * Return the ID of the nth album. Requires an ordinal argument to select
 * an album from a list of albums in the current artist
 * @param ordinal This select requires one ordinal argument to select an album
 */
#define MBE_ArtistGetAlbumId      \
        "http://musicbrainz.org/mm/mm-2.0#albumList []"

/* -------------------------------------------------------------------------
 * albumList queries
 * -------------------------------------------------------------------------
 */

/**
 * Return the name of the currently selected Album
 */
#define MBE_AlbumGetAlbumName      \
        "http://purl.org/dc/elements/1.1/title"

/**
 * Return the ID of the currently selected Album. The value of this
 * query is indeed empty!
 */
#define MBE_AlbumGetAlbumId        \
        "" // yes, empty! 

/**
 * Return the mumber of tracks in the currently selected Album
 */
#define MBE_AlbumGetNumTracks      \
        "http://musicbrainz.org/mm/mm-2.0#trackList [COUNT]"

/**
 * Return the Id of the nth track in the album. Requires a
 * track index ordinal. 1 for the first track, etc...
 * @param ordinal This select requires one ordinal argument to select a track
 */
#define MBE_AlbumGetTrackId        \
        "http://musicbrainz.org/mm/mm-2.0#trackList [] "

/**
 * Return the track number of the nth track in the album. Requires a
 * track index ordinal. 1 for the first track, etc...
 * @param ordinal This select requires one ordinal argument to select a track
 */
#define MBE_AlbumGetTrackNum       \
        "http://musicbrainz.org/mm/mm-2.0#trackList [] http://musicbrainz.org/mm/mm-2.0#trackNum"

/**
 * Return the track name of the nth track in the album. Requires a
 * track index ordinal. 1 for the first track, etc...
 * @param ordinal This select requires one ordinal argument to select a track
 */
#define MBE_AlbumGetTrackName      \
        "http://musicbrainz.org/mm/mm-2.0#trackList [] http://purl.org/dc/elements/1.1/title"

/**
 * Return the track duration of the nth track in the album. Requires a
 * track index ordinal. 1 for the first track, etc...
 * @param ordinal This select requires one ordinal argument to select a track
 */
#define MBE_AlbumGetTrackDuration       \
        "http://musicbrainz.org/mm/mm-2.0#trackList [] http://musicbrainz.org/mm/mm-2.0#duration"

/**
 * Return the artist name of the nth track in the album. Requires a
 * track index ordinal. 1 for the first track, etc...
 * @param ordinal This select requires one ordinal argument to select a track
 */
#define MBE_AlbumGetArtistName     \
        "http://musicbrainz.org/mm/mm-2.0#trackList [] http://purl.org/dc/elements/1.1/creator http://purl.org/dc/elements/1.1/title"

/**
 * Return the artist sortname of the nth track in the album. Requires a
 * track index ordinal. 1 for the first track, etc...
 * @param ordinal This select requires one ordinal argument to select a track
 */
#define MBE_AlbumGetArtistSortName \
        "http://musicbrainz.org/mm/mm-2.0#trackList [] http://purl.org/dc/elements/1.1/creator http://musicbrainz.org/mm/mm-2.0#sortName"

/**
 * Return the artist Id of the nth track in the album. Requires a
 * track index ordinal. 1 for the first track, etc...
 * @param ordinal This select requires one ordinal argument to select a track
 */
#define MBE_AlbumGetArtistId       \
        "http://musicbrainz.org/mm/mm-2.0#trackList [] http://purl.org/dc/elements/1.1/creator"

/* -------------------------------------------------------------------------
 * trackList queries
 * -------------------------------------------------------------------------
 */

/**
 * Return the name of the currently selected track
 */
#define MBE_TrackGetTrackName      \
        "http://purl.org/dc/elements/1.1/title"

/**
 * Return the ID of the currently selected track. The value of this
 * query is indeed empty!
 */
#define MBE_TrackGetTrackId        \
        "" // yes, empty! 

/**
 * Return the track number in the currently selected track
 */
#define MBE_TrackGetTrackNum      \
        "http://musicbrainz.org/mm/mm-2.0#trackNum"

/**
 * Return the track duration in the currently selected track
 */
#define MBE_TrackGetTrackDuration \
        "http://musicbrainz.org/mm/mm-2.0#duration"

/**
 * Return the name of the artist for this track. 
 */
#define MBE_TrackGetArtistName      \
        "http://purl.org/dc/elements/1.1/creator http://purl.org/dc/elements/1.1/title"

/**
 * Return the sortname of the artist for this track. 
 */
#define MBE_TrackGetArtistSortName      \
        "http://purl.org/dc/elements/1.1/creator http://musicbrainz.org/mm/mm-2.0#sortName"

/**
 * Return the Id of the artist for this track. 
 */
#define MBE_TrackGetArtistId      \
        "http://purl.org/dc/elements/1.1/creator"

/**
 * Return the name of the album for this track. Requires an ordinal to
 * select which album to retrieve the name from.
 * @param ordinal This select requires one ordinal argument to select an album 
 */
#define MBE_TrackGetAlbumName      \
        "http://purl.org/dc/elements/1.1/creator http://musicbrainz.org/mm/mm-2.0#albumList [] http://purl.org/dc/elements/1.1/title"

/**
 * Return the Id of the album for this track. Requires an ordinal to
 * select which album to retrieve the name from.
 * @param ordinal This select requires one ordinal argument to select an album 
 */
#define MBE_TrackGetAlbumId      \
        "http://purl.org/dc/elements/1.1/creator http://musicbrainz.org/mm/mm-2.0#albumList []"

/**
 * Return the track duration in the currently selected track
 */
#define MBE_TrackGetTrackDuration      \
        "http://musicbrainz.org/mm/mm-2.0#duration"


/* -------------------------------------------------------------------------
 * ExchangeMetadata queries
 * -------------------------------------------------------------------------
 */
/**
 * return the artist name for the exchanged metadata item
 */
#define MBE_MEGetArtistName        \
        "http://musicbrainz.org/mm/mq-1.0#artistName"
/**
 * return the album name for the exchanged metadata item
 */
#define MBE_MEGetAlbumName         \
        "http://musicbrainz.org/mm/mq-1.0#albumName"
/**
 * return the track name for the exchanged metadata item
 */
#define MBE_MEGetTrackName         \
        "http://musicbrainz.org/mm/mq-1.0#trackName"
/**
 * return the track number for the exchanged metadata item
 */
#define MBE_MEGetTrackNum          \
        "http://musicbrainz.org/mm/mm-2.0#trackNum"
/**
 * return the TRM ID for the exchanged metadata item
 */
#define MBE_MEGetTRMId             \
        "http://musicbrainz.org/mm/mm-2.0#trmid"
/**
 * return the duration in milliseconds for the exchanged metadata item
 */
#define MBE_MEGetDuration          \
        "http://musicbrainz.org/mm/mm-2.0#duration"
/**
 * return the release year for the exchanged metadata item
 */
#define MBE_MEGetYear              \
        "http://musicbrainz.org/mm/mm-2.0#issued"
/**
 * return the genre for the exchanged metadata item
 */
#define MBE_MEGetGenre             \
        "http://musicbrainz.org/mm/mm-2.0#genre"
/**
 * return the description for the exchanged metadata item
 */
#define MBE_MEGetDescription       \
        "http://purl.org/dc/elements/1.1/description"

/* -------------------------------------------------------------------------
 * Quick track/trm queries
 * -------------------------------------------------------------------------
 */

/**
 * Return the name of the aritst
 */
#define MBE_QuickGetArtistName      \
        "http://musicbrainz.org/mm/mq-1.0#artistName"

/**
 * Return the name of the aritst
 */
#define MBE_QuickGetAlbumName      \
        "http://musicbrainz.org/mm/mq-1.0#albumName"

/**
 * Return the name of the aritst
 */
#define MBE_QuickGetTrackName      \
        "http://musicbrainz.org/mm/mq-1.0#trackName"

/**
 * Return the name of the aritst
 */
#define MBE_QuickGetTrackNum       \
        "http://musicbrainz.org/mm/mm-2.0#trackNum"

/**
 * Return the MB track id
 */
#define MBE_QuickGetTrackId       \
        "http://musicbrainz.org/mm/mm-2.0#trackid"

/**
 * Return the track duration
 */
#define MBE_QuickGetTrackDuration       \
        "http://musicbrainz.org/mm/mm-2.0#duration"

/* -------------------------------------------------------------------------
 * Extract queries for the MBQ_GetCDTOC query
 * -------------------------------------------------------------------------
 */
/**
 * return the CDIndex ID from the table of contents from the CD
 */
#define MBE_TOCGetCDIndexId           \
        "http://musicbrainz.org/mm/mm-2.0#cdindexId"
/**
 * return the first track number from the table of contents from the CD
 */
#define MBE_TOCGetFirstTrack          \
        "http://musicbrainz.org/mm/mm-2.0#firstTrack"
/**
 * return the last track number (total number of tracks on the CD) 
 * from the table of contents from the CD
 */
#define MBE_TOCGetLastTrack           \
        "http://musicbrainz.org/mm/mm-2.0#lastTrack"
/**
 * return the sector offset from the nth track. One ordinal argument must
 * be given to specify the track. Track 1 is a special lead-out track,
 * and the actual track 1 on a CD can be retrieved as track 2 and so forth.
 */
#define MBE_TOCGetTrackSectorOffset   \
        "http://musicbrainz.org/mm/mm-2.0#toc [] http://musicbrainz.org/mm/mm-2.0#sectorOffset"
/**
 * return the number of sectors for the nth track. One ordinal argument must
 * be given to specify the track. Track 1 is a special lead-out track,
 * and the actual track 1 on a CD can be retrieved as track 2 and so forth.
 */
#define MBE_TOCGetTrackNumSectors     \
        "http://musicbrainz.org/mm/mm-2.0#toc [] http://musicbrainz.org/mm/mm-2.0#numSectors"

/* -------------------------------------------------------------------------
 * Extract queries for the MBQ_AuthenticateQuery query
 * -------------------------------------------------------------------------
 */
/**
 * return the Session Id from the Auth Query. This query will be used 
 * internally by the client library.
 */
#define MBE_AuthGetSessionId  "http://musicbrainz.org/mm/mq-1.0#sessionId"

/**
 * return the Auth Challenge data from the Auth Query This query will be used 
 * internally by the client library.
 */
#define MBE_AuthGetChallenge  "http://musicbrainz.org/mm/mq-1.0#authChallenge"

/* -------------------------------------------------------------------------
 * Local queries (queries are automatically generated)
 * -------------------------------------------------------------------------
 */
/**
 * Use this query to look up a CD from MusicBrainz. This query will
 * examine the CD-ROM in the CD-ROM drive specified by mb_SetDevice
 * and then send the CD-ROM data to the server. The server will then
 * find any matching CDs and return then as an albumList.
 */
#define MBQ_GetCDInfo              \
        "@CDINFO@"
/**
 * Use this query to examine the table of contents of a CD. This query will
 * examine the CD-ROM in the CD-ROM drive specified by mb_SetDevice, and
 * then let the use extract data from the table of contents using the
 * MBQ_TOCXXXXX functions. No live net connection is required for this query.
 */
#define MBQ_GetCDTOC               \
        "@LOCALCDINFO@"
/**
 * Internal use only. (For right now)
 */
#define MBQ_AssociateCD            \
        "@CDINFOASSOCIATECD@"

/* -------------------------------------------------------------------------
 * Server queries (queries must have argument(s) substituted in them)
 * -------------------------------------------------------------------------
 */

/**
 * This query is use to start an authenticated session with the MB server.
 * The username is sent to the server, and the server responds with 
 * session id and a challenge sequence that the client needs to use to create 
 * a session key. The session key and session id need to be provided with
 * the MBQ_SubmitXXXX functions in order to give moderators/users credit
 * for their submissions. This query will be carried out by the client
 * libary automatically -- you should not need to use it.
 * @param username -- the name of the user who would like to submit data.
 */
#define MBQ_Authenticate \
    "<mq:AuthenticateQuery>\n" \
    "   <mq:username>@1@</mq:username>\n" \
    "</mq:AuthenticateQuery>\n" 

/**
 * Use this query to return an albumList for the given CD Index Id
 * @param cdindexId The cdindex id to look up at the remote server.
 */
#define MBQ_GetCDInfoFromCDIndexId \
    "<mq:GetCDInfo>\n" \
    "   <mq:depth>@DEPTH@</mq:depth>\n" \
    "   <mm:cdindexId>@1@</mm:cdindexId>\n" \
    "</mq:GetCDInfo>\n" 

/**
 * Use this query to return the basic metadata information (artistname,
 * albumname, trackname, tracknumber) for a given trm id. Optionally, 
 * you can also specifiy the basic artist metadata, so that if the server
 * cannot match on the TRM id, it will attempt to match based on the basic
 * metadata.
 * @param trmid The TRM id for the track to be looked up
 * @param artistName The name of the artist
 * @param albumName The name of the album
 * @param trackName The name of the track
 * @param trackNum The number of the track
 */
#define MBQ_QuickTrackInfoFromTRMId \
    "<mq:QuickTrackInfoFromTRMId>\n" \
    "   <mm:trmid>@1@</mm:trmid>\n" \
    "   <mq:artistName>@2@</mq:artistName>\n" \
    "   <mq:albumName>@3@</mq:albumName>\n" \
    "   <mq:trackName>@4@</mq:trackName>\n" \
    "   <mm:trackNum>@5@</mm:trackNum>\n" \
    "   <mm:duration>@6@</mm:duration>\n" \
    "</mq:QuickTrackInfoFromTRMId>\n" 

/**
 * Use this query to return the basic metadata information (artistname,
 * albumname, trackname, tracknumber) for a given track mb id
 * @param trackid The MB track id for the track to be looked up
 */
#define MBQ_QuickTrackInfoFromTrackId \
    "<mq:QuickTrackInfoFromTrackId>\n" \
    "   <mm:trackid>@1@</mm:trackid>\n" \
    "   <mm:albumid>@2@</mm:albumid>\n" \
    "</mq:QuickTrackInfoFromTrackId>\n" 

/**
 * Use this query to find artists by name. This function returns an artistList 
 * for the given artist name.
 * @param artistName The name of the artist to find.
 */
#define MBQ_FindArtistByName \
    "<mq:FindArtist>\n" \
    "   <mq:depth>@DEPTH@</mq:depth>\n" \
    "   <mq:artistName>@1@</mq:artistName>\n" \
    "   <mq:maxItems>@MAX_ITEMS@</mq:maxItems>\n" \
    "</mq:FindArtist>\n" 

/**
 * Use this query to find albums by name. This function returns an albumList 
 * for the given album name. 
 * @param albumName The name of the album to find.
 */
#define MBQ_FindAlbumByName \
    "<mq:FindAlbum>\n" \
    "   <mq:depth>@DEPTH@</mq:depth>\n" \
    "   <mq:maxItems>@MAX_ITEMS@</mq:maxItems>\n" \
    "   <mq:albumName>@1@</mq:albumName>\n" \
    "</mq:FindAlbum>\n" 

/**
 * Use this query to find tracks by name. This function returns a trackList 
 * for the given track name. 
 * @param trackName The name of the track to find.
 */
#define MBQ_FindTrackByName \
    "<mq:FindTrack>\n" \
    "   <mq:depth>@DEPTH@</mq:depth>\n" \
    "   <mq:maxItems>@MAX_ITEMS@</mq:maxItems>\n" \
    "   <mq:trackName>@1@</mq:trackName>\n" \
    "</mq:FindTrack>\n" 

/**
 * Use this function to find TRM Ids that match a given artistName
 * and trackName, This query returns a trmidList.
 * @param artistName The name of the artist to find.
 * @param trackName The name of the track to find.
 */
#define MBQ_FindDistinctTRMId \
    "<mq:FindDistinctTRMID>\n" \
    "   <mq:depth>@DEPTH@</mq:depth>\n" \
    "   <mq:artistName>@1@</mq:artistName>\n" \
    "   <mq:trackName>@2@</mq:trackName>\n" \
    "</mq:FindDistinctTRMID>\n" 

/** 
 * Retrieve an artistList from a given Artist id 
 */
#define MBQ_GetArtistById \
    "http://@URL@/artist/@1@/@DEPTH@" 

/** 
 * Retrieve an albumList from a given Album id 
 */
#define MBQ_GetAlbumById \
    "http://@URL@/album/@1@/@DEPTH@" 

/** 
 * Retrieve an trackList from a given Track id 
 */
#define MBQ_GetTrackById \
    "http://@URL@/track/@1@/@DEPTH@" 

/** 
 * Retrieve an trackList from a given TRM Id 
 */
#define MBQ_GetTrackByTRMId \
    "http://@URL@/trmid/@1@/@DEPTH@" 

/** 
 * Retrieve an lyricList from a given Track Id
 */
#define MBQ_GetSyncTextById \
    "   <mm:cdindexId>@1@</mm:cdindexId>\n" \
    "http://@URL@/synctext/@1@/@DEPTH@" 

/**
 * Look up a track using only a TRM ID. This query returns the same
 * information as the ExchangeMetadata query, but no metadata is sent
 * to the server.
 * @param trmid The TRM Id of the track.
 */
#define MBQ_LookupMetadata \
    "<mq:LookupMetadata>\n" \
    "   <mm:trmid>@1@</mm:trmid>\n" \
    "</mq:LookupMetadata>\n" 

/** 
 * Internal use only.
 */
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
    "   <mq:sessionId>@SESSID@</mq:sessionId>\n" \
    "   <mq:sessionKey>@SESSKEY@</mq:sessionKey>\n" \
    "</mq:SubmitTrack>\n" 

/** 
 * Submit a single TrackId, TRM Id pair to MusicBrainz. This query can
 * handle only one pair at a time, which is inefficient. The user may wish
 * to create the query RDF text by hand and provide more than one pair
 * in the rdf:Bag, since the server can handle up to 1000 pairs in one
 * query.
 * @param TrackGID  The Global ID field of the track
 * @param trmid     The TRM Id of the track.
 */
#define MBQ_SubmitTrackTRMId \
    "<mq:SubmitTRMList>\n" \
    " <mm:trmList>\n" \
    "  <rdf:Bag>\n" \
    "   <rdf:li>\n" \
    "    <mq:trmTrackPair>\n" \
    "     <mm:trackid>@1@</mm:trackid>\n" \
    "     <mm:trmid>@2@</mm:trmid>\n" \
    "    </mq:trmTrackPair>\n" \
    "   </rdf:li>\n" \
    "  </rdf:Bag>\n" \
    " </mm:trmList>\n" \
    " <mq:sessionId>@SESSID@</mq:sessionId>\n" \
    " <mq:sessionKey>@SESSKEY@</mq:sessionKey>\n" \
    "</mq:SubmitTRMList>\n" 

#endif
