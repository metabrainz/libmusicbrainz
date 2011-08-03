unsigned char mb4_medium_contains_discid(Mb4Medium Medium, const char *DiscID)
{
	unsigned char Ret=0;

	if (Medium)
	{
		MusicBrainz4::CMedium *TheMedium=reinterpret_cast<MusicBrainz4::CMedium *>(Medium);
		if (TheMedium)
			Ret=TheMedium->ContainsDiscID(DiscID);
	}

	return Ret;
}
