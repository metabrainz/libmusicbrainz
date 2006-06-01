/*
 * MusicBrainz -- The Internet music metadatabase
 *
 * Copyright (C) 2006 Lukas Lalinsky
 *	
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA	 02111-1307	 USA
 *
 * $Id$
 */
 
#ifndef __MUSICBRAINZ3_MB_C_H__
#define __MUSICBRAINZ3_MB_C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <musicbrainz3/config.h>

/*
  TODO:
   * Type names: MBXxx, mb_xxx or mb_xxx_t?
   * Error handling? 
     * Error messages
   * Returning of lists?
*/

/* {{{ Typedefs */

typedef void *MBArtist;
typedef void *MBArtistAlias;
typedef void *MBArtistIncludes;
typedef void *MBDisc;
typedef void *MBEntity;
typedef void *MBQuery;
typedef void *MBRelation;
typedef void *MBRelease;
typedef void *MBReleaseEvent;
typedef void *MBReleaseIncludes;
typedef void *MBUser;
typedef void *MBTrack;
typedef void *MBTrackIncludes;
typedef void *MBWebService;

/* }}} */

/* {{{ MusicBrainz::WebService */

MB_API void
mb_webservice_init();

/* }}} */

/* {{{ MusicBrainz::Query */

/**
 * Creates a new instance of MBQuery.
 *
 * @see MusicBrainz::Query::Query
 */
MB_API MBQuery
mb_query_new(MBWebService ws, const char *client_id);

/**
 * Deletes the MBQuery instance.
 *
 * @see MusicBrainz::Query::~Query
 */
MB_API void
mb_query_free(MBQuery query);

/**
 * Returns an artist.
 * 
 * @see MusicBrainz::Query::getArtistById
 */
MB_API MBArtist
mb_query_get_artist_by_id(MBQuery query, const char *id, MBArtistIncludes inc);

/**
 * Returns an release.
 * 
 * @see MusicBrainz::Query::getReleaseById
 */
MB_API MBRelease
mb_query_get_release_by_id(MBQuery query, const char *id, MBReleaseIncludes inc);

/**
 * Returns an track.
 * 
 * @see MusicBrainz::Query::getTrackById
 */
MB_API MBTrack
mb_query_get_track_by_id(MBQuery query, const char *id, MBTrackIncludes inc);

/**
 * Returns information about a MusicBrainz user.
 * 
 * @see MusicBrainz::Query::getUserByName
 */
MB_API MBUser
mb_query_get_user_by_name(MBQuery query, const char *name);

/* }}} */

/* {{{ MusicBrainz::Artist */

/**
 * Deletes the MBArtist instance.
 */
MB_API void
mb_artist_free(MBArtist artist);

/**
 * Returns the artist's ID.
 *
 * @see MusicBrainz::Artist::getId	
 */
MB_API void
mb_artist_get_id(MBArtist artist, char *str, int len);

/**
 * Returns the artist's type.
 *
 * @see MusicBrainz::Artist::getType	
 */
MB_API void
mb_artist_get_type(MBArtist artist, char *str, int len);

/**
 * Returns the artist's name.
 *
 * @see MusicBrainz::Artist::getName	
 */
MB_API void
mb_artist_get_name(MBArtist artist, char *str, int len);

/**
 * Returns the artist's sort name.
 *
 * @see MusicBrainz::Artist::getSortName	
 */
MB_API void
mb_artist_get_sortname(MBArtist artist, char *str, int len);

/**
 * Returns the disambiguation attribute. 
 *
 * @see MusicBrainz::Artist::getDisambiguation
 */
MB_API void
mb_artist_get_disambiguation(MBArtist artist, char *str, int len);

/**
 * Returns a unique artist name (using disambiguation). 
 *
 * @see MusicBrainz::Artist::getUniqueName
 */
MB_API void
mb_artist_get_unique_name(MBArtist artist, char *str, int len);

/**
 * Returns the birth/foundation date. 
 *
 * @see MusicBrainz::Artist::getBeginDate
 */
MB_API void
mb_artist_get_begin_date(MBArtist artist, char *str, int len);

/**
 * Returns the death/dissolving date. 
 *
 * @see MusicBrainz::Artist::getEndDate
 */
MB_API void
mb_artist_get_end_date(MBArtist artist, char *str, int len);

/* }}} */

/* {{{ MusicBrainz::Release */

/**
 * Deletes the MBRelease instance.
 */
MB_API void
mb_release_free(MBRelease release);

/**
 * Returns the release's ID. 
 *
 * @see MusicBrainz::Release::getId
 */
MB_API void
mb_release_get_id(MBRelease release, char *str, int len);

/**
 * Returns the release's title. 
 *
 * @see MusicBrainz::Release::getTitle
 */
MB_API void
mb_release_get_title(MBRelease release, char *str, int len);

/**
 * Returns the language used in release and track titles. 
 *
 * @see MusicBrainz::Release::getTextLanguage
 */
MB_API void
mb_release_get_text_language(MBRelease release, char *str, int len);

/**
 * Returns the script used in release and track titles. 
 *
 * @see MusicBrainz::Release::getTextScript
 */
MB_API void
mb_release_get_text_script(MBRelease release, char *str, int len);

/**
 * Returns the Amazon shop identifier (ASIN). 
 *
 * @see MusicBrainz::Release::getAsin
 */
MB_API void
mb_release_get_asin(MBRelease release, char *str, int len);

/**
 * Returns the offset of the track list.
 *
 * @see MusicBrainz::Release::getTracksOffset
 */
MB_API int
mb_release_get_tracks_offset(MBRelease release);

/* }}} */

/* {{{ MusicBrainz::Track */

/**
 * Deletes the MBTrack instance.
 */
MB_API void
mb_track_free(MBTrack track);

/**
 * Returns the track's ID. 
 *
 * @see MusicBrainz::Track::getId
 */
MB_API void
mb_track_get_id(MBTrack track, char *str, int len);

/**
 * Returns the track's title. 
 *
 * @see MusicBrainz::Track::getTitle
 */
MB_API void
mb_track_get_title(MBTrack track, char *str, int len);

/**
 * Returns the track's duration. 
 *
 * @see MusicBrainz::Track::getDuration
 */
MB_API int
mb_track_get_duration(MBTrack track);

/* }}} */

/* {{{ MusicBrainz::ArtistAlias */

/**
 * Returns the alias.
 *
 * @see MusicBrainz::ArtistAlias::getValue
 */
MB_API void
mb_artist_alias_get_value(MBArtistAlias alias, char *str, int len);

/**
 * Returns the alias type. 
 *
 * @see MusicBrainz::ArtistAlias::getType
 */
MB_API void
mb_artist_alias_get_type(MBArtistAlias alias, char *str, int len);

/**
 * Returns the alias script.
 *
 * @see MusicBrainz::ArtistAlias::getScript
 */
MB_API void
mb_artist_alias_get_script(MBArtistAlias alias, char *str, int len);

/* }}} */

/* {{{ MusicBrainz::User */

/**
 * Deletes the MBUsers instance.
 */
MB_API void
mb_user_free(MBUser user);

/**
 * Returns the user name.
 *
 * @see MusicBrainz::User::getName
 */
MB_API void
mb_user_get_name(MBUser user, char *str, int len);

/**
 * Returns true if a nag screen should be displayed to the user.
 *
 * @see MusicBrainz::User::getShowNag
 */
MB_API int
mb_user_get_show_nag(MBUser user);

/* }}} */

/* {{{ MusicBrainz::ArtistIncludes */

MB_API MBArtistIncludes
mb_artist_includes_new();

MB_API void
mb_artist_includes_free(MBArtistIncludes inc);

MB_API MBArtistIncludes
mb_artist_includes_aliases(MBArtistIncludes inc);

MB_API MBArtistIncludes
mb_artist_includes_releases(MBArtistIncludes inc, const char *type);

MB_API MBArtistIncludes
mb_artist_includes_va_releases(MBArtistIncludes inc, const char *type);

MB_API MBArtistIncludes
mb_artist_includes_artist_relations(MBArtistIncludes inc);

MB_API MBArtistIncludes
mb_artist_includes_release_relations(MBArtistIncludes inc);

MB_API MBArtistIncludes
mb_artist_includes_track_relations(MBArtistIncludes inc);

MB_API MBArtistIncludes
mb_artist_includes_url_relations(MBArtistIncludes inc);

/* }}} */

/* {{{ MusicBrainz::ReleaseIncludes */

MB_API MBReleaseIncludes
mb_release_includes_new();

MB_API void
mb_release_includes_free(MBReleaseIncludes inc);

MB_API MBReleaseIncludes
mb_release_includes_artist(MBReleaseIncludes inc);

MB_API MBReleaseIncludes
mb_release_includes_counts(MBReleaseIncludes inc);

MB_API MBReleaseIncludes
mb_release_includes_release_events(MBReleaseIncludes inc);

MB_API MBReleaseIncludes
mb_release_includes_discs(MBReleaseIncludes inc);

MB_API MBReleaseIncludes
mb_release_includes_tracks(MBReleaseIncludes inc);

MB_API MBReleaseIncludes
mb_release_includes_artist_relations(MBReleaseIncludes inc);

MB_API MBReleaseIncludes
mb_release_includes_release_relations(MBReleaseIncludes inc);

MB_API MBReleaseIncludes
mb_release_includes_track_relations(MBReleaseIncludes inc);

MB_API MBReleaseIncludes
mb_release_includes_url_relations(MBReleaseIncludes inc);

/* }}} */

/* {{{ MusicBrainz::TrackIncludes */

MB_API MBTrackIncludes
mb_track_includes_new();

MB_API void
mb_track_includes_free(MBArtistIncludes inc);

MB_API MBTrackIncludes
mb_track_includes_artist(MBArtistIncludes inc);

MB_API MBTrackIncludes
mb_track_includes_releases(MBArtistIncludes inc);

MB_API MBTrackIncludes
mb_track_includes_puids(MBArtistIncludes inc);

MB_API MBTrackIncludes
mb_track_includes_artist_relations(MBArtistIncludes inc);

MB_API MBTrackIncludes
mb_track_includes_release_relations(MBTrackIncludes inc);

MB_API MBTrackIncludes
mb_track_includes_track_relations(MBTrackIncludes inc);

MB_API MBTrackIncludes
mb_track_includes_url_relations(MBTrackIncludes inc);

/* }}} */

/* {{{ MusicBrainz::ArtistAlias */

/**
 * Returns the country a release took place.
 *
 * @see MusicBrainz::ReleaseEvent::getCountry 
 */
MB_API void
mb_release_event_get_country(MBReleaseEvent releaseEvent, char *str, int len);

/**
 * Returns the date a release took place.
 *
 * @see MusicBrainz::ReleaseEvent::getDate
 */
MB_API void
mb_release_event_get_date(MBReleaseEvent releaseEvent, char *str, int len);

/* }}} */

/* {{{ MusicBrainz::Relation */

/**
 * Returns this relation's type.
 *
 * @see MusicBrainz::Relation::getType
 */
MB_API void
mb_relation_get_type(MBRelation relation, char *str, int len);

/**
 * Returns the target's ID.
 *
 * @see MusicBrainz::Relation::getTargetId
 */
MB_API void
mb_relation_get_target_id(MBRelation relation, char *str, int len);

/**
 * Returns the target's type.
 *
 * @see MusicBrainz::Relation::getTargetType
 */
MB_API void
mb_relation_get_target_type(MBRelation relation, char *str, int len);

/**
 * Returns the begin date.
 *
 * @see MusicBrainz::Relation::getBeginDate
 */
MB_API void
mb_relation_get_begin_date(MBRelation relation, char *str, int len);

/**
 * Returns the end date.
 *
 * @see MusicBrainz::Relation::getEndDate
 */
MB_API void
mb_relation_get_end_date(MBRelation relation, char *str, int len);

/**
 * Returns the reading direction.
 *
 * @see MusicBrainz::Relation::getDirection
 */
MB_API int
mb_relation_get_direction(MBRelation relation);

/**
 * Returns this relation's target object.
 *
 * @see MusicBrainz::Relation::getTarget
 */
MB_API MBEntity
mb_relation_get_target(MBRelation relation);

/* }}} */

/* {{{ MusicBrainz::Disc */

/**
 * Returns the MusicBrainz DiscID. 
 *
 * @see MusicBrainz::Disc::getId
 */
MB_API void
mb_disc_get_id(MBDisc disc, char *str, int len);

/**
 * Returns the length of the disc in sectors. 
 *
 * @see MusicBrainz::Disc::getSectors
 */
MB_API int
mb_disc_get_sectors(MBDisc disc);

/**
 * Returns the number of the first track on this disc.
 *
 * @see MusicBrainz::Disc::getFirstTrackNum
 */
MB_API int
mb_disc_get_first_track_num(MBDisc disc);

/**
 * Returns the number of the last track on this disc.
 *
 * @see MusicBrainz::Disc::getLastTrackNum
 */
MB_API int
mb_disc_get_last_track_num(MBDisc disc);

/* }}} */

#ifdef __cplusplus
}
#endif

#endif
