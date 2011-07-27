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

/*

	Things you should delete using the appropriate mb4_xxx_delete() function:

	* The query object you create to do the actual work
	* Any object or list returned from one of the mb4_query_xxx() functions
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
	typedef void *Mb4Entity;
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
	typedef void *Mb4NonMBTrack;
	typedef void *Mb4NonMBTrackList;
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

	int mb4_entity_ext_attributes_size(Mb4Entity Entity);
	int mb4_entity_ext_attribute_name(Mb4Entity Entity, int Item, char *str, int len);
	int mb4_entity_ext_attribute_value(Mb4Entity Entity, int Item, char *str, int len);

	int mb4_entity_ext_elements_size(Mb4Entity Entity);
	int mb4_entity_ext_element_name(Mb4Entity Entity, int Item, char *str, int len);
	int mb4_entity_ext_element_value(Mb4Entity Entity, int Item, char *str, int len);

/**
 * delete an #Mb4Alias object
 *
 * @param Alias Object to delete
 */
	void mb4_alias_delete(Mb4Alias Alias);

/**
 * @see MusicBrainz4::CAlias::Locale
 *
 * @param Alias #Mb4Alias object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_alias_get_locale(Mb4Alias Alias, char *str, int len);

/**
 * @see MusicBrainz4::CAlias::Text
 *
 * @param Alias #Mb4Alias object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_alias_get_text(Mb4Alias Alias, char *str, int len);


/**
 * Delete an #Mb4Annotation object
 *
 * @param Annotation Object to delete
 */
	void mb4_annotation_delete(Mb4Annotation Annotation);

/**
 * @see MusicBrainz4::CAnnotation::Type
 *
 * @param Annotation #Mb4Annotation object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_annotation_get_type(Mb4Annotation Annotation, char *str, int len);

/**
 * @see MusicBrainz4::CAnnotation::Entity
 *
 * @param Annotation #Mb4Annotation object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_annotation_get_entity(Mb4Annotation Annotation, char *str, int len);

/**
 * @see MusicBrainz4::CAnnotation::Name
 *
 * @param Annotation #Mb4Annotation object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_annotation_get_name(Mb4Annotation Annotation, char *str, int len);

/**
 * @see MusicBrainz4::CAnnotation::Text
 *
 * @param Annotation #Mb4Annotation object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_annotation_get_text(Mb4Annotation Annotation, char *str, int len);


/**
 * Delete an #Mb4Artist object
 *
 * @param Artist Object to delete
 */
	void mb4_artist_delete(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::ID
 *
 * @param Artist #Mb4Artist object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_artist_get_id(Mb4Artist Artist, char *str, int len);

/**
 * @see MusicBrainz4::CArtist::Type
 *
 * @param Artist #Mb4Artist object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_artist_get_type(Mb4Artist Artist, char *str, int len);

/**
 * @see MusicBrainz4::CArtist::Name
 *
 * @param Artist #Mb4Artist object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_artist_get_name(Mb4Artist Artist, char *str, int len);

/**
 * @see MusicBrainz4::CArtist::SortName
 *
 * @param Artist #Mb4Artist object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_artist_get_sortname(Mb4Artist Artist, char *str, int len);

/**
 * @see MusicBrainz4::CArtist::Gender
 *
 * @param Artist #Mb4Artist object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_artist_get_gender(Mb4Artist Artist, char *str, int len);

/**
 * @see MusicBrainz4::CArtist::Country
 *
 * @param Artist #Mb4Artist object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_artist_get_country(Mb4Artist Artist, char *str, int len);

/**
 * @see MusicBrainz4::CArtist::Disambiguation
 *
 * @param Artist #Mb4Artist object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_artist_get_disambiguation(Mb4Artist Artist, char *str, int len);

/**
 * @see MusicBrainz4::CArtist::Lifespan
 *
 * @param Artist #Mb4Artist object
 *
 * @return #Mb4Lifespan object
 */
	Mb4Lifespan mb4_artist_get_lifespan(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::AliasList
 *
 * @param Artist #Mb4Artist object
 *
 * @return #Mb4AliasList.
 */
	Mb4AliasList mb4_artist_get_aliaslist(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::RecordingList
 *
 * @param Artist #Mb4Artist object
 *
 * @return #Mb4RecordingList.
 */
	Mb4RecordingList mb4_artist_get_recordinglist(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::ReleaseList
 *
 * @param Artist #Mb4Artist object
 *
 * @return #Mb4ReleaseList.
 */
	Mb4ReleaseList mb4_artist_get_releaselist(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::ReleaseGroupList
 *
 * @param Artist #Mb4Artist object
 *
 * @return #Mb4ReleaseGroupList.
 */
	Mb4ReleaseGroupList mb4_artist_get_releasegrouplist(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::LabelList
 *
 * @param Artist #Mb4Artist object
 *
 * @return #Mb4LabelList.
 */
	Mb4LabelList mb4_artist_get_labellist(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::WorkList
 *
 * @param Artist #Mb4Artist object
 *
 * @return #Mb4WorkList.
 */
	Mb4WorkList mb4_artist_get_worklist(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::RelationList
 *
 * @param Artist #Mb4Artist object
 *
 * @return #Mb4RelationList.
 */
	Mb4RelationList mb4_artist_get_relationlist(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::TagList
 *
 * @param Artist #Mb4Artist object
 *
 * @return #Mb4TagList.
 */
	Mb4TagList mb4_artist_get_taglist(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::UserTagList
 *
 * @param Artist #Mb4Artist object
 *
 * @return #Mb4UserTagList.
 */
	Mb4UserTagList mb4_artist_get_usertaglist(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::Rating
 *
 * @param Artist #Mb4Artist object
 *
 * @return #Mb4Rating object.
 */
	Mb4Rating mb4_artist_get_rating(Mb4Artist Artist);

/**
 * @see MusicBrainz4::CArtist::UserRating
 *
 * @param Artist #Mb4Artist object
 *
 * @return #Mb4UserRating object.
 */
	Mb4UserRating mb4_artist_get_userrating(Mb4Artist Artist);

/**
 * Delete an #Mb4ArtistCredit object
 *
 * @param ArtistCredit Object to delete
 */
	void mb4_artistcredit_delete(Mb4ArtistCredit ArtistCredit);

/**
 * @see MusicBrainz4::CArtistCredit::NameCreditList
 *
 * @param ArtistCredit #Mb4ArtistCredit object
 *
 * @return #Mb4NameCreditList.
 */
	Mb4NameCreditList mb4_artistcredit_get_namecreditlist(Mb4ArtistCredit ArtistCredit);

/**
 * Delete an #Mb4Attribute object
 *
 * @param Attribute Object to delete
 */
	void mb4_attribute_delete(Mb4Attribute Attribute);

/**
 * @see MusicBrainz4::CAttribute::Text
 *
 * @param Attribute #Mb4Attribute object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_attribute_get_text(Mb4Attribute Attribute, char *str, int len);

/**
 * Delete a #Mb4CDStub object
 *
 * @param CDStub Object to delete
 */
	void mb4_cdstub_delete(Mb4CDStub CDStub);

/**
 * @see MusicBrainz4::CCDStub::ID
 *
 * @param CDStub #Mb4CDStub object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_cdstub_get_id(Mb4CDStub CDStub, char *str, int len);

/**
 * @see MusicBrainz4::CCDStub::Title
 *
 * @param CDStub #Mb4CDStub object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_cdstub_get_title(Mb4CDStub CDStub, char *str, int len);

/**
 * @see MusicBrainz4::CCDStub::Artist
 *
 * @param CDStub #Mb4CDStub object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_cdstub_get_artist(Mb4CDStub CDStub, char *str, int len);

/**
 * @see MusicBrainz4::CCDStub::Barcode
 *
 * @param CDStub #Mb4CDStub object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_cdstub_get_barcode(Mb4CDStub CDStub, char *str, int len);

/**
 * @see MusicBrainz4::CCDStub::Comment
 *
 * @param CDStub #Mb4CDStub object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_cdstub_get_comment(Mb4CDStub CDStub, char *str, int len);

/**
 * @see MusicBrainz4::CCDStub::NonMBTrackList
 *
 * @param CDStub #Mb4CDStub object
 *
 * @return #Mb4NonMBTrackList.
 */
	Mb4NonMBTrackList mb4_cdstub_get_nonmbtracklist(Mb4CDStub CDStub);


/**
 * Delete a #Mb4Collection object
 *
 * @param Collection Object to delete
 */
	void mb4_collection_delete(Mb4Collection Collection);

/**
 * @see MusicBrainz4::CCollection::ID
 *
 * @param Collection #Mb4Collection object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_collection_get_id(Mb4Collection Collection, char *str, int len);

/**
 * @see MusicBrainz4::CCollection::Name
 *
 * @param Collection #Mb4Collection object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_collection_get_name(Mb4Collection Collection, char *str, int len);

/**
 * @see MusicBrainz4::CCollection::Editor
 *
 * @param Collection #Mb4Collection object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_collection_get_editor(Mb4Collection Collection, char *str, int len);

/**
 * @see MusicBrainz4::CCollection::ReleaseList
 *
 * @param Collection #Mb4Collection object
 *
 * @return #Mb4ReleaseList.
 */
	Mb4ReleaseList mb4_collection_get_releaselist(Mb4Collection Collection);

/**
 * Delete a #Mb4Disc object
 *
 * @param Disc Object to delete
 */
	void mb4_disc_delete(Mb4Disc Disc);

/**
 * @see MusicBrainz4::CDisc::ID
 *
 * @param Disc #Mb4Disc object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_disc_get_id(Mb4Disc Disc, char *str, int len);

/**
 * @see MusicBrainz4::CDisc::Sectors
 *
 * @param Disc #Mb4Disc object
 *
 * @return Number of sectors
 */
	int mb4_disc_get_sectors(Mb4Disc Disc);

/**
 * @see MusicBrainz4::CDisc::ReleaseList
 *
 * @param Disc #Mb4Disc object
 *
 * @return #Mb4ReleaseList.
 */
	Mb4ReleaseList mb4_disc_get_releaselist(Mb4Disc Disc);


/**
 * Delete a #Mb4FreeDBDisc object
 *
 * @param FreeDBDisc Object to delete
 */
	void mb4_freedbdisc_delete(Mb4FreeDBDisc FreeDBDisc);

/**
 * @see MusicBrainz4::CFreeDBDisc::ID
 *
 * @param FreeDBDisc #Mb4FreeDBDisc object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_freedbdisc_get_id(Mb4FreeDBDisc FreeDBDisc, char *str, int len);

/**
 * @see MusicBrainz4::CFreeDBDisc::Title
 *
 * @param FreeDBDisc #Mb4FreeDBDisc object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_freedbdisc_get_title(Mb4FreeDBDisc FreeDBDisc, char *str, int len);

/**
 * @see MusicBrainz4::CFreeDBDisc::Artist
 *
 * @param FreeDBDisc #Mb4FreeDBDisc object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_freedbdisc_get_artist(Mb4FreeDBDisc FreeDBDisc, char *str, int len);

/**
 * @see MusicBrainz4::CFreeDBDisc::Category
 *
 * @param FreeDBDisc #Mb4FreeDBDisc object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_freedbdisc_get_category(Mb4FreeDBDisc FreeDBDisc, char *str, int len);

/**
 * @see MusicBrainz4::CFreeDBDisc::Year
 *
 * @param FreeDBDisc #Mb4FreeDBDisc object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_freedbdisc_get_year(Mb4FreeDBDisc FreeDBDisc, char *str, int len);

/**
 * @see MusicBrainz4::CFreeDBDisc::NonMBTrackList
 *
 * @param FreeDBDisc #Mb4FreeDBDisc object
 *
 * @return #Mb4NonMBTrackList.
 */
	Mb4NonMBTrackList mb4_freedbdisc_get_nonmbtracklist(Mb4FreeDBDisc FreeDBDisc);


/**
 * Delete an #Mb4ISRC object
 *
 * @param ISRC Object to delete
 */
	void mb4_isrc_delete(Mb4ISRC ISRC);

/**
 * @see MusicBrainz4::CISRC::ID
 *
 * @param ISRC #Mb4ISRC object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_isrc_get_id(Mb4ISRC ISRC, char *str, int len);

/**
 * @see MusicBrainz4::CISRC::RecordingList
 *
 * @param ISRC #Mb4ISRC object
 *
 * @return #Mb4RecordingList.
 */
	Mb4RecordingList mb4_isrc_get_recordinglist(Mb4ISRC ISRC);


/**
 * Delete a #Mb4Label object
 *
 * @param Label Object to delete
 */
	void mb4_label_delete(Mb4Label Label);

/**
 * @see MusicBrainz4::CLabel::ID
 *
 * @param Label #Mb4Label object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_label_get_id(Mb4Label Label, char *str, int len);

/**
 * @see MusicBrainz4::CLabel::Type
 *
 * @param Label #Mb4Label object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_label_get_type(Mb4Label Label, char *str, int len);

/**
 * @see MusicBrainz4::CLabel::Name
 *
 * @param Label #Mb4Label object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_label_get_name(Mb4Label Label, char *str, int len);

/**
 * @see MusicBrainz4::CLabel::SortName
 *
 * @param Label #Mb4Label object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_label_get_sortname(Mb4Label Label, char *str, int len);

/**
 * @see MusicBrainz4::CLabel::LabelCode
 *
 * @param Label #Mb4Label object
 *
 * @return Label code
 */
	int mb4_label_get_labelcode(Mb4Label Label);

/**
 * @see MusicBrainz4::CLabel::Disambiguation
 *
 * @param Label #Mb4Label object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_label_get_disambiguation(Mb4Label Label, char *str, int len);

/**
 * @see MusicBrainz4::CLabel::Country
 *
 * @param Label #Mb4Label object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_label_get_country(Mb4Label Label, char *str, int len);

/**
 * @see MusicBrainz4::CLabel::Lifespan
 *
 * @param Label #Mb4Label object
 *
 * @return #Mb4Lifespan object
 */
	Mb4Lifespan mb4_label_get_lifespan(Mb4Label Label);

/**
 * @see MusicBrainz4::CLabel::AliasList
 *
 * @param Label #Mb4Label object
 *
 * @return #Mb4AliasList.
 */
	Mb4AliasList mb4_label_get_aliaslist(Mb4Label Label);

/**
 * @see MusicBrainz4::CLabel::ReleaseList
 *
 * @param Label #Mb4Label object
 *
 * @return #Mb4ReleaseList.
 */
	Mb4ReleaseList mb4_label_get_releaselist(Mb4Label Label);

/**
 * @see MusicBrainz4::CLabel::RelationList
 *
 * @param Label #Mb4Label object
 *
 * @return #Mb4RelationList.
 */
	Mb4RelationList mb4_label_get_relationlist(Mb4Label Label);

/**
 * @see MusicBrainz4::CLabel::TagList
 *
 * @param Label #Mb4Label object
 *
 * @return #Mb4TagList.
 */
	Mb4TagList mb4_label_get_taglist(Mb4Label Label);

/**
 * @see MusicBrainz4::CLabel::UserTagList
 *
 * @param Label #Mb4Label object
 *
 * @return #Mb4UserTagList.
 */
	Mb4UserTagList mb4_label_get_usertaglist(Mb4Label Label);

/**
 * @see MusicBrainz4::CLabel::Rating
 *
 * @param Label #Mb4Label object
 *
 * @return #Mb4Rating object
 */
	Mb4Rating mb4_label_get_rating(Mb4Label Label);

/**
 * @see MusicBrainz4::CLabel::UserRating
 *
 * @param Label #Mb4Label object
 *
 * @return #Mb4UserRating object
 */
	Mb4UserRating mb4_label_get_userrating(Mb4Label Label);

/**
 * Delete a #Mb4LabelInfo object
 *
 * @param LabelInfo Object to delete
 */
	void mb4_labelinfo_delete(Mb4LabelInfo LabelInfo);

/**
 * @see MusicBrainz4::CLabelInfo::CatalogNumber
 *
 * @param LabelInfo #Mb4LabelInfo object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_labelinfo_get_catalognumber(Mb4LabelInfo LabelInfo, char *str, int len);

/**
 * @see MusicBrainz4::CLabelInfo::Label
 *
 * @param LabelInfo #Mb4LabelInfo object
 *
 * @return Label object
 */
	Mb4Label mb4_labelinfo_get_label(Mb4LabelInfo LabelInfo);

/**
 * Delete a #Mb4Lifespan object
 *
 * @param Lifespan Object to delete
 */
	void mb4_lifespan_delete(Mb4Lifespan Lifespan);

/**
 * @see MusicBrainz4::CLifespan::Begin
 *
 * @param Lifespan #Mb4Lifespan object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_lifespan_get_begin(Mb4Lifespan Lifespan, char *str, int len);

/**
 * @see MusicBrainz4::CLifespan::End
 *
 * @param Lifespan #Mb4Lifespan object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_lifespan_get_end(Mb4Lifespan Lifespan, char *str, int len);


/**
 * Delete a #Mb4Medium object
 *
 * @param Medium Object to delete
 */
	void mb4_medium_delete(Mb4Medium Medium);

/**
 * @see MusicBrainz4::CMedium::Title
 *
 * @param Medium #Mb4Medium object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_medium_get_title(Mb4Medium Medium, char *str, int len);

/**
 * @see MusicBrainz4::CMedium::Position
 *
 * @param Medium #Mb4Medium object
 *
 * @return Returned position
 */
	int mb4_medium_get_position(Mb4Medium Medium);

/**
 * @see MusicBrainz4::CMedium::Format
 *
 * @param Medium #Mb4Medium object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_medium_get_format(Mb4Medium Medium, char *str, int len);

/**
 * @see MusicBrainz4::CMedium::DiscList
 *
 * @param Medium #Mb4Medium object
 *
 * @return #Mb4DiscList object
 */
	Mb4DiscList mb4_medium_get_disclist(Mb4Medium Medium);

/**
 * @see MusicBrainz4::CMedium::TrackList
 *
 * @param Medium #Mb4Medium object
 *
 * @return #Mb4TrackList object
 */
	Mb4TrackList mb4_medium_get_tracklist(Mb4Medium Medium);

/**
 * @see MusicBrainz4::CMedium::ContainsDiscID
 *
 * @param Medium #Mb4Medium object
 * @param DiscID DiscID to check
 *
 * @return 1 if DiscID found, 0 otherwise
 */
	unsigned char mb4_medium_contains_discid(Mb4Medium Medium, const char *DiscID);

/**
 * Delete a #Mb4Message object
 *
 * @param Message Object to delete
 */
	void mb4_message_delete(Mb4Message Message);

/**
 * @see MusicBrainz4::CMessage::Text
 *
 * @param Message #Mb4Message object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_message_get_text(Mb4Message Message, char *str, int len);

/**
 * Delete a #Mb4Metadata object
 *
 * @param Metadata Object to delete
 */
	void mb4_metadata_delete(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::XMLNS
 *
 * @param Metadata #Mb4Metadata object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_metadata_get_xmlns(Mb4Metadata Metadata, char *str, int len);

/**
 * @see MusicBrainz4::CMetadata::XMLNSExt
 *
 * @param Metadata #Mb4Metadata object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_metadata_get_xmlnsext(Mb4Metadata Metadata, char *str, int len);

/**
 * @see MusicBrainz4::CMetadata::Generator
 *
 * @param Metadata #Mb4Metadata object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_metadata_get_generator(Mb4Metadata Metadata, char *str, int len);

/**
 * @see MusicBrainz4::CMetadata::Created
 *
 * @param Metadata #Mb4Metadata object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_metadata_get_created(Mb4Metadata Metadata, char *str, int len);

/**
 * @see MusicBrainz4::CMetadata::Artist
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4Artist object
 */
	Mb4Artist mb4_metadata_get_artist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::Release
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4Release object
 */
	Mb4Release mb4_metadata_get_release(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::ReleaseGroup
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4ReleaseGroup object
 */
	Mb4ReleaseGroup mb4_metadata_get_releasegroup(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::Recording
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4Recording object
 */
	Mb4Recording mb4_metadata_get_recording(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::Label
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4Label object
 */
	Mb4Label mb4_metadata_get_label(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::Work
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4Work object
 */
	Mb4Work mb4_metadata_get_work(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::PUID
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4PUID object
 */
	Mb4PUID mb4_metadata_get_puid(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::ISRC
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4ISRC object
 */
	Mb4ISRC mb4_metadata_get_isrc(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::Disc
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4Disc object
 */
	Mb4Disc mb4_metadata_get_disc(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::LabelInfoList
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4LabelInfoList
 */
	Mb4LabelInfoList mb4_metadata_get_labelinfolist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::Rating
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4Rating object
 */
	Mb4Rating mb4_metadata_get_rating(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::UserRating
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4UserRating object
 */
	Mb4UserRating mb4_metadata_get_userrating(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::Collection
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4Collection object
 */
	Mb4Collection mb4_metadata_get_collection(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::ArtistList
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4ArtistList
 */
	Mb4ArtistList mb4_metadata_get_artistlist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::ReleaseList
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4ReleaseList
 */
	Mb4ReleaseList mb4_metadata_get_releaselist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::ReleaseGroupList
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4ReleaseGroupList
 */
	Mb4ReleaseGroupList mb4_metadata_get_releasegrouplist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::RecordingList
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4RecordingList
 */
	Mb4RecordingList mb4_metadata_get_recordinglist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::LabelList
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4LabelList
 */
	Mb4LabelList mb4_metadata_get_labellist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::WorkList
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4WorkList
 */
	Mb4WorkList mb4_metadata_get_worklist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::ISRC
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4ISRCList
 */
	Mb4ISRCList mb4_metadata_get_isrclist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::AnnotationList
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4AnnotationList
 */
	Mb4AnnotationList mb4_metadata_get_annotationlist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::CDStubList
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4CDStubList
 */
	Mb4CDStubList mb4_metadata_get_cdstublist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::FreeDBDiscList
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4FreeDBDiscList
 */
	Mb4FreeDBDiscList mb4_metadata_get_freedbdisclist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::TagList
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4TagList
 */
	Mb4TagList mb4_metadata_get_taglist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::UserTagList
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4UserTagList
 */
	Mb4UserTagList mb4_metadata_get_usertaglist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::CollectionList
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4CollectionList
 */
	Mb4CollectionList mb4_metadata_get_collectionlist(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::CDStub
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4CDStub object
 */
	Mb4CDStub mb4_metadata_get_cdstub(Mb4Metadata Metadata);

/**
 * @see MusicBrainz4::CMetadata::Message
 *
 * @param Metadata #Mb4Metadata object
 *
 * @return #Mb4Message object
 */
	Mb4Message mb4_metadata_get_message(Mb4Metadata Metadata);

/**
 * Delete a #Mb4NameCredit object
 *
 * @param NameCredit Object to delete
 */
	void mb4_namecredit_delete(Mb4NameCredit NameCredit);

/**
 * @see MusicBrainz4::CNameCredit::JoinPhrase
 *
 * @param NameCredit #Mb4NameCredit object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_namecredit_get_joinphrase(Mb4NameCredit NameCredit, char *str, int len);

/**
 * @see MusicBrainz4::CNameCredit::Name
 *
 * @param NameCredit #Mb4NameCredit object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_namecredit_get_name(Mb4NameCredit NameCredit, char *str, int len);

/**
 * @see MusicBrainz4::CNameCredit::Artist
 *
 * @param NameCredit #Mb4NameCredit object
 *
 * @return #Mb4Artist object
 */
	Mb4Artist mb4_namecredit_get_artist(Mb4NameCredit NameCredit);

/**
 * Delete a #Mb4NonMBTrack object
 *
 * @param NonMBTrack Object to delete
 */
	void mb4_nonmbtrack_delete(Mb4NonMBTrack NonMBTrack);

/**
 * @see MusicBrainz4::CNonMBTrack::Title
 *
 * @param NonMBTrack #Mb4NonMBTrack object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_nonmbtrack_get_title(Mb4NonMBTrack NonMBTrack, char *str, int len);

/**
 * @see MusicBrainz4::CNonMBTrack::Artist
 *
 * @param NonMBTrack #Mb4NonMBTrack object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_nonmbtrack_get_artist(Mb4NonMBTrack NonMBTrack, char *str, int len);

/**
 * @see MusicBrainz4::CNonMBTrack::Length
 *
 * @param NonMBTrack #Mb4NonMBTrack object
 *
 * @return Returned length
 */
	int mb4_nonmbtrack_get_length(Mb4NonMBTrack NonMBTrack);


/**
 * Delete a #Mb4PUID object
 *
 * @param PUID Object to delete
 */
	void mb4_puid_delete(Mb4PUID PUID);

/**
 * @see MusicBrainz4::CPUID::ID
 *
 * @param PUID #Mb4PUID object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_puid_get_id(Mb4PUID PUID, char *str, int len);

/**
 * @see MusicBrainz4::CPUID::RecordingList
 *
 * @param PUID #Mb4PUID object
 *
 * @return #Mb4RecordingList
 */
	Mb4RecordingList mb4_puid_get_recordinglist(Mb4PUID PUID);

/**
 * Create a new instance of #Mb4Query.
 *
 * @see MusicBrainz4::CQuery::CQuery
 *
 * @param UserAgent User agent to be passed to submissions
 * @param Server Server to use, pass null to use the default server
 * @param Port Port to use, pass 0 to use the default port
 *
 * @return The newly created #Mb4Query object. This object <b>must</b> be deleted once
 *				finished with.
 */

	Mb4Query mb4_query_new(const char *UserAgent, const char *Server, int Port);

/**
 * Delete a #Mb4Query object
 *
 * @param Query Object to delete
 */
	void mb4_query_delete(Mb4Query Query);

/**
 * Set the username for authenticating to MusicBrainz
 *
 * @see MusicBrainz4::CQuery::SetUserName
 *
 * @param Query #Mb4Query object
 * @param UserName Username to use
 */
	void mb4_query_set_username(Mb4Query Query, const char *UserName);

/**
 * Set the password for authenticating to MusicBrainz
 *
 * @see MusicBrainz4::CQuery::SetPassword
 *
 * @param Query #Mb4Query object
 * @param Password Password to use
 */
	void mb4_query_set_password(Mb4Query Query, const char *Password);

/**
 * Set the proxy server
 *
 * @see MusicBrainz4::CQuery::SetProxyHost
 *
 * @param Query #Mb4Query object
 * @param ProxyHost Proxy server to use
 */
	void mb4_query_set_proxyhost(Mb4Query Query, const char *ProxyHost);

/**
 *	Set the port to use on the proxy server
 *
 * @see MusicBrainz4::CQuery::SetProxyPort
 *
 * @param Query #Mb4Query object
 * @param ProxyPort Port to use on proxy server
 */
	void mb4_query_set_proxyport(Mb4Query Query, int ProxyPort);

/**
 *	Set the username to use to authenticate to the proxy server
 *
 * @see MusicBrainz4::CQuery::SetProxyUserName
 *
 * @param Query #Mb4Query object
 * @param	ProxyUserName User name to use
 */
	void mb4_query_set_proxyusername(Mb4Query Query, const char *ProxyUserName);

/**
 * Set the password to use to authenticate to the proxy server
 *
 * @see MusicBrainz4::CQuery::SetProxyPassword
 *
 * @param Query #Mb4Query object
 * @param ProxyPassword Password to use
 */
	void mb4_query_set_proxypassword(Mb4Query Query, const char *ProxyPassword);

/**
 *	Return a list of releases that match the specified Disc ID
 *
 * @see MusicBrainz4::CQuery::LookupDiscID
 *
 * @param Query #Mb4Query object
 * @param	DiscID DiscID to lookup
 *
 * @return A #Mb4ReleaseList object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4ReleaseList mb4_query_lookup_discid(Mb4Query Query, const char *DiscID);

/**
 * Return full information about a specific release
 *
 * @see MusicBrainz4::CQuery::LookupRelease
 *
 * @param Query #Mb4Query object
 * @param	Release Release to return information for
 *
 * @return A #Mb4Release object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Release mb4_query_lookup_release(Mb4Query Query, const char *Release);

/**
 *	Perform a generic query
 *
 * @see MusicBrainz4::CQuery::Query
 *
 * @param Query #Mb4Query object
 * @param	Entity The entity to query
 * @param ID The ID to query
 * @param Resource The resource to query
 * @param	NumParams The number of parameters in the following arrays
 * @param ParamNames Array of strings containing parameter names
 * @param	ParamValues Array of space seperated parameter values
 *
 * @return A #Mb4Metadata object. This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4Metadata mb4_query_query(Mb4Query Query, const char *Entity, const char *ID, const char *Resource, int NumParams, char **ParamNames, char **ParamValues);

/**
 *	Add a list of releases to a collection
 *
 * @see MusicBrainz4::CQuery::AddCollectionEntries
 *
 * @param Query #Mb4Query object
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
 * @param Query #Mb4Query object
 * @param	Collection ID of collection to delete releases from
 * @param	NumEntries The number of entries to delete
 * @param Entries Array of strings of release IDs to delete
 *
 * @return 0 on failure, 1 on success
 */
	unsigned char mb4_query_delete_collection_entries(Mb4Query Query, const char *Collection, int NumEntries, const char **Entries);

/**
 * @see MusicBrainz4::CQuery::tQueryResult
 */

	typedef enum
	{
			eQuery_Success=0,
			eQuery_ConnectionError,
			eQuery_Timeout,
			eQuery_AuthenticationError,
			eQuery_FetchError,
			eQuery_RequestError,
			eQuery_ResourceNotFound
	} tQueryResult;

/**
 * @see MusicBrainz4::CQuery::LastResult
 *
 * @param Query #Mb4Query object
 *
 * @return Last query result code
 */
	tQueryResult mb4_query_get_lastresult(Mb4Query Query);

/**
 * @see MusicBrainz4::CQuery::LastHTTPCode
 *
 * @param Query #Mb4Query object
 *
 * @return Last HTTP response code
 */
	int mb4_query_get_lasthttpcode(Mb4Query Query);

/**
 * @see MusicBrainz4::CQuery::LastErrorMessage
 *
 * @param Query #Mb4Query object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_query_get_lasterrormessage(Mb4Query Query, char *str, int len);

/**
 * Delete a #Mb4Rating object
 *
 * @param Rating Object to delete
 */
	void mb4_rating_delete(Mb4Rating Rating);

/**
 * @see MusicBrainz4::CRating::VotesCount
 *
 * @param Rating #Mb4Rating object
 *
 * @return Votes count
 */
	int mb4_rating_get_votescount(Mb4Rating Rating);

/**
 *
 *
 * @see MusicBrainz4::CRating::Rating
 *
 * @param Rating #Mb4Rating object
 *
 * @return Returned rating
 */
	double mb4_rating_get_rating(Mb4Rating Rating);

/**
 * Delete a #Mb4Recording object
 *
 * @param Recording Object to delete
 */
	void mb4_recording_delete(Mb4Recording Recording);

/**
 * @see MusicBrainz4::CRecording::ID
 *
 * @param Recording #Mb4Recording object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_recording_get_id(Mb4Recording Recording, char *str, int len);

/**
 * @see MusicBrainz4::CRecording::Title
 *
 * @param Recording #Mb4Recording object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_recording_get_title(Mb4Recording Recording, char *str, int len);

/**
 * @see MusicBrainz4::CRecording::Length
 *
 * @param Recording #Mb4Recording object
 *
 * @return Returned length
 */
	int mb4_recording_get_length(Mb4Recording Recording);

/**
 * @see MusicBrainz4::CRecording::Disambiguation
 *
 * @param Recording #Mb4Recording object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_recording_get_disambiguation(Mb4Recording Recording, char *str, int len);

/**
 * @see MusicBrainz4::CRecording::ArtistCredit
 *
 * @param Recording #Mb4Recording object
 *
 * @return #Mb4ArtistCredit object
 */
	Mb4ArtistCredit mb4_recording_get_artistcredit(Mb4Recording Recording);

/**
 * @see MusicBrainz4::CRecording::ReleaseList
 *
 * @param Recording #Mb4Recording object
 *
 * @return #Mb4ReleaseList
 */
	Mb4ReleaseList mb4_recording_get_releaselist(Mb4Recording Recording);

/**
 * @see MusicBrainz4::CRecording::PUIDList
 *
 * @param Recording #Mb4Recording object
 *
 * @return #Mb4PUIDList
 */
	Mb4PUIDList mb4_recording_get_puidlist(Mb4Recording Recording);

/**
 * @see MusicBrainz4::CRecording::ISRCList
 *
 * @param Recording #Mb4Recording object
 *
 * @return #Mb4ISRCList
 */
	Mb4ISRCList mb4_recording_get_isrclist(Mb4Recording Recording);

/**
 * @see MusicBrainz4::CRecording::RelationList
 *
 * @param Recording #Mb4Recording object
 *
 * @return #Mb4RelationList
 */
	Mb4RelationList mb4_recording_get_relationlist(Mb4Recording Recording);

/**
 * @see MusicBrainz4::CRecording::TagList
 *
 * @param Recording #Mb4Recording object
 *
 * @return #Mb4TagList
 */
	Mb4TagList mb4_recording_get_taglist(Mb4Recording Recording);

/**
 * @see MusicBrainz4::CRecording::UserTagList
 *
 * @param Recording #Mb4Recording object
 *
 * @return #Mb4UserTagList
 */
	Mb4UserTagList mb4_recording_get_usertaglist(Mb4Recording Recording);

/**
 * @see MusicBrainz4::CRecording::Rating
 *
 * @param Recording #Mb4Recording object
 *
 * @return #Mb4Rating object
 */
	Mb4Rating mb4_recording_get_rating(Mb4Recording Recording);

/**
 * @see MusicBrainz4::CRecording::UserRating
 *
 * @param Recording #Mb4Recording object
 *
 * @return #Mb4UserRating object
 */
	Mb4UserRating mb4_recording_get_userrating(Mb4Recording Recording);

/**
 * Delete a #Mb4Relation object
 *
 * @param Relation Object to delete
 */
	void mb4_relation_delete(Mb4Relation Relation);

/**
 * @see MusicBrainz4::CRelation::Type
 *
 * @param Relation #Mb4Relation object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_relation_get_type(Mb4Relation Relation, char *str, int len);

/**
 * @see MusicBrainz4::CRelation::Target
 *
 * @param Relation #Mb4Relation object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_relation_get_target(Mb4Relation Relation, char *str, int len);

/**
 * @see MusicBrainz4::CRelation::Direction
 *
 * @param Relation #Mb4Relation object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_relation_get_direction(Mb4Relation Relation, char *str, int len);

/**
 * @see MusicBrainz4::CRelation::AttributeList
 *
 * @param Relation #Mb4Relation object
 *
 * @return #Mb4AttributeList
 */
	Mb4AttributeList mb4_relation_get_attributelist(Mb4Relation Relation);

/**
 * @see MusicBrainz4::CRelation::Begin
 *
 * @param Relation #Mb4Relation object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_relation_get_begin(Mb4Relation Relation, char *str, int len);

/**
 * @see MusicBrainz4::CRelation::End
 *
 * @param Relation #Mb4Relation object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_relation_get_end(Mb4Relation Relation, char *str, int len);

/**
 * @see MusicBrainz4::CRelation::Artist
 *
 * @param Relation #Mb4Relation object
 *
 * @return #Mb4Artist object
 */
	Mb4Artist mb4_relation_get_artist(Mb4Relation Relation);

/**
 * @see MusicBrainz4::CRelation::Release
 *
 * @param Relation #Mb4Relation object
 *
 * @return #Mb4Release object
 */
	Mb4Release mb4_relation_get_release(Mb4Relation Relation);

/**
 * @see MusicBrainz4::CRelation::ReleaseGroup
 *
 * @param Relation #Mb4Relation object
 *
 * @return #Mb4ReleaseGroup object
 */
	Mb4ReleaseGroup mb4_relation_get_releasegroup(Mb4Relation Relation);

/**
 * @see MusicBrainz4::CRelation::Recording
 *
 * @param Relation #Mb4Relation object
 *
 * @return #Mb4Recording object
 */
	Mb4Recording mb4_relation_get_recording(Mb4Relation Relation);

/**
 * @see MusicBrainz4::CRelation::Label
 *
 * @param Relation #Mb4Relation object
 *
 * @return #Mb4Label object
 */
	Mb4Label mb4_relation_get_label(Mb4Relation Relation);

/**
 * @see MusicBrainz4::CRelation::Work
 *
 * @param Relation #Mb4Relation object
 *
 * @return #Mb4Work object
 */
	Mb4Work mb4_relation_get_work(Mb4Relation Relation);


/**
 * Delete a #Mb4Release object
 *
 * @param Release Object to delete
 */
	void mb4_release_delete(Mb4Release Release);

/**
 * @see MusicBrainz4::CRelease::ID
 *
 * @param Release #Mb4Release object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_release_get_id(Mb4Release Release, char *str, int len);

/**
 * @see MusicBrainz4::CRelease::Title
 *
 * @param Release #Mb4Release object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_release_get_title(Mb4Release Release, char *str, int len);

/**
 * @see MusicBrainz4::CRelease::Status
 *
 * @param Release #Mb4Release object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_release_get_status(Mb4Release Release, char *str, int len);

/**
 * @see MusicBrainz4::CRelease::Quality
 *
 * @param Release #Mb4Release object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_release_get_quality(Mb4Release Release, char *str, int len);

/**
 * @see MusicBrainz4::CRelease::Disambiguation
 *
 * @param Release #Mb4Release object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_release_get_disambiguation(Mb4Release Release, char *str, int len);

/**
 * @see MusicBrainz4::CRelease::Packaging
 *
 * @param Release #Mb4Release object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_release_get_packaging(Mb4Release Release, char *str, int len);

/**
 * @see MusicBrainz4::CRelease::TextRepresentation
 *
 * @param Release #Mb4Release object
 *
 * @return #Mb4TextRepresentation object
 */
	Mb4TextRepresentation mb4_release_get_textrepresentation(Mb4Release Release);

/**
 * @see MusicBrainz4::CRelease::ArtistCredit
 *
 * @param Release #Mb4Release object
 *
 * @return #Mb4ArtistCredit object
 */
	Mb4ArtistCredit mb4_release_get_artistcredit(Mb4Release Release);

/**
 * @see MusicBrainz4::CRelease::ReleaseGroup
 *
 * @param Release #Mb4Release object
 *
 * @return #Mb4ReleaseGroup object
 */
	Mb4ReleaseGroup mb4_release_get_releasegroup(Mb4Release Release);

/**
 * @see MusicBrainz4::CRelease::Date
 *
 * @param Release #Mb4Release object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_release_get_date(Mb4Release Release, char *str, int len);

/**
 * @see MusicBrainz4::CRelease::Country
 *
 * @param Release #Mb4Release object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_release_get_country(Mb4Release Release, char *str, int len);

/**
 * @see MusicBrainz4::CRelease::Barcode
 *
 * @param Release #Mb4Release object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_release_get_barcode(Mb4Release Release, char *str, int len);

/**
 * @see MusicBrainz4::CRelease::ASIN
 *
 * @param Release #Mb4Release object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_release_get_asin(Mb4Release Release, char *str, int len);

/**
 * @see MusicBrainz4::CRelease::LabelInfoList
 *
 * @param Release #Mb4Release object
 *
 * @return #Mb4LabelInfoList
 */
	Mb4LabelInfoList mb4_release_get_labelinfolist(Mb4Release Release);

/**
 * @see MusicBrainz4::CRelease::MediumList
 *
 * @param Release #Mb4Release object
 *
 * @return #Mb4MediumList
 */
	Mb4MediumList mb4_release_get_mediumlist(Mb4Release Release);

/**
 * @see MusicBrainz4::CRelease::RelationList
 *
 * @param Release #Mb4Release object
 *
 * @return #Mb4RelationList
 */
	Mb4RelationList mb4_release_get_relationlist(Mb4Release Release);

/**
 * @see MusicBrainz4::CRelease::MediaMatchingDiscID
 *
 * @param Release #Mb4Release object
 * @param DiscID DiscID to match
 *
 * @return #Mb4MediumList.  This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb4MediumList mb4_release_media_matching_discid(Mb4Release Release, const char *DiscID);

/**
 * Delete a #Mb4ReleaseGroup object
 *
 * @param ReleaseGroup Object to delete
 */
	void mb4_releasegroup_delete(Mb4ReleaseGroup ReleaseGroup);

/**
 * @see MusicBrainz4::CReleaseGroup::ID
 *
 * @param ReleaseGroup #Mb4ReleaseGroup object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_releasegroup_get_id(Mb4ReleaseGroup ReleaseGroup, char *str, int len);

/**
 * @see MusicBrainz4::CReleaseGroup::Type
 *
 * @param ReleaseGroup #Mb4ReleaseGroup object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_releasegroup_get_type(Mb4ReleaseGroup ReleaseGroup, char *str, int len);

/**
 * @see MusicBrainz4::CReleaseGroup::FirstReleaseDate
 *
 * @param ReleaseGroup #Mb4ReleaseGroup object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_releasegroup_get_firstreleasedate(Mb4ReleaseGroup ReleaseGroup, char *str, int len);

/**
 * @see MusicBrainz4::CReleaseGroup::Title
 *
 * @param ReleaseGroup #Mb4ReleaseGroup object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_releasegroup_get_title(Mb4ReleaseGroup ReleaseGroup, char *str, int len);

/**
 * @see MusicBrainz4::CReleaseGroup::Disambiguation
 *
 * @param ReleaseGroup #Mb4ReleaseGroup object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_releasegroup_get_disambiguation(Mb4ReleaseGroup ReleaseGroup, char *str, int len);

/**
 * @see MusicBrainz4::CReleaseGroup::ArtistCredit
 *
 * @param ReleaseGroup #Mb4ReleaseGroup object
 *
 * @return #Mb4ArtistCredit object
 */
	Mb4ArtistCredit mb4_releasegroup_get_artistcredit(Mb4ReleaseGroup ReleaseGroup);

/**
 * @see MusicBrainz4::CReleaseGroup::ReleaseList
 *
 * @param ReleaseGroup #Mb4ReleaseGroup object
 *
 * @return #Mb4ReleaseList
 */
	Mb4ReleaseList mb4_releasegroup_get_releaselist(Mb4ReleaseGroup ReleaseGroup);

/**
 * @see MusicBrainz4::CReleaseGroup::RelationList
 *
 * @param ReleaseGroup #Mb4ReleaseGroup object
 *
 * @return #Mb4RelationList
 */
	Mb4RelationList mb4_releasegroup_get_relationlist(Mb4ReleaseGroup ReleaseGroup);

/**
 * @see MusicBrainz4::CReleaseGroup::TagList
 *
 * @param ReleaseGroup #Mb4ReleaseGroup object
 *
 * @return #Mb4TagList
 */
	Mb4TagList mb4_releasegroup_get_taglist(Mb4ReleaseGroup ReleaseGroup);

/**
 * @see MusicBrainz4::CReleaseGroup::UserTagList
 *
 * @param ReleaseGroup #Mb4ReleaseGroup object
 *
 * @return #Mb4UserTagList
 */
	Mb4UserTagList mb4_releasegroup_get_usertaglist(Mb4ReleaseGroup ReleaseGroup);

/**
 * @see MusicBrainz4::CReleaseGroup::Rating
 *
 * @param ReleaseGroup #Mb4ReleaseGroup object
 *
 * @return #Mb4Rating object
 */
	Mb4Rating mb4_releasegroup_get_rating(Mb4ReleaseGroup ReleaseGroup);

/**
 * @see MusicBrainz4::CReleaseGroup::UserRating
 *
 * @param ReleaseGroup #Mb4ReleaseGroup object
 *
 * @return #Mb4UserRating object
 */
	Mb4UserRating mb4_releasegroup_get_userrating(Mb4ReleaseGroup ReleaseGroup);

/**
 * Delete a #Mb4Tag object
 *
 * @param Tag Object to delete
 */
	void mb4_tag_delete(Mb4Tag Tag);

/**
 * @see MusicBrainz4::CTag::Count
 *
 * @param Tag #Mb4Tag object
 *
 * @return Tag count
 */
	int mb4_tag_get_count(Mb4Tag Tag);

/**
 * @see MusicBrainz4::CTag::Name
 *
 * @param Tag #Mb4Tag object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_tag_get_name(Mb4Tag Tag, char *str, int len);


/**
 * Delete a #Mb4TextRepresentation object
 *
 * @param TextRepresentation Object to delete
 */
	void mb4_textrepresentation_delete(Mb4TextRepresentation TextRepresentation);

/**
 * @see MusicBrainz4::CTextRepresentation::Language
 *
 * @param TextRepresentation #Mb4TextRepresentation object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_textrepresentation_get_language(Mb4TextRepresentation TextRepresentation, char *str, int len);

/**
 * @see MusicBrainz4::CTextRepresentation::Script
 *
 * @param TextRepresentation #Mb4TextRepresentation object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_textrepresentation_get_script(Mb4TextRepresentation TextRepresentation, char *str, int len);


/**
 * Delete a #Mb4Track object
 *
 * @param Track Object to delete
 */
	void mb4_track_delete(Mb4Track Track);

/**
 * @see MusicBrainz4::CTrack::Position
 *
 * @param Track #Mb4Track object
 *
 * @return Track position
 */
	int mb4_track_get_position(Mb4Track Track);

/**
 * @see MusicBrainz4::CTrack::Title
 *
 * @param Track #Mb4Track object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_track_get_title(Mb4Track Track, char *str, int len);

/**
 * @see MusicBrainz4::CTrack::Recording
 *
 * @param Track #Mb4Track object
 *
 * @return #Mb4Recording object
 */
	Mb4Recording mb4_track_get_recording(Mb4Track Track);

/**
 * @see MusicBrainz4::CTrack::Length
 *
 * @param Track #Mb4Track object
 *
 * @return #Mb4Track length
 */
	int mb4_track_get_length(Mb4Track Track);

/**
 * @see MusicBrainz4::CTrack::ArtistCredit
 *
 * @param Track #Mb4Track object
 *
 * @return #Mb4ArtistCredit object
 */
	Mb4ArtistCredit mb4_track_get_artistcredit(Mb4Track Track);


/**
 * Delete a #Mb4UserRating object
 *
 * @param UserRating Object to delete
 */
	void mb4_userrating_delete(Mb4UserRating UserRating);

/**
 * @see MusicBrainz4::CUserRating::UserRating
 *
 * @param UserRating #Mb4UserRating object
 *
 * @return User rating
 */
	int mb4_userrating_get_userrating(Mb4UserRating UserRating);


/**
 * Delete a #Mb4UserTag object
 *
 * @param UserTag Object to delete
 */
	void mb4_usertag_delete(Mb4UserTag UserTag);

/**
 * @see MusicBrainz4::CUserTag::Name
 *
 * @param UserTag #Mb4UserTag object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_usertag_get_name(Mb4UserTag UserTag, char *str, int len);


/**
 * Delete a #Mb4Work object
 *
 * @param Work Object to delete
 */
	void mb4_work_delete(Mb4Work Work);

/**
 * @see MusicBrainz4::CWork::ID
 *
 * @param Work #Mb4Work object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_work_get_id(Mb4Work Work, char *str, int len);

/**
 * @see MusicBrainz4::CWork::Type
 *
 * @param Work #Mb4Work object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_work_get_type(Mb4Work Work, char *str, int len);

/**
 * @see MusicBrainz4::CWork::Title
 *
 * @param Work #Mb4Work object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_work_get_title(Mb4Work Work, char *str, int len);

/**
 * @see MusicBrainz4::CWork::ArtistCredit
 *
 * @param Work #Mb4Work object
 *
 * @return #Mb4ArtistCredit object
 */
	Mb4ArtistCredit mb4_work_get_artistcredit(Mb4Work Work);

/**
 * @see MusicBrainz4::CWork::ISWC
 *
 * @param Work #Mb4Work object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_work_get_iswc(Mb4Work Work, char *str, int len);

/**
 * @see MusicBrainz4::CWork::Disambiguation
 *
 * @param Work #Mb4Work object
 * @param str Returned string
 * @param len Number of characters available in return string
 *
 * @return The number of characters in the string to copy (not including terminating NULL)
 */
	int mb4_work_get_disambiguation(Mb4Work Work, char *str, int len);

/**
 * @see MusicBrainz4::CWork::AliasList
 *
 * @param Work #Mb4Work object
 *
 * @return #Mb4AliasList
 */
	Mb4AliasList mb4_work_get_aliaslist(Mb4Work Work);

/**
 * @see MusicBrainz4::CWork::RelationList
 *
 * @param Work #Mb4Work object
 *
 * @return #Mb4RelationList
 */
	Mb4RelationList mb4_work_get_relationlist(Mb4Work Work);

/**
 * @see MusicBrainz4::CWork::TagList
 *
 * @param Work #Mb4Work object
 *
 * @return #Mb4TagList
 */
	Mb4TagList mb4_work_get_taglist(Mb4Work Work);

/**
 * @see MusicBrainz4::CWork::UserTagList
 *
 * @param Work #Mb4Work object
 *
 * @return #Mb4UserTagList
 */
	Mb4UserTagList mb4_work_get_usertaglist(Mb4Work Work);

/**
 * @see MusicBrainz4::CWork::Rating
 *
 * @param Work #Mb4Work object
 *
 * @return #Mb4Rating object
 */
	Mb4Rating mb4_work_get_rating(Mb4Work Work);

/**
 * @see MusicBrainz4::CWork::UserRating
 *
 * @param Work #Mb4Work object
 *
 * @return #Mb4UserRating object
 */
	Mb4UserRating mb4_work_get_userrating(Mb4Work Work);

/**
 * Delete an #Mb4AliasList
 *
 * @param List List to delete
 */
	void mb4_alias_list_delete(Mb4AliasList List);

/**
 *	Return the number of entries in an #Mb4AliasList
 *
 * @param	List List to use
 */
	int mb4_alias_list_size(Mb4AliasList List);

/**
 *	Returns an entry from an #Mb4AliasList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return #Mb4Alias object.
 */
	Mb4Alias mb4_alias_list_item(Mb4AliasList List, int Item);


/**
 * Delete an #Mb4AnnotationList
 *
 * @param List List to delete
 */
	void mb4_annotation_list_delete(Mb4AnnotationList List);

/**
 *	Return the number of entries in an #Mb4AnnotationList
 *
 * @param	List List to use
 */
	int mb4_annotation_list_size(Mb4AnnotationList List);

/**
 *	Returns an entry from an #Mb4AnnotationList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return An #Mb4Annotation object.
 */
	Mb4Annotation mb4_annotation_list_item(Mb4AnnotationList List, int Item);

/**
 * Delete an #Mb4ArtistList
 *
 * @param List List to delete
 */
	void mb4_artist_list_delete(Mb4ArtistList List);

/**
 *	Return the number of entries in an #Mb4ArtistList
 *
 * @param	List List to use
 */
	int mb4_artist_list_size(Mb4ArtistList List);

/**
 *	Returns an entry from an #Mb4ArtistList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return An #Mb4Artist object.
 */
	Mb4Artist mb4_artist_list_item(Mb4ArtistList List, int Item);

/**
 * Delete an #Mb4AttributeList
 *
 * @param List List to delete
 */
	void mb4_attribute_list_delete(Mb4AttributeList List);

/**
 *	Return the number of entries in an #Mb4AttributeList
 *
 * @param	List List to use
 */
	int mb4_attribute_list_size(Mb4AttributeList List);

/**
 *	Returns an entry from an #Mb4AttributeList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return An #Mb4Attribute object.
 */
	Mb4Attribute mb4_attribute_list_item(Mb4AttributeList List, int Item);

/**
 * Delete a #Mb4CDStubList
 *
 * @param List List to delete
 */
	void mb4_cdstub_list_delete(Mb4CDStubList List);

/**
 *	Return the number of entries in a #Mb4CDStubList
 *
 * @param	List List to use
 */
	int mb4_cdstub_list_size(Mb4CDStubList List);

/**
 *	Returns an entry from a #Mb4CDStubList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A #Mb4CDStub object.
 */
	Mb4CDStub mb4_cdstub_list_item(Mb4CDStubList List, int Item);

/**
 * Delete a #Mb4CollectionList
 *
 * @param List List to delete
 */
	void mb4_collection_list_delete(Mb4CollectionList List);

/**
 *	Return the number of entries in a #Mb4CollectionList
 *
 * @param	List List to use
 */
	int mb4_collection_list_size(Mb4CollectionList List);

/**
 *	Returns an entry from a #Mb4CollectionList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A #Mb4Collection object.
 */
	Mb4Collection mb4_collection_list_item(Mb4CollectionList List, int Item);

/**
 * Delete a #Mb4DiscList
 *
 * @param List List to delete
 */
	void mb4_disc_list_delete(Mb4DiscList List);

/**
 *	Return the number of entries in a #Mb4DiscList
 *
 * @param	List List to use
 */
	int mb4_disc_list_size(Mb4DiscList List);

/**
 *	Returns an entry from a #Mb4DiscList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A #Mb4Disc object.
 */
	Mb4Disc mb4_disc_list_item(Mb4DiscList List, int Item);

/**
 * Delete a #Mb4FreeDBDiscList
 *
 * @param List List to delete
 */
	void mb4_freedbdisc_list_delete(Mb4FreeDBDiscList List);

/**
 *	Return the number of entries in a #Mb4FreeDBDiscList
 *
 * @param	List List to use
 */
	int mb4_freedbdisc_list_size(Mb4FreeDBDiscList List);

/**
 *	Returns an entry from a #Mb4FreeDBDiscList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A #Mb4FreeDBDisc object.
 */
	Mb4FreeDBDisc mb4_freedbdisc_list_item(Mb4FreeDBDiscList List, int Item);

/**
 * Delete an #Mb4ISRCList
 *
 * @param List List to delete
 */
	void mb4_isrc_list_delete(Mb4ISRCList List);

/**
 *	Return the number of entries in an #Mb4ISRCList
 *
 * @param	List List to use
 */
	int mb4_isrc_list_size(Mb4ISRCList List);

/**
 *	Returns an entry from an #Mb4ISRCList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return An #Mb4ISRC object.
 */
	Mb4ISRC mb4_isrc_list_item(Mb4ISRCList List, int Item);

/**
 * Delete a #Mb4LabelList
 *
 * @param List List to delete
 */
	void mb4_label_list_delete(Mb4LabelList List);

/**
 *	Return the number of entries in a #Mb4LabelList
 *
 * @param	List List to use
 */
	int mb4_label_list_size(Mb4LabelList List);

/**
 *	Returns an entry from a #Mb4LabelList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A #Mb4Label object.
 */
	Mb4Label mb4_label_list_item(Mb4LabelList List, int Item);

/**
 * Delete a #Mb4LabelInfoList
 *
 * @param List List to delete
 */
	void mb4_labelinfo_list_delete(Mb4LabelInfoList List);

/**
 *	Return the number of entries in a #Mb4LabelInfoList
 *
 * @param	List List to use
 */
	int mb4_labelinfo_list_size(Mb4LabelInfoList List);

/**
 *	Returns an entry from a #Mb4LabelInfoList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A #Mb4LabelInfo object.
 */
	Mb4LabelInfo mb4_labelinfo_list_item(Mb4LabelInfoList List, int Item);

/**
 * Delete a #Mb4MediumList
 *
 * @param List List to delete
 */
	void mb4_medium_list_delete(Mb4MediumList List);

/**
 *	Return the number of entries in a #Mb4MediumList
 *
 * @param	List List to use
 */
	int mb4_medium_list_size(Mb4MediumList List);

/**
 *	Returns an entry from a #Mb4MediumList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A #Mb4Medium object.
 */
	Mb4Medium mb4_medium_list_item(Mb4MediumList List, int Item);

/**
 * Delete a #Mb4NameCreditList
 *
 * @param List List to delete
 */
	void mb4_namecredit_list_delete(Mb4NameCreditList List);

/**
 *	Return the number of entries in a #Mb4NameCreditList
 *
 * @param	List List to use
 */
	int mb4_namecredit_list_size(Mb4NameCreditList List);

/**
 *	Returns an entry from a #Mb4NameCreditList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A #Mb4NameCredit object.
 */
	Mb4NameCredit mb4_namecredit_list_item(Mb4NameCreditList List, int Item);

/**
 * Delete a #Mb4NonMBTrackList
 *
 * @param List List to delete
 */
	void mb4_nonmbtrack_list_delete(Mb4NonMBTrackList List);

/**
 *	Return the number of entries in a #Mb4NonMBTrackList
 *
 * @param	List List to use
 */
	int mb4_nonmbtrack_list_size(Mb4NonMBTrackList List);

/**
 *	Returns an entry from a #Mb4NonMBTrackList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A #Mb4NonMBTrack object.
 */
	Mb4NonMBTrack mb4_nonmbtrack_list_item(Mb4NonMBTrackList List, int Item);

/**
 * Delete a #Mb4PUIDList
 *
 * @param List List to delete
 */
	void mb4_puid_list_delete(Mb4PUIDList List);

/**
 *	Return the number of entries in a #Mb4PUIDList
 *
 * @param	List List to use
 */
	int mb4_puid_list_size(Mb4PUIDList List);

/**
 *	Returns an entry from a #Mb4PUIDList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A #Mb4PUID object.
 */
	Mb4PUID mb4_puid_list_item(Mb4PUIDList List, int Item);

/**
 * Delete a #Mb4RecordingList
 *
 * @param List List to delete
 */
	void mb4_recording_list_delete(Mb4RecordingList List);

/**
 *	Return the number of entries in a #Mb4RecordingList
 *
 * @param	List List to use
 */
	int mb4_recording_list_size(Mb4RecordingList List);

/**
 *	Returns an entry from a #Mb4RecordingList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A #Mb4Recording object.
 */
	Mb4Recording mb4_recording_list_item(Mb4RecordingList List, int Item);

/**
 * Delete a #Mb4RelationList
 *
 * @param List List to delete
 */
	void mb4_relation_list_delete(Mb4RelationList List);

/**
 *	Return the number of entries in a #Mb4RelationList
 *
 * @param	List List to use
 */
	int mb4_relation_list_size(Mb4RelationList List);

/**
 *	Returns an entry from a #Mb4RelationList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A #Mb4Relation object.
 */
	Mb4Relation mb4_relation_list_item(Mb4RelationList List, int Item);

/**
 * Delete a #Mb4ReleaseList
 *
 * @param List List to delete
 */
	void mb4_release_list_delete(Mb4ReleaseList List);

/**
 *	Return the number of entries in a #Mb4ReleaseList
 *
 * @param	List List to use
 */
	int mb4_release_list_size(Mb4ReleaseList List);

/**
 *	Returns an entry from a #Mb4ReleaseList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A #Mb4Release object.
 */
	Mb4Release mb4_release_list_item(Mb4ReleaseList List, int Item);

/**
 * Delete a #Mb4ReleaseGroupList
 *
 * @param List List to delete
 */
	void mb4_releasegroup_list_delete(Mb4ReleaseGroupList List);

/**
 *	Return the number of entries in a #Mb4ReleaseGroupList
 *
 * @param	List List to use
 */
	int mb4_releasegroup_list_size(Mb4ReleaseGroupList List);

/**
 *	Returns an entry from a #Mb4ReleaseGroupList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A #Mb4ReleaseGroup object.
 */
	Mb4ReleaseGroup mb4_releasegroup_list_item(Mb4ReleaseGroupList List, int Item);

/**
 * Delete a #Mb4TagList
 *
 * @param List List to delete
 */
	void mb4_tag_list_delete(Mb4TagList List);

/**
 *	Return the number of entries in a #Mb4TagList
 *
 * @param	List List to use
 */
	int mb4_tag_list_size(Mb4TagList List);

/**
 *	Returns an entry from a #Mb4TagList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A #Mb4Tag object.
 */
	Mb4Tag mb4_tag_list_item(Mb4TagList List, int Item);

/**
 * Delete a #Mb4TrackList
 *
 * @param List List to delete
 */
	void mb4_track_list_delete(Mb4TrackList List);

/**
 *	Return the number of entries in a #Mb4TrackList
 *
 * @param	List List to use
 */
	int mb4_track_list_size(Mb4TrackList List);

/**
 *	Returns an entry from a #Mb4TrackList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A #Mb4Track object.
 */
	Mb4Track mb4_track_list_item(Mb4TrackList List, int Item);

/**
 * Delete a #Mb4UserTagList
 *
 * @param List List to delete
 */
	void mb4_usertag_list_delete(Mb4UserTagList List);

/**
 *	Return the number of entries in a #Mb4UserTagList
 *
 * @param	List List to use
 */
	int mb4_usertag_list_size(Mb4UserTagList List);

/**
 *	Returns an entry from a #Mb4UserTagList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A #Mb4UserTag object.
 */
	Mb4UserTag mb4_usertag_list_item(Mb4UserTagList List, int Item);

/**
 * Delete a #Mb4WorkList
 *
 * @param List List to delete
 */
	void mb4_work_list_delete(Mb4WorkList List);

/**
 *	Return the number of entries in a #Mb4WorkList
 *
 * @param	List List to use
 */
	int mb4_work_list_size(Mb4WorkList List);

/**
 *	Returns an entry from a #Mb4WorkList
 *
 * @param List List to use
 * @param Item Item number to return
 *
 * @return A #Mb4Work object.
 */
	Mb4Work mb4_work_list_item(Mb4WorkList List, int Item);

#ifdef __cplusplus
}
#endif

#endif


