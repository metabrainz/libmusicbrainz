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

