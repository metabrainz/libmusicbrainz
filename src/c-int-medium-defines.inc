/**
 * @see MusicBrainz4::CMedium::ContainsDiscID
 *
 * @param Medium #Mb4Medium object
 * @param DiscID DiscID to check
 *
 * @return 1 if DiscID found, 0 otherwise
 */
	unsigned char mb4_medium_contains_discid(Mb4Medium Medium, const char *DiscID);
