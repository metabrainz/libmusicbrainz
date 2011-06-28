#include <string>

#include "musicbrainz4/Query.h"
#include "musicbrainz4/Medium.h"
#include "musicbrainz4/ReleaseGroup.h"
#include "musicbrainz4/Track.h"
#include "musicbrainz4/Recording.h"
#include "musicbrainz4/Disc.h"

int main(int argc, const char *argv[])
{
	if (argc==2)
	{
		std::string DiscID=argv[1];

		MusicBrainz4::CQuery Query("cdlookuptest/v1.0");

		MusicBrainz4::CMetadata Metadata=Query.Query("discid",DiscID);
		if (Metadata.Disc() && Metadata.Disc()->ReleaseList())
		{
			MusicBrainz4::CGenericList<MusicBrainz4::CRelease> *ReleaseList=Metadata.Disc()->ReleaseList();
			std::list<MusicBrainz4::CRelease> Releases=ReleaseList->Items();

			std::cout << "Found " << Releases.size() << " release(s)" << std::endl;

			for (std::list<MusicBrainz4::CRelease>::const_iterator ThisRelease=Releases.begin();ThisRelease!=Releases.end();ThisRelease++)
			{
				MusicBrainz4::CRelease Release=(*ThisRelease);

				std::cout << "Basic release: " << std::endl << Release << std::endl;

				//The releases returned from LookupDiscID don't contain full information

				MusicBrainz4::CQuery::tParamMap Params;
				Params["inc"]="artists labels recordings release-groups url-rels discids artist-credits";

				Metadata=Query.Query("release",Release.ID(),"",Params);
				if (Metadata.Release())
				{
					MusicBrainz4::CRelease *FullRelease=Metadata.Release();

					//However, these releases will include information for all media in the release
					//So we need to filter out the only the media we want.

					MusicBrainz4::CGenericList<MusicBrainz4::CMedium> MediaList=FullRelease->MediaMatchingDiscID(DiscID);
					std::list<MusicBrainz4::CMedium> Media=MediaList.Items();

					if (Media.size())
					{
						if (FullRelease->ReleaseGroup())
							std::cout << "Release group title: '" << FullRelease->ReleaseGroup()->Title() << "'" << std::endl;
						else
							std::cout << "No release group for this release" << std::endl;

						std::cout << "Found " << Media.size() << " media item(s)" << std::endl;

						for (std::list<MusicBrainz4::CMedium>::const_iterator ThisMedium=Media.begin();ThisMedium!=Media.end();ThisMedium++)
						{
							MusicBrainz4::CMedium Medium=(*ThisMedium);

							std::cout << "Found media: '" << Medium.Title() << "', position " << Medium.Position() << std::endl;

							MusicBrainz4::CGenericList<MusicBrainz4::CTrack> *TrackList=Medium.TrackList();
							if (TrackList)
							{
								std::list<MusicBrainz4::CTrack> Tracks=TrackList->Items();
								for (std::list<MusicBrainz4::CTrack>::const_iterator ThisTrack=Tracks.begin();ThisTrack!=Tracks.end();ThisTrack++)
								{
									MusicBrainz4::CTrack Track=(*ThisTrack);
									MusicBrainz4::CRecording *Recording=Track.Recording();

									if (Recording)
										std::cout << "Track: " << Track.Position() << " - '" << Recording->Title() << "'" << std::endl;
									else
										std::cout << "Track: " << Track.Position() << " - '" << Track.Title() << "'" << std::endl;
								}
							}
						}
					}
				}
			}
		}
	}
	else
	{
		std::cerr << "Usage: " << argv[0] << " discid" << std::endl;
	}

	return 0;
}