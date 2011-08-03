Mb4MediumList mb4_release_media_matching_discid(Mb4Release Release, const char *DiscID)
{
	if (Release)
	{
		MusicBrainz4::CRelease *TheRelease=reinterpret_cast<MusicBrainz4::CRelease *>(Release);
		if (TheRelease)
			return new MusicBrainz4::CMediumList(TheRelease->MediaMatchingDiscID(DiscID));
	}

	return 0;
}

