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

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

#ifndef _MUSICBRAINZ4_MB_C_H
#define _MUSICBRAINZ4_MB_C_H

#ifdef __cplusplus
extern "C"
{
#endif

	typedef void *Mb4Alias;
	typedef void *Mb4AliasList;
	typedef void *Mb4Annotation;
	typedef void *Mb4AnnotationList;
	typedef void *Mb4Artist;
	typedef void *Mb4ArtistCredit;
	typedef void *Mb4ArtistList;
	typedef void *Mb4Attribute;
	typedef void *Mb4AttributeList;
	typedef void *Mb4CDStub;
	typedef void *Mb4CDStubList;
	typedef void *Mb4Collection;
	typedef void *Mb4CollectionList;
	typedef void *Mb4Disc;
	typedef void *Mb4DiscList;
	typedef void *Mb4FreeDBDisc;
	typedef void *Mb4FreeDBDiscList;
	typedef void *Mb4ISRC;
	typedef void *Mb4ISRCList;
	typedef void *Mb4Label;
	typedef void *Mb4LabelInfo;
	typedef void *Mb4LabelInfoList;
	typedef void *Mb4LabelList;
	typedef void *Mb4Lifespan;
	typedef void *Mb4Medium;
	typedef void *Mb4MediumList;
	typedef void *Mb4Metadata;
	typedef void *Mb4NameCredit;
	typedef void *Mb4NameCreditList;
	typedef void *Mb4NoneMBTrack;
	typedef void *Mb4NoneMBTrackList;
	typedef void *Mb4PUID;
	typedef void *Mb4PUIDList;
	typedef void *Mb4Query;
	typedef void *Mb4Rating;
	typedef void *Mb4RatingList;
	typedef void *Mb4Recording;
	typedef void *Mb4RecordingList;
	typedef void *Mb4Relation;
	typedef void *Mb4RelationList;
	typedef void *Mb4Release;
	typedef void *Mb4ReleaseGroup;
	typedef void *Mb4ReleaseGroupList;
	typedef void *Mb4ReleaseList;
	typedef void *Mb4Tag;
	typedef void *Mb4TagList;
	typedef void *Mb4TextRepresentation;
	typedef void *Mb4Track;
	typedef void *Mb4TrackList;
	typedef void *Mb4UserRating;
	typedef void *Mb4UserTag;
	typedef void *Mb4UserTagList;
	typedef void *Mb4Work;
	typedef void *Mb4WorkList;

	void mb4_alias_delete(Mb4Alias Alias);
	void mb4_alias_get_type(Mb4Alias Alias, char *str, int len);
	void mb4_alias_get_script(Mb4Alias Alias, char *str, int len);
	void mb4_alias_get_text(Mb4Alias Alias, char *str, int len);

	void mb4_annotation_delete(Mb4Annotation Annotation);
	void mb4_annotation_get_type(Mb4Annotation Annotation, char *str, int len);
	void mb4_annotation_get_entity(Mb4Annotation Annotation, char *str, int len);
	void mb4_annotation_get_name(Mb4Annotation Annotation, char *str, int len);
	void mb4_annotation_get_text(Mb4Annotation Annotation, char *str, int len);

	void mb4_artist_delete(Mb4Artist Artist);
	void mb4_artist_get_id(Mb4Artist Artist, char *str, int len);
	void mb4_artist_get_type(Mb4Artist Artist, char *str, int len);
	void mb4_artist_get_name(Mb4Artist Artist, char *str, int len);
	void mb4_artist_get_sortname(Mb4Artist Artist, char *str, int len);
	void mb4_artist_get_gender(Mb4Artist Artist, char *str, int len);
	void mb4_artist_get_country(Mb4Artist Artist, char *str, int len);
	void mb4_artist_get_disambiguation(Mb4Artist Artist, char *str, int len);
	Mb4Lifespan mb4_artist_get_lifespan(Mb4Artist Artist);
	Mb4AliasList mb4_artist_get_aliaslist(Mb4Artist Artist);
	Mb4RecordingList mb4_artist_get_recordinglist(Mb4Artist Artist);
	Mb4ReleaseList mb4_artist_get_releaselist(Mb4Artist Artist);
	Mb4ReleaseGroupList mb4_artist_get_releasegrouplist(Mb4Artist Artist);
	Mb4LabelList mb4_artist_get_labellist(Mb4Artist Artist);
	Mb4WorkList mb4_artist_get_worklist(Mb4Artist Artist);
	Mb4RelationList mb4_artist_get_relationlist(Mb4Artist Artist);
	Mb4TagList mb4_artist_get_taglist(Mb4Artist Artist);
	Mb4UserTagList mb4_artist_get_usertaglist(Mb4Artist Artist);
	Mb4Rating mb4_artist_get_rating(Mb4Artist Artist);
	Mb4UserRating mb4_artist_get_userrating(Mb4Artist Artist);

	void mb4_artistcredit_delete(Mb4Artist Artist);
	Mb4NameCreditList mb4_artistcredit_get_namecreditlist(Mb4Artist Artist);

	void mb4_attribute_delete(Mb4Attribute Attribute);
	void mb4_attribute_get_text(Mb4Attribute Attribute, char *str, int len);

	void mb4_cdstub_delete(Mb4CDStub CDStub);
	void mb4_cdstub_get_id(Mb4CDStub CDStub, char *str, int len);
	void mb4_cdstub_get_title(Mb4CDStub CDStub, char *str, int len);
	void mb4_cdstub_get_artist(Mb4CDStub CDStub, char *str, int len);
	void mb4_cdstub_get_barcode(Mb4CDStub CDStub, char *str, int len);
	void mb4_cdstub_get_comment(Mb4CDStub CDStub, char *str, int len);
	Mb4NoneMBTrackList mb4_cdstub_get_nonembtracklist(Mb4CDStub CDStub);

	void mb4_collection_delete(Mb4Collection Collection);
	void mb4_collection_get_id(Mb4Collection Collection, char *str, int len);
	void mb4_collection_get_name(Mb4Collection Collection, char *str, int len);
	void mb4_collection_get_editor(Mb4Collection Collection, char *str, int len);
	Mb4ReleaseList mb4_collection_get_releaselist(Mb4Collection Collection);

	void mb4_disc_delete(Mb4Disc Disc);
	void mb4_disc_get_id(Mb4Disc Disc, char *str, int len);
	void mb4_disc_get_sectors(Mb4Disc Disc, char *str, int len);
	Mb4ReleaseList mb4_disc_get_releaselist(Mb4Disc Disc);

	void mb4_freedbdisc_delete(Mb4FreeDBDisc FreeDBDisc);
	void mb4_freedbdisc_get_id(Mb4FreeDBDisc FreeDBDisc, char *str, int len);
	void mb4_freedbdisc_get_title(Mb4FreeDBDisc FreeDBDisc, char *str, int len);
	void mb4_freedbdisc_get_artist(Mb4FreeDBDisc FreeDBDisc, char *str, int len);
	void mb4_freedbdisc_get_category(Mb4FreeDBDisc FreeDBDisc, char *str, int len);
	void mb4_freedbdisc_get_year(Mb4FreeDBDisc FreeDBDisc, char *str, int len);
	Mb4NoneMBTrackList mb4_freedbdisc_get_nonembtracklist(Mb4FreeDBDisc FreeDBDisc);

	void mb4_isrc_delete(Mb4ISRC ISRC);
	void mb4_isrc_get_id(Mb4ISRC ISRC, char *str, int len);
	Mb4RecordingList mb4_isrc_get_recordinglist(Mb4ISRC ISRC);

	void mb4_label_delete(Mb4Label Label);
	void mb4_label_get_id(Mb4Label Label, char *str, int len);
	void mb4_label_get_type(Mb4Label Label, char *str, int len);
	void mb4_label_get_name(Mb4Label Label, char *str, int len);
	void mb4_label_get_sortname(Mb4Label Label, char *str, int len);
	void mb4_label_get_labelcode(Mb4Label Label, char *str, int len);
	void mb4_label_get_disambiguation(Mb4Label Label, char *str, int len);
	void mb4_label_get_country(Mb4Label Label, char *str, int len);
	Mb4Lifespan mb4_label_get_lifespan(Mb4Label Label);
	Mb4AliasList mb4_label_get_aliaslist(Mb4Label Label);
	Mb4ReleaseList mb4_label_get_releaselist(Mb4Label Label);
	Mb4RelationList mb4_label_get_relationlist(Mb4Label Label);
	Mb4TagList mb4_label_get_taglist(Mb4Label Label);
	Mb4UserTagList mb4_label_get_usertaglist(Mb4Label Label);
	Mb4Rating mb4_label_get_rating(Mb4Label Label);
	Mb4UserRating mb4_label_get_userrating(Mb4Label Label);

	void mb4_labelinfo_delete(Mb4LabelInfo LabelInfo);
	void mb4_labelinfo_get_catalognumber(Mb4LabelInfo LabelInfo, char *str, int len);
	Mb4Label mb4_labelinfo_get_label(Mb4LabelInfo LabelInfo);

	void mb4_lifespan_delete(Mb4Lifespan Lifespan);
	void mb4_lifespan_get_begin(Mb4Lifespan Lifespan, char *str, int len);
	void mb4_lifespan_get_end(Mb4Lifespan Lifespan, char *str, int len);

	void mb4_medium_delete(Mb4Medium Medium);
	void mb4_medium_get_title(Mb4Medium Medium, char *str, int len);
	int mb4_medium_get_position(Mb4Medium Medium);
	void mb4_medium_get_format(Mb4Medium Medium, char *str, int len);
	Mb4DiscList mb4_medium_get_disclist(Mb4Medium Medium);
	Mb4TrackList mb4_medium_get_tracklist(Mb4Medium Medium);
	unsigned char mb4_medium_contains_discid(Mb4Medium Medium, const char *DiscID);

	void mb4_metadata_delete(Mb4Metadata Metadata);
	void mb4_metadata_get_generator(Mb4Metadata Metadata, char *str, int len);
	void mb4_metadata_get_created(Mb4Metadata Metadata, char *str, int len);
	Mb4Artist mb4_metadata_get_artist(Mb4Metadata Metadata);
	Mb4Release mb4_metadata_get_release(Mb4Metadata Metadata);
	Mb4ReleaseGroup mb4_metadata_get_releasegroup(Mb4Metadata Metadata);
	Mb4Recording mb4_metadata_get_recording(Mb4Metadata Metadata);
	Mb4Label mb4_metadata_get_label(Mb4Metadata Metadata);
	Mb4Work mb4_metadata_get_work(Mb4Metadata Metadata);
	Mb4PUID mb4_metadata_get_puid(Mb4Metadata Metadata);
	Mb4ISRC mb4_metadata_get_isrc(Mb4Metadata Metadata);
	Mb4Disc mb4_metadata_get_disc(Mb4Metadata Metadata);
	Mb4LabelInfoList mb4_metadata_get_labelinfolist(Mb4Metadata Metadata);
	Mb4Rating mb4_metadata_get_rating(Mb4Metadata Metadata);
	Mb4UserRating mb4_metadata_get_userrating(Mb4Metadata Metadata);
	Mb4Collection mb4_metadata_get_collection(Mb4Metadata Metadata);
	Mb4ArtistList mb4_metadata_get_artistlist(Mb4Metadata Metadata);
	Mb4ReleaseList mb4_metadata_get_releaselist(Mb4Metadata Metadata);
	Mb4ReleaseGroupList mb4_metadata_get_releasegrouplist(Mb4Metadata Metadata);
	Mb4RecordingList mb4_metadata_get_recordinglist(Mb4Metadata Metadata);
	Mb4LabelList mb4_metadata_get_labellist(Mb4Metadata Metadata);
	Mb4WorkList mb4_metadata_get_worklist(Mb4Metadata Metadata);
	Mb4ISRCList mb4_metadata_get_isrclist(Mb4Metadata Metadata);
	Mb4AnnotationList mb4_metadata_get_annotationlist(Mb4Metadata Metadata);
	Mb4CDStubList mb4_metadata_get_cdstublist(Mb4Metadata Metadata);
	Mb4FreeDBDiscList mb4_metadata_get_freedbdisclist(Mb4Metadata Metadata);
	Mb4TagList mb4_metadata_get_taglist(Mb4Metadata Metadata);
	Mb4UserTagList mb4_metadata_get_usertaglist(Mb4Metadata Metadata);
	Mb4CollectionList mb4_metadata_get_collectionlist(Mb4Metadata Metadata);
	Mb4CDStub mb4_metadata_get_cdstub(Mb4Metadata Metadata);

	void mb4_namecredit_delete(Mb4NameCredit NameCredit);
	void mb4_namecredit_get_joinphrase(Mb4NameCredit NameCredit, char *str, int len);
	void mb4_namecredit_get_name(Mb4NameCredit NameCredit, char *str, int len);
	Mb4Artist mb4_namecredit_get_artist(Mb4NameCredit NameCredit);

	void mb4_nonembtrack_delete(Mb4NoneMBTrack NoneMBTrack);
	void mb4_nonembtrack_get_title(Mb4NoneMBTrack NoneMBTrack, char *str, int len);
	void mb4_nonembtrack_get_artist(Mb4NoneMBTrack NoneMBTrack, char *str, int len);
	void mb4_nonembtrack_get_length(Mb4NoneMBTrack NoneMBTrack, char *str, int len);

	void mb4_puid_delete(Mb4PUID PUID);
	void mb4_puid_get_id(Mb4PUID PUID, char *str, int len);
	Mb4RecordingList mb4_puid_get_recordinglist(Mb4PUID PUID);

	Mb4Query mb4_query_new(const char *Server);
	void mb4_query_delete(Mb4Query Query);
	Mb4ReleaseList mb4_query_lookup_discid(Mb4Query Query, const char *DiscID);
	Mb4Release mb4_query_lookup_release(Mb4Query Query, const char *Release);
	Mb4Metadata mb4_query_query(Mb4Query Query, const char *Resource, const char *ID, int NumParams, char **ParamNames, char **ParamValues);

	void mb4_rating_delete(Mb4Rating Rating);
	int mb4_rating_get_votescount(Mb4Rating Rating);
	double mb4_rating_get_rating(Mb4Rating Rating);

	void mb4_recording_delete(Mb4Recording Recording);
	void mb4_recording_get_id(Mb4Recording Recording, char *str, int len);
	void mb4_recording_get_title(Mb4Recording Recording, char *str, int len);
	void mb4_recording_get_length(Mb4Recording Recording, char *str, int len);
	void mb4_recording_get_disambiguation(Mb4Recording Recording, char *str, int len);
	Mb4ArtistCredit mb4_recording_get_artistcredit(Mb4Recording Recording);
	Mb4ReleaseList mb4_recording_get_releaselist(Mb4Recording Recording);
	Mb4PUIDList mb4_recording_get_puidlist(Mb4Recording Recording);
	Mb4ISRCList mb4_recording_get_isrclist(Mb4Recording Recording);
	Mb4RelationList mb4_recording_get_relationlist(Mb4Recording Recording);
	Mb4TagList mb4_recording_get_taglist(Mb4Recording Recording);
	Mb4UserTagList mb4_recording_get_usertaglist(Mb4Recording Recording);
	Mb4Rating mb4_recording_get_rating(Mb4Recording Recording);
	Mb4UserRating mb4_recording_get_userrating(Mb4Recording Recording);

	void mb4_release_delete(Mb4Release Release);
	void mb4_release_get_id(Mb4Release Release, char *str, int len);
	void m4b_release_get_title(Mb4Release Release, char *str, int len);
	void m4b_release_get_status(Mb4Release Release, char *str, int len);
	void m4b_release_get_quality(Mb4Release Release, char *str, int len);
	void m4b_release_get_disambiguation(Mb4Release Release, char *str, int len);
	void m4b_release_get_packaging(Mb4Release Release, char *str, int len);
	Mb4TextRepresentation mb4_release_get_textrepresentation(Mb4Release Release);
	void m4b_release_get_date(Mb4Release Release, char *str, int len);
	void m4b_release_get_country(Mb4Release Release, char *str, int len);
	void m4b_release_get_barcode(Mb4Release Release, char *str, int len);
	void m4b_release_get_asin(Mb4Release Release, char *str, int len);
	Mb4LabelInfoList mb4_release_get_labelinfolist(Mb4Release Release);
	Mb4MediumList mb4_release_get_mediumlist(Mb4Release Release);
	Mb4RelationList mb4_release_get_relationlist(Mb4Release Release);
	Mb4MediumList mb4_release_media_matching_discid(Mb4Release Release, const char *DiscID);

	void mb4_relation_delete(Mb4Relation Relation);
	void mb4_relation_get_type(Mb4Relation Relation, char *str, int len);
	void mb4_relation_get_target(Mb4Relation Relation, char *str, int len);
	void mb4_relation_get_direction(Mb4Relation Relation, char *str, int len);
	Mb4AttributeList mb4_relation_get_attributelist(Mb4Relation Relation);
	void mb4_relation_get_begin(Mb4Relation Relation, char *str, int len);
	void mb4_relation_get_end(Mb4Relation Relation, char *str, int len);
	Mb4Artist mb4_relation_get_artist(Mb4Relation Relation);
	Mb4Release mb4_relation_get_release(Mb4Relation Relation);
	Mb4ReleaseGroup mb4_relation_get_releasegroup(Mb4Relation Relation);
	Mb4Recording mb4_relation_get_recording(Mb4Relation Relation);
	Mb4Label mb4_relation_get_label(Mb4Relation Relation);
	Mb4Work mb4_relation_get_work(Mb4Relation Relation);

	void mb4_release_delete(Mb4Release Release);
	void mb4_release_get_id(Mb4Release Release, char *str, int len);
	void mb4_release_get_title(Mb4Release Release, char *str, int len);
	void mb4_release_get_status(Mb4Release Release, char *str, int len);
	void mb4_release_get_quality(Mb4Release Release, char *str, int len);
	void mb4_release_get_disambiguation(Mb4Release Release, char *str, int len);
	void mb4_release_get_packaging(Mb4Release Release, char *str, int len);
	Mb4TextRepresentation mb4_release_get_textrepresentation(Mb4Release Release);
	Mb4ArtistCredit mb4_release_get_artistcredit(Mb4Release Release);
	Mb4ReleaseGroup mb4_release_get_releasegroup(Mb4Release Release);
	void mb4_release_get_date(Mb4Release Release, char *str, int len);
	void mb4_release_get_country(Mb4Release Release, char *str, int len);
	void mb4_release_get_barcode(Mb4Release Release, char *str, int len);
	void mb4_release_get_asin(Mb4Release Release, char *str, int len);
	Mb4LabelInfoList mb4_release_get_labelinfolist(Mb4Release Release);
	Mb4MediumList mb4_release_get_mediumlist(Mb4Release Release);
	Mb4RelationList mb4_release_get_relationlist(Mb4Release Release);
	Mb4MediumList mb4_release_media_matching_disc_id(Mb4Release Release, const char *DiscID);

	void mb4_releasegroup_delete(Mb4ReleaseGroup ReleaseGroup);
	void mb4_releasegroup_get_id(Mb4ReleaseGroup ReleaseGroup, char *str, int len);
	void mb4_releasegroup_get_type(Mb4ReleaseGroup ReleaseGroup, char *str, int len);
	void mb4_releasegroup_get_title(Mb4ReleaseGroup ReleaseGroup, char *str, int len);
	void mb4_releasegroup_get_comment(Mb4ReleaseGroup ReleaseGroup, char *str, int len);
	Mb4ArtistCredit mb4_releasegroup_get_artistcredit(Mb4ReleaseGroup ReleaseGroup);
	Mb4ReleaseList mb4_releasegroup_get_releaselist(Mb4ReleaseGroup ReleaseGroup);
	Mb4RelationList mb4_releasegroup_get_relationlist(Mb4ReleaseGroup ReleaseGroup);
	Mb4TagList mb4_releasegroup_get_taglist(Mb4ReleaseGroup ReleaseGroup);
	Mb4UserTagList mb4_releasegroup_get_usertaglist(Mb4ReleaseGroup ReleaseGroup);
	Mb4Rating mb4_releasegroup_get_rating(Mb4ReleaseGroup ReleaseGroup);
	Mb4UserRating mb4_releasegroup_get_userrating(Mb4ReleaseGroup ReleaseGroup);

	void mb4_tag_delete(Mb4Tag Tag);
	int mb4_tag_get_count(Mb4Tag Tag);
	void mb4_tag_get_name(Mb4Tag Tag, char *str, int len);

	void mb4_textrepresentation_delete(Mb4TextRepresentation TextRepresentation);
	void mb4_textrepresentation_get_language(Mb4TextRepresentation TextRepresentation, char *str, int len);
	void mb4_textrepresentation_get_script(Mb4TextRepresentation TextRepresentation, char *str, int len);

	void mb4_track_delete(Mb4Track Track);
	int mb4_track_get_position(Mb4Track Track);
	void mb4_track_get_title(Mb4Track Track, char *str, int len);
	Mb4Recording mb4_track_get_recording(Mb4Track Track, char *str, int len);

	void mb4_userrating_delete(Mb4UserRating UserRating);
	int mb4_userrating_get_userrating(Mb4UserRating UserRating);

	void mb4_usertag_delete(Mb4UserTag UserTag);
	void mb4_usertag_get_name(Mb4UserTag UserTag, char *str, int len);

	void mb4_work_delete(Mb4Work Work);
	void mb4_work_get_id(Mb4Work Work, char *str, int len);
	void mb4_work_get_type(Mb4Work Work, char *str, int len);
	void mb4_work_get_title(Mb4Work Work, char *str, int len);
	Mb4ArtistCredit mb4_work_get_artistcredit(Mb4Work Work);
	void mb4_work_get_iswc(Mb4Work Work, char *str, int len);
	void mb4_work_get_disambiguation(Mb4Work Work, char *str, int len);
	Mb4AliasList mb4_work_get_aliaslist(Mb4Work Work);
	Mb4RelationList mb4_work_get_relationlist(Mb4Work Work);
	Mb4TagList mb4_work_get_taglist(Mb4Work Work);
	Mb4UserTagList mb4_work_get_usertaglist(Mb4Work Work);
	Mb4Rating mb4_work_get_rating(Mb4Work Work);
	Mb4UserRating mb4_work_get_userrating(Mb4Work Work);

	void mb4_alias_list_delete(Mb4AliasList List);
	int mb4_alias_list_size(Mb4AliasList List);
	Mb4Alias mb4_alias_list_item(Mb4AliasList List, int Item);

	void mb4_annotation_list_delete(Mb4AnnotationList List);
	int mb4_annotation_list_size(Mb4AnnotationList List);
	Mb4Annotation mb4_annoation_list_item(Mb4AnnotationList List, int Item);

	void mb4_artist_list_delete(Mb4ArtistList List);
	int mb4_artist_list_size(Mb4ArtistList List);
	Mb4Artist mb4_artist_list_item(Mb4ArtistList List, int Item);

	void mb4_attribute_list_delete(Mb4AttributeList List);
	int mb4_attribute_list_size(Mb4AttributeList List);
	Mb4Attribute mb4_attribute_list_item(Mb4AttributeList List, int Item);

	void mb4_cdstub_list_delete(Mb4CDStubList List);
	int mb4_cdstub_list_size(Mb4CDStubList List);
	Mb4CDStub mb4_cdstub_list_item(Mb4CDStubList List, int Item);

	void mb4_collection_list_delete(Mb4CollectionList List);
	int mb4_collection_list_size(Mb4CollectionList List);
	Mb4Collection mb4_collection_list_item(Mb4CollectionList List, int Item);

	void mb4_disc_list_delete(Mb4DiscList List);
	int mb4_disc_list_size(Mb4DiscList List);
	Mb4Disc mb4_disc_list_item(Mb4DiscList List, int Item);

	void mb4_freedbdisc_list_delete(Mb4FreeDBDiscList List);
	int mb4_freedbdisc_list_size(Mb4FreeDBDiscList List);
	Mb4FreeDBDisc mb4_freedbdisc_list_item(Mb4FreeDBDiscList List, int Item);

	void mb4_isrc_list_delete(Mb4ISRCList List);
	int mb4_isrc_list_size(Mb4ISRCList List);
	Mb4ISRC mb4_isrc_list_item(Mb4ISRCList List, int Item);

	void mb4_label_list_delete(Mb4LabelList List);
	int mb4_label_list_size(Mb4LabelList List);
	Mb4Label mb4_label_list_item(Mb4LabelList List, int Item);

	void mb4_labelinfo_list_delete(Mb4LabelInfoList List);
	int mb4_labelinfo_list_size(Mb4LabelInfoList List);
	Mb4LabelInfo mb4_labelinfo_list_item(Mb4LabelInfoList List, int Item);

	void mb4_medium_list_delete(Mb4MediumList List);
	int mb4_medium_list_size(Mb4MediumList List);
	Mb4Medium mb4_medium_list_item(Mb4MediumList List, int Item);

	void mb4_namecredit_list_delete(Mb4NameCreditList List);
	int mb4_namecredit_list_size(Mb4NameCreditList List);
	Mb4NameCredit mb4_namecredit_list_item(Mb4NameCreditList List, int Item);

	void mb4_nonembtrack_list_delete(Mb4NoneMBTrackList List);
	int mb4_nonembtrack_list_size(Mb4NoneMBTrackList List);
	Mb4NoneMBTrack mb4_nonembtrack_list_item(Mb4NoneMBTrackList List, int Item);

	void mb4_puid_list_delete(Mb4PUIDList List);
	int mb4_puid_list_size(Mb4PUIDList List);
	Mb4PUID mb4_puid_list_item(Mb4PUIDList List, int Item);

	void mb4_recording_list_delete(Mb4RecordingList List);
	int mb4_recording_list_size(Mb4RecordingList List);
	Mb4Recording mb4_recording_list_item(Mb4RecordingList List, int Item);

	void mb4_relation_list_delete(Mb4RelationList List);
	int mb4_relation_list_size(Mb4RelationList List);
	Mb4Relation mb4_relation_list_item(Mb4RelationList List, int Item);

	void mb4_release_list_delete(Mb4ReleaseList List);
	int mb4_release_list_size(Mb4ReleaseList List);
	Mb4Release mb4_release_list_item(Mb4ReleaseList List, int Item);

	void mb4_releasegroup_list_delete(Mb4ReleaseGroupList List);
	int mb4_releasegroup_list_size(Mb4ReleaseGroupList List);
	Mb4ReleaseGroup mb4_releasegroup_list_item(Mb4ReleaseGroupList List, int Item);

	void mb4_tag_list_delete(Mb4TagList List);
	int mb4_tag_list_size(Mb4TagList List);
	Mb4Tag mb4_tag_list_item(Mb4TagList List, int Item);

	void mb4_track_list_delete(Mb4TrackList List);
	int mb4_track_list_size(Mb4TrackList List);
	Mb4Track mb4_track_list_item(Mb4TrackList List, int Item);

	void mb4_usertag_list_delete(Mb4UserTagList List);
	int mb4_usertag_list_size(Mb4UserTagList List);
	Mb4UserTag mb4_usertag_list_item(Mb4UserTagList List, int Item);

	void mb4_work_list_delete(Mb4WorkList List);
	int mb4_work_list_size(Mb4WorkList List);
	Mb4Work mb4_work_list_item(Mb4WorkList List, int Item);

#ifdef __cplusplus
}
#endif

#endif


