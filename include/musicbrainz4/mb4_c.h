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

/*

	Things you should delete using the appropriate mb4_xxx_delete() function:

	* The query object you create to do the actual work
	* Any object or list returned from one of the mb4_query_xxx() functions
	* Any list item retrieved from mb4_xxxx_list_item() functions
	* The return from mb4_release_media_matching_discid() function

	Everything else remains managed by the library, and should not be deleted

	If in doubt, valgrind is a useful way to spot leaks or things being deleted
	when they shouldn't be.

*/



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
	typedef void *Mb4Message;
	typedef void *Mb4Metadata;
	typedef void *Mb4NameCredit;
	typedef void *Mb4NameCreditList;
	typedef void *Mb4NoneMBTrack;
	typedef void *Mb4NoneMBTrackList;
	typedef void *Mb4PUID;
	typedef void *Mb4PUIDList;
	typedef void *Mb4Query;
	typedef void *Mb4Rating;
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

/**
 * delete an Alias object
 *
 * @param Alias Object to delete
 */
	void mb4_alias_delete(Mb4Alias Alias);

/**
 * @see MusicBrainz4::CAlias::Type
 *
 * @param Alias Alias object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_alias_get_type(Mb4Alias Alias, char *str, int len);

/**
 * @see MusicBrainz4::CAlias::Script
 *
 * @param Alias Alias object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_alias_get_script(Mb4Alias Alias, char *str, int len);

/**
 * @see MusicBrainz4::CAlias::Text
 *
 * @param Alias Alias object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_alias_get_text(Mb4Alias Alias, char *str, int len);


/**
 * Delete an Annotation object
 *
 * @param Annotation Object to delete
 */
	void mb4_annotation_delete(Mb4Annotation Annotation);

/**
 * @see MusicBrainz4::CAnnotation::Type
 *
 * @param Annotation Annotation object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_annotation_get_type(Mb4Annotation Annotation, char *str, int len);

/**
 * @see MusicBrainz4::CAnnotation::Entity
 *
 * @param Annotation Annotation object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_annotation_get_entity(Mb4Annotation Annotation, char *str, int len);

/**
 * @see MusicBrainz4::CAnnotation::Name
 *
 * @param Annotation Annotation object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_annotation_get_name(Mb4Annotation Annotation, char *str, int len);

/**
 * @see MusicBrainz4::CAnnotation::Text
 *
 * @param Annotation Annotation object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_annotation_get_text(Mb4Annotation Annotation, char *str, int len);


/**
 * Delete an Artist object
 *
 * @param Artist Object to delete
 */
	void mb4_artist_delete(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::ID
 *
 * @param Artist Artist object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_artist_get_id(Mb4Artist Artist, char *str, int len);

/**
 * @see MusicBrainz4::CArtist::Type
 *
 * @param Artist Artist object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_artist_get_type(Mb4Artist Artist, char *str, int len);

/**
 * @see MusicBrainz4::CArtist::Name
 *
 * @param Artist Artist object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_artist_get_name(Mb4Artist Artist, char *str, int len);

/**
 * @see MusicBrainz4::CArtist::SortName
 *
 * @param Artist Artist object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_artist_get_sortname(Mb4Artist Artist, char *str, int len);

/**
 * @see MusicBrainz4::CArtist::Gender
 *
 * @param Artist Artist object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_artist_get_gender(Mb4Artist Artist, char *str, int len);

/**
 * @see MusicBrainz4::CArtist::Country
 *
 * @param Artist Artist object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_artist_get_country(Mb4Artist Artist, char *str, int len);

/**
 * @see MusicBrainz4::CArtist::Disambiguation
 *
 * @param Artist Artist object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_artist_get_disambiguation(Mb4Artist Artist, char *str, int len);

/**
 * @see MusicBrainz4::CArtist::Lifespan
 *
 * @param Artist Artist object
 *
 * @return Lifespan object
 */
	Mb4Lifespan mb4_artist_get_lifespan(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::AliasList
 *
 * @param Artist Artist object
 *
 * @return Alias list.
 */
	Mb4AliasList mb4_artist_get_aliaslist(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::RecordingList
 *
 * @param Artist Artist object
 *
 * @return Recording list.
 */
	Mb4RecordingList mb4_artist_get_recordinglist(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::ReleaseList
 *
 * @param Artist Artist object
 *
 * @return Release list.
 */
	Mb4ReleaseList mb4_artist_get_releaselist(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::ReleaseGroupList
 *
 * @param Artist Artist object
 *
 * @return ReleaseGroup list.
 */
	Mb4ReleaseGroupList mb4_artist_get_releasegrouplist(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::LabelList
 *
 * @param Artist Artist object
 *
 * @return Label list.
 */
	Mb4LabelList mb4_artist_get_labellist(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::WorkList
 *
 * @param Artist Artist object
 *
 * @return Work list.
 */
	Mb4WorkList mb4_artist_get_worklist(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::RelationList
 *
 * @param Artist Artist object
 *
 * @return Relation list.
 */
	Mb4RelationList mb4_artist_get_relationlist(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::TagList
 *
 * @param Artist Artist object
 *
 * @return Tag list.
 */
	Mb4TagList mb4_artist_get_taglist(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::UserTagList
 *
 * @param Artist Artist object
 *
 * @return UserTag list.
 */
	Mb4UserTagList mb4_artist_get_usertaglist(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::Rating
 *
 * @param Artist Artist object
 *
 * @return Rating object.
 */
	Mb4Rating mb4_artist_get_rating(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::UserRating
 *
 * @param Artist Artist object
 *
 * @return UserRating object.
 */
	Mb4UserRating mb4_artist_get_userrating(Mb4Artist Artist);


/**
 * Delete an ArtistCredit object
 *
 * @param ArtistCredit Object to delete
 */
	void mb4_artistcredit_delete(Mb4ArtistCredit ArtistCredit);

/**
 * @see MusicBrainz4::CArtistCredit::NameCreditList
 *
 * @param ArtistCredit ArtistCredit object
 *
 * @return NameCredit list.
 */
	Mb4NameCreditList mb4_artistcredit_get_namecreditlist(Mb4ArtistCredit ArtistCredit);


/**
 * Delete an Attribute object
 *
 * @param Attribute Object to delete
 */
	void mb4_attribute_delete(Mb4Attribute Attribute);

/**
 * @see MusicBrainz4::CAttribute::Text
 *
 * @param Attribute Attribute object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_attribute_get_text(Mb4Attribute Attribute, char *str, int len);


/**
 * Delete a CDStub object
 *
 * @param CDStub Object to delete
 */
	void mb4_cdstub_delete(Mb4CDStub CDStub);

/**
 * @see MusicBrainz4::CCDStub::ID
 *
 * @param CDStub CDStub object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_cdstub_get_id(Mb4CDStub CDStub, char *str, int len);

/**
 * @see MusicBrainz4::CCDStub::Title
 *
 * @param CDStub CDStub object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_cdstub_get_title(Mb4CDStub CDStub, char *str, int len);

/**
 * @see MusicBrainz4::CCDStub::Artist
 *
 * @param CDStub CDStub object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_cdstub_get_artist(Mb4CDStub CDStub, char *str, int len);

/**
 * @see MusicBrainz4::CCDStub::Barcode
 *
 * @param CDStub CDStub object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_cdstub_get_barcode(Mb4CDStub CDStub, char *str, int len);

/**
 * @see MusicBrainz4::CCDStub::Comment
 *
 * @param CDStub CDStub object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_cdstub_get_comment(Mb4CDStub CDStub, char *str, int len);

/**
 * @see MusicBrainz4::CCDStub::NoneMBTrackList
 *
 * @param CDStub CDStub object
 *
 * @return NoneMBTrack list.
 */
	Mb4NoneMBTrackList mb4_cdstub_get_nonembtracklist(Mb4CDStub CDStub);


/**
 * Delete a Collection object
 *
 * @param Collection Object to delete
 */
	void mb4_collection_delete(Mb4Collection Collection);

/**
 * @see MusicBrainz4::CCollection::ID
 *
 * @param Collection Collection object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_collection_get_id(Mb4Collection Collection, char *str, int len);

/**
 * @see MusicBrainz4::CCollection::Name
 *
 * @param Collection Collection object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_collection_get_name(Mb4Collection Collection, char *str, int len);

/**
 * @see MusicBrainz4::CCollection::Editor
 *
 * @param Collection Collection object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_collection_get_editor(Mb4Collection Collection, char *str, int len);

/**
 * @see MusicBrainz4::CCollection::ReleaseList
 *
 * @param Collection Collection object
 *
 * @return Release list.
 */
	Mb4ReleaseList mb4_collection_get_releaselist(Mb4Collection Collection);


/**
 * Delete a Disc object
 *
 * @param Disc Object to delete
 */
	void mb4_disc_delete(Mb4Disc Disc);

/**
 * @see MusicBrainz4::CDisc::ID
 *
 * @param Disc Disc object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_disc_get_id(Mb4Disc Disc, char *str, int len);

/**
 * @see MusicBrainz4::CDisc::Sectors
 *
 * @param Disc Disc object
 *
 * @return Number of sectors
 */
	int mb4_disc_get_sectors(Mb4Disc Disc);

/**
 * @see MusicBrainz4::CDisc::ReleaseList
 *
 * @param Disc Disc object
 *
 * @return Release list.
 */
	Mb4ReleaseList mb4_disc_get_releaselist(Mb4Disc Disc);


/**
 * Delete a FreeDBDisc object
 *
 * @param FreeDBDisc Object to delete
 */
	void mb4_freedbdisc_delete(Mb4FreeDBDisc FreeDBDisc);

/**
 * @see MusicBrainz4::CFreeDBDisc::ID
 *
 * @param FreeDBDisc FreeDBDisc object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_freedbdisc_get_id(Mb4FreeDBDisc FreeDBDisc, char *str, int len);

/**
 * @see MusicBrainz4::CFreeDBDisc::Title
 *
 * @param FreeDBDisc FreeDBDisc object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_freedbdisc_get_title(Mb4FreeDBDisc FreeDBDisc, char *str, int len);

/**
 * @see MusicBrainz4::CFreeDBDisc::Artist
 *
 * @param FreeDBDisc FreeDBDisc object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_freedbdisc_get_artist(Mb4FreeDBDisc FreeDBDisc, char *str, int len);

/**
 * @see MusicBrainz4::CFreeDBDisc::Category
 *
 * @param FreeDBDisc FreeDBDisc object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_freedbdisc_get_category(Mb4FreeDBDisc FreeDBDisc, char *str, int len);

/**
 * @see MusicBrainz4::CFreeDBDisc::Year
 *
 * @param FreeDBDisc FreeDBDisc object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_freedbdisc_get_year(Mb4FreeDBDisc FreeDBDisc, char *str, int len);

/**
 * @see MusicBrainz4::CFreeDBDisc::NoneMBTrackList
 *
 * @param FreeDBDisc FreeDBDisc object
 *
 * @return NoneMBTrack list.
 */
	Mb4NoneMBTrackList mb4_freedbdisc_get_nonembtracklist(Mb4FreeDBDisc FreeDBDisc);


/**
 * Delete an ISRC object
 *
 * @param ISRC Object to delete
 */
	void mb4_isrc_delete(Mb4ISRC ISRC);

/**
 * @see MusicBrainz4::CISRC::ID
 *
 * @param ISRC ISRC object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_isrc_get_id(Mb4ISRC ISRC, char *str, int len);

/**
 * @see MusicBrainz4::CISRC::RecordingList
 *
 * @param ISRC ISRC object
 *
 * @return Recording list.
 */
	Mb4RecordingList mb4_isrc_get_recordinglist(Mb4ISRC ISRC);


/**
 * Delete a Label object
 *
 * @param Label Object to delete
 */
	void mb4_label_delete(Mb4Label Label);

/**
 * @see MusicBrainz4::CLabel::ID
 *
 * @param Label Label object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_label_get_id(Mb4Label Label, char *str, int len);

/**
 * @see MusicBrainz4::CLabel::Type
 *
 * @param Label Label object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_label_get_type(Mb4Label Label, char *str, int len);

/**
 * @see MusicBrainz4::CLabel::Name
 *
 * @param Label Label object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_label_get_name(Mb4Label Label, char *str, int len);

/**
 * @see MusicBrainz4::CLabel::SortName
 *
 * @param Label Label object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_label_get_sortname(Mb4Label Label, char *str, int len);

/**
 * @see MusicBrainz4::CLabel::LabelCode
 *
 * @param Label Label object
 *
 * @return Label code
 */
	int mb4_label_get_labelcode(Mb4Label Label);

/**
 * @see MusicBrainz4::CLabel::Disambiguation
 *
 * @param Label Label object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_label_get_disambiguation(Mb4Label Label, char *str, int len);

/**
 * @see MusicBrainz4::CLabel::Country
 *
 * @param Label Label object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_label_get_country(Mb4Label Label, char *str, int len);

/**
 * @see MusicBrainz4::CLabel::Lifespan
 *
 * @param Label Label object
 *
 * @return Lifespan object
 */
	Mb4Lifespan mb4_label_get_lifespan(Mb4Label Label);

/**
 * @see MusicBrainz4::CLabel::AliasList
 *
 * @param Label Label object
 *
 * @return Alias list.
 */
	Mb4AliasList mb4_label_get_aliaslist(Mb4Label Label);

/**
 * @see MusicBrainz4::CLabel::ReleaseList
 *
 * @param Label Label object
 *
 * @return Release list.
 */
	Mb4ReleaseList mb4_label_get_releaselist(Mb4Label Label);

/**
 * @see MusicBrainz4::CLabel::RelationList
 *
 * @param Label Label object
 *
 * @return Relation list.
 */
	Mb4RelationList mb4_label_get_relationlist(Mb4Label Label);

/**
 * @see MusicBrainz4::CLabel::TagList
 *
 * @param Label Label object
 *
 * @return Tag list.
 */
	Mb4TagList mb4_label_get_taglist(Mb4Label Label);

/**
 * @see MusicBrainz4::CLabel::UserTagList
 *
 * @param Label Label object
 *
 * @return UserTag list.
 */
	Mb4UserTagList mb4_label_get_usertaglist(Mb4Label Label);

/**
 * @see MusicBrainz4::CLabel::Rating
 *
 * @param Label Label object
 *
 * @return Rating object
 */
	Mb4Rating mb4_label_get_rating(Mb4Label Label);

/**
 * @see MusicBrainz4::CLabel::UserRating
 *
 * @param Label Label object
 *
 * @return UserRating object
 */
	Mb4UserRating mb4_label_get_userrating(Mb4Label Label);


/**
 * Delete a LabelInfo object
 *
 * @param LabelInfo Object to delete
 */
	void mb4_labelinfo_delete(Mb4LabelInfo LabelInfo);

/**
 * @see MusicBrainz4::CLabelInfo::CatalogNumber
 *
 * @param LabelInfo LabelInfo object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_labelinfo_get_catalognumber(Mb4LabelInfo LabelInfo, char *str, int len);

/**
 * @see MusicBrainz4::CLabelInfo::Label
 *
 * @param LabelInfo LabelInfo object
 *
 * @return Label object
 */
	Mb4Label mb4_labelinfo_get_label(Mb4LabelInfo LabelInfo);


/**
 * Delete a Lifespan object
 *
 * @param Lifespan Object to delete
 */
	void mb4_lifespan_delete(Mb4Lifespan Lifespan);

/**
 * @see MusicBrainz4::CLifespan::Begin
 *
 * @param Lifespan Lifespan object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_lifespan_get_begin(Mb4Lifespan Lifespan, char *str, int len);

/**
 * @see MusicBrainz4::CLifespan::End
 *
 * @param Lifespan Lifespan object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_lifespan_get_end(Mb4Lifespan Lifespan, char *str, int len);


/**
 * Delete a Medium object
 *
 * @param Medium Object to delete
 */
	void mb4_medium_delete(Mb4Medium Medium);

/**
 * @see MusicBrainz4::CMedium::Title
 *
 * @param Medium Medium object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_medium_get_title(Mb4Medium Medium, char *str, int len);

/**
 * @see MusicBrainz4::CMedium::Position
 *
 * @param Medium Medium object
 *
 * @return Returned position
 */
	int mb4_medium_get_position(Mb4Medium Medium);

/**
 * @see MusicBrainz4::CMedium::Format
 *
 * @param Medium Medium object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_medium_get_format(Mb4Medium Medium, char *str, int len);

/**
 * @see MusicBrainz4::CMedium::DiscList
 *
 * @param Medium Medium object
 *
 * @return DiscList object
 */
	Mb4DiscList mb4_medium_get_disclist(Mb4Medium Medium);

/**
 * @see MusicBrainz4::CMedium::TrackList
 *
 * @param Medium Medium object
 *
 * @return TrackList object
 */
	Mb4TrackList mb4_medium_get_tracklist(Mb4Medium Medium);

/**
 * @see MusicBrainz4::CMedium::ContainsDiscID
 *
 * @param Medium Medium object
 * @param DiscID DiscID to check
 *
 * @return 1 if DiscID found, 0 otherwise
 */
	unsigned char mb4_medium_contains_discid(Mb4Medium Medium, const char *DiscID);


/**
 * Delete a Message object
 *
 * @param Message Object to delete
 */
	void mb4_message_delete(Mb4Message Message);

/**
 * @see MusicBrainz4::CMessage::Text
 *
 * @param Message Message object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_message_get_text(Mb4Message Message, char *str, int len);


/**
 * Delete a Metadata object
 *
 * @param Metadata Object to delete
 */
	void mb4_metadata_delete(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::Generator
 *
 * @param Metadata Metadata object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_metadata_get_generator(Mb4Metadata Metadata, char *str, int len);

/**
 * @see MusicBrainz4::CMetadata::Created
 *
 * @param Metadata Metadata object
 * @param str Returned string
 * @param len Number of characters available in return string
 */
	void mb4_metadata_get_created(Mb4Metadata Metadata, char *str, int len);

/**
 * @see MusicBrainz4::CMetadata::Artist
 *
 * @param Metadata Metadata object
 *
 * @return Artist object
 */
	Mb4Artist mb4_metadata_get_artist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::Release
 *
 * @param Metadata Metadata object
 *
 * @return Release object
 */
	Mb4Release mb4_metadata_get_release(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::ReleaseGroup
 *
 * @param Metadata Metadata object
 *
 * @return ReleaseGroup object
 */
	Mb4ReleaseGroup mb4_metadata_get_releasegroup(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::Recording
 *
 * @param Metadata Metadata object
 *
 * @return Recording object
 */
	Mb4Recording mb4_metadata_get_recording(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::Label
 *
 * @param Metadata Metadata object
 *
 * @return Label object
 */
	Mb4Label mb4_metadata_get_label(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::Work
 *
 * @param Metadata Metadata object
 *
 * @return Work object
 */
	Mb4Work mb4_metadata_get_work(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::PUID
 *
 * @param Metadata Metadata object
 *
 * @return PUID object
 */
	Mb4PUID mb4_metadata_get_puid(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::ISRC
 *
 * @param Metadata Metadata object
 *
 * @return ISRC object
 */
	Mb4ISRC mb4_metadata_get_isrc(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::Disc
 *
 * @param Metadata Metadata object
 *
 * @return Disc object
 */
	Mb4Disc mb4_metadata_get_disc(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::LabelInfoList
 *
 * @param Metadata Metadata object
 *
 * @return LabelInfo list
 */
	Mb4LabelInfoList mb4_metadata_get_labelinfolist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::Rating
 *
 * @param Metadata Metadata object
 *
 * @return Rating object
 */
	Mb4Rating mb4_metadata_get_rating(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::UserRating
 *
 * @param Metadata Metadata object
 *
 * @return UserRating object
 */
	Mb4UserRating mb4_metadata_get_userrating(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::Collection
 *
 * @param Metadata Metadata object
 *
 * @return Collection object
 */
	Mb4Collection mb4_metadata_get_collection(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::ArtistList
 *
 * @param Metadata Metadata object
 *
 * @return Artist list
 */
	Mb4ArtistList mb4_metadata_get_artistlist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::ReleaseList
 *
 * @param Metadata Metadata object
 *
 * @return Release list
 */
	Mb4ReleaseList mb4_metadata_get_releaselist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::ReleaseGroupList
 *
 * @param Metadata Metadata object
 *
 * @return ReleaseGroup list
 */
	Mb4ReleaseGroupList mb4_metadata_get_releasegrouplist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::RecordingList
 *
 * @param Metadata Metadata object
 *
 * @return Recording list
 */
	Mb4RecordingList mb4_metadata_get_recordinglist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::LabelList
 *
 * @param Metadata Metadata object
 *
 * @return Label list
 */
	Mb4LabelList mb4_metadata_get_labellist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::WorkList
 *
 * @param Metadata Metadata object
 *
 * @return Work list
 */
	Mb4WorkList mb4_metadata_get_worklist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::ISRC
 *
 * @param Metadata Metadata object
 *
 * @return ISRC list
 */
	Mb4ISRCList mb4_metadata_get_isrclist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::AnnotationList
 *
 * @param Metadata Metadata object
 *
 * @return Annotation list
 */
	Mb4AnnotationList mb4_metadata_get_annotationlist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::CDStubList
 *
 * @param Metadata Metadata object
 *
 * @return CDStub list
 */
	Mb4CDStubList mb4_metadata_get_cdstublist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::FreeDBDiscList
 *
 * @param Metadata Metadata object
 *
 * @return FreeFBDisc list
 */
	Mb4FreeDBDiscList mb4_metadata_get_freedbdisclist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::TagList
 *
 * @param Metadata Metadata object
 *
 * @return Tag list
 */
	Mb4TagList mb4_metadata_get_taglist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::UserTagList
 *
 * @param Metadata Metadata object
 *
 * @return UserTag list
 */
	Mb4UserTagList mb4_metadata_get_usertaglist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::CollectionList
 *
 * @param Metadata Metadata object
 *
 * @return Collection list
 */
	Mb4CollectionList mb4_metadata_get_collectionlist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::CDStub
 *
 * @param Metadata Metadata object
 *
 * @return CDStub object
 */
	Mb4CDStub mb4_metadata_get_cdstub(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::Message
 *
 * @param Metadata Metadata object
 *
 * @return Message object
 */
	Mb4Message mb4_metadata_get_message(Mb4Metadata Metadata);


/**
 * Delete an object
 *
 * @param NameCredit Object to delete
 */
	void mb4_namecredit_delete(Mb4NameCredit NameCredit);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_namecredit_get_joinphrase(Mb4NameCredit NameCredit, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_namecredit_get_name(Mb4NameCredit NameCredit, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4Artist mb4_namecredit_get_artist(Mb4NameCredit NameCredit);


/**
 * Delete an object
 *
 * @param NoneMBTrack Object to delete
 */
	void mb4_nonembtrack_delete(Mb4NoneMBTrack NoneMBTrack);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_nonembtrack_get_title(Mb4NoneMBTrack NoneMBTrack, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_nonembtrack_get_artist(Mb4NoneMBTrack NoneMBTrack, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	int mb4_nonembtrack_get_length(Mb4NoneMBTrack NoneMBTrack);


/**
 * Delete an object
 *
 * @param PUID Object to delete
 */
	void mb4_puid_delete(Mb4PUID PUID);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_puid_get_id(Mb4PUID PUID, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4RecordingList mb4_puid_get_recordinglist(Mb4PUID PUID);

/**
 * Create a new instance of CQuery.
 *
 * @see MusicBrainz4::CQuery::CQuery
 *
 * @param UserAgent User agent to be passed to submissions
 * @param Server Server to use, pass null to use the default server
 * @param Port Port to use, pass 0 to use the default port
 *
 * @return The newly created Query object. This object <b>must</b> be deleted once
 *				finished with.
 */

	Mb4Query mb4_query_new(const char *UserAgent, const char *Server, int Port);

/**
 * Delete a Query object
 *
 * @param Query Object to delete
 */
	void mb4_query_delete(Mb4Query Query);

/**
 * Set the username for authenticating to MusicBrainz
 *
 * @see MusicBrainz4::CQuery::SetUserName
 *
 * @param Query Query object
 * @param UserName Username to use
 */
	void mb4_query_set_username(Mb4Query Query, const char *UserName);

/**
 * Set the password for authenticating to MusicBrainz
 *
 * @see MusicBrainz4::CQuery::SetPassword
 *
 * @param Query Query object
 * @param Password Password to use
 */
	void mb4_query_set_password(Mb4Query Query, const char *Password);

/**
 * Set the proxy server
 *
 * @see MusicBrainz4::CQuery::SetProxyHost
 *
 * @param Query Query object
 * @param ProxyHost Proxy server to use
 */
	void mb4_query_set_proxyhost(Mb4Query Query, const char *ProxyHost);

/**
 *	Set the port to use on the proxy server
 *
 * @see MusicBrainz4::CQuery::SetProxyPort
 *
 * @param Query Query object
 * @param ProxyPort Port to use on proxy server
 */
	void mb4_query_set_proxyport(Mb4Query Query, int ProxyPort);

/**
 *	Set the username to use to authenticate to the proxy server
 *
 * @see MusicBrainz4::CQuery::SetProxyUserName
 *
 * @param Query Query object
 * @param	ProxyUserName User name to use
 */
	void mb4_query_set_proxyusername(Mb4Query Query, const char *ProxyUserName);

/**
 * Set the password to use to authenticate to the proxy server
 *
 * @see MusicBrainz4::CQuery::SetProxyPassword
 *
 * @param Query Query object
 * @param ProxyPassword Password to use
 */
	void mb4_query_set_proxypassword(Mb4Query Query, const char *ProxyPassword);

/**
 *	Return a list of releases that match the specified Disc ID
 *
 * @see MusicBrainz4::CQuery::LookupDiscID
 *
 * @param Query Query object
 * @param	DiscID DiscID to lookup
 *
 * @return A release list object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4ReleaseList mb4_query_lookup_discid(Mb4Query Query, const char *DiscID);

/**
 * Return full information about a specific release
 *
 * @see MusicBrainz4::CQuery::LookupRelease
 *
 * @param Query Query object
 * @param	Release Release to return information for
 *
 * @return A object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Release mb4_query_lookup_release(Mb4Query Query, const char *Release);

/**
 *	Perform a generic query
 *
 * @see MusicBrainz4::CQuery::Query
 *
 * @param Query Query object
 * @param	Entity The entity to query
 * @param ID The ID to query
 * @param Resource The resource to query
 * @param	NumParams The number of parameters in the following arrays
 * @param ParamNames Array of strings containing parameter names
 * @param	Array of space seperated parameter values
 *
 * @return A metadata object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Metadata mb4_query_query(Mb4Query Query, const char *Entity, const char *ID, const char *Resource, int NumParams, char **ParamNames, char **ParamValues);

/**
 *	Add a list of releases to a collection
 *
 * @see MusicBrainz4::CQuery::AddCollectionEntries
 *
 * @param Query Query object
 * @param	Collection ID of collection to add releases to
 * @param	NumEntries The number of entries to add
 * @param Entries Array of strings of release IDs to add
 *
 * @return 0 on failure, 1 on success
 */
	unsigned char mb4_query_add_collection_entries(Mb4Query Query, const char *Collection, int NumEntries, const char **Entries);

/**
 *	Delete a list of releases from a collection
 *
 * @see MusicBrainz4::CQuery::AddCollectionEntries
 *
 * @param Query Query object
 * @param	Collection ID of collection to delete releases from
 * @param	NumEntries The number of entries to delete
 * @param Entries Array of strings of release IDs to delete
 *
 * @return 0 on failure, 1 on success
 */
	unsigned char mb4_query_delete_collection_entries(Mb4Query Query, const char *Collection, int NumEntries, const char **Entries);


/**
 * Delete an object
 *
 * @param Rating Object to delete
 */
	void mb4_rating_delete(Mb4Rating Rating);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	int mb4_rating_get_votescount(Mb4Rating Rating);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	double mb4_rating_get_rating(Mb4Rating Rating);


/**
 * Delete an object
 *
 * @param Recording Object to delete
 */
	void mb4_recording_delete(Mb4Recording Recording);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_recording_get_id(Mb4Recording Recording, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_recording_get_title(Mb4Recording Recording, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	int mb4_recording_get_length(Mb4Recording Recording);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_recording_get_disambiguation(Mb4Recording Recording, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4ArtistCredit mb4_recording_get_artistcredit(Mb4Recording Recording);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4ReleaseList mb4_recording_get_releaselist(Mb4Recording Recording);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4PUIDList mb4_recording_get_puidlist(Mb4Recording Recording);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4ISRCList mb4_recording_get_isrclist(Mb4Recording Recording);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4RelationList mb4_recording_get_relationlist(Mb4Recording Recording);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4TagList mb4_recording_get_taglist(Mb4Recording Recording);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4UserTagList mb4_recording_get_usertaglist(Mb4Recording Recording);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4Rating mb4_recording_get_rating(Mb4Recording Recording);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4UserRating mb4_recording_get_userrating(Mb4Recording Recording);


/**
 * Delete an object
 *
 * @param Release Object to delete
 */
	void mb4_release_delete(Mb4Release Release);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_id(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_title(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_status(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_quality(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_disambiguation(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_packaging(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4TextRepresentation mb4_release_get_textrepresentation(Mb4Release Release);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_date(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_country(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_barcode(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_asin(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4LabelInfoList mb4_release_get_labelinfolist(Mb4Release Release);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4MediumList mb4_release_get_mediumlist(Mb4Release Release);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4RelationList mb4_release_get_relationlist(Mb4Release Release);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4MediumList mb4_release_media_matching_discid(Mb4Release Release, const char *DiscID);


/**
 * Delete an object
 *
 * @param Relation Object to delete
 */
	void mb4_relation_delete(Mb4Relation Relation);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_relation_get_type(Mb4Relation Relation, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_relation_get_target(Mb4Relation Relation, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_relation_get_direction(Mb4Relation Relation, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4AttributeList mb4_relation_get_attributelist(Mb4Relation Relation);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_relation_get_begin(Mb4Relation Relation, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_relation_get_end(Mb4Relation Relation, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4Artist mb4_relation_get_artist(Mb4Relation Relation);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4Release mb4_relation_get_release(Mb4Relation Relation);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4ReleaseGroup mb4_relation_get_releasegroup(Mb4Relation Relation);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4Recording mb4_relation_get_recording(Mb4Relation Relation);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4Label mb4_relation_get_label(Mb4Relation Relation);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4Work mb4_relation_get_work(Mb4Relation Relation);


/**
 * Delete an object
 *
 * @param Release Object to delete
 */
	void mb4_release_delete(Mb4Release Release);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_id(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_title(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_status(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_quality(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_disambiguation(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_packaging(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4TextRepresentation mb4_release_get_textrepresentation(Mb4Release Release);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4ArtistCredit mb4_release_get_artistcredit(Mb4Release Release);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4ReleaseGroup mb4_release_get_releasegroup(Mb4Release Release);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_date(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_country(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_barcode(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_release_get_asin(Mb4Release Release, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4LabelInfoList mb4_release_get_labelinfolist(Mb4Release Release);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4MediumList mb4_release_get_mediumlist(Mb4Release Release);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4RelationList mb4_release_get_relationlist(Mb4Release Release);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4MediumList mb4_release_media_matching_disc_id(Mb4Release Release, const char *DiscID);


/**
 * Delete an object
 *
 * @param ReleaseGroup Object to delete
 */
	void mb4_releasegroup_delete(Mb4ReleaseGroup ReleaseGroup);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_releasegroup_get_id(Mb4ReleaseGroup ReleaseGroup, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_releasegroup_get_type(Mb4ReleaseGroup ReleaseGroup, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_releasegroup_get_title(Mb4ReleaseGroup ReleaseGroup, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_releasegroup_get_comment(Mb4ReleaseGroup ReleaseGroup, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4ArtistCredit mb4_releasegroup_get_artistcredit(Mb4ReleaseGroup ReleaseGroup);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4ReleaseList mb4_releasegroup_get_releaselist(Mb4ReleaseGroup ReleaseGroup);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4RelationList mb4_releasegroup_get_relationlist(Mb4ReleaseGroup ReleaseGroup);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4TagList mb4_releasegroup_get_taglist(Mb4ReleaseGroup ReleaseGroup);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4UserTagList mb4_releasegroup_get_usertaglist(Mb4ReleaseGroup ReleaseGroup);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4Rating mb4_releasegroup_get_rating(Mb4ReleaseGroup ReleaseGroup);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4UserRating mb4_releasegroup_get_userrating(Mb4ReleaseGroup ReleaseGroup);


/**
 * Delete an object
 *
 * @param Tag Object to delete
 */
	void mb4_tag_delete(Mb4Tag Tag);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	int mb4_tag_get_count(Mb4Tag Tag);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_tag_get_name(Mb4Tag Tag, char *str, int len);


/**
 * Delete an object
 *
 * @param TextRepresentation Object to delete
 */
	void mb4_textrepresentation_delete(Mb4TextRepresentation TextRepresentation);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_textrepresentation_get_language(Mb4TextRepresentation TextRepresentation, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_textrepresentation_get_script(Mb4TextRepresentation TextRepresentation, char *str, int len);


/**
 * Delete an object
 *
 * @param Track Object to delete
 */
	void mb4_track_delete(Mb4Track Track);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	int mb4_track_get_position(Mb4Track Track);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_track_get_title(Mb4Track Track, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4Recording mb4_track_get_recording(Mb4Track Track);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	int mb4_track_get_length(Mb4Track Track);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4ArtistCredit mb4_track_get_artistcredit(Mb4Track Track);


/**
 * Delete an object
 *
 * @param UserRating Object to delete
 */
	void mb4_userrating_delete(Mb4UserRating UserRating);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	int mb4_userrating_get_userrating(Mb4UserRating UserRating);


/**
 * Delete an object
 *
 * @param UserTag Object to delete
 */
	void mb4_usertag_delete(Mb4UserTag UserTag);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_usertag_get_name(Mb4UserTag UserTag, char *str, int len);


/**
 * Delete an object
 *
 * @param Work Object to delete
 */
	void mb4_work_delete(Mb4Work Work);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_work_get_id(Mb4Work Work, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_work_get_type(Mb4Work Work, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_work_get_title(Mb4Work Work, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4ArtistCredit mb4_work_get_artistcredit(Mb4Work Work);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_work_get_iswc(Mb4Work Work, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	void mb4_work_get_disambiguation(Mb4Work Work, char *str, int len);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4AliasList mb4_work_get_aliaslist(Mb4Work Work);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4RelationList mb4_work_get_relationlist(Mb4Work Work);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4TagList mb4_work_get_taglist(Mb4Work Work);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4UserTagList mb4_work_get_usertaglist(Mb4Work Work);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4Rating mb4_work_get_rating(Mb4Work Work);

/**
 *
 *
 * @see
 *
 * @param
 * @param
 * @param
 */
	Mb4UserRating mb4_work_get_userrating(Mb4Work Work);


/**
 * Delete an Alias list
 *
 * @param List List to delete
 */
	void mb4_alias_list_delete(Mb4AliasList List);

/**
 *	Return the number of entries in an Alias list
 *
 * @param	List List to use
 */
	int mb4_alias_list_size(Mb4AliasList List);

/**
 *	Returns an entry from an Alias list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return An Alias object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Alias mb4_alias_list_item(Mb4AliasList List, int Item);


/**
 * Delete an Annotation list
 *
 * @param List List to delete
 */
	void mb4_annotation_list_delete(Mb4AnnotationList List);

/**
 *	Return the number of entries in an Annotation list
 *
 * @param	List List to use
 */
	int mb4_annotation_list_size(Mb4AnnotationList List);

/**
 *	Returns an entry from an Annotation list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return An Annotation object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Annotation mb4_annotation_list_item(Mb4AnnotationList List, int Item);


/**
 * Delete an Artist list
 *
 * @param List List to delete
 */
	void mb4_artist_list_delete(Mb4ArtistList List);

/**
 *	Return the number of entries in an Artist list
 *
 * @param	List List to use
 */
	int mb4_artist_list_size(Mb4ArtistList List);

/**
 *	Returns an entry from an Artist list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return An Artist object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Artist mb4_artist_list_item(Mb4ArtistList List, int Item);


/**
 * Delete an Attribute list
 *
 * @param List List to delete
 */
	void mb4_attribute_list_delete(Mb4AttributeList List);

/**
 *	Return the number of entries in an Attribute list
 *
 * @param	List List to use
 */
	int mb4_attribute_list_size(Mb4AttributeList List);

/**
 *	Returns an entry from an Attribute list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return An Attribute object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Attribute mb4_attribute_list_item(Mb4AttributeList List, int Item);


/**
 * Delete a CDStub list
 *
 * @param List List to delete
 */
	void mb4_cdstub_list_delete(Mb4CDStubList List);

/**
 *	Return the number of entries in a CDStub list
 *
 * @param	List List to use
 */
	int mb4_cdstub_list_size(Mb4CDStubList List);

/**
 *	Returns an entry from a CDStub list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A CDStub object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4CDStub mb4_cdstub_list_item(Mb4CDStubList List, int Item);


/**
 * Delete a Collection list
 *
 * @param List List to delete
 */
	void mb4_collection_list_delete(Mb4CollectionList List);

/**
 *	Return the number of entries in a Collection list
 *
 * @param	List List to use
 */
	int mb4_collection_list_size(Mb4CollectionList List);

/**
 *	Returns an entry from a Collection list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A Collection object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Collection mb4_collection_list_item(Mb4CollectionList List, int Item);


/**
 * Delete a Disc list
 *
 * @param List List to delete
 */
	void mb4_disc_list_delete(Mb4DiscList List);

/**
 *	Return the number of entries in a Disc list
 *
 * @param	List List to use
 */
	int mb4_disc_list_size(Mb4DiscList List);

/**
 *	Returns an entry from a Disc list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A Disc object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Disc mb4_disc_list_item(Mb4DiscList List, int Item);


/**
 * Delete a FreeDBDisc list
 *
 * @param List List to delete
 */
	void mb4_freedbdisc_list_delete(Mb4FreeDBDiscList List);

/**
 *	Return the number of entries in a FreeDBDisc list
 *
 * @param	List List to use
 */
	int mb4_freedbdisc_list_size(Mb4FreeDBDiscList List);

/**
 *	Returns an entry from a FreeDBDisc list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A FreeDBDisc object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4FreeDBDisc mb4_freedbdisc_list_item(Mb4FreeDBDiscList List, int Item);


/**
 * Delete an ISRC list
 *
 * @param List List to delete
 */
	void mb4_isrc_list_delete(Mb4ISRCList List);

/**
 *	Return the number of entries in an ISRC list
 *
 * @param	List List to use
 */
	int mb4_isrc_list_size(Mb4ISRCList List);

/**
 *	Returns an entry from an ISRC list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return An ISRC object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4ISRC mb4_isrc_list_item(Mb4ISRCList List, int Item);


/**
 * Delete a Label list
 *
 * @param List List to delete
 */
	void mb4_label_list_delete(Mb4LabelList List);

/**
 *	Return the number of entries in a Label list
 *
 * @param	List List to use
 */
	int mb4_label_list_size(Mb4LabelList List);

/**
 *	Returns an entry from a Label list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A Label object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Label mb4_label_list_item(Mb4LabelList List, int Item);


/**
 * Delete a LabelInfo list
 *
 * @param List List to delete
 */
	void mb4_labelinfo_list_delete(Mb4LabelInfoList List);

/**
 *	Return the number of entries in a LabelInfo list
 *
 * @param	List List to use
 */
	int mb4_labelinfo_list_size(Mb4LabelInfoList List);

/**
 *	Returns an entry from a LabelInfo list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A LabelInfo object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4LabelInfo mb4_labelinfo_list_item(Mb4LabelInfoList List, int Item);


/**
 * Delete a Medium list
 *
 * @param List List to delete
 */
	void mb4_medium_list_delete(Mb4MediumList List);

/**
 *	Return the number of entries in a Medium list
 *
 * @param	List List to use
 */
	int mb4_medium_list_size(Mb4MediumList List);

/**
 *	Returns an entry from a Medium list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A Medium object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Medium mb4_medium_list_item(Mb4MediumList List, int Item);


/**
 * Delete a NameCredit list
 *
 * @param List List to delete
 */
	void mb4_namecredit_list_delete(Mb4NameCreditList List);

/**
 *	Return the number of entries in a NameCredit list
 *
 * @param	List List to use
 */
	int mb4_namecredit_list_size(Mb4NameCreditList List);

/**
 *	Returns an entry from a NameCredit list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A NameCredit object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4NameCredit mb4_namecredit_list_item(Mb4NameCreditList List, int Item);


/**
 * Delete a NoneMBTrack list
 *
 * @param List List to delete
 */
	void mb4_nonembtrack_list_delete(Mb4NoneMBTrackList List);

/**
 *	Return the number of entries in a NoneMBTrack list
 *
 * @param	List List to use
 */
	int mb4_nonembtrack_list_size(Mb4NoneMBTrackList List);

/**
 *	Returns an entry from a NoneMBTrack list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A NoneMBTrack object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4NoneMBTrack mb4_nonembtrack_list_item(Mb4NoneMBTrackList List, int Item);


/**
 * Delete a PUID list
 *
 * @param List List to delete
 */
	void mb4_puid_list_delete(Mb4PUIDList List);

/**
 *	Return the number of entries in a PUID list
 *
 * @param	List List to use
 */
	int mb4_puid_list_size(Mb4PUIDList List);

/**
 *	Returns an entry from a PUID list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A PUID object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4PUID mb4_puid_list_item(Mb4PUIDList List, int Item);


/**
 * Delete a Recording list
 *
 * @param List List to delete
 */
	void mb4_recording_list_delete(Mb4RecordingList List);

/**
 *	Return the number of entries in a Recording list
 *
 * @param	List List to use
 */
	int mb4_recording_list_size(Mb4RecordingList List);

/**
 *	Returns an entry from a Recording list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A Recording object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Recording mb4_recording_list_item(Mb4RecordingList List, int Item);


/**
 * Delete a Relation list
 *
 * @param List List to delete
 */
	void mb4_relation_list_delete(Mb4RelationList List);

/**
 *	Return the number of entries in a Relation list
 *
 * @param	List List to use
 */
	int mb4_relation_list_size(Mb4RelationList List);

/**
 *	Returns an entry from a Relation list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A Relation object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Relation mb4_relation_list_item(Mb4RelationList List, int Item);


/**
 * Delete a Release list
 *
 * @param List List to delete
 */
	void mb4_release_list_delete(Mb4ReleaseList List);

/**
 *	Return the number of entries in a Release list
 *
 * @param	List List to use
 */
	int mb4_release_list_size(Mb4ReleaseList List);

/**
 *	Returns an entry from a Release list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A Release object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Release mb4_release_list_item(Mb4ReleaseList List, int Item);


/**
 * Delete a ReleaseGroup list
 *
 * @param List List to delete
 */
	void mb4_releasegroup_list_delete(Mb4ReleaseGroupList List);

/**
 *	Return the number of entries in a ReleaseGroup list
 *
 * @param	List List to use
 */
	int mb4_releasegroup_list_size(Mb4ReleaseGroupList List);

/**
 *	Returns an entry from a ReleaseGroup list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A ReleaseGroup object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4ReleaseGroup mb4_releasegroup_list_item(Mb4ReleaseGroupList List, int Item);


/**
 * Delete a Tag list
 *
 * @param List List to delete
 */
	void mb4_tag_list_delete(Mb4TagList List);

/**
 *	Return the number of entries in a Tag list
 *
 * @param	List List to use
 */
	int mb4_tag_list_size(Mb4TagList List);

/**
 *	Returns an entry from a Tag list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A Tag object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Tag mb4_tag_list_item(Mb4TagList List, int Item);


/**
 * Delete a Track list
 *
 * @param List List to delete
 */
	void mb4_track_list_delete(Mb4TrackList List);

/**
 *	Return the number of entries in a Track list
 *
 * @param	List List to use
 */
	int mb4_track_list_size(Mb4TrackList List);

/**
 *	Returns an entry from a Track list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A Track object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Track mb4_track_list_item(Mb4TrackList List, int Item);


/**
 * Delete a UserTag list
 *
 * @param List List to delete
 */
	void mb4_usertag_list_delete(Mb4UserTagList List);

/**
 *	Return the number of entries in a UserTag list
 *
 * @param	List List to use
 */
	int mb4_usertag_list_size(Mb4UserTagList List);

/**
 *	Returns an entry from a UserTag list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A UserTag object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4UserTag mb4_usertag_list_item(Mb4UserTagList List, int Item);


/**
 * Delete a Work list
 *
 * @param List List to delete
 */
	void mb4_work_list_delete(Mb4WorkList List);

/**
 *	Return the number of entries in a Work list
 *
 * @param	List List to use
 */
	int mb4_work_list_size(Mb4WorkList List);

/**
 *	Returns an entry from a Work list
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A Work object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Work mb4_work_list_item(Mb4WorkList List, int Item);

#ifdef __cplusplus
}
#endif

#endif


