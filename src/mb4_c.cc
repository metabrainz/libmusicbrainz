/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libmusicbrainz4 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

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
#include "musicbrainz4/Query.h"
#include "musicbrainz4/Rating.h"
#include "musicbrainz4/Recording.h"
#include "musicbrainz4/RecordingList.h"
#include "musicbrainz4/Relation.h"
#include "musicbrainz4/RelationList.h"
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

#define MB4_C_NEW_NOARGS(TYPE1, TYPE2) \
	Mb4##TYPE1 \
	mb4_##TYPE2##_new() \
	{ \
		TYPE1 *o = new TYPE1(); \
		return (Mb4##TYPE1)o; \
	}

#define MB4_C_DELETE(TYPE1, TYPE2) \
	void \
	mb4_##TYPE2##_delete(Mb4##TYPE1 o) \
	{ \
		delete (MusicBrainz4::C##TYPE1 *)o; \
	}

#define MB4_C_STR_SETTER(TYPE1, TYPE2, PROP1, PROP2) \
	void \
	mb4_##TYPE2##_set_##PROP2(Mb4##TYPE1 o, const char *str) \
	{ \
		try { \
			((MusicBrainz4::C##TYPE1 *)o)->Set##PROP1(str); \
		} \
		catch (...) { \
		} \
	}

#define MB4_C_INT_SETTER(TYPE1, TYPE2, PROP1, PROP2) \
	void \
	mb4_##TYPE2##_set_##PROP2(Mb4##TYPE1 o, int i) \
	{ \
		try { \
			((MusicBrainz4::C##TYPE1 *)o)->Set##PROP1(i); \
		} \
		catch (...) { \
		} \
	}

#define MB4_C_STR_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	int \
	mb4_##TYPE2##_get_##PROP2(Mb4##TYPE1 o, char *str, int len) \
	{ \
		int ret=0; \
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
		try { \
			return ((MusicBrainz4::C##TYPE1 *)o)->PROP1(); \
		} \
		catch (...) { \
			return 0; \
		} \
	}

#define MB4_C_DOUBLE_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	double \
	mb4_##TYPE2##_get_##PROP2(Mb4##TYPE1 o) \
	{ \
		try { \
			return ((MusicBrainz4::C##TYPE1 *)o)->PROP1(); \
		} \
		catch (...) { \
			return 0; \
		} \
	}

#define MB4_C_BOOL_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	unsigned char \
	mb4_##TYPE2##_get_##PROP2(Mb##TYPE1 o) \
	{ \
		try { \
			return ((TYPE1 *)o)->PROP1() ? 1 : 0; \
		} \
		catch (...) { \
			return 0; \
		} \
	}

#define MB4_C_OBJ_GETTER(TYPE1, TYPE2, PROP1, PROP2) \
	Mb4##PROP1 \
	mb4_##TYPE2##_get_##PROP2(Mb4##TYPE1 o) \
	{ \
		try { \
			return (Mb4##PROP1)((MusicBrainz4::C##TYPE1 *)o)->PROP1(); \
		} \
		catch (...) { \
			return (Mb4##PROP1)0; \
		} \
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
		try { \
			return ((MusicBrainz4::C##TYPE1##List *)List)->NumItems(); \
		} \
		catch (...) { \
			return 0; \
		} \
	} \
 \
	Mb4##TYPE1 \
	mb4_##TYPE2##_list_item(Mb4##TYPE1##List List, int Item) \
	{ \
		try { \
			return ((MusicBrainz4::C##TYPE1##List *)List)->Item(Item); \
		} \
		catch (...) { \
			return (Mb4##TYPE1)0; \
		} \
	}

#define MB4_C_EXT_GETTER(PROP1, PROP2) \
	int \
	mb4_entity_ext_##PROP2##s_size(Mb4Entity o) \
	{ \
		return ((MusicBrainz4::CEntity *)o)->Ext##PROP1##s().size(); \
	} \
	int \
	mb4_entity_ext_##PROP2##_name(Mb4Entity o, int Item, char *str, int len) \
	{ \
		int ret; \
		std::map<std::string,std::string> Items=((MusicBrainz4::CEntity *)o)->Ext##PROP1##s(); \
		std::string Name=GetMapName(Items,Item); \
		ret=Name.length(); \
		if (str && len) \
		{ \
			strncpy(str, Name.c_str(), len); \
			str[len-1]='\0'; \
		} \
		return ret; \
	} \
	int \
	mb4_entity_ext_##PROP2##_value(Mb4Entity o, int Item, char *str, int len) \
	{ \
		int ret; \
		std::map<std::string,std::string> Items=((MusicBrainz4::CEntity *)o)->Ext##PROP1##s(); \
		std::string Name=GetMapValue(Items,Item); \
		ret=Name.length(); \
		if (str && len) \
		{ \
			strncpy(str, Name.c_str(), len); \
			str[len-1]='\0'; \
		} \
		return ret; \
	} \

MB4_C_EXT_GETTER(Attribute,attribute)
MB4_C_EXT_GETTER(Element,element)

MB4_C_DELETE(Alias,alias)
MB4_C_STR_GETTER(Alias,alias,Locale,locale)
MB4_C_STR_GETTER(Alias,alias,Text,text)

MB4_C_DELETE(Annotation,annotation)
MB4_C_STR_GETTER(Annotation,annotation,Type,type)
MB4_C_STR_GETTER(Annotation,annotation,Entity,entity)
MB4_C_STR_GETTER(Annotation,annotation,Name,name)
MB4_C_STR_GETTER(Annotation,annotation,Text,text)

MB4_C_DELETE(Artist,artist)
MB4_C_STR_GETTER(Artist,artist,ID,id)
MB4_C_STR_GETTER(Artist,artist,Type,type)
MB4_C_STR_GETTER(Artist,artist,Name,name)
MB4_C_STR_GETTER(Artist,artist,SortName,sortname)
MB4_C_STR_GETTER(Artist,artist,Gender,gender)
MB4_C_STR_GETTER(Artist,artist,Country,country)
MB4_C_STR_GETTER(Artist,artist,Disambiguation,disambiguation)
MB4_C_OBJ_GETTER(Artist,artist,Lifespan,lifespan)
MB4_C_OBJ_GETTER(Artist,artist,AliasList,aliaslist)
MB4_C_OBJ_GETTER(Artist,artist,RecordingList,recordinglist)
MB4_C_OBJ_GETTER(Artist,artist,ReleaseList,releaselist)
MB4_C_OBJ_GETTER(Artist,artist,ReleaseGroupList,releasegrouplist)
MB4_C_OBJ_GETTER(Artist,artist,LabelList,labellist)
MB4_C_OBJ_GETTER(Artist,artist,WorkList,worklist)
MB4_C_OBJ_GETTER(Artist,artist,RelationList,relationlist)
MB4_C_OBJ_GETTER(Artist,artist,TagList,taglist)
MB4_C_OBJ_GETTER(Artist,artist,UserTagList,usertaglist)
MB4_C_OBJ_GETTER(Artist,artist,Rating,rating)
MB4_C_OBJ_GETTER(Artist,artist,UserRating,userrating)

MB4_C_DELETE(ArtistCredit,artistcredit)
MB4_C_OBJ_GETTER(ArtistCredit,artistcredit,NameCreditList,namecreditlist)

MB4_C_DELETE(Attribute,attribute)
MB4_C_STR_GETTER(Attribute,attribute,Text,text)

MB4_C_DELETE(CDStub,cdstub)
MB4_C_STR_GETTER(CDStub,cdstub,ID,id)
MB4_C_STR_GETTER(CDStub,cdstub,Title,title)
MB4_C_STR_GETTER(CDStub,cdstub,Artist,artist)
MB4_C_STR_GETTER(CDStub,cdstub,Barcode,barcode)
MB4_C_STR_GETTER(CDStub,cdstub,Comment,comment)
MB4_C_OBJ_GETTER(CDStub,cdstub,NonMBTrackList,nonmbtracklist)

MB4_C_DELETE(Collection,collection)
MB4_C_STR_GETTER(Collection,collection,ID,id)
MB4_C_STR_GETTER(Collection,collection,Name,name)
MB4_C_STR_GETTER(Collection,collection,Editor,editor)
MB4_C_OBJ_GETTER(Collection,collection,ReleaseList,releaselist)

MB4_C_DELETE(Disc,disc)
MB4_C_STR_GETTER(Disc,disc,ID,id)
MB4_C_INT_GETTER(Disc,disc,Sectors,sectors)
MB4_C_OBJ_GETTER(Disc,disc,ReleaseList,releaselist)

MB4_C_DELETE(FreeDBDisc,freedbdisc)
MB4_C_STR_GETTER(FreeDBDisc,freedbdisc,ID,id)
MB4_C_STR_GETTER(FreeDBDisc,freedbdisc,Title,title)
MB4_C_STR_GETTER(FreeDBDisc,freedbdisc,Artist,artist)
MB4_C_STR_GETTER(FreeDBDisc,freedbdisc,Category,category)
MB4_C_STR_GETTER(FreeDBDisc,freedbdisc,Year,year)
MB4_C_OBJ_GETTER(FreeDBDisc,freedbdisc,NonMBTrackList,nonmbtracklist)

MB4_C_DELETE(ISRC,isrc)
MB4_C_STR_GETTER(ISRC,isrc,ID,id)
MB4_C_OBJ_GETTER(ISRC,isrc,RecordingList,recordinglist)

MB4_C_DELETE(Label,label)
MB4_C_STR_GETTER(Label,label,ID,id)
MB4_C_STR_GETTER(Label,label,Type,type)
MB4_C_STR_GETTER(Label,label,Name,name)
MB4_C_STR_GETTER(Label,label,SortName,sortname)
MB4_C_INT_GETTER(Label,label,LabelCode,labelcode)
MB4_C_STR_GETTER(Label,label,Disambiguation,disambiguation)
MB4_C_STR_GETTER(Label,label,Country,country)
MB4_C_OBJ_GETTER(Label,label,Lifespan,lifespan)
MB4_C_OBJ_GETTER(Label,label,AliasList,aliaslist)
MB4_C_OBJ_GETTER(Label,label,ReleaseList,releaselist)
MB4_C_OBJ_GETTER(Label,label,RelationList,relationlist)
MB4_C_OBJ_GETTER(Label,label,TagList,taglist)
MB4_C_OBJ_GETTER(Label,label,UserTagList,usertaglist)
MB4_C_OBJ_GETTER(Label,label,Rating,rating)
MB4_C_OBJ_GETTER(Label,label,UserRating,userrating)

MB4_C_DELETE(LabelInfo,labelinfo)
MB4_C_STR_GETTER(LabelInfo,labelinfo,CatalogNumber,catalognumber)
MB4_C_OBJ_GETTER(LabelInfo,labelinfo,Label,label)

MB4_C_DELETE(Lifespan,lifespan)
MB4_C_STR_GETTER(Lifespan,lifespan,Begin,begin)
MB4_C_STR_GETTER(Lifespan,lifespan,End,end)

MB4_C_DELETE(Medium,medium)
MB4_C_STR_GETTER(Medium,medium,Title,title)
MB4_C_INT_GETTER(Medium,medium,Position,position)
MB4_C_STR_GETTER(Medium,medium,Format,format)
MB4_C_OBJ_GETTER(Medium,medium,DiscList,disclist)
MB4_C_OBJ_GETTER(Medium,medium,TrackList,tracklist)

unsigned char mb4_medium_contains_discid(Mb4Medium Medium, const char *DiscID)
{
	unsigned char Ret=0;

	MusicBrainz4::CMedium *TheMedium=reinterpret_cast<MusicBrainz4::CMedium *>(Medium);
	if (TheMedium)
		Ret=TheMedium->ContainsDiscID(DiscID);

	return Ret;
}

MB4_C_DELETE(Message,message)
MB4_C_STR_GETTER(Message,message,Text,text)

MB4_C_DELETE(Metadata,metadata)
MB4_C_STR_GETTER(Metadata,metadata,XMLNS,xmlns)
MB4_C_STR_GETTER(Metadata,metadata,XMLNSExt,xmlnsext)
MB4_C_STR_GETTER(Metadata,metadata,Generator,generator)
MB4_C_STR_GETTER(Metadata,metadata,Created,created)
MB4_C_OBJ_GETTER(Metadata,metadata,Artist,artist)
MB4_C_OBJ_GETTER(Metadata,metadata,Release,release)
MB4_C_OBJ_GETTER(Metadata,metadata,ReleaseGroup,releasegroup)
MB4_C_OBJ_GETTER(Metadata,metadata,Recording,recording)
MB4_C_OBJ_GETTER(Metadata,metadata,Label,label)
MB4_C_OBJ_GETTER(Metadata,metadata,Work,work)
MB4_C_OBJ_GETTER(Metadata,metadata,PUID,puid)
MB4_C_OBJ_GETTER(Metadata,metadata,ISRC,isrc)
MB4_C_OBJ_GETTER(Metadata,metadata,Disc,disc)
MB4_C_OBJ_GETTER(Metadata,metadata,LabelInfoList,labelinfolist)
MB4_C_OBJ_GETTER(Metadata,metadata,Rating,rating)
MB4_C_OBJ_GETTER(Metadata,metadata,UserRating,userrating)
MB4_C_OBJ_GETTER(Metadata,metadata,Collection,collection)
MB4_C_OBJ_GETTER(Metadata,metadata,ArtistList,artistlist)
MB4_C_OBJ_GETTER(Metadata,metadata,ReleaseList,releaselist)
MB4_C_OBJ_GETTER(Metadata,metadata,ReleaseGroupList,releasegrouplist)
MB4_C_OBJ_GETTER(Metadata,metadata,RecordingList,recordinglist)
MB4_C_OBJ_GETTER(Metadata,metadata,LabelList,labellist)
MB4_C_OBJ_GETTER(Metadata,metadata,WorkList,worklist)
MB4_C_OBJ_GETTER(Metadata,metadata,ISRCList,isrclist)
MB4_C_OBJ_GETTER(Metadata,metadata,AnnotationList,annotationlist)
MB4_C_OBJ_GETTER(Metadata,metadata,CDStubList,cdstublist)
MB4_C_OBJ_GETTER(Metadata,metadata,FreeDBDiscList,freedbdisclist)
MB4_C_OBJ_GETTER(Metadata,metadata,TagList,taglist)
MB4_C_OBJ_GETTER(Metadata,metadata,UserTagList,usertaglist)
MB4_C_OBJ_GETTER(Metadata,metadata,CollectionList,collectionlist)
MB4_C_OBJ_GETTER(Metadata,metadata,CDStub,cdstub)
MB4_C_OBJ_GETTER(Metadata,metadata,Message,message)

MB4_C_DELETE(NameCredit,namecredit)
MB4_C_STR_GETTER(NameCredit,namecredit,JoinPhrase,joinphrase)
MB4_C_STR_GETTER(NameCredit,namecredit,Name,name)
MB4_C_OBJ_GETTER(NameCredit,namecredit,Artist,artist)

MB4_C_DELETE(NonMBTrack,nonmbtrack)
MB4_C_STR_GETTER(NonMBTrack,nonmbtrack,Title,title)
MB4_C_STR_GETTER(NonMBTrack,nonmbtrack,Artist,artist)
MB4_C_INT_GETTER(NonMBTrack,nonmbtrack,Length,length)

MB4_C_DELETE(PUID,puid)
MB4_C_STR_GETTER(PUID,puid,ID,id)
MB4_C_OBJ_GETTER(PUID,puid,RecordingList,recordinglist)

Mb4Query mb4_query_new(const char *UserAgent, const char *Server, int Port)
{
	return new MusicBrainz4::CQuery(UserAgent, Server ? Server : "musicbrainz.org", Port!=0 ? Port : 80);
}

MB4_C_DELETE(Query,query)
MB4_C_STR_SETTER(Query,query,UserName,username)
MB4_C_STR_SETTER(Query,query,Password,password)
MB4_C_STR_SETTER(Query,query,ProxyHost,proxyhost)
MB4_C_INT_SETTER(Query,query,ProxyPort,proxyport)
MB4_C_STR_SETTER(Query,query,ProxyUserName,proxyusername)
MB4_C_STR_SETTER(Query,query,ProxyPassword,proxypassword)

Mb4ReleaseList mb4_query_lookup_discid(Mb4Query Query, const char *DiscID)
{
	try
	{
		MusicBrainz4::CQuery *TheQuery=reinterpret_cast<MusicBrainz4::CQuery *>(Query);
		if (TheQuery)
			return new MusicBrainz4::CReleaseList(TheQuery->LookupDiscID(DiscID));
	}

	catch(...)
	{
	}

	return 0;
}

Mb4Release mb4_query_lookup_release(Mb4Query Query, const char *Release)
{
	try
	{
		MusicBrainz4::CQuery *TheQuery=reinterpret_cast<MusicBrainz4::CQuery *>(Query);
		if (TheQuery)
			return new MusicBrainz4::CRelease(TheQuery->LookupRelease(Release));
	}

	catch(...)
	{
	}

	return 0;
}

Mb4Metadata mb4_query_query(Mb4Query Query, const char *Entity, const char *ID, const char *Resource, int NumParams, char **ParamName, char **ParamValue)
{
	try
	{
		MusicBrainz4::CQuery::tParamMap Params;

		for (int count=0;count<NumParams;count++)
		{
			if (ParamName[count] && ParamValue[count])
				Params[ParamName[count]]=ParamValue[count];
		}

		MusicBrainz4::CQuery *TheQuery=reinterpret_cast<MusicBrainz4::CQuery *>(Query);
		if (TheQuery)
			return new MusicBrainz4::CMetadata(TheQuery->Query(Entity?Entity:"",
																										ID?ID:"",
																										Resource?Resource:"",
																										Params));
	}

	catch(...)
	{
	}

	return 0;
}

unsigned char mb4_query_add_collection_entries(Mb4Query Query, const char *Collection, int NumEntries, const char **Entries)
{
	try
	{
		std::vector<std::string> VecEntries;

		MusicBrainz4::CQuery *TheQuery=reinterpret_cast<MusicBrainz4::CQuery *>(Query);
		if (TheQuery)
		{
			for (int count=0;count<NumEntries;count++)
			{
				if (Entries && Entries[count])
				{
					VecEntries.push_back(Entries[count]);
				}
			}

			return TheQuery->AddCollectionEntries(Collection,VecEntries)?1:0;
		}
	}

	catch(...)
	{
	}

	return 0;
}

unsigned char mb4_query_delete_collection_entries(Mb4Query Query, const char *Collection, int NumEntries, const char **Entries)
{
	try
	{
		std::vector<std::string> VecEntries;

		MusicBrainz4::CQuery *TheQuery=reinterpret_cast<MusicBrainz4::CQuery *>(Query);
		if (TheQuery)
		{
			for (int count=0;count<NumEntries;count++)
			{
				if (Entries && Entries[count])
				{
					VecEntries.push_back(Entries[count]);
				}
			}

			return TheQuery->AddCollectionEntries(Collection,VecEntries)?1:0;
		}
	}

	catch(...)
	{
	}

	return 0;
}

tQueryResult mb4_query_get_lastresult(Mb4Query o)
{
	try
	{
		return (tQueryResult)((MusicBrainz4::CQuery *)o)->LastResult();
	}

	catch (...)
	{
		return eQuery_FetchError;
	}
}

MB4_C_INT_GETTER(Query,query,LastHTTPCode,lasthttpcode)
MB4_C_STR_GETTER(Query,query,LastErrorMessage,lasterrormessage)

MB4_C_DELETE(Rating,rating)
MB4_C_INT_GETTER(Rating,rating,VotesCount,votescount)
MB4_C_DOUBLE_GETTER(Rating,rating,Rating,rating)

MB4_C_DELETE(Recording,recording)
MB4_C_STR_GETTER(Recording,recording,ID,id)
MB4_C_STR_GETTER(Recording,recording,Title,title)
MB4_C_INT_GETTER(Recording,recording,Length,length)
MB4_C_STR_GETTER(Recording,recording,Disambiguation,disambiguation)
MB4_C_OBJ_GETTER(Recording,recording,ArtistCredit,artistcredit)
MB4_C_OBJ_GETTER(Recording,recording,ReleaseList,releaselist)
MB4_C_OBJ_GETTER(Recording,recording,PUIDList,puidlist)
MB4_C_OBJ_GETTER(Recording,recording,ISRCList,isrclist)
MB4_C_OBJ_GETTER(Recording,recording,RelationList,relationlist)
MB4_C_OBJ_GETTER(Recording,recording,TagList,taglist)
MB4_C_OBJ_GETTER(Recording,recording,UserTagList,usertaglist)
MB4_C_OBJ_GETTER(Recording,recording,Rating,rating)
MB4_C_OBJ_GETTER(Recording,recording,UserRating,userrating)

MB4_C_DELETE(Relation,relation)
MB4_C_STR_GETTER(Relation,relation,Type,type)
MB4_C_STR_GETTER(Relation,relation,Target,target)
MB4_C_STR_GETTER(Relation,relation,Direction,direction)
MB4_C_OBJ_GETTER(Relation,relation,AttributeList,attributelist)
MB4_C_STR_GETTER(Relation,relation,Begin,begin)
MB4_C_STR_GETTER(Relation,relation,End,end)
MB4_C_OBJ_GETTER(Relation,relation,Artist,artist)
MB4_C_OBJ_GETTER(Relation,relation,Release,release)
MB4_C_OBJ_GETTER(Relation,relation,ReleaseGroup,releasegroup)
MB4_C_OBJ_GETTER(Relation,relation,Recording,recording)
MB4_C_OBJ_GETTER(Relation,relation,Label,label)
MB4_C_OBJ_GETTER(Relation,relation,Work,work)

MB4_C_DELETE(Release,release)
MB4_C_STR_GETTER(Release,release,ID,id)
MB4_C_STR_GETTER(Release,release,Title,title)
MB4_C_STR_GETTER(Release,release,Status,status)
MB4_C_STR_GETTER(Release,release,Quality,quality)
MB4_C_STR_GETTER(Release,release,Disambiguation,disambiguation)
MB4_C_STR_GETTER(Release,release,Packaging,packaging)
MB4_C_OBJ_GETTER(Release,release,TextRepresentation,textrepresentation)
MB4_C_OBJ_GETTER(Release,release,ArtistCredit,artistcredit)
MB4_C_OBJ_GETTER(Release,release,ReleaseGroup,releasegroup)
MB4_C_STR_GETTER(Release,release,Date,date)
MB4_C_STR_GETTER(Release,release,Country,country)
MB4_C_STR_GETTER(Release,release,Barcode,barcode)
MB4_C_STR_GETTER(Release,release,ASIN,asin)
MB4_C_OBJ_GETTER(Release,release,LabelInfoList,labelinfolist)
MB4_C_OBJ_GETTER(Release,release,MediumList,mediumlist)
MB4_C_OBJ_GETTER(Release,release,RelationList,relationlist)

Mb4MediumList mb4_release_media_matching_discid(Mb4Release Release, const char *DiscID)
{
	MusicBrainz4::CRelease *TheRelease=reinterpret_cast<MusicBrainz4::CRelease *>(Release);
	if (TheRelease)
		return new MusicBrainz4::CMediumList(TheRelease->MediaMatchingDiscID(DiscID));

	return 0;
}

MB4_C_DELETE(ReleaseGroup,releasegroup)
MB4_C_STR_GETTER(ReleaseGroup,releasegroup,ID,id)
MB4_C_STR_GETTER(ReleaseGroup,releasegroup,Type,type)
MB4_C_STR_GETTER(ReleaseGroup,releasegroup,FirstReleaseDate,firstreleasedate)
MB4_C_STR_GETTER(ReleaseGroup,releasegroup,Title,title)
MB4_C_STR_GETTER(ReleaseGroup,releasegroup,Disambiguation,disambiguation)
MB4_C_OBJ_GETTER(ReleaseGroup,releasegroup,ArtistCredit,artistcredit)
MB4_C_OBJ_GETTER(ReleaseGroup,releasegroup,ReleaseList,releaselist)
MB4_C_OBJ_GETTER(ReleaseGroup,releasegroup,RelationList,relationlist)
MB4_C_OBJ_GETTER(ReleaseGroup,releasegroup,TagList,taglist)
MB4_C_OBJ_GETTER(ReleaseGroup,releasegroup,UserTagList,usertaglist)
MB4_C_OBJ_GETTER(ReleaseGroup,releasegroup,Rating,rating)
MB4_C_OBJ_GETTER(ReleaseGroup,releasegroup,UserRating,userrating)

MB4_C_DELETE(Tag,tag)
MB4_C_INT_GETTER(Tag,tag,Count,count)
MB4_C_STR_GETTER(Tag,tag,Name,name)

MB4_C_DELETE(TextRepresentation,textrepresentation)
MB4_C_STR_GETTER(TextRepresentation,textrepresentation,Language,language)
MB4_C_STR_GETTER(TextRepresentation,textrepresentation,Script,script)

MB4_C_DELETE(Track,track)
MB4_C_INT_GETTER(Track,track,Position,position)
MB4_C_STR_GETTER(Track,track,Title,title)
MB4_C_OBJ_GETTER(Track,track,Recording,recording)
MB4_C_INT_GETTER(Track,track,Length,length)
MB4_C_OBJ_GETTER(Track,track,ArtistCredit,artistcredit)

MB4_C_DELETE(UserRating,userrating)
MB4_C_INT_GETTER(UserRating,userrating,UserRating,userrating)

MB4_C_DELETE(UserTag,usertag)
MB4_C_STR_GETTER(UserTag,usertag,Name,name)

MB4_C_DELETE(Work,work)
MB4_C_STR_GETTER(Work,work,ID,id)
MB4_C_STR_GETTER(Work,work,Type,type)
MB4_C_STR_GETTER(Work,work,Title,title)
MB4_C_OBJ_GETTER(Work,work,ArtistCredit,artistcredit)
MB4_C_STR_GETTER(Work,work,ISWC,iswc)
MB4_C_STR_GETTER(Work,work,Disambiguation,disambiguation)
MB4_C_OBJ_GETTER(Work,work,AliasList,aliaslist)
MB4_C_OBJ_GETTER(Work,work,RelationList,relationlist)
MB4_C_OBJ_GETTER(Work,work,TagList,taglist)
MB4_C_OBJ_GETTER(Work,work,UserTagList,usertaglist)
MB4_C_OBJ_GETTER(Work,work,Rating,rating)
MB4_C_OBJ_GETTER(Work,work,UserRating,userrating)

MB4_C_LIST_GETTER(Alias,alias)
MB4_C_LIST_GETTER(Annotation,annotation)
MB4_C_LIST_GETTER(Artist,artist)
MB4_C_LIST_GETTER(Attribute,attribute)
MB4_C_LIST_GETTER(CDStub,cdstub)
MB4_C_LIST_GETTER(Collection,collection)
MB4_C_LIST_GETTER(Disc,disc)
MB4_C_LIST_GETTER(FreeDBDisc,freedbdisc)
MB4_C_LIST_GETTER(ISRC,isrc)
MB4_C_LIST_GETTER(Label,label)
MB4_C_LIST_GETTER(LabelInfo,labelinfo)
MB4_C_LIST_GETTER(Medium,medium)
MB4_C_LIST_GETTER(NameCredit,namecredit)
MB4_C_LIST_GETTER(NonMBTrack,nonmbtrack)
MB4_C_LIST_GETTER(PUID,puid)
MB4_C_LIST_GETTER(Recording,recording)
MB4_C_LIST_GETTER(Relation,relation)
MB4_C_LIST_GETTER(Release,release)
MB4_C_LIST_GETTER(ReleaseGroup,releasegroup)
MB4_C_LIST_GETTER(Tag,tag)
MB4_C_LIST_GETTER(Track,track)
MB4_C_LIST_GETTER(UserTag,usertag)
MB4_C_LIST_GETTER(Work,work)
