#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "musicbrainz4/mb_c.h"

int main(int argc, const char *argv[])
{
	Mb4Query Query=0;
	char DiscID[256]="tLGBAiCflG8ZI6lFcOt87vXjEcI-";

	if (argc==2)
	{
		strncpy(DiscID,argv[1],sizeof(DiscID));
		DiscID[sizeof(DiscID)-1]='\0';
	}

	Query=mb4_query_new("www.musicbrainz.org");
	if (Query)
	{
		Mb4Metadata Metadata=NULL;

		printf("Got query\n");

		Metadata=mb4_query_query(Query,"discid",DiscID,0,NULL,NULL);
		if (Metadata)
		{
			Mb4Disc *Disc=mb4_metadata_get_disc(Metadata);
			printf("Got metadata\n");

			if (Disc)
			{
				Mb4ReleaseList ReleaseList=mb4_disc_get_releaselist(Disc);

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

						mb4_release_delete(Release);
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
	Mb4ISRC ISRC=0;
	Mb4ISRCList ISRCList=0;
	Mb4Label Label=0;
	Mb4LabelInfo LabelInfo=0;
	Mb4LabelInfoList LabelInfoList=0;
	Mb4LabelList LabelList=0;
	Mb4Lifespan Lifespan=0;
	Mb4Medium Medium=0;
	Mb4MediumList MediumList=0;
	Mb4Metadata Metadata=0;
	Mb4NameCredit NameCredit=0;
	Mb4NameCreditList NameCreditList=0;
	Mb4NoneMBTrack NoneMBTrack=0;
	Mb4NoneMBTrackList NoneMBTrackList=0;
	Mb4PUID PUID=0;
	Mb4PUIDList PUIDList=0;
	Mb4Query Query=0;
	Mb4Rating Rating=0;
	Mb4Recording Recording=0;
	Mb4RecordingList RecordingList=0;
	Mb4Relation Relation=0;
	Mb4RelationList RelationList=0;
	Mb4Release Release=0;
	Mb4ReleaseGroup ReleaseGroup=0;
	Mb4ReleaseGroupList ReleaseGroupList=0;
	Mb4ReleaseList ReleaseList=0;
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

	mb4_alias_get_type(Alias,Str,Size);
	mb4_alias_get_script(Alias,Str,Size);
	mb4_alias_get_text(Alias,Str,Size);
	mb4_alias_delete(Alias);

	mb4_annotation_get_type(Annotation,Str,Size);
	mb4_annotation_get_entity(Annotation,Str,Size);
	mb4_annotation_get_name(Annotation,Str,Size);
	mb4_annotation_get_text(Annotation,Str,Size);
	mb4_annotation_delete(Annotation);

	mb4_artist_get_id(Artist,Str,Size);
	mb4_artist_get_type(Artist,Str,Size);
	mb4_artist_get_name(Artist,Str,Size);
	mb4_artist_get_sortname(Artist,Str,Size);
	mb4_artist_get_gender(Artist,Str,Size);
	mb4_artist_get_country(Artist,Str,Size);
	mb4_artist_get_disambiguation(Artist,Str,Size);
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
	mb4_artist_delete(Artist);

	NameCreditList=mb4_artistcredit_get_namecreditlist(ArtistCredit);
	mb4_artistcredit_delete(ArtistCredit);

	mb4_attribute_get_text(Attribute,Str,Size);
	mb4_attribute_delete(Attribute);

	mb4_cdstub_get_id(CDStub,Str,Size);
	mb4_cdstub_get_title(CDStub,Str,Size);
	mb4_cdstub_get_artist(CDStub,Str,Size);
	mb4_cdstub_get_barcode(CDStub,Str,Size);
	mb4_cdstub_get_comment(CDStub,Str,Size);
	NoneMBTrackList=mb4_cdstub_get_nonembtracklist(CDStub);
	mb4_cdstub_delete(CDStub);

	mb4_disc_get_id(Disc,Str,Size);
	mb4_disc_get_sectors(Disc,Str,Size);
	ReleaseList=mb4_disc_get_releaselist(Disc);
	mb4_disc_delete(Disc);

	mb4_collection_get_id(Collection,Str,Size);
	mb4_collection_get_name(Collection,Str,Size);
	mb4_collection_get_editor(Collection,Str,Size);
	ReleaseList=mb4_collection_get_releaselist(Collection);
	mb4_collection_delete(Collection);

	mb4_freedbdisc_get_id(FreeDBDisc,Str,Size);
	mb4_freedbdisc_get_title(FreeDBDisc,Str,Size);
	mb4_freedbdisc_get_artist(FreeDBDisc,Str,Size);
	mb4_freedbdisc_get_category(FreeDBDisc,Str,Size);
	mb4_freedbdisc_get_year(FreeDBDisc,Str,Size);
	NoneMBTrackList=mb4_freedbdisc_get_nonembtracklist(FreeDBDisc);
	mb4_freedbdisc_delete(FreeDBDisc);

	mb4_isrc_get_id(ISRC,Str,Size);
	RecordingList=mb4_isrc_get_recordinglist(ISRC);
	mb4_isrc_delete(ISRC);

	mb4_label_get_id(Label,Str,Size);
	mb4_label_get_type(Label,Str,Size);
	mb4_label_get_name(Label,Str,Size);
	mb4_label_get_sortname(Label,Str,Size);
	mb4_label_get_labelcode(Label,Str,Size);
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
	mb4_label_delete(Label);

	mb4_labelinfo_get_catalognumber(LabelInfo,Str,Size);
	Label=mb4_labelinfo_get_label(LabelInfo);
	mb4_labelinfo_delete(LabelInfo);

	mb4_lifespan_get_begin(Lifespan,Str,Size);
	mb4_lifespan_get_end(Lifespan,Str,Size);
	mb4_lifespan_delete(Lifespan);

	mb4_medium_get_title(Medium,Str,Size);
	DummyInt=mb4_medium_get_position(Medium);
	mb4_medium_get_format(Medium,Str,Size);
	DiscList=mb4_medium_get_disclist(Medium);
	TrackList=mb4_medium_get_tracklist(Medium);
	DummyBool=mb4_medium_contains_discid(Medium,"1234");
	mb4_medium_delete(Medium);

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
	mb4_metadata_delete(Metadata);

	mb4_nonembtrack_get_title(NoneMBTrack,Str,Size);
	mb4_nonembtrack_get_artist(NoneMBTrack,Str,Size);
	mb4_nonembtrack_get_length(NoneMBTrack,Str,Size);
	mb4_nonembtrack_delete(NoneMBTrack);

	mb4_namecredit_get_joinphrase(NameCredit,Str,Size);
	mb4_namecredit_get_name(NameCredit,Str,Size);
	Artist=mb4_namecredit_get_artist(NameCredit);
	mb4_namecredit_delete(NameCredit);

	mb4_puid_get_id(PUID,Str,Size);
	RecordingList=mb4_puid_get_recordinglist(PUID);
	mb4_puid_delete(PUID);

	Query=mb4_query_new("server");
	ReleaseList=mb4_query_lookup_discid(Query,"discid");
	Release=mb4_query_lookup_release(Query,"release");
	Metadata=mb4_query_query(Query,"resource","id",0,0,0);
	mb4_query_delete(Query);

	DummyInt=mb4_rating_get_votescount(Rating);
	DummyDouble=mb4_rating_get_rating(Rating);
	mb4_rating_delete(Rating);

	mb4_recording_get_id(Recording,Str,Size);
	mb4_recording_get_title(Recording,Str,Size);
	mb4_recording_get_length(Recording,Str,Size);
	mb4_recording_get_disambiguation(Recording,Str,Size);
	ArtistCredit=mb4_recording_get_artistcredit(Recording);
	ReleaseList=mb4_recording_get_releaselist(Recording);
	PUIDList=mb4_recording_get_puidlist(Recording);
	ISRCList=mb4_recording_get_isrclist(Recording);
	RelationList=mb4_recording_get_relationlist(Recording);
	TagList=mb4_recording_get_taglist(Recording);
	UserTagList=mb4_recording_get_usertaglist(Recording);
	Rating=mb4_recording_get_rating(Recording);
	UserRating=mb4_recording_get_userrating(Recording);
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
	MediumList=mb4_release_media_matching_discid(Release,"discid");
	mb4_release_delete(Release);

	mb4_releasegroup_get_id(ReleaseGroup,Str,Size);
	mb4_releasegroup_get_type(ReleaseGroup,Str,Size);
	mb4_releasegroup_get_title(ReleaseGroup,Str,Size);
	mb4_releasegroup_get_comment(ReleaseGroup,Str,Size);
	ArtistCredit=mb4_releasegroup_get_artistcredit(ReleaseGroup);
	ReleaseList=mb4_releasegroup_get_releaselist(ReleaseGroup);
	RelationList=mb4_releasegroup_get_relationlist(ReleaseGroup);
	TagList=mb4_releasegroup_get_taglist(ReleaseGroup);
	UserTagList=mb4_releasegroup_get_usertaglist(ReleaseGroup);
	Rating=mb4_releasegroup_get_rating(ReleaseGroup);
	UserRating=mb4_releasegroup_get_userrating(ReleaseGroup);
	mb4_releasegroup_delete(ReleaseGroup);

	DummyInt=mb4_tag_get_count(Tag);
	mb4_tag_get_name(Tag,Str,Size);
	mb4_tag_delete(Tag);

	mb4_textrepresentation_get_language(TextRepresentation,Str,Size);
	mb4_textrepresentation_get_script(TextRepresentation,Str,Size);
	mb4_textrepresentation_delete(TextRepresentation);

	DummyInt=mb4_track_get_position(Track);
	mb4_track_get_title(Track,Str,Size);
	Recording=mb4_track_get_recording(Track);
	mb4_track_delete(Track);

	DummyInt=mb4_userrating_get_userrating(UserRating);
	mb4_userrating_delete(UserRating);

	mb4_usertag_get_name(UserTag,Str,Size);
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

	mb4_alias_list_size(AliasList);
	Alias=mb4_alias_list_item(AliasList,0);
	mb4_alias_list_delete(AliasList);

}
