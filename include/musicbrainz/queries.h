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
 */
#define MBS_SelectArtist           \
        "http://musicbrainz.org/mm/mm-2.0#artistList []"

/**
 * Use this Select Query to select an album from an query that returns
 * a list of albums. Giving the argument 1 for the ordinal selects 
 * the first album in the list, 2 the second and so on. Use
 * MBE_AlbumXXXXXX queries to extract data after the select.
 */
#define MBS_SelectAlbum            \
        "http://musicbrainz.org/mm/mm-2.0#albumList []"

/**
 * Use this Select Query to select a track from an query that returns
 * a list of tracks. Giving the argument 1 for the ordinal selects 
 * the first track in the list, 2 the second and so on. Use
 * MBE_TrackXXXXXX queries to extract data after the select.
 */
#define MBS_SelectTrack            \
        "http://musicbrainz.org/mm/mm-2.0#trackList []"

/**
 * Use this Select Query to select a set of lyrics from an query that returns
 * a list of lyrics. Giving the argument 1 for the ordinal selects 
 * the first lyric in the list, 2 the second and so on. Use
 * MBE_LyricsXXXXXX queries to extract data after the select.
 */
#define MBS_SelectLyrics           \
        "http://musicbrainz.org/mm/mm-2.0#lyricList []"

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
 * Return the ID of the currently selected Album. The value of this
 * query is indeed empty!
 */
#define MBE_ArtistGetArtistId        \
        "" // yes, empty! 

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
 */
#define MBE_AlbumGetTrackId        \
        "http://musicbrainz.org/mm/mm-2.0#trackList [] "

/**
 * Return the track number of the nth track in the album. Requires a
 * track index ordinal. 1 for the first track, etc...
 */
#define MBE_AlbumGetTrackNum       \
        "http://musicbrainz.org/mm/mm-2.0#trackList [] http://musicbrainz.org/mm/mm-2.0#trackNum"

/**
 * Return the track name of the nth track in the album. Requires a
 * track index ordinal. 1 for the first track, etc...
 */
#define MBE_AlbumGetTrackName      \
        "http://musicbrainz.org/mm/mm-2.0#trackList [] http://purl.org/dc/elements/1.1/title"

/**
 * Return the artist name of the nth track in the album. Requires a
 * track index ordinal. 1 for the first track, etc...
 */
#define MBE_AlbumGetArtistName     \
        "http://musicbrainz.org/mm/mm-2.0#trackList [] http://purl.org/dc/elements/1.1/creator http://purl.org/dc/elements/1.1/title"

/**
 * Return the artist Id of the nth track in the album. Requires a
 * track index ordinal. 1 for the first track, etc...
 */
#define MBE_AlbumGetArtistId       \
        "http://musicbrainz.org/mm/mm-2.0#trackList [] http://purl.org/dc/elements/1.1/creator"

// artistList queries TBC!
// trackList queries TBC!

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
 * Server queries (queries must have argument substituted in them)
 * -------------------------------------------------------------------------
 */
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
 * Use this query to find artists by name. This function returns an artistList 
 * for the given artist name.
 * @param artistName The name of the artist to find.
 */
#define MBQ_FindArtistByName \
    "<mq:FindArtist>\n" \
    "   <mq:depth>@DEPTH@</mq:depth>\n" \
    "   <mq:artistName>@1@</mq:artistName>\n" \
    "</mq:FindArtist>\n" 

/**
 * Use this query to find albums by name. This function returns an albumList 
 * for the given album name. An optional artistName may also be given. If 
 * you do not wish to give an Artist name, pass an empty string for the
 * artistName.
 * @param artistName The name of the artist to find.
 * @param albumName The name of the album to find.
 */
#define MBQ_FindAlbumByName \
    "<mq:FindAlbum>\n" \
    "   <mq:depth>@DEPTH@</mq:depth>\n" \
    "   <mq:artistName>@1@</mq:artistName>\n" \
    "   <mq:albumName>@2@</mq:albumName>\n" \
    "</mq:FindAlbum>\n" 

/**
 * Use this query to find tracks by name. This function returns a trackList 
 * for the given track name. At least one artistName or one albumName or
 * both must also be given. If you leave artistName or albumName blank,
 * pass an empty string in its place.
 * @param artistName The name of the artist to find.
 * @param albumName The name of the album to find.
 * @param trackName The name of the track to find.
 */
#define MBQ_FindTrackByName \
    "<mq:FindTrack>\n" \
    "   <mq:depth>@DEPTH@</mq:depth>\n" \
    "   <mq:artistName>@1@</mq:artistName>\n" \
    "   <mq:albumName>@2@</mq:albumName>\n" \
    "   <mq:trackName>@3@</mq:trackName>\n" \
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
    "http://@URL@/artist/@1@" 

/** 
 * Retrieve an albumList from a given Album id 
 */
#define MBQ_GetAlbumById \
    "http://@URL@/album/@1@" 

/** 
 * Retrieve an trackList from a given Track id 
 */
#define MBQ_GetTrackById \
    "http://@URL@/track/@1@" 

/** 
 * Retrieve an trackList from a given TRM Id 
 */
#define MBQ_GetTrackByTRMId \
    "http://@URL@/trmid/@1@" 

/** 
 * Retrieve an lyricList from a given Track Id
 */
#define MBQ_GetSyncTextById \
    "http://@URL@/synctext/@1@" 

/**
 * Do a Metadata exchange with the MusicBrainz server. The user
 * must fill out as many of the fields as possible. All of the
 * fields but fileName, issued, genre, description are required.
 * If not all required fields are present, the server will not
 * accept the metadata into its Pending Table. However, the
 * server will attempt to look up any known information about
 * the track from the TRM ID, and return this data to the
 * user. The user may extract the information returned by the
 * server by using the MBE_MEXXXXXXX functions.
 * @param artistName The name of the artist for the given track. 
 * @param albumName The name of the album for the given track.
 * @param trackName The name of the track.
 * @param trmid The TRM Id of the track.
 * @param fileName The complete filename of the track.
 * @param issued The year the track was released
 * @param genre The genre that this track is classified as.
 * @param description A description associated with this track.
 * @param bitprint The Bitzi bitprint for this file. See mb_CalculateBitprint() 
          for details on this and the remaining arguments.
 * @param first20 The first 20 characters of this file encoded in hex.
 * @param fileSize The size of the file in bytes.
 * @param audioSha1 The sha1 value calculated for the audio contents.
 * @param duration The length of the track in milliseconds.
 * @param sampleRate The samplerate of this track in hertz.
 * @param bitRate The bitrate of this track in kbps.
 * @param channels The number of channels for this track. 2 = Stereo
 * @param vbr 1 if file is VBR, 0 otherwise 
 */
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
    "</mq:SubmitTrack>\n" 

#endif
