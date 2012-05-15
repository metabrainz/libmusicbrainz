/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libmusicbrainz5 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include "musicbrainz5/defines.h"

#include "musicbrainz5/Query.h"

#include "musicbrainz5/mb5_c.h"

#include <string.h>

#include "musicbrainz5/Alias.h"
#include "musicbrainz5/AliasList.h"
#include "musicbrainz5/Annotation.h"
#include "musicbrainz5/AnnotationList.h"
#include "musicbrainz5/Artist.h"
#include "musicbrainz5/ArtistList.h"
#include "musicbrainz5/ArtistCredit.h"
#include "musicbrainz5/Attribute.h"
#include "musicbrainz5/AttributeList.h"
#include "musicbrainz5/CDStub.h"
#include "musicbrainz5/CDStubList.h"
#include "musicbrainz5/Collection.h"
#include "musicbrainz5/CollectionList.h"
#include "musicbrainz5/Disc.h"
#include "musicbrainz5/DiscList.h"
#include "musicbrainz5/FreeDBDisc.h"
#include "musicbrainz5/FreeDBDiscList.h"
#include "musicbrainz5/IPI.h"
#include "musicbrainz5/ISRC.h"
#include "musicbrainz5/ISRCList.h"
#include "musicbrainz5/ISWC.h"
#include "musicbrainz5/ISWCList.h"
#include "musicbrainz5/Label.h"
#include "musicbrainz5/LabelList.h"
#include "musicbrainz5/LabelInfo.h"
#include "musicbrainz5/LabelInfoList.h"
#include "musicbrainz5/Lifespan.h"
#include "musicbrainz5/Medium.h"
#include "musicbrainz5/MediumList.h"
#include "musicbrainz5/Message.h"
#include "musicbrainz5/Metadata.h"
#include "musicbrainz5/NameCredit.h"
#include "musicbrainz5/NameCreditList.h"
#include "musicbrainz5/NonMBTrack.h"
#include "musicbrainz5/NonMBTrackList.h"
#include "musicbrainz5/PUID.h"
#include "musicbrainz5/PUIDList.h"
#include "musicbrainz5/Rating.h"
#include "musicbrainz5/Recording.h"
#include "musicbrainz5/RecordingList.h"
#include "musicbrainz5/Relation.h"
#include "musicbrainz5/RelationList.h"
#include "musicbrainz5/RelationListList.h"
#include "musicbrainz5/Release.h"
#include "musicbrainz5/ReleaseGroup.h"
#include "musicbrainz5/ReleaseGroupList.h"
#include "musicbrainz5/SecondaryType.h"
#include "musicbrainz5/SecondaryTypeList.h"
#include "musicbrainz5/Tag.h"
#include "musicbrainz5/TagList.h"
#include "musicbrainz5/TextRepresentation.h"
#include "musicbrainz5/Track.h"
#include "musicbrainz5/TrackList.h"
#include "musicbrainz5/UserRating.h"
#include "musicbrainz5/UserTag.h"
#include "musicbrainz5/UserTagList.h"
#include "musicbrainz5/Work.h"
#include "musicbrainz5/WorkList.h"

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

#define MB5_C_DELETE(TYPE1, TYPE2) \
	void \
	mb5_##TYPE2##_delete(Mb5##TYPE1 o) \
	{ \
		delete (MusicBrainz5::C##TYPE1 *)o; \
	}

#define MB5_C_CLONE(TYPE1, TYPE2) \
	Mb5##TYPE1 \
	mb5_##TYPE2##_clone(Mb5##TYPE1 o) \
	{ \
		if (o) \
			return (Mb5##TYPE1)new MusicBrainz5::C##TYPE1(*(MusicBrainz5::C##TYPE1 *)o); \
		return 0;\
	}

#define MB5_C_STR_SETTER(TYPE1, TYPE2, PROP1, PROP2) \
	void \
	mb5_##TYPE2##_set_##PROP2(Mb5##TYPE1 o, const char *str) \
	{ \
		if (o) \
		{ \
			try { \
				((MusicBrainz5::C##TYPE1 *)o)->Set##PROP1(str); \
			} \
			catch (...) { \
			} \
		} \
	}

#define MB5_C_INT_SETTER(TYPE1, TYPE2, PROP1, PROP2) \
	void \
	mb5_##TYPE2##_set_##PROP2(Mb5##TYPE1 o, int i) \
	{ \
		if (o) \
		{ \
			try { \
				((MusicBrainz5::C##TYPE1 *)o)->Set##PROP1(i); \
			} \
			catch (...) { \
			} \
		} \
	}

#define MB5_C_STR_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	int \
	mb5_##TYPE2##_get_##PROP2(Mb5##TYPE1 o, char *str, int len) \
	{ \
		int ret=0; \
		if (str) \
			*str=0; \
		if (o) \
		{ \
			try { \
				ret=((MusicBrainz5::C##TYPE1 *)o)->PROP1().length(); \
				if (str && len) \
				{ \
					strncpy(str, ((MusicBrainz5::C##TYPE1 *)o)->PROP1().c_str(), len); \
					str[len-1]='\0'; \
				} \
			} \
			catch (...) { \
				str[0] = '\0'; \
			} \
		} \
		return ret; \
	}

#define MB5_C_INT_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	int \
	mb5_##TYPE2##_get_##PROP2(Mb5##TYPE1 o) \
	{ \
		if (o) \
		{ \
			try { \
				return ((MusicBrainz5::C##TYPE1 *)o)->PROP1(); \
			} \
			catch (...) { \
			} \
		} \
		return 0; \
	}

#define MB5_C_DOUBLE_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	double \
	mb5_##TYPE2##_get_##PROP2(Mb5##TYPE1 o) \
	{ \
		if (o) \
		{ \
			try { \
				return ((MusicBrainz5::C##TYPE1 *)o)->PROP1(); \
			} \
			catch (...) { \
			} \
		} \
		return 0; \
	}

#define MB5_C_BOOL_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	unsigned char \
	mb5_##TYPE2##_get_##PROP2(Mb##TYPE1 o) \
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

#define MB5_C_OBJ_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	Mb5##PROP1 \
	mb5_##TYPE2##_get_##PROP2(Mb5##TYPE1 o) \
	{ \
		if (o) \
		{ \
			try { \
				return (Mb5##PROP1)((MusicBrainz5::C##TYPE1 *)o)->PROP1(); \
			} \
			catch (...) { \
			} \
		} \
		return (Mb5##PROP1)0; \
	}

#define MB5_C_LIST_GETTER(TYPE1, TYPE2) \
	void \
	mb5_##TYPE2##_list_delete(Mb5##TYPE1 o) \
	{ \
		delete (MusicBrainz5::C##TYPE1##List *)o; \
	} \
	int \
	mb5_##TYPE2##_list_size(Mb5##TYPE1##List List) \
	{ \
		if (List) \
		{ \
			try { \
				return ((MusicBrainz5::C##TYPE1##List *)List)->NumItems(); \
			} \
			catch (...) { \
				return 0; \
			} \
		} \
		return 0; \
	} \
 \
	Mb5##TYPE1 \
	mb5_##TYPE2##_list_item(Mb5##TYPE1##List List, int Item) \
	{ \
		if (List) \
		{ \
			try { \
				return ((MusicBrainz5::C##TYPE1##List *)List)->Item(Item); \
			} \
			catch (...) { \
				return (Mb5##TYPE1)0; \
			} \
		} \
		return (Mb5##TYPE1)0; \
	} \
	int \
	mb5_##TYPE2##_list_get_count(Mb5##TYPE1##List List) \
	{ \
		if (List) \
		{ \
			try { \
				return ((MusicBrainz5::C##TYPE1##List *)List)->Count(); \
			} \
			catch (...) { \
				return 0; \
			} \
		} \
		return 0; \
	} \
 \
	int \
	mb5_##TYPE2##_list_get_offset(Mb5##TYPE1##List List) \
	{ \
		if (List) \
		{ \
			try { \
				return ((MusicBrainz5::C##TYPE1##List *)List)->Offset(); \
			} \
			catch (...) { \
				return 0; \
			} \
		} \
		return 0; \
	} \
 \

#define MB5_C_EXT_GETTER(PROP1, PROP2) \
	int \
	mb5_entity_ext_##PROP2##s_size(Mb5Entity o) \
	{ \
		if (o) \
		{ \
			return ((MusicBrainz5::CEntity *)o)->Ext##PROP1##s().size(); \
		} \
		return 0; \
	} \
	int \
	mb5_entity_ext_##PROP2##_name(Mb5Entity o, int Item, char *str, int len) \
	{ \
		int ret=0; \
		if (str) \
			*str=0; \
		if (o) \
		{ \
			std::map<std::string,std::string> Items=((MusicBrainz5::CEntity *)o)->Ext##PROP1##s(); \
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
	mb5_entity_ext_##PROP2##_value(Mb5Entity o, int Item, char *str, int len) \
	{ \
		int ret=0; \
		if (str) \
			*str=0; \
		if (o) \
		{ \
			std::map<std::string,std::string> Items=((MusicBrainz5::CEntity *)o)->Ext##PROP1##s(); \
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

