/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include "musicbrainz4/Query.h"

#include "musicbrainz4/mb4_c.h"

#include <string.h>

#include "musicbrainz4/Alias.h"
#include "musicbrainz4/AliasList.h"
#include "musicbrainz4/Annotation.h"
#include "musicbrainz4/AnnotationList.h"
#include "musicbrainz4/Artist.h"
#include "musicbrainz4/ArtistList.h"
#include "musicbrainz4/ArtistCredit.h"
#include "musicbrainz4/Attribute.h"
#include "musicbrainz4/AttributeList.h"
#include "musicbrainz4/CDStub.h"
#include "musicbrainz4/CDStubList.h"
#include "musicbrainz4/Collection.h"
#include "musicbrainz4/CollectionList.h"
#include "musicbrainz4/Disc.h"
#include "musicbrainz4/DiscList.h"
#include "musicbrainz4/FreeDBDisc.h"
#include "musicbrainz4/FreeDBDiscList.h"
#include "musicbrainz4/ISRC.h"
#include "musicbrainz4/ISRCList.h"
#include "musicbrainz4/Label.h"
#include "musicbrainz4/LabelList.h"
#include "musicbrainz4/LabelInfo.h"
#include "musicbrainz4/LabelInfoList.h"
#include "musicbrainz4/Lifespan.h"
#include "musicbrainz4/Medium.h"
#include "musicbrainz4/MediumList.h"
#include "musicbrainz4/Message.h"
#include "musicbrainz4/Metadata.h"
#include "musicbrainz4/NameCredit.h"
#include "musicbrainz4/NameCreditList.h"
#include "musicbrainz4/NonMBTrack.h"
#include "musicbrainz4/NonMBTrackList.h"
#include "musicbrainz4/PUID.h"
#include "musicbrainz4/PUIDList.h"
#include "musicbrainz4/Rating.h"
#include "musicbrainz4/Recording.h"
#include "musicbrainz4/RecordingList.h"
#include "musicbrainz4/Relation.h"
#include "musicbrainz4/RelationList.h"
#include "musicbrainz4/RelationListList.h"
#include "musicbrainz4/Release.h"
#include "musicbrainz4/ReleaseGroup.h"
#include "musicbrainz4/ReleaseGroupList.h"
#include "musicbrainz4/Tag.h"
#include "musicbrainz4/TagList.h"
#include "musicbrainz4/TextRepresentation.h"
#include "musicbrainz4/Track.h"
#include "musicbrainz4/TrackList.h"
#include "musicbrainz4/UserRating.h"
#include "musicbrainz4/UserTag.h"
#include "musicbrainz4/UserTagList.h"
#include "musicbrainz4/Work.h"
#include "musicbrainz4/WorkList.h"

std::string GetMapName(std::map<std::string,std::string> Map, int Item)
{
	std::string Ret;

	if (Item<(int)Map.size())
	{
		std::map<std::string,std::string>::const_iterator ThisItem=Map.begin();

		int count=0;

		while (count<Item)
		{
			++count;
			++ThisItem;
		}

		Ret=(*ThisItem).first;
	}

	return Ret;
}

std::string GetMapValue(std::map<std::string,std::string> Map, int Item)
{
	std::string Ret;

	if (Item<(int)Map.size())
	{
		std::map<std::string,std::string>::const_iterator ThisItem=Map.begin();

		int count=0;

		while (count<Item)
		{
			++count;
			++ThisItem;
		}

		Ret=(*ThisItem).second;
	}

	return Ret;
}

#define MB4_C_DELETE(TYPE1, TYPE2) \
	void \
	mb4_##TYPE2##_delete(Mb4##TYPE1 o) \
	{ \
		delete (MusicBrainz4::C##TYPE1 *)o; \
	}

#define MB4_C_CLONE(TYPE1, TYPE2) \
	Mb4##TYPE1 \
	mb4_##TYPE2##_clone(Mb4##TYPE1 o) \
	{ \
		if (o) \
			return (Mb4##TYPE1)new MusicBrainz4::C##TYPE1(*(MusicBrainz4::C##TYPE1 *)o); \
		return 0;\
	}

#define MB4_C_STR_SETTER(TYPE1, TYPE2, PROP1, PROP2) \
	void \
	mb4_##TYPE2##_set_##PROP2(Mb4##TYPE1 o, const char *str) \
	{ \
		if (o) \
		{ \
			try { \
				((MusicBrainz4::C##TYPE1 *)o)->Set##PROP1(str); \
			} \
			catch (...) { \
			} \
		} \
	}

#define MB4_C_INT_SETTER(TYPE1, TYPE2, PROP1, PROP2) \
	void \
	mb4_##TYPE2##_set_##PROP2(Mb4##TYPE1 o, int i) \
	{ \
		if (o) \
		{ \
			try { \
				((MusicBrainz4::C##TYPE1 *)o)->Set##PROP1(i); \
			} \
			catch (...) { \
			} \
		} \
	}

#define MB4_C_STR_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	int \
	mb4_##TYPE2##_get_##PROP2(Mb4##TYPE1 o, char *str, int len) \
	{ \
		int ret=0; \
		if (str) \
			*str=0; \
		if (o) \
		{ \
			try { \
				ret=((MusicBrainz4::C##TYPE1 *)o)->PROP1().length(); \
				if (str && len) \
				{ \
					strncpy(str, ((MusicBrainz4::C##TYPE1 *)o)->PROP1().c_str(), len); \
					str[len-1]='\0'; \
				} \
			} \
			catch (...) { \
				str[0] = '\0'; \
			} \
		} \
		return ret; \
	}

#define MB4_C_INT_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	int \
	mb4_##TYPE2##_get_##PROP2(Mb4##TYPE1 o) \
	{ \
		if (o) \
		{ \
			try { \
				return ((MusicBrainz4::C##TYPE1 *)o)->PROP1(); \
			} \
			catch (...) { \
			} \
		} \
		return 0; \
	}

#define MB4_C_DOUBLE_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	double \
	mb4_##TYPE2##_get_##PROP2(Mb4##TYPE1 o) \
	{ \
		if (o) \
		{ \
			try { \
				return ((MusicBrainz4::C##TYPE1 *)o)->PROP1(); \
			} \
			catch (...) { \
			} \
		} \
		return 0; \
	}

#define MB4_C_BOOL_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	unsigned char \
	mb4_##TYPE2##_get_##PROP2(Mb##TYPE1 o) \
	{ \
		if (o) \
		{ \
			try { \
				return ((TYPE1 *)o)->PROP1() ? 1 : 0; \
			} \
			catch (...) { \
				return 0; \
			} \
		} \
	}

#define MB4_C_OBJ_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	Mb4##PROP1 \
	mb4_##TYPE2##_get_##PROP2(Mb4##TYPE1 o) \
	{ \
		if (o) \
		{ \
			try { \
				return (Mb4##PROP1)((MusicBrainz4::C##TYPE1 *)o)->PROP1(); \
			} \
			catch (...) { \
			} \
		} \
		return (Mb4##PROP1)0; \
	}

#define MB4_C_LIST_GETTER(TYPE1, TYPE2) \
	void \
	mb4_##TYPE2##_list_delete(Mb4##TYPE1 o) \
	{ \
		delete (MusicBrainz4::C##TYPE1##List *)o; \
	} \
	int \
	mb4_##TYPE2##_list_size(Mb4##TYPE1##List List) \
	{ \
		if (List) \
		{ \
			try { \
				return ((MusicBrainz4::C##TYPE1##List *)List)->NumItems(); \
			} \
			catch (...) { \
				return 0; \
			} \
		} \
		return 0; \
	} \
 \
	Mb4##TYPE1 \
	mb4_##TYPE2##_list_item(Mb4##TYPE1##List List, int Item) \
	{ \
		if (List) \
		{ \
			try { \
				return ((MusicBrainz4::C##TYPE1##List *)List)->Item(Item); \
			} \
			catch (...) { \
				return (Mb4##TYPE1)0; \
			} \
		} \
		return (Mb4##TYPE1)0; \
	} \
	int \
	mb4_##TYPE2##_list_get_count(Mb4##TYPE1##List List) \
	{ \
		if (List) \
		{ \
			try { \
				return ((MusicBrainz4::C##TYPE1##List *)List)->Count(); \
			} \
			catch (...) { \
				return 0; \
			} \
		} \
		return 0; \
	} \
 \
	int \
	mb4_##TYPE2##_list_get_offset(Mb4##TYPE1##List List) \
	{ \
		if (List) \
		{ \
			try { \
				return ((MusicBrainz4::C##TYPE1##List *)List)->Offset(); \
			} \
			catch (...) { \
				return 0; \
			} \
		} \
		return 0; \
	} \
 \

#define MB4_C_EXT_GETTER(PROP1, PROP2) \
	int \
	mb4_entity_ext_##PROP2##s_size(Mb4Entity o) \
	{ \
		if (o) \
		{ \
			return ((MusicBrainz4::CEntity *)o)->Ext##PROP1##s().size(); \
		} \
		return 0; \
	} \
	int \
	mb4_entity_ext_##PROP2##_name(Mb4Entity o, int Item, char *str, int len) \
	{ \
		int ret=0; \
		if (str) \
			*str=0; \
		if (o) \
		{ \
			std::map<std::string,std::string> Items=((MusicBrainz4::CEntity *)o)->Ext##PROP1##s(); \
			std::string Name=GetMapName(Items,Item); \
			ret=Name.length(); \
			if (str && len) \
			{ \
				strncpy(str, Name.c_str(), len); \
				str[len-1]='\0'; \
			} \
		} \
		return ret; \
	} \
	int \
	mb4_entity_ext_##PROP2##_value(Mb4Entity o, int Item, char *str, int len) \
	{ \
		int ret=0; \
		if (str) \
			*str=0; \
		if (o) \
		{ \
			std::map<std::string,std::string> Items=((MusicBrainz4::CEntity *)o)->Ext##PROP1##s(); \
			std::string Name=GetMapValue(Items,Item); \
			ret=Name.length(); \
			if (str && len) \
			{ \
				strncpy(str, Name.c_str(), len); \
				str[len-1]='\0'; \
			} \
		} \
		return ret; \
	} \

