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
	typedef void *Mb4Artist;
	typedef void *Mb4ArtistCredit;
	typedef void *Mb4Attribute;
	typedef void *Mb4CDStub;
	typedef void *Mb4Collection;
	typedef void *Mb4Disc;
	typedef void *Mb4FreeDBDisc;
	typedef void *Mb4ISRC;
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
	Mb4ReleaseGroupList mb4_artist_get_grouplist(Mb4Artist Artist);
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

	void mb4_metadata_delete(Mb4Metadata Metadata);
	Mb4ReleaseList mb4_metadata_get_releaselist(Mb4Metadata Metadata);
	Mb4Disc mb4_metadata_get_disc(Mb4Metadata Metadata);

	Mb4Query mb4_query_new(const char *Server);
	void mb4_query_delete(Mb4Query Query);
	Mb4Metadata mb4_query_query(Mb4Query Query, const char *Resource, const char *ID, int NumParams, char **ParamNames, char **ParamValues);

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

	int mb4_alias_list_size(Mb4AliasList List);
	Mb4Alias mb4_alias_list_item(Mb4AliasList List, int Item);

	int mb4_label_list_size(Mb4LabelList List);
	Mb4Label mb4_label_list_item(Mb4LabelList List, int Item);

	int mb4_labelinfo_list_size(Mb4LabelInfoList List);
	Mb4LabelInfo mb4_labelinfo_list_item(Mb4LabelInfoList List, int Item);

	int mb4_medium_list_size(Mb4MediumList List);
	Mb4Medium mb4_medium_list_item(Mb4MediumList List, int Item);

	int mb4_nonembtrack_list_size(Mb4NoneMBTrackList List);
	Mb4NoneMBTrack mb4_nonembtrack_list_item(Mb4NoneMBTrackList List, int Item);

	int mb4_namecredit_list_size(Mb4NameCreditList List);
	Mb4NameCredit mb4_namecredit_list_item(Mb4NameCreditList List, int Item);

	int mb4_recording_list_size(Mb4RecordingList List);
	Mb4Recording mb4_recording_list_item(Mb4RecordingList List, int Item);

	int mb4_relation_list_size(Mb4RelationList List);
	Mb4Relation mb4_relation_list_item(Mb4RelationList List, int Item);

	int mb4_releasegroup_list_size(Mb4ReleaseGroupList List);
	Mb4ReleaseGroup mb4_releasegroup_list_item(Mb4ReleaseGroupList List, int Item);

	int mb4_release_list_size(Mb4ReleaseList List);
	Mb4Release mb4_release_list_item(Mb4ReleaseList List, int Item);

	int mb4_tag_list_size(Mb4TagList List);
	Mb4Tag mb4_tag_list_item(Mb4TagList List, int Item);

	int mb4_usertag_list_size(Mb4UserTagList List);
	Mb4UserTag mb4_usertag_list_item(Mb4UserTagList List, int Item);

	int mb4_work_list_size(Mb4WorkList List);
	Mb4Work mb4_work_list_item(Mb4WorkList List, int Item);

#ifdef __cplusplus
}
#endif

#endif


