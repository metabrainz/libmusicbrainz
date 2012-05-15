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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "musicbrainz5/mb5_c.h"

void PrintRelationList(Mb5RelationList RelationList)
{
	char Type[256];
	int count;

	mb5_relation_list_get_targettype(RelationList,Type,sizeof(Type));
	printf("Target type is '%s'\n",Type);

	for (count=0;count<mb5_relation_list_size(RelationList);count++)
	{
		char Target[256];
		char Type[256];

		Mb5Relation Relation=mb5_relation_list_item(RelationList,count);

		mb5_relation_get_target(Relation,Target,sizeof(Target));
		mb5_relation_get_type(Relation,Type,sizeof(Type));

		printf("Relation: %d - Type '%s', Target '%s'\n",count,Type,Target);
	}
}

int main(int argc, const char *argv[])
{
	Mb5Query Query=0;
	char DiscID[256]="tLGBAiCflG8ZI6lFcOt87vXjEcI-";

	Query=mb5_query_new("ctest","test.musicbrainz.org",0);
	if (Query)
	{
		char Version[256];
		Mb5Metadata Metadata=0;

		mb5_query_get_version(Query,Version,sizeof(Version));
		printf("Version is '%s'\n",Version);

		Metadata=mb5_query_query(Query,"work","b0d17375-5593-390e-a936-1a65ce74c630","",0,NULL,NULL);
		if (Metadata)
		{
			Mb5Work Work=0;

			Work=mb5_metadata_get_work(Metadata);
			if (Work)
			{
				Mb5ISWCList ISWCList=0;

				ISWCList=mb5_work_get_iswclist(Work);
				if (ISWCList)
				{
					int ISWCNum;

					printf("Got ISWC list, size %d\n",mb5_iswc_list_size(ISWCList));

					for (ISWCNum=0;ISWCNum<mb5_iswc_list_size(ISWCList);ISWCNum++)
					{
						Mb5ISWC ISWC=mb5_iswc_list_item(ISWCList,ISWCNum);

						if (ISWC)
						{
							char ISWCStr[256];

							mb5_iswc_get_iswc(ISWC,ISWCStr,sizeof(ISWCStr));

							printf("Got ISWC %d - '%s'\n",ISWCNum,ISWCStr);
						}
					}
				}
			}
		}

		mb5_query_delete(Query);
	}

	return 0;

	if (argc==2)
	{
		strncpy(DiscID,argv[1],sizeof(DiscID));
		DiscID[sizeof(DiscID)-1]='\0';
	}

	Query=mb5_query_new("ctest",0,0);
	if (Query)
	{
		Mb5Metadata Metadata=NULL;
		char **ParamNames;
		char **ParamValues;

		printf("Got query\n");

		mb5_query_set_username(Query,"username");
		mb5_query_set_password(Query,"password");

		ParamNames=malloc(sizeof(char *));
		ParamNames[0]=malloc(256);
		ParamValues=malloc(sizeof(char *));
		ParamValues[0]=malloc(256);

		strcpy(ParamNames[0],"inc");
		strcpy(ParamValues[0],"artists release-groups url-rels work-level-rels work-rels artist-rels");

		Metadata=mb5_query_query(Query,"recording","3631f569-520d-40ff-a1ee-076604723275","",1,ParamNames,ParamValues);
		if (Metadata)
		{
			Mb5Recording Recording=mb5_metadata_get_recording(Metadata);
			printf("Got metadata\n");

			if (Recording)
			{
				Mb5RelationListList RelationListList=mb5_recording_get_relationlistlist(Recording);

				printf("Got recording\n");

				if (RelationListList)
				{
					int RelationListNum;

					printf("Got relation list list, size %d\n",mb5_relationlist_list_size(RelationListList));

					for (RelationListNum=0;RelationListNum<mb5_relationlist_list_size(RelationListList);RelationListNum++)
					{
						Mb5RelationList RelationList=mb5_relationlist_list_item(RelationListList,RelationListNum);

						if (RelationList)
						{
							printf("Got relation list %d\n",RelationListNum);

							PrintRelationList(RelationList);
						}
					}
				}
			}

			mb5_metadata_delete(Metadata);
		}

		Metadata=mb5_query_query(Query,"collection",0,0,0,NULL,NULL);
		if (Metadata)
		{
			printf("Got collections");
			mb5_metadata_delete(Metadata);
		}

		Metadata=mb5_query_query(Query,"discid",DiscID,0,0,NULL,NULL);
		if (Metadata)
		{
			Mb5Disc *Disc=mb5_metadata_get_disc(Metadata);
			printf("Got metadata\n");

			if (Disc)
			{
				int Len=0;
				char *Buff=0;
				Mb5ReleaseList ReleaseList=mb5_disc_get_releaselist(Disc);

				Len=mb5_disc_get_id(Disc,Buff,Len);
				printf("Len is %d\n",Len);
				Buff=malloc(Len+1);
				Len=mb5_disc_get_id(Disc,Buff,Len+1);
				printf("Len is %d (%s)\n",Len,Buff);
				free(Buff);

				printf("Got disc\n");

				if (ReleaseList)
				{
					int count;

					printf("Got release list\n");

					printf("%d items\n",mb5_release_list_size(ReleaseList));

					for (count=0;count<mb5_release_list_size(ReleaseList);count++)
					{
						char ID[256];
						Mb5Release Release=mb5_release_list_item(ReleaseList,count);

						printf("Got release %d\n",count);

						mb5_release_get_id(Release,ID,sizeof(ID));
						printf("ID is '%s'\n",ID);
					}
				}
			}

			mb5_metadata_delete(Metadata);
		}

		mb5_query_delete(Query);
	}

	return 0;
}

void CompileTest()
{
	Mb5Alias Alias=0;
	Mb5AliasList AliasList=0;
	Mb5Annotation Annotation=0;
	Mb5AnnotationList AnnotationList=0;
	Mb5Artist Artist=0;
	Mb5ArtistCredit ArtistCredit=0;
	Mb5ArtistList ArtistList=0;
	Mb5Attribute Attribute=0;
	Mb5AttributeList AttributeList=0;
	Mb5CDStub CDStub=0;
	Mb5CDStubList CDStubList=0;
	Mb5Collection Collection=0;
	Mb5CollectionList CollectionList=0;
	Mb5Disc Disc=0;
	Mb5DiscList DiscList=0;
	Mb5FreeDBDisc FreeDBDisc=0;
	Mb5FreeDBDiscList FreeDBDiscList=0;
	Mb5IPI IPI=0;
	Mb5IPIList IPIList=0;
	Mb5ISRC ISRC=0;
	Mb5ISRCList ISRCList=0;
	Mb5ISWC ISWC=0;
	Mb5ISWCList ISWCList=0;
	Mb5Label Label=0;
	Mb5LabelInfo LabelInfo=0;
	Mb5LabelInfoList LabelInfoList=0;
	Mb5LabelList LabelList=0;
	Mb5Lifespan Lifespan=0;
	Mb5Medium Medium=0;
	Mb5MediumList MediumList=0;
	Mb5Message Message=0;
	Mb5Metadata Metadata=0;
	Mb5NameCredit NameCredit=0;
	Mb5NameCreditList NameCreditList=0;
	Mb5NonMBTrack NonMBTrack=0;
	Mb5NonMBTrackList NonMBTrackList=0;
	Mb5PUID PUID=0;
	Mb5PUIDList PUIDList=0;
	Mb5Query Query=0;
	Mb5Rating Rating=0;
	Mb5Recording Recording=0;
	Mb5RecordingList RecordingList=0;
	Mb5Relation Relation=0;
	Mb5RelationList RelationList=0;
	Mb5RelationListList RelationListList=0;
	Mb5Release Release=0;
	Mb5ReleaseGroup ReleaseGroup=0;
	Mb5ReleaseGroupList ReleaseGroupList=0;
	Mb5ReleaseList ReleaseList=0;
	Mb5SecondaryType SecondaryType=0;
	Mb5SecondaryTypeList SecondaryTypeList=0;
	Mb5Tag Tag=0;
	Mb5TagList TagList=0;
	Mb5TextRepresentation TextRepresentation=0;
	Mb5Track Track=0;
	Mb5TrackList TrackList=0;
	Mb5UserRating UserRating=0;
	Mb5UserTag UserTag=0;
	Mb5UserTagList UserTagList=0;
	Mb5Work Work=0;
	Mb5WorkList WorkList=0;
	char Str[256];
	int Size=sizeof(Str);
	int DummyInt=0;
	double DummyDouble=0;
	unsigned char DummyBool=0;
	tQueryResult DummyResult=eQuery_Success;

	DummyInt=mb5_entity_ext_attributes_size(Alias);
	DummyInt=mb5_entity_ext_attribute_name(Alias, 0, Str, Size);
	DummyInt=mb5_entity_ext_attribute_value(Alias, 0, Str, Size);

	DummyInt=mb5_entity_ext_elements_size(Alias);
	DummyInt=mb5_entity_ext_element_name(Alias, 0, Str, Size);
	DummyInt=mb5_entity_ext_element_value(Alias, 0, Str, Size);

	mb5_alias_get_locale(Alias,Str,Size);
	mb5_alias_get_text(Alias,Str,Size);
	mb5_alias_get_sortname(Alias,Str,Size);
	mb5_alias_get_type(Alias,Str,Size);
	mb5_alias_get_primary(Alias,Str,Size);
	mb5_alias_get_begindate(Alias,Str,Size);
	mb5_alias_get_enddate(Alias,Str,Size);
	Alias=mb5_alias_clone(Alias);
	mb5_alias_delete(Alias);

	mb5_annotation_get_type(Annotation,Str,Size);
	mb5_annotation_get_entity(Annotation,Str,Size);
	mb5_annotation_get_name(Annotation,Str,Size);
	mb5_annotation_get_text(Annotation,Str,Size);
	Annotation=mb5_annotation_clone(Annotation);
	mb5_annotation_delete(Annotation);

	mb5_artist_get_id(Artist,Str,Size);
	mb5_artist_get_type(Artist,Str,Size);
	mb5_artist_get_name(Artist,Str,Size);
	mb5_artist_get_sortname(Artist,Str,Size);
	mb5_artist_get_gender(Artist,Str,Size);
	mb5_artist_get_country(Artist,Str,Size);
	mb5_artist_get_disambiguation(Artist,Str,Size);
	IPIList=mb5_artist_get_ipilist(Artist);
	Lifespan=mb5_artist_get_lifespan(Artist);
	AliasList=mb5_artist_get_aliaslist(Artist);
	RecordingList=mb5_artist_get_recordinglist(Artist);
	ReleaseList=mb5_artist_get_releaselist(Artist);
	ReleaseGroupList=mb5_artist_get_releasegrouplist(Artist);
	LabelList=mb5_artist_get_labellist(Artist);
	WorkList=mb5_artist_get_worklist(Artist);
	RelationListList=mb5_artist_get_relationlistlist(Artist);
	TagList=mb5_artist_get_taglist(Artist);
	UserTagList=mb5_artist_get_usertaglist(Artist);
	Rating=mb5_artist_get_rating(Artist);
	UserRating=mb5_artist_get_userrating(Artist);
	Artist=mb5_artist_clone(Artist);
	mb5_artist_delete(Artist);

	NameCreditList=mb5_artistcredit_get_namecreditlist(ArtistCredit);
	ArtistCredit=mb5_artistcredit_clone(ArtistCredit);
	mb5_artistcredit_delete(ArtistCredit);

	mb5_attribute_get_text(Attribute,Str,Size);
	Attribute=mb5_attribute_clone(Attribute);
	mb5_attribute_delete(Attribute);

	mb5_cdstub_get_id(CDStub,Str,Size);
	mb5_cdstub_get_title(CDStub,Str,Size);
	mb5_cdstub_get_artist(CDStub,Str,Size);
	mb5_cdstub_get_barcode(CDStub,Str,Size);
	mb5_cdstub_get_comment(CDStub,Str,Size);
	NonMBTrackList=mb5_cdstub_get_nonmbtracklist(CDStub);
	CDStub=mb5_cdstub_clone(CDStub);
	mb5_cdstub_delete(CDStub);

	mb5_disc_get_id(Disc,Str,Size);
	DummyInt=mb5_disc_get_sectors(Disc);
	ReleaseList=mb5_disc_get_releaselist(Disc);
	Disc=mb5_disc_clone(Disc);
	mb5_disc_delete(Disc);

	mb5_collection_get_id(Collection,Str,Size);
	mb5_collection_get_name(Collection,Str,Size);
	mb5_collection_get_editor(Collection,Str,Size);
	ReleaseList=mb5_collection_get_releaselist(Collection);
	Collection=mb5_collection_clone(Collection);
	mb5_collection_delete(Collection);

	mb5_freedbdisc_get_id(FreeDBDisc,Str,Size);
	mb5_freedbdisc_get_title(FreeDBDisc,Str,Size);
	mb5_freedbdisc_get_artist(FreeDBDisc,Str,Size);
	mb5_freedbdisc_get_category(FreeDBDisc,Str,Size);
	mb5_freedbdisc_get_year(FreeDBDisc,Str,Size);
	NonMBTrackList=mb5_freedbdisc_get_nonmbtracklist(FreeDBDisc);
	FreeDBDisc=mb5_freedbdisc_clone(FreeDBDisc);
	mb5_freedbdisc_delete(FreeDBDisc);

	mb5_ipi_get_ipi(IPI,Str,Size);
	IPI=mb5_ipi_clone(IPI);
	mb5_ipi_delete(IPI);

	mb5_isrc_get_id(ISRC,Str,Size);
	RecordingList=mb5_isrc_get_recordinglist(ISRC);
	ISRC=mb5_isrc_clone(ISRC);
	mb5_isrc_delete(ISRC);

	mb5_iswc_get_iswc(ISWC,Str,Size);
	ISWC=mb5_iswc_clone(ISWC);
	mb5_iswc_delete(ISWC);

	mb5_label_get_id(Label,Str,Size);
	mb5_label_get_type(Label,Str,Size);
	mb5_label_get_name(Label,Str,Size);
	mb5_label_get_sortname(Label,Str,Size);
	DummyInt=mb5_label_get_labelcode(Label);
	IPIList=mb5_label_get_ipilist(Label);
	mb5_label_get_disambiguation(Label,Str,Size);
	mb5_label_get_country(Label,Str,Size);
	Lifespan=mb5_label_get_lifespan(Label);
	AliasList=mb5_label_get_aliaslist(Label);
	ReleaseList=mb5_label_get_releaselist(Label);
	RelationListList=mb5_label_get_relationlistlist(Label);
	TagList=mb5_label_get_taglist(Label);
	UserTagList=mb5_label_get_usertaglist(Label);
	Rating=mb5_label_get_rating(Label);
	UserRating=mb5_label_get_userrating(Label);
	Label=mb5_label_clone(Label);
	mb5_label_delete(Label);

	mb5_labelinfo_get_catalognumber(LabelInfo,Str,Size);
	Label=mb5_labelinfo_get_label(LabelInfo);
	LabelInfo=mb5_labelinfo_clone(LabelInfo);
	mb5_labelinfo_delete(LabelInfo);

	mb5_lifespan_get_begin(Lifespan,Str,Size);
	mb5_lifespan_get_end(Lifespan,Str,Size);
	mb5_lifespan_get_ended(Lifespan,Str,Size);
	Lifespan=mb5_lifespan_clone(Lifespan);
	mb5_lifespan_delete(Lifespan);

	mb5_medium_get_title(Medium,Str,Size);
	DummyInt=mb5_medium_get_position(Medium);
	mb5_medium_get_format(Medium,Str,Size);
	DiscList=mb5_medium_get_disclist(Medium);
	TrackList=mb5_medium_get_tracklist(Medium);
	DummyBool=mb5_medium_contains_discid(Medium,"1234");
	Medium=mb5_medium_clone(Medium);
	mb5_medium_delete(Medium);

	mb5_message_get_text(Message,Str,Size);
	Message=mb5_message_clone(Message);
	mb5_message_delete(Message);

	mb5_metadata_get_xmlns(Metadata,Str,Size);
	mb5_metadata_get_xmlnsext(Metadata,Str,Size);
	mb5_metadata_get_generator(Metadata,Str,Size);
	mb5_metadata_get_created(Metadata,Str,Size);
	Artist=mb5_metadata_get_artist(Metadata);
	Release=mb5_metadata_get_release(Metadata);
	ReleaseGroup=mb5_metadata_get_releasegroup(Metadata);
	Recording=mb5_metadata_get_recording(Metadata);
	Label=mb5_metadata_get_label(Metadata);
	Work=mb5_metadata_get_work(Metadata);
	PUID=mb5_metadata_get_puid(Metadata);
	ISRC=mb5_metadata_get_isrc(Metadata);
	Disc=mb5_metadata_get_disc(Metadata);
	LabelInfoList=mb5_metadata_get_labelinfolist(Metadata);
	Rating=mb5_metadata_get_rating(Metadata);
	UserRating=mb5_metadata_get_userrating(Metadata);
	Collection=mb5_metadata_get_collection(Metadata);
	ArtistList=mb5_metadata_get_artistlist(Metadata);
	ReleaseList=mb5_metadata_get_releaselist(Metadata);
	ReleaseGroupList=mb5_metadata_get_releasegrouplist(Metadata);
	RecordingList=mb5_metadata_get_recordinglist(Metadata);
	LabelList=mb5_metadata_get_labellist(Metadata);
	WorkList=mb5_metadata_get_worklist(Metadata);
	ISRCList=mb5_metadata_get_isrclist(Metadata);
	AnnotationList=mb5_metadata_get_annotationlist(Metadata);
	CDStubList=mb5_metadata_get_cdstublist(Metadata);
	FreeDBDiscList=mb5_metadata_get_freedbdisclist(Metadata);
	TagList=mb5_metadata_get_taglist(Metadata);
	UserTagList=mb5_metadata_get_usertaglist(Metadata);
	CollectionList=mb5_metadata_get_collectionlist(Metadata);
	CDStub=mb5_metadata_get_cdstub(Metadata);
	Message=mb5_metadata_get_message(Metadata);
	Metadata=mb5_metadata_clone(Metadata);
	mb5_metadata_delete(Metadata);

	mb5_nonmbtrack_get_title(NonMBTrack,Str,Size);
	mb5_nonmbtrack_get_artist(NonMBTrack,Str,Size);
	DummyInt=mb5_nonmbtrack_get_length(NonMBTrack);
	NonMBTrack=mb5_nonmbtrack_clone(NonMBTrack);
	mb5_nonmbtrack_delete(NonMBTrack);

	mb5_namecredit_get_joinphrase(NameCredit,Str,Size);
	mb5_namecredit_get_name(NameCredit,Str,Size);
	Artist=mb5_namecredit_get_artist(NameCredit);
	NameCredit=mb5_namecredit_clone(NameCredit);
	mb5_namecredit_delete(NameCredit);

	mb5_puid_get_id(PUID,Str,Size);
	RecordingList=mb5_puid_get_recordinglist(PUID);
	PUID=mb5_puid_clone(PUID);
	mb5_puid_delete(PUID);

	Query=mb5_query_new("useragent", "server",0);
	mb5_query_set_username(Query,"");
	mb5_query_set_password(Query,"");
	mb5_query_set_proxyhost(Query,"");
	mb5_query_set_proxyport(Query,0);
	mb5_query_set_proxyusername(Query,"");
	mb5_query_set_proxypassword(Query,"");
	ReleaseList=mb5_query_lookup_discid(Query,"discid");
	Release=mb5_query_lookup_release(Query,"release");
	Metadata=mb5_query_query(Query,"entity","id","resource",0,0,0);
	DummyBool=mb5_query_add_collection_entries(Query,Collection,0,0);
	DummyBool=mb5_query_delete_collection_entries(Query,Collection,0,0);
	DummyResult=mb5_query_get_lastresult(Query);
	DummyInt=mb5_query_get_lasthttpcode(Query);
	mb5_query_get_lasterrormessage(Query,Str,Size);
	mb5_query_get_version(Query,Str,Size);
	mb5_query_delete(Query);

	DummyInt=mb5_rating_get_votescount(Rating);
	DummyDouble=mb5_rating_get_rating(Rating);
	Rating=mb5_rating_clone(Rating);
	mb5_rating_delete(Rating);

	mb5_recording_get_id(Recording,Str,Size);
	mb5_recording_get_title(Recording,Str,Size);
	DummyInt=mb5_recording_get_length(Recording);
	mb5_recording_get_disambiguation(Recording,Str,Size);
	ArtistCredit=mb5_recording_get_artistcredit(Recording);
	ReleaseList=mb5_recording_get_releaselist(Recording);
	PUIDList=mb5_recording_get_puidlist(Recording);
	ISRCList=mb5_recording_get_isrclist(Recording);
	RelationListList=mb5_recording_get_relationlistlist(Recording);
	TagList=mb5_recording_get_taglist(Recording);
	UserTagList=mb5_recording_get_usertaglist(Recording);
	Rating=mb5_recording_get_rating(Recording);
	UserRating=mb5_recording_get_userrating(Recording);
	Recording=mb5_recording_clone(Recording);
	mb5_recording_delete(Recording);

	mb5_relation_get_type(Relation,Str,Size);
	mb5_relation_get_target(Relation,Str,Size);
	mb5_relation_get_direction(Relation,Str,Size);
	AttributeList=mb5_relation_get_attributelist(Relation);
	mb5_relation_get_begin(Relation,Str,Size);
	mb5_relation_get_end(Relation,Str,Size);
	Artist=mb5_relation_get_artist(Relation);
	Release=mb5_relation_get_release(Relation);
	ReleaseGroup=mb5_relation_get_releasegroup(Relation);
	Recording=mb5_relation_get_recording(Relation);
	Label=mb5_relation_get_label(Relation);
	Work=mb5_relation_get_work(Relation);
	Relation=mb5_relation_clone(Relation);
	mb5_relation_delete(Relation);

	mb5_release_get_id(Release,Str,Size);
	mb5_release_get_title(Release,Str,Size);
	mb5_release_get_status(Release,Str,Size);
	mb5_release_get_quality(Release,Str,Size);
	mb5_release_get_disambiguation(Release,Str,Size);
	mb5_release_get_packaging(Release,Str,Size);
	TextRepresentation=mb5_release_get_textrepresentation(Release);
	ArtistCredit=mb5_release_get_artistcredit(Release);
	ReleaseGroup=mb5_release_get_releasegroup(Release);
	mb5_release_get_date(Release,Str,Size);
	mb5_release_get_country(Release,Str,Size);
	mb5_release_get_barcode(Release,Str,Size);
	mb5_release_get_asin(Release,Str,Size);
	LabelInfoList=mb5_release_get_labelinfolist(Release);
	MediumList=mb5_release_get_mediumlist(Release);
	RelationListList=mb5_release_get_relationlistlist(Release);
	CollectionList=mb5_release_get_collectionlist(Release);
	MediumList=mb5_release_media_matching_discid(Release,"discid");
	Release=mb5_release_clone(Release);
	mb5_release_delete(Release);

	mb5_releasegroup_get_id(ReleaseGroup,Str,Size);
	mb5_releasegroup_get_primarytype(ReleaseGroup,Str,Size);
	mb5_releasegroup_get_firstreleasedate(ReleaseGroup,Str,Size);
	mb5_releasegroup_get_title(ReleaseGroup,Str,Size);
	mb5_releasegroup_get_disambiguation(ReleaseGroup,Str,Size);
	ArtistCredit=mb5_releasegroup_get_artistcredit(ReleaseGroup);
	ReleaseList=mb5_releasegroup_get_releaselist(ReleaseGroup);
	RelationListList=mb5_releasegroup_get_relationlistlist(ReleaseGroup);
	TagList=mb5_releasegroup_get_taglist(ReleaseGroup);
	UserTagList=mb5_releasegroup_get_usertaglist(ReleaseGroup);
	Rating=mb5_releasegroup_get_rating(ReleaseGroup);
	UserRating=mb5_releasegroup_get_userrating(ReleaseGroup);
	SecondaryTypeList=mb5_releasegroup_get_secondarytypelist(ReleaseGroup);
	ReleaseGroup=mb5_releasegroup_clone(ReleaseGroup);
	mb5_releasegroup_delete(ReleaseGroup);

	DummyInt=mb5_tag_get_count(Tag);
	mb5_tag_get_name(Tag,Str,Size);
	Tag=mb5_tag_clone(Tag);
	mb5_tag_delete(Tag);

	mb5_textrepresentation_get_language(TextRepresentation,Str,Size);
	mb5_textrepresentation_get_script(TextRepresentation,Str,Size);
	TextRepresentation=mb5_textrepresentation_clone(TextRepresentation);
	mb5_textrepresentation_delete(TextRepresentation);

	DummyInt=mb5_track_get_position(Track);
	mb5_track_get_title(Track,Str,Size);
	Recording=mb5_track_get_recording(Track);
	DummyInt=mb5_track_get_length(Track);
	ArtistCredit=mb5_track_get_artistcredit(Track);
	mb5_track_get_number(Track,Str,Size);
	Track=mb5_track_clone(Track);
	mb5_track_delete(Track);

	DummyInt=mb5_userrating_get_userrating(UserRating);
	UserRating=mb5_userrating_clone(UserRating);
	mb5_userrating_delete(UserRating);

	mb5_usertag_get_name(UserTag,Str,Size);
	UserTag=mb5_usertag_clone(UserTag);
	mb5_usertag_delete(UserTag);

	mb5_work_get_id(Work,Str,Size);
	mb5_work_get_type(Work,Str,Size);
	mb5_work_get_title(Work,Str,Size);
	ArtistCredit=mb5_work_get_artistcredit(Work);
	ISWCList=mb5_work_get_iswclist(Work);
	mb5_work_get_disambiguation(Work,Str,Size);
	AliasList=mb5_work_get_aliaslist(Work);
	RelationListList=mb5_work_get_relationlistlist(Work);
	TagList=mb5_work_get_taglist(Work);
	UserTagList=mb5_work_get_usertaglist(Work);
	Rating=mb5_work_get_rating(Work);
	UserRating=mb5_work_get_userrating(Work);
	mb5_work_get_language(Work,Str,Size);

	mb5_alias_list_size(AliasList);
	Alias=mb5_alias_list_item(AliasList,0);
	AliasList=mb5_alias_clone(AliasList);
	DummyInt=mb5_alias_list_get_count(AliasList);
	DummyInt=mb5_alias_list_get_offset(AliasList);
	mb5_alias_list_delete(AliasList);

	mb5_annotation_list_size(AnnotationList);
	Annotation=mb5_annotation_list_item(AnnotationList,0);
	AnnotationList=mb5_annotation_list_clone(AnnotationList);
	DummyInt=mb5_annotation_list_get_count(AnnotationList);
	DummyInt=mb5_annotation_list_get_offset(AnnotationList);
	mb5_annotation_list_delete(AnnotationList);

	DummyInt=mb5_artist_list_size(ArtistList);
	Artist=mb5_artist_list_item(ArtistList,0);
	ArtistList=mb5_artist_list_clone(ArtistList);
	DummyInt=mb5_artist_list_get_count(ArtistList);
	DummyInt=mb5_artist_list_get_offset(ArtistList);
	mb5_artist_list_delete(ArtistList);

	DummyInt=mb5_attribute_list_size(AttributeList);
	Attribute=mb5_attribute_list_item(AttributeList,0);
	AttributeList=mb5_attribute_list_clone(AttributeList);
	DummyInt=mb5_attribute_list_get_count(AttributeList);
	DummyInt=mb5_attribute_list_get_offset(AttributeList);
	mb5_attribute_list_delete(AttributeList);

	DummyInt=mb5_cdstub_list_size(CDStubList);
	CDStub=mb5_cdstub_list_item(CDStubList,0);
	CDStubList=mb5_cdstub_list_clone(CDStubList);
	DummyInt=mb5_cdstub_list_get_count(CDStubList);
	DummyInt=mb5_cdstub_list_get_offset(CDStubList);
	mb5_cdstub_list_delete(CDStubList);

	DummyInt=mb5_collection_list_size(CollectionList);
	Collection=mb5_collection_list_item(CollectionList,0);
	CollectionList=mb5_collection_list_clone(CollectionList);
	DummyInt=mb5_collection_list_get_count(CollectionList);
	DummyInt=mb5_collection_list_get_offset(CollectionList);
	mb5_collection_list_delete(CollectionList);

	DummyInt=mb5_disc_list_size(DiscList);
	Disc=mb5_disc_list_item(DiscList,0);
	DiscList=mb5_disc_list_clone(DiscList);
	DummyInt=mb5_disc_list_get_count(DiscList);
	DummyInt=mb5_disc_list_get_offset(DiscList);
	mb5_disc_list_delete(DiscList);

	DummyInt=mb5_freedbdisc_list_size(FreeDBDiscList);
	FreeDBDisc=mb5_freedbdisc_list_item(FreeDBDiscList,0);
	FreeDBDiscList=mb5_freedbdisc_list_clone(FreeDBDiscList);
	DummyInt=mb5_freedbdisc_list_get_count(FreeDBDiscList);
	DummyInt=mb5_freedbdisc_list_get_offset(FreeDBDiscList);
	mb5_freedbdisc_list_delete(FreeDBDiscList);

	DummyInt=mb5_ipi_list_size(IPIList);
	ISRC=mb5_ipi_list_item(IPIList,0);
	ISRCList=mb5_ipi_list_clone(IPIList);
	DummyInt=mb5_ipi_list_get_count(IPIList);
	DummyInt=mb5_ipi_list_get_offset(IPIList);
	mb5_ipi_list_delete(IPIList);

	DummyInt=mb5_isrc_list_size(ISRCList);
	ISRC=mb5_isrc_list_item(ISRCList,0);
	ISRCList=mb5_isrc_list_clone(ISRCList);
	DummyInt=mb5_isrc_list_get_count(ISRCList);
	DummyInt=mb5_isrc_list_get_offset(ISRCList);
	mb5_isrc_list_delete(ISRCList);

	DummyInt=mb5_iswc_list_size(ISWCList);
	ISWC=mb5_iswc_list_item(ISWCList,0);
	ISWCList=mb5_iswc_list_clone(ISWCList);
	DummyInt=mb5_iswc_list_get_count(ISWCList);
	DummyInt=mb5_iswc_list_get_offset(ISWCList);
	mb5_iswc_list_delete(ISWCList);

	DummyInt=mb5_label_list_size(LabelList);
	Label=mb5_label_list_item(LabelList,0);
	LabelList=mb5_label_list_clone(LabelList);
	DummyInt=mb5_label_list_get_count(LabelList);
	DummyInt=mb5_label_list_get_offset(LabelList);
	mb5_label_list_delete(LabelList);

	DummyInt=mb5_labelinfo_list_size(LabelInfoList);
	LabelInfo=mb5_labelinfo_list_item(LabelInfoList,0);
	LabelInfoList=mb5_labelinfo_list_clone(LabelInfoList);
	DummyInt=mb5_labelinfo_list_get_count(LabelInfoList);
	DummyInt=mb5_labelinfo_list_get_offset(LabelInfoList);
	mb5_labelinfo_list_delete(LabelInfoList);

	DummyInt=mb5_medium_list_size(MediumList);
	Medium=mb5_medium_list_item(MediumList,0);
	DummyInt=mb5_medium_list_get_trackcount(MediumList);
	MediumList=mb5_medium_list_clone(MediumList);
	DummyInt=mb5_medium_list_get_count(MediumList);
	DummyInt=mb5_medium_list_get_offset(MediumList);
	mb5_medium_list_delete(MediumList);

	DummyInt=mb5_namecredit_list_size(NameCreditList);
	NameCredit=mb5_namecredit_list_item(NameCreditList,0);
	NameCreditList=mb5_namecredit_list_clone(NameCreditList);
	DummyInt=mb5_namecredit_list_get_count(NameCreditList);
	DummyInt=mb5_namecredit_list_get_offset(NameCreditList);
	mb5_namecredit_list_delete(NameCreditList);

	DummyInt=mb5_nonmbtrack_list_size(NonMBTrackList);
	NonMBTrack=mb5_nonmbtrack_list_item(NonMBTrackList,0);
	NonMBTrackList=mb5_nonmbtrack_list_clone(NonMBTrackList);
	DummyInt=mb5_nonmbtrack_list_get_count(NonMBTrackList);
	DummyInt=mb5_nonmbtrack_list_get_offset(NonMBTrackList);
	mb5_nonmbtrack_list_delete(NonMBTrackList);

	DummyInt=mb5_puid_list_size(PUIDList);
	PUID=mb5_puid_list_item(PUIDList,0);
	PUIDList=mb5_puid_list_clone(PUIDList);
	DummyInt=mb5_puid_list_get_count(PUIDList);
	DummyInt=mb5_puid_list_get_offset(PUIDList);
	mb5_puid_list_delete(PUIDList);

	DummyInt=mb5_recording_list_size(RecordingList);
	Recording=mb5_recording_list_item(RecordingList,0);
	RecordingList=mb5_recording_list_clone(RecordingList);
	DummyInt=mb5_recording_list_get_count(RecordingList);
	DummyInt=mb5_recording_list_get_offset(RecordingList);
	mb5_recording_list_delete(RecordingList);

	DummyInt=mb5_relation_list_size(RelationList);
	Relation=mb5_relation_list_item(RelationList,0);
	DummyInt=mb5_relation_list_get_targettype(RelationList,Str,Size);
	RelationList=mb5_relation_list_clone(RelationList);
	DummyInt=mb5_relation_list_get_count(RelationList);
	DummyInt=mb5_relation_list_get_offset(RelationList);
	mb5_relation_list_delete(RelationList);

	DummyInt=mb5_relationlist_list_size(RelationListList);
	Relation=mb5_relationlist_list_item(RelationListList,0);
	RelationList=mb5_relationlist_list_clone(RelationListList);
	DummyInt=mb5_relationlist_list_get_count(RelationListList);
	DummyInt=mb5_relationlist_list_get_offset(RelationListList);
	mb5_relationlist_list_delete(RelationListList);

	DummyInt=mb5_release_list_size(ReleaseList);
	Release=mb5_release_list_item(ReleaseList,0);
	ReleaseList=mb5_release_list_clone(ReleaseList);
	DummyInt=mb5_release_list_get_count(ReleaseList);
	DummyInt=mb5_release_list_get_offset(ReleaseList);
	mb5_release_list_delete(ReleaseList);

	DummyInt=mb5_releasegroup_list_size(ReleaseGroupList);
	ReleaseGroup=mb5_releasegroup_list_item(ReleaseGroupList,0);
	ReleaseGroupList=mb5_releasegroup_list_clone(ReleaseGroupList);
	DummyInt=mb5_releasegroup_list_get_count(ReleaseGroupList);
	DummyInt=mb5_releasegroup_list_get_offset(ReleaseGroupList);
	mb5_releasegroup_list_delete(ReleaseGroupList);

	DummyInt=mb5_secondarytype_list_size(SecondaryTypeList);
	SecondaryType=mb5_secondarytype_list_item(SecondaryTypeList,0);
	ReleaseGroupList=mb5_secondarytype_list_clone(SecondaryTypeList);
	DummyInt=mb5_secondarytype_list_get_count(SecondaryTypeList);
	DummyInt=mb5_secondarytype_list_get_offset(SecondaryTypeList);
	mb5_secondarytype_list_delete(SecondaryTypeList);

	DummyInt=mb5_tag_list_size(TagList);
	Tag=mb5_tag_list_item(TagList,0);
	TagList=mb5_tag_list_clone(TagList);
	DummyInt=mb5_tag_list_get_count(TagList);
	DummyInt=mb5_tag_list_get_offset(TagList);
	mb5_tag_list_delete(TagList);

	DummyInt=mb5_track_list_size(TrackList);
	Track=mb5_track_list_item(TrackList,0);
	TrackList=mb5_track_list_clone(TrackList);
	DummyInt=mb5_track_list_get_count(TrackList);
	DummyInt=mb5_track_list_get_offset(TrackList);
	mb5_track_list_delete(TrackList);

	DummyInt=mb5_usertag_list_size(UserTagList);
	UserTag=mb5_usertag_list_item(UserTagList,0);
	UserTagList=mb5_usertag_list_clone(UserTagList);
	DummyInt=mb5_usertag_list_get_count(UserTagList);
	DummyInt=mb5_usertag_list_get_offset(UserTagList);
	mb5_usertag_list_delete(UserTagList);

	DummyInt=mb5_work_list_size(WorkList);
	Work=mb5_work_list_item(WorkList,0);
	WorkList=mb5_work_list_clone(WorkList);
	DummyInt=mb5_work_list_get_count(WorkList);
	DummyInt=mb5_work_list_get_offset(WorkList);
	mb5_work_list_delete(WorkList);

	DummyInt=DummyInt;
	DummyDouble=DummyDouble;
	DummyBool=DummyBool;
	DummyResult=DummyResult;
}
