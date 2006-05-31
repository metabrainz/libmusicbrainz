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
 
#include <string.h>
#include <musicbrainz3/query.h>
#include <musicbrainz3/mb_c.h>

extern "C" {

using namespace std;
using namespace MusicBrainz;

/* A little bit of cpp goodness :) */

#define MB_C_FREE(TYPE1, TYPE2) \
	void \
	mb_##TYPE2##_free(MB##TYPE1 o) \
	{ \
		delete (TYPE1 *)o; \
	} 

#define MB_C_STR_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	int \
	mb_##TYPE2##_get_##PROP2(MB##TYPE1 o, char *str, int len) \
	{ \
		try { \
			strncpy(str, ((TYPE1 *)o)->get##PROP1().c_str(), len); \
			return 1; \
		} \
		catch (...) { \
			str[0] = '\0'; \
			return 0; \
		} \
	} 

#define MB_C_INT_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	int \
	mb_##TYPE2##_get_##PROP2(MB##TYPE1 o) \
	{ \
		try { \
			return ((TYPE1 *)o)->get##PROP1(); \
		} \
		catch (...) { \
			return 0; \
		} \
	} 

#define MB_C_BOOL_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	int \
	mb_##TYPE2##_get_##PROP2(MB##TYPE1 o) \
	{ \
		try { \
			return ((TYPE1 *)o)->get##PROP1() ? 1 : 0; \
		} \
		catch (...) { \
			return 0; \
		} \
	} 

/* === MusicBrainz::WebService === */

void
mb_webservice_init()
{
	WebService::init();
}

/* === MusicBrainz::Query === */

MBQuery
mb_query_new(MBWebService ws, const char *client_id)
{
	Query *query = new Query((WebService *)ws, client_id ? client_id : "");
	return (MBQuery)query;
}

MB_C_FREE(Query, query)

MBArtist
mb_query_get_artist_by_id(MBQuery q, const char *id)
{
	Query *query = (Query *)q;
	return (MBArtist)query->getArtistById(id);
}

MBRelease
mb_query_get_release_by_id(MBQuery q, const char *id)
{
	Query *query = (Query *)q;
	return (MBRelease)query->getReleaseById(id);
}

MBTrack
mb_query_get_track_by_id(MBQuery q, const char *id)
{
	Query *query = (Query *)q;
	return (MBTrack)query->getTrackById(id);
}

/* === MusicBrainz::Artist === */

MB_C_STR_GETTER(Artist, artist, Id, id)
MB_C_STR_GETTER(Artist, artist, Type, type)
MB_C_STR_GETTER(Artist, artist, Name, name)
MB_C_STR_GETTER(Artist, artist, SortName, sortname)
MB_C_STR_GETTER(Artist, artist, BeginDate, begin_date)
MB_C_STR_GETTER(Artist, artist, EndDate, end_date)

/* === MusicBrainz::Release === */

MB_C_STR_GETTER(Release, release, Id, id)
MB_C_STR_GETTER(Release, release, Title, title)
MB_C_STR_GETTER(Release, release, TextLanguage, text_language)
MB_C_STR_GETTER(Release, release, TextScript, text_script)
MB_C_STR_GETTER(Release, release, Asin, asin)

/* === MusicBrainz::Track === */

MB_C_STR_GETTER(Track, track, Id, id)
MB_C_STR_GETTER(Track, track, Title, title)
MB_C_INT_GETTER(Track, track, Duration, duration)

/* === MusicBrainz::ArtistAlias === */

MB_C_STR_GETTER(ArtistAlias, artist_alias, Value, value)
MB_C_STR_GETTER(ArtistAlias, artist_alias, Type, type)
MB_C_STR_GETTER(ArtistAlias, artist_alias, Script, script)

/* === MusicBrainz::User === */

MB_C_STR_GETTER(User, user, Name, name)
MB_C_BOOL_GETTER(User, user, ShowNag, show_nag)

}
