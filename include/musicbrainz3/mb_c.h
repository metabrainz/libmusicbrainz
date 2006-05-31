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
     * Consistency of string and int/bool getters
	 * Error messages
   * Returning of lists?
*/

typedef void *MBQuery;
typedef void *MBWebService;

typedef void *MBArtist;
typedef void *MBArtistAlias;
typedef void *MBTrack;
typedef void *MBRelease;
typedef void *MBUser;

/* === MusicBrainz::WebService === */

MB_API void
mb_webservice_init();

/* === MusicBrainz::Query === */

MB_API MBQuery
mb_query_new(MBWebService ws, const char *client_id);

MB_API void
mb_query_free(MBQuery query);

MB_API MBArtist
mb_query_get_artist_by_id(MBQuery query, const char *id);

MB_API MBRelease
mb_query_get_release_by_id(MBQuery query, const char *id);

MB_API MBTrack
mb_query_get_track_by_id(MBQuery query, const char *id);

/* === MusicBrainz::Artist === */

MB_API int
mb_artist_get_id(MBArtist artist, char *str, int len);

MB_API int
mb_artist_get_type(MBArtist artist, char *str, int len);

MB_API int
mb_artist_get_name(MBArtist artist, char *str, int len);

MB_API int
mb_artist_get_sortname(MBArtist artist, char *str, int len);

MB_API int
mb_artist_get_begin_date(MBArtist artist, char *str, int len);

MB_API int
mb_artist_get_end_date(MBArtist artist, char *str, int len);

/* === MusicBrainz::Release === */

MB_API int
mb_release_get_id(MBRelease release, char *str, int len);

MB_API int
mb_release_get_title(MBRelease release, char *str, int len);

MB_API int
mb_release_get_text_language(MBRelease release, char *str, int len);

MB_API int
mb_release_get_text_script(MBRelease release, char *str, int len);

MB_API int
mb_release_get_asin(MBRelease release, char *str, int len);

/* === MusicBrainz::Track === */

MB_API int
mb_track_get_id(MBTrack track, char *str, int len);

MB_API int
mb_track_get_title(MBTrack track, char *str, int len);

MB_API int
mb_track_get_duration(MBTrack track);

/* === MusicBrainz::ArtistAlias === */

MB_API int
mb_artist_alias_get_value(MBArtistAlias alias, char *str, int len);

MB_API int
mb_artist_alias_get_type(MBArtistAlias alias, char *str, int len);

MB_API int
mb_artist_alias_get_script(MBArtistAlias alias, char *str, int len);

/* === MusicBrainz::User === */

MB_API int
mb_user_get_name(MBUser user, char *str, int len);

MB_API int
mb_user_get_show_nag(MBUser user);

#ifdef __cplusplus
}
#endif

#endif
