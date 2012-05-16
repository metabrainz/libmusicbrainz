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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "musicbrainz4/mb4_c.h"

void PrintRelationList(Mb4RelationList RelationList)
{
	char Type[256];
	int count;

	mb4_relation_list_get_targettype(RelationList,Type,sizeof(Type));
	printf("Target type is '%s'\n",Type);

	for (count=0;count<mb4_relation_list_size(RelationList);count++)
	{
		char Target[256];
		char Type[256];

		Mb4Relation Relation=mb4_relation_list_item(RelationList,count);

		mb4_relation_get_target(Relation,Target,sizeof(Target));
		mb4_relation_get_type(Relation,Type,sizeof(Type));

		printf("Relation: %d - Type '%s', Target '%s'\n",count,Type,Target);
	}
}

int main(int argc, const char *argv[])
{
	Mb4Query Query=0;
	char DiscID[256]="tLGBAiCflG8ZI6lFcOt87vXjEcI-";

	Query=mb4_query_new("ctest","test.musicbrainz.org",0);
	if (Query)
	{
		char Version[256];
		Mb4Metadata Metadata=0;

		mb4_query_get_version(Query,Version,sizeof(Version));
		printf("Version is '%s'\n",Version);

		Metadata=mb4_query_query(Query,"work","b0d17375-5593-390e-a936-1a65ce74c630","",0,NULL,NULL);
		if (Metadata)
		{
			Mb4Work Work=0;

			Work=mb4_metadata_get_work(Metadata);
			if (Work)
			{
				Mb4ISWCList ISWCList=0;
				char ISWCStr[256];

				mb4_work_get_iswc(Work,ISWCStr,sizeof(ISWCStr));
				printf("ISWC: '%s'\n",ISWCStr);

				ISWCList=mb4_work_get_iswclist(Work);
				if (ISWCList)
				{
					int ISWCNum;

					printf("Got ISWC list, size %d\n",mb4_iswc_list_size(ISWCList));

					for (ISWCNum=0;ISWCNum<mb4_iswc_list_size(ISWCList);ISWCNum++)
					{
						Mb4ISWC ISWC=mb4_iswc_list_item(ISWCList,ISWCNum);

						if (ISWC)
						{
							char ISWCStr[256];

							mb4_iswc_get_iswc(ISWC,ISWCStr,sizeof(ISWCStr));

							printf("Got ISWC %d - '%s'\n",ISWCNum,ISWCStr);
						}
					}
				}
			}
		}

		mb4_query_delete(Query);
	}

	return 0;

	if (argc==2)
	{
		strncpy(DiscID,argv[1],sizeof(DiscID));
		DiscID[sizeof(DiscID)-1]='\0';
	}

	Query=mb4_query_new("ctest",0,0);
	if (Query)
	{
		Mb4Metadata Metadata=NULL;
		char **ParamNames;
		char **ParamValues;

		printf("Got query\n");

		mb4_query_set_username(Query,"username");
		mb4_query_set_password(Query,"password");

		ParamNames=malloc(sizeof(char *));
		ParamNames[0]=malloc(256);
		ParamValues=malloc(sizeof(char *));
		ParamValues[0]=malloc(256);

		strcpy(ParamNames[0],"inc");
		strcpy(ParamValues[0],"artists release-groups url-rels work-level-rels work-rels artist-rels");

		Metadata=mb4_query_query(Query,"recording","3631f569-520d-40ff-a1ee-076604723275","",1,ParamNames,ParamValues);
		if (Metadata)
		{
			Mb4Recording Recording=mb4_metadata_get_recording(Metadata);
			printf("Got metadata\n");

			if (Recording)
			{
				Mb4RelationList RelationList=mb4_recording_get_relationlist(Recording);
				Mb4RelationListList RelationListList=mb4_recording_get_relationlistlist(Recording);

				printf("Got recording\n");

				if (RelationListList)
				{
					int RelationListNum;

					printf("Got relation list list, size %d\n",mb4_relationlist_list_size(RelationListList));

					for (RelationListNum=0;RelationListNum<mb4_relationlist_list_size(RelationListList);RelationListNum++)
					{
						Mb4RelationList RelationList=mb4_relationlist_list_item(RelationListList,RelationListNum);

						if (RelationList)
						{
							printf("Got relation list %d\n",RelationListNum);

							PrintRelationList(RelationList);
						}
					}
				}

				if (RelationList)
				{
					printf("Got relation list\n");

					PrintRelationList(RelationList);
				}
			}

			mb4_metadata_delete(Metadata);
		}

		Metadata=mb4_query_query(Query,"collection",0,0,0,NULL,NULL);
		if (Metadata)
		{
			printf("Got collections");
			mb4_metadata_delete(Metadata);
		}

		Metadata=mb4_query_query(Query,"discid",DiscID,0,0,NULL,NULL);
		if (Metadata)
		{
			Mb4Disc *Disc=mb4_metadata_get_disc(Metadata);
			printf("Got metadata\n");

			if (Disc)
			{
				int Len=0;
				char *Buff=0;
				Mb4ReleaseList ReleaseList=mb4_disc_get_releaselist(Disc);

				Len=mb4_disc_get_id(Disc,Buff,Len);
				printf("Len is %d\n",Len);
				Buff=malloc(Len+1);
				Len=mb4_disc_get_id(Disc,Buff,Len+1);
				printf("Len is %d (%s)\n",Len,Buff);
				free(Buff);

				printf("Got disc\n");

				if (ReleaseList)
				{
					int count;

					printf("Got release list\n");

					printf("%d items\n",mb4_release_list_size(ReleaseList));

					for (count=0;count<mb4_release_list_size(ReleaseList);count++)
					{
						char ID[256];
						Mb4Release Release=mb4_release_list_item(ReleaseList,count);

						printf("Got release %d\n",count);

						mb4_release_get_id(Release,ID,sizeof(ID));
						printf("ID is '%s'\n",ID);
					}
				}
			}

			mb4_metadata_delete(Metadata);
		}

		mb4_query_delete(Query);
	}

	return 0;
}

void CompileTest()
{
	Mb4Alias Alias=0;
	Mb4AliasList AliasList=0;
	Mb4Annotation Annotation=0;
	Mb4AnnotationList AnnotationList=0;
	Mb4Artist Artist=0;
	Mb4ArtistCredit ArtistCredit=0;
	Mb4ArtistList ArtistList=0;
	Mb4Attribute Attribute=0;
	Mb4AttributeList AttributeList=0;
	Mb4CDStub CDStub=0;
	Mb4CDStubList CDStubList=0;
	Mb4Collection Collection=0;
	Mb4CollectionList CollectionList=0;
	Mb4Disc Disc=0;
	Mb4DiscList DiscList=0;
	Mb4FreeDBDisc FreeDBDisc=0;
	Mb4FreeDBDiscList FreeDBDiscList=0;
	Mb4IPI IPI=0;
	Mb4IPIList IPIList=0;
	Mb4ISRC ISRC=0;
	Mb4ISRCList ISRCList=0;
	Mb4ISWC ISWC=0;
	Mb4ISWCList ISWCList=0;
	Mb4Label Label=0;
	Mb4LabelInfo LabelInfo=0;
	Mb4LabelInfoList LabelInfoList=0;
	Mb4LabelList LabelList=0;
	Mb4Lifespan Lifespan=0;
	Mb4Medium Medium=0;
	Mb4MediumList MediumList=0;
	Mb4Message Message=0;
	Mb4Metadata Metadata=0;
	Mb4NameCredit NameCredit=0;
	Mb4NameCreditList NameCreditList=0;
	Mb4NonMBTrack NonMBTrack=0;
	Mb4NonMBTrackList NonMBTrackList=0;
	Mb4PUID PUID=0;
	Mb4PUIDList PUIDList=0;
	Mb4Query Query=0;
	Mb4Rating Rating=0;
	Mb4Recording Recording=0;
	Mb4RecordingList RecordingList=0;
	Mb4Relation Relation=0;
	Mb4RelationList RelationList=0;
	Mb4RelationListList RelationListList=0;
	Mb4Release Release=0;
	Mb4ReleaseGroup ReleaseGroup=0;
	Mb4ReleaseGroupList ReleaseGroupList=0;
	Mb4ReleaseList ReleaseList=0;
	Mb4SecondaryType SecondaryType=0;
	Mb4SecondaryTypeList SecondaryTypeList=0;
	Mb4Tag Tag=0;
	Mb4TagList TagList=0;
	Mb4TextRepresentation TextRepresentation=0;
	Mb4Track Track=0;
	Mb4TrackList TrackList=0;
	Mb4UserRating UserRating=0;
	Mb4UserTag UserTag=0;
	Mb4UserTagList UserTagList=0;
	Mb4Work Work=0;
	Mb4WorkList WorkList=0;
	char Str[256];
	int Size=sizeof(Str);
	int DummyInt=0;
	double DummyDouble=0;
	unsigned char DummyBool=0;
	tQueryResult DummyResult=eQuery_Success;

	DummyInt=mb4_entity_ext_attributes_size(Alias);
	DummyInt=mb4_entity_ext_attribute_name(Alias, 0, Str, Size);
	DummyInt=mb4_entity_ext_attribute_value(Alias, 0, Str, Size);

	DummyInt=mb4_entity_ext_elements_size(Alias);
	DummyInt=mb4_entity_ext_element_name(Alias, 0, Str, Size);
	DummyInt=mb4_entity_ext_element_value(Alias, 0, Str, Size);

	mb4_alias_get_locale(Alias,Str,Size);
	mb4_alias_get_text(Alias,Str,Size);
	mb4_alias_get_sortname(Alias,Str,Size);
	mb4_alias_get_type(Alias,Str,Size);
	mb4_alias_get_primary(Alias,Str,Size);
	mb4_alias_get_begindate(Alias,Str,Size);
	mb4_alias_get_enddate(Alias,Str,Size);
	Alias=mb4_alias_clone(Alias);
	mb4_alias_delete(Alias);

	mb4_annotation_get_type(Annotation,Str,Size);
	mb4_annotation_get_entity(Annotation,Str,Size);
	mb4_annotation_get_name(Annotation,Str,Size);
	mb4_annotation_get_text(Annotation,Str,Size);
	Annotation=mb4_annotation_clone(Annotation);
	mb4_annotation_delete(Annotation);

	mb4_artist_get_id(Artist,Str,Size);
	mb4_artist_get_type(Artist,Str,Size);
	mb4_artist_get_name(Artist,Str,Size);
	mb4_artist_get_sortname(Artist,Str,Size);
	mb4_artist_get_gender(Artist,Str,Size);
	mb4_artist_get_country(Artist,Str,Size);
	mb4_artist_get_disambiguation(Artist,Str,Size);
	mb4_artist_get_ipi(Artist,Str,Size);
	IPIList=mb4_artist_get_ipilist(Artist);
	Lifespan=mb4_artist_get_lifespan(Artist);
	AliasList=mb4_artist_get_aliaslist(Artist);
	RecordingList=mb4_artist_get_recordinglist(Artist);
	ReleaseList=mb4_artist_get_releaselist(Artist);
	ReleaseGroupList=mb4_artist_get_releasegrouplist(Artist);
	LabelList=mb4_artist_get_labellist(Artist);
	WorkList=mb4_artist_get_worklist(Artist);
	RelationList=mb4_artist_get_relationlist(Artist);
	TagList=mb4_artist_get_taglist(Artist);
	UserTagList=mb4_artist_get_usertaglist(Artist);
	Rating=mb4_artist_get_rating(Artist);
	UserRating=mb4_artist_get_userrating(Artist);
	Artist=mb4_artist_clone(Artist);
	mb4_artist_delete(Artist);

	NameCreditList=mb4_artistcredit_get_namecreditlist(ArtistCredit);
	ArtistCredit=mb4_artistcredit_clone(ArtistCredit);
	mb4_artistcredit_delete(ArtistCredit);

	mb4_attribute_get_text(Attribute,Str,Size);
	Attribute=mb4_attribute_clone(Attribute);
	mb4_attribute_delete(Attribute);

	mb4_cdstub_get_id(CDStub,Str,Size);
	mb4_cdstub_get_title(CDStub,Str,Size);
	mb4_cdstub_get_artist(CDStub,Str,Size);
	mb4_cdstub_get_barcode(CDStub,Str,Size);
	mb4_cdstub_get_comment(CDStub,Str,Size);
	NonMBTrackList=mb4_cdstub_get_nonmbtracklist(CDStub);
	CDStub=mb4_cdstub_clone(CDStub);
	mb4_cdstub_delete(CDStub);

	mb4_disc_get_id(Disc,Str,Size);
	DummyInt=mb4_disc_get_sectors(Disc);
	ReleaseList=mb4_disc_get_releaselist(Disc);
	Disc=mb4_disc_clone(Disc);
	mb4_disc_delete(Disc);

	mb4_collection_get_id(Collection,Str,Size);
	mb4_collection_get_name(Collection,Str,Size);
	mb4_collection_get_editor(Collection,Str,Size);
	ReleaseList=mb4_collection_get_releaselist(Collection);
	Collection=mb4_collection_clone(Collection);
	mb4_collection_delete(Collection);

	mb4_freedbdisc_get_id(FreeDBDisc,Str,Size);
	mb4_freedbdisc_get_title(FreeDBDisc,Str,Size);
	mb4_freedbdisc_get_artist(FreeDBDisc,Str,Size);
	mb4_freedbdisc_get_category(FreeDBDisc,Str,Size);
	mb4_freedbdisc_get_year(FreeDBDisc,Str,Size);
	NonMBTrackList=mb4_freedbdisc_get_nonmbtracklist(FreeDBDisc);
	FreeDBDisc=mb4_freedbdisc_clone(FreeDBDisc);
	mb4_freedbdisc_delete(FreeDBDisc);

	mb4_ipi_get_ipi(IPI,Str,Size);
	IPI=mb4_ipi_clone(IPI);
	mb4_ipi_delete(IPI);

	mb4_isrc_get_id(ISRC,Str,Size);
	RecordingList=mb4_isrc_get_recordinglist(ISRC);
	ISRC=mb4_isrc_clone(ISRC);
	mb4_isrc_delete(ISRC);

	mb4_iswc_get_iswc(ISWC,Str,Size);
	ISWC=mb4_iswc_clone(ISWC);
	mb4_iswc_delete(ISWC);

	mb4_label_get_id(Label,Str,Size);
	mb4_label_get_type(Label,Str,Size);
	mb4_label_get_name(Label,Str,Size);
	mb4_label_get_sortname(Label,Str,Size);
	DummyInt=mb4_label_get_labelcode(Label);
	mb4_label_get_ipi(Label,Str,Size);
	IPIList=mb4_label_get_ipilist(Label);
	mb4_label_get_disambiguation(Label,Str,Size);
	mb4_label_get_country(Label,Str,Size);
	Lifespan=mb4_label_get_lifespan(Label);
	AliasList=mb4_label_get_aliaslist(Label);
	ReleaseList=mb4_label_get_releaselist(Label);
	RelationList=mb4_label_get_relationlist(Label);
	TagList=mb4_label_get_taglist(Label);
	UserTagList=mb4_label_get_usertaglist(Label);
	Rating=mb4_label_get_rating(Label);
	UserRating=mb4_label_get_userrating(Label);
	Label=mb4_label_clone(Label);
	mb4_label_delete(Label);

	mb4_labelinfo_get_catalognumber(LabelInfo,Str,Size);
	Label=mb4_labelinfo_get_label(LabelInfo);
	LabelInfo=mb4_labelinfo_clone(LabelInfo);
	mb4_labelinfo_delete(LabelInfo);

	mb4_lifespan_get_begin(Lifespan,Str,Size);
	mb4_lifespan_get_end(Lifespan,Str,Size);
	mb4_lifespan_get_ended(Lifespan,Str,Size);
	Lifespan=mb4_lifespan_clone(Lifespan);
	mb4_lifespan_delete(Lifespan);

	mb4_medium_get_title(Medium,Str,Size);
	DummyInt=mb4_medium_get_position(Medium);
	mb4_medium_get_format(Medium,Str,Size);
	DiscList=mb4_medium_get_disclist(Medium);
	TrackList=mb4_medium_get_tracklist(Medium);
	DummyBool=mb4_medium_contains_discid(Medium,"1234");
	Medium=mb4_medium_clone(Medium);
	mb4_medium_delete(Medium);

	mb4_message_get_text(Message,Str,Size);
	Message=mb4_message_clone(Message);
	mb4_message_delete(Message);

	mb4_metadata_get_xmlns(Metadata,Str,Size);
	mb4_metadata_get_xmlnsext(Metadata,Str,Size);
	mb4_metadata_get_generator(Metadata,Str,Size);
	mb4_metadata_get_created(Metadata,Str,Size);
	Artist=mb4_metadata_get_artist(Metadata);
	Release=mb4_metadata_get_release(Metadata);
	ReleaseGroup=mb4_metadata_get_releasegroup(Metadata);
	Recording=mb4_metadata_get_recording(Metadata);
	Label=mb4_metadata_get_label(Metadata);
	Work=mb4_metadata_get_work(Metadata);
	PUID=mb4_metadata_get_puid(Metadata);
	ISRC=mb4_metadata_get_isrc(Metadata);
	Disc=mb4_metadata_get_disc(Metadata);
	LabelInfoList=mb4_metadata_get_labelinfolist(Metadata);
	Rating=mb4_metadata_get_rating(Metadata);
	UserRating=mb4_metadata_get_userrating(Metadata);
	Collection=mb4_metadata_get_collection(Metadata);
	ArtistList=mb4_metadata_get_artistlist(Metadata);
	ReleaseList=mb4_metadata_get_releaselist(Metadata);
	ReleaseGroupList=mb4_metadata_get_releasegrouplist(Metadata);
	RecordingList=mb4_metadata_get_recordinglist(Metadata);
	LabelList=mb4_metadata_get_labellist(Metadata);
	WorkList=mb4_metadata_get_worklist(Metadata);
	ISRCList=mb4_metadata_get_isrclist(Metadata);
	AnnotationList=mb4_metadata_get_annotationlist(Metadata);
	CDStubList=mb4_metadata_get_cdstublist(Metadata);
	FreeDBDiscList=mb4_metadata_get_freedbdisclist(Metadata);
	TagList=mb4_metadata_get_taglist(Metadata);
	UserTagList=mb4_metadata_get_usertaglist(Metadata);
	CollectionList=mb4_metadata_get_collectionlist(Metadata);
	CDStub=mb4_metadata_get_cdstub(Metadata);
	Message=mb4_metadata_get_message(Metadata);
	Metadata=mb4_metadata_clone(Metadata);
	mb4_metadata_delete(Metadata);

	mb4_nonmbtrack_get_title(NonMBTrack,Str,Size);
	mb4_nonmbtrack_get_artist(NonMBTrack,Str,Size);
	DummyInt=mb4_nonmbtrack_get_length(NonMBTrack);
	NonMBTrack=mb4_nonmbtrack_clone(NonMBTrack);
	mb4_nonmbtrack_delete(NonMBTrack);

	mb4_namecredit_get_joinphrase(NameCredit,Str,Size);
	mb4_namecredit_get_name(NameCredit,Str,Size);
	Artist=mb4_namecredit_get_artist(NameCredit);
	NameCredit=mb4_namecredit_clone(NameCredit);
	mb4_namecredit_delete(NameCredit);

	mb4_puid_get_id(PUID,Str,Size);
	RecordingList=mb4_puid_get_recordinglist(PUID);
	PUID=mb4_puid_clone(PUID);
	mb4_puid_delete(PUID);

	Query=mb4_query_new("useragent", "server",0);
	mb4_query_set_username(Query,"");
	mb4_query_set_password(Query,"");
	mb4_query_set_proxyhost(Query,"");
	mb4_query_set_proxyport(Query,0);
	mb4_query_set_proxyusername(Query,"");
	mb4_query_set_proxypassword(Query,"");
	ReleaseList=mb4_query_lookup_discid(Query,"discid");
	Release=mb4_query_lookup_release(Query,"release");
	Metadata=mb4_query_query(Query,"entity","id","resource",0,0,0);
	DummyBool=mb4_query_add_collection_entries(Query,Collection,0,0);
	DummyBool=mb4_query_delete_collection_entries(Query,Collection,0,0);
	DummyResult=mb4_query_get_lastresult(Query);
	DummyInt=mb4_query_get_lasthttpcode(Query);
	mb4_query_get_lasterrormessage(Query,Str,Size);
	mb4_query_get_version(Query,Str,Size);
	mb4_query_delete(Query);

	DummyInt=mb4_rating_get_votescount(Rating);
	DummyDouble=mb4_rating_get_rating(Rating);
	Rating=mb4_rating_clone(Rating);
	mb4_rating_delete(Rating);

	mb4_recording_get_id(Recording,Str,Size);
	mb4_recording_get_title(Recording,Str,Size);
	DummyInt=mb4_recording_get_length(Recording);
	mb4_recording_get_disambiguation(Recording,Str,Size);
	ArtistCredit=mb4_recording_get_artistcredit(Recording);
	ReleaseList=mb4_recording_get_releaselist(Recording);
	PUIDList=mb4_recording_get_puidlist(Recording);
	ISRCList=mb4_recording_get_isrclist(Recording);
	RelationList=mb4_recording_get_relationlist(Recording);
	RelationListList=mb4_recording_get_relationlistlist(Recording);
	TagList=mb4_recording_get_taglist(Recording);
	UserTagList=mb4_recording_get_usertaglist(Recording);
	Rating=mb4_recording_get_rating(Recording);
	UserRating=mb4_recording_get_userrating(Recording);
	Recording=mb4_recording_clone(Recording);
	mb4_recording_delete(Recording);

	mb4_relation_get_type(Relation,Str,Size);
	mb4_relation_get_target(Relation,Str,Size);
	mb4_relation_get_direction(Relation,Str,Size);
	AttributeList=mb4_relation_get_attributelist(Relation);
	mb4_relation_get_begin(Relation,Str,Size);
	mb4_relation_get_end(Relation,Str,Size);
	Artist=mb4_relation_get_artist(Relation);
	Release=mb4_relation_get_release(Relation);
	ReleaseGroup=mb4_relation_get_releasegroup(Relation);
	Recording=mb4_relation_get_recording(Relation);
	Label=mb4_relation_get_label(Relation);
	Work=mb4_relation_get_work(Relation);
	Relation=mb4_relation_clone(Relation);
	mb4_relation_delete(Relation);

	mb4_release_get_id(Release,Str,Size);
	mb4_release_get_title(Release,Str,Size);
	mb4_release_get_status(Release,Str,Size);
	mb4_release_get_quality(Release,Str,Size);
	mb4_release_get_disambiguation(Release,Str,Size);
	mb4_release_get_packaging(Release,Str,Size);
	TextRepresentation=mb4_release_get_textrepresentation(Release);
	ArtistCredit=mb4_release_get_artistcredit(Release);
	ReleaseGroup=mb4_release_get_releasegroup(Release);
	mb4_release_get_date(Release,Str,Size);
	mb4_release_get_country(Release,Str,Size);
	mb4_release_get_barcode(Release,Str,Size);
	mb4_release_get_asin(Release,Str,Size);
	LabelInfoList=mb4_release_get_labelinfolist(Release);
	MediumList=mb4_release_get_mediumlist(Release);
	RelationList=mb4_release_get_relationlist(Release);
	CollectionList=mb4_release_get_collectionlist(Release);
	MediumList=mb4_release_media_matching_discid(Release,"discid");
	Release=mb4_release_clone(Release);
	mb4_release_delete(Release);

	mb4_releasegroup_get_id(ReleaseGroup,Str,Size);
	mb4_releasegroup_get_type(ReleaseGroup,Str,Size);
	mb4_releasegroup_get_primarytype(ReleaseGroup,Str,Size);
	mb4_releasegroup_get_firstreleasedate(ReleaseGroup,Str,Size);
	mb4_releasegroup_get_title(ReleaseGroup,Str,Size);
	mb4_releasegroup_get_disambiguation(ReleaseGroup,Str,Size);
	ArtistCredit=mb4_releasegroup_get_artistcredit(ReleaseGroup);
	ReleaseList=mb4_releasegroup_get_releaselist(ReleaseGroup);
	RelationList=mb4_releasegroup_get_relationlist(ReleaseGroup);
	TagList=mb4_releasegroup_get_taglist(ReleaseGroup);
	UserTagList=mb4_releasegroup_get_usertaglist(ReleaseGroup);
	Rating=mb4_releasegroup_get_rating(ReleaseGroup);
	UserRating=mb4_releasegroup_get_userrating(ReleaseGroup);
	SecondaryTypeList=mb4_releasegroup_get_secondarytypelist(ReleaseGroup);
	ReleaseGroup=mb4_releasegroup_clone(ReleaseGroup);
	mb4_releasegroup_delete(ReleaseGroup);

	DummyInt=mb4_tag_get_count(Tag);
	mb4_tag_get_name(Tag,Str,Size);
	Tag=mb4_tag_clone(Tag);
	mb4_tag_delete(Tag);

	mb4_textrepresentation_get_language(TextRepresentation,Str,Size);
	mb4_textrepresentation_get_script(TextRepresentation,Str,Size);
	TextRepresentation=mb4_textrepresentation_clone(TextRepresentation);
	mb4_textrepresentation_delete(TextRepresentation);

	DummyInt=mb4_track_get_position(Track);
	mb4_track_get_title(Track,Str,Size);
	Recording=mb4_track_get_recording(Track);
	DummyInt=mb4_track_get_length(Track);
	ArtistCredit=mb4_track_get_artistcredit(Track);
	mb4_track_get_number(Track,Str,Size);
	Track=mb4_track_clone(Track);
	mb4_track_delete(Track);

	DummyInt=mb4_userrating_get_userrating(UserRating);
	UserRating=mb4_userrating_clone(UserRating);
	mb4_userrating_delete(UserRating);

	mb4_usertag_get_name(UserTag,Str,Size);
	UserTag=mb4_usertag_clone(UserTag);
	mb4_usertag_delete(UserTag);

	mb4_work_get_id(Work,Str,Size);
	mb4_work_get_type(Work,Str,Size);
	mb4_work_get_title(Work,Str,Size);
	ArtistCredit=mb4_work_get_artistcredit(Work);
	mb4_work_get_iswc(Work,Str,Size);
	mb4_work_get_disambiguation(Work,Str,Size);
	AliasList=mb4_work_get_aliaslist(Work);
	RelationList=mb4_work_get_relationlist(Work);
	TagList=mb4_work_get_taglist(Work);
	UserTagList=mb4_work_get_usertaglist(Work);
	Rating=mb4_work_get_rating(Work);
	UserRating=mb4_work_get_userrating(Work);
	mb4_work_get_language(Work,Str,Size);

	mb4_alias_list_size(AliasList);
	Alias=mb4_alias_list_item(AliasList,0);
	AliasList=mb4_alias_clone(AliasList);
	DummyInt=mb4_alias_list_get_count(AliasList);
	DummyInt=mb4_alias_list_get_offset(AliasList);
	mb4_alias_list_delete(AliasList);

	mb4_annotation_list_size(AnnotationList);
	Annotation=mb4_annotation_list_item(AnnotationList,0);
	AnnotationList=mb4_annotation_list_clone(AnnotationList);
	DummyInt=mb4_annotation_list_get_count(AnnotationList);
	DummyInt=mb4_annotation_list_get_offset(AnnotationList);
	mb4_annotation_list_delete(AnnotationList);

	DummyInt=mb4_artist_list_size(ArtistList);
	Artist=mb4_artist_list_item(ArtistList,0);
	ArtistList=mb4_artist_list_clone(ArtistList);
	DummyInt=mb4_artist_list_get_count(ArtistList);
	DummyInt=mb4_artist_list_get_offset(ArtistList);
	mb4_artist_list_delete(ArtistList);

	DummyInt=mb4_attribute_list_size(AttributeList);
	Attribute=mb4_attribute_list_item(AttributeList,0);
	AttributeList=mb4_attribute_list_clone(AttributeList);
	DummyInt=mb4_attribute_list_get_count(AttributeList);
	DummyInt=mb4_attribute_list_get_offset(AttributeList);
	mb4_attribute_list_delete(AttributeList);

	DummyInt=mb4_cdstub_list_size(CDStubList);
	CDStub=mb4_cdstub_list_item(CDStubList,0);
	CDStubList=mb4_cdstub_list_clone(CDStubList);
	DummyInt=mb4_cdstub_list_get_count(CDStubList);
	DummyInt=mb4_cdstub_list_get_offset(CDStubList);
	mb4_cdstub_list_delete(CDStubList);

	DummyInt=mb4_collection_list_size(CollectionList);
	Collection=mb4_collection_list_item(CollectionList,0);
	CollectionList=mb4_collection_list_clone(CollectionList);
	DummyInt=mb4_collection_list_get_count(CollectionList);
	DummyInt=mb4_collection_list_get_offset(CollectionList);
	mb4_collection_list_delete(CollectionList);

	DummyInt=mb4_disc_list_size(DiscList);
	Disc=mb4_disc_list_item(DiscList,0);
	DiscList=mb4_disc_list_clone(DiscList);
	DummyInt=mb4_disc_list_get_count(DiscList);
	DummyInt=mb4_disc_list_get_offset(DiscList);
	mb4_disc_list_delete(DiscList);

	DummyInt=mb4_freedbdisc_list_size(FreeDBDiscList);
	FreeDBDisc=mb4_freedbdisc_list_item(FreeDBDiscList,0);
	FreeDBDiscList=mb4_freedbdisc_list_clone(FreeDBDiscList);
	DummyInt=mb4_freedbdisc_list_get_count(FreeDBDiscList);
	DummyInt=mb4_freedbdisc_list_get_offset(FreeDBDiscList);
	mb4_freedbdisc_list_delete(FreeDBDiscList);

	DummyInt=mb4_ipi_list_size(IPIList);
	ISRC=mb4_ipi_list_item(IPIList,0);
	ISRCList=mb4_ipi_list_clone(IPIList);
	DummyInt=mb4_ipi_list_get_count(IPIList);
	DummyInt=mb4_ipi_list_get_offset(IPIList);
	mb4_ipi_list_delete(IPIList);

	DummyInt=mb4_isrc_list_size(ISRCList);
	ISRC=mb4_isrc_list_item(ISRCList,0);
	ISRCList=mb4_isrc_list_clone(ISRCList);
	DummyInt=mb4_isrc_list_get_count(ISRCList);
	DummyInt=mb4_isrc_list_get_offset(ISRCList);
	mb4_isrc_list_delete(ISRCList);

	DummyInt=mb4_iswc_list_size(ISWCList);
	ISWC=mb4_iswc_list_item(ISWCList,0);
	ISWCList=mb4_iswc_list_clone(ISWCList);
	DummyInt=mb4_iswc_list_get_count(ISWCList);
	DummyInt=mb4_iswc_list_get_offset(ISWCList);
	mb4_iswc_list_delete(ISWCList);

	DummyInt=mb4_label_list_size(LabelList);
	Label=mb4_label_list_item(LabelList,0);
	LabelList=mb4_label_list_clone(LabelList);
	DummyInt=mb4_label_list_get_count(LabelList);
	DummyInt=mb4_label_list_get_offset(LabelList);
	mb4_label_list_delete(LabelList);

	DummyInt=mb4_labelinfo_list_size(LabelInfoList);
	LabelInfo=mb4_labelinfo_list_item(LabelInfoList,0);
	LabelInfoList=mb4_labelinfo_list_clone(LabelInfoList);
	DummyInt=mb4_labelinfo_list_get_count(LabelInfoList);
	DummyInt=mb4_labelinfo_list_get_offset(LabelInfoList);
	mb4_labelinfo_list_delete(LabelInfoList);

	DummyInt=mb4_medium_list_size(MediumList);
	Medium=mb4_medium_list_item(MediumList,0);
	DummyInt=mb4_medium_list_get_trackcount(MediumList);
	MediumList=mb4_medium_list_clone(MediumList);
	DummyInt=mb4_medium_list_get_count(MediumList);
	DummyInt=mb4_medium_list_get_offset(MediumList);
	mb4_medium_list_delete(MediumList);

	DummyInt=mb4_namecredit_list_size(NameCreditList);
	NameCredit=mb4_namecredit_list_item(NameCreditList,0);
	NameCreditList=mb4_namecredit_list_clone(NameCreditList);
	DummyInt=mb4_namecredit_list_get_count(NameCreditList);
	DummyInt=mb4_namecredit_list_get_offset(NameCreditList);
	mb4_namecredit_list_delete(NameCreditList);

	DummyInt=mb4_nonmbtrack_list_size(NonMBTrackList);
	NonMBTrack=mb4_nonmbtrack_list_item(NonMBTrackList,0);
	NonMBTrackList=mb4_nonmbtrack_list_clone(NonMBTrackList);
	DummyInt=mb4_nonmbtrack_list_get_count(NonMBTrackList);
	DummyInt=mb4_nonmbtrack_list_get_offset(NonMBTrackList);
	mb4_nonmbtrack_list_delete(NonMBTrackList);

	DummyInt=mb4_puid_list_size(PUIDList);
	PUID=mb4_puid_list_item(PUIDList,0);
	PUIDList=mb4_puid_list_clone(PUIDList);
	DummyInt=mb4_puid_list_get_count(PUIDList);
	DummyInt=mb4_puid_list_get_offset(PUIDList);
	mb4_puid_list_delete(PUIDList);

	DummyInt=mb4_recording_list_size(RecordingList);
	Recording=mb4_recording_list_item(RecordingList,0);
	RecordingList=mb4_recording_list_clone(RecordingList);
	DummyInt=mb4_recording_list_get_count(RecordingList);
	DummyInt=mb4_recording_list_get_offset(RecordingList);
	mb4_recording_list_delete(RecordingList);

	DummyInt=mb4_relation_list_size(RelationList);
	Relation=mb4_relation_list_item(RelationList,0);
	DummyInt=mb4_relation_list_get_targettype(RelationList,Str,Size);
	RelationList=mb4_relation_list_clone(RelationList);
	DummyInt=mb4_relation_list_get_count(RelationList);
	DummyInt=mb4_relation_list_get_offset(RelationList);
	mb4_relation_list_delete(RelationList);

	DummyInt=mb4_relationlist_list_size(RelationListList);
	Relation=mb4_relationlist_list_item(RelationListList,0);
	RelationList=mb4_relationlist_list_clone(RelationListList);
	DummyInt=mb4_relationlist_list_get_count(RelationListList);
	DummyInt=mb4_relationlist_list_get_offset(RelationListList);
	mb4_relationlist_list_delete(RelationListList);

	DummyInt=mb4_release_list_size(ReleaseList);
	Release=mb4_release_list_item(ReleaseList,0);
	ReleaseList=mb4_release_list_clone(ReleaseList);
	DummyInt=mb4_release_list_get_count(ReleaseList);
	DummyInt=mb4_release_list_get_offset(ReleaseList);
	mb4_release_list_delete(ReleaseList);

	DummyInt=mb4_releasegroup_list_size(ReleaseGroupList);
	ReleaseGroup=mb4_releasegroup_list_item(ReleaseGroupList,0);
	ReleaseGroupList=mb4_releasegroup_list_clone(ReleaseGroupList);
	DummyInt=mb4_releasegroup_list_get_count(ReleaseGroupList);
	DummyInt=mb4_releasegroup_list_get_offset(ReleaseGroupList);
	mb4_releasegroup_list_delete(ReleaseGroupList);

	DummyInt=mb4_secondarytype_list_size(SecondaryTypeList);
	SecondaryType=mb4_secondarytype_list_item(SecondaryTypeList,0);
	ReleaseGroupList=mb4_secondarytype_list_clone(SecondaryTypeList);
	DummyInt=mb4_secondarytype_list_get_count(SecondaryTypeList);
	DummyInt=mb4_secondarytype_list_get_offset(SecondaryTypeList);
	mb4_secondarytype_list_delete(SecondaryTypeList);

	DummyInt=mb4_tag_list_size(TagList);
	Tag=mb4_tag_list_item(TagList,0);
	TagList=mb4_tag_list_clone(TagList);
	DummyInt=mb4_tag_list_get_count(TagList);
	DummyInt=mb4_tag_list_get_offset(TagList);
	mb4_tag_list_delete(TagList);

	DummyInt=mb4_track_list_size(TrackList);
	Track=mb4_track_list_item(TrackList,0);
	TrackList=mb4_track_list_clone(TrackList);
	DummyInt=mb4_track_list_get_count(TrackList);
	DummyInt=mb4_track_list_get_offset(TrackList);
	mb4_track_list_delete(TrackList);

	DummyInt=mb4_usertag_list_size(UserTagList);
	UserTag=mb4_usertag_list_item(UserTagList,0);
	UserTagList=mb4_usertag_list_clone(UserTagList);
	DummyInt=mb4_usertag_list_get_count(UserTagList);
	DummyInt=mb4_usertag_list_get_offset(UserTagList);
	mb4_usertag_list_delete(UserTagList);

	DummyInt=mb4_work_list_size(WorkList);
	Work=mb4_work_list_item(WorkList,0);
	WorkList=mb4_work_list_clone(WorkList);
	DummyInt=mb4_work_list_get_count(WorkList);
	DummyInt=mb4_work_list_get_offset(WorkList);
	mb4_work_list_delete(WorkList);

	DummyInt=DummyInt;
	DummyDouble=DummyDouble;
	DummyBool=DummyBool;
	DummyResult=DummyResult;
	SecondaryType=SecondaryType;
}
