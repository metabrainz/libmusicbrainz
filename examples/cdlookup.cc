/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libmusicbrainz5 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include <string>

#include "musicbrainz5/Query.h"
#include "musicbrainz5/Medium.h"
#include "musicbrainz5/MediumList.h"
#include "musicbrainz5/ReleaseGroup.h"
#include "musicbrainz5/Track.h"
#include "musicbrainz5/TrackList.h"
#include "musicbrainz5/Recording.h"
#include "musicbrainz5/Disc.h"
#include "musicbrainz5/HTTPFetch.h"
#include "musicbrainz5/Release.h"

int main(int argc, const char *argv[])
{
	if (argc==2)
	{
		std::string DiscID=argv[1];

		MusicBrainz5::CQuery Query("cdlookupexample-1.0");

		std::cout << "Library version: '" << Query.Version() << "'" << std::endl;

		try
		{
			MusicBrainz5::CMetadata Metadata=Query.Query("discid",DiscID);
			if (Metadata.Disc() && Metadata.Disc()->ReleaseList())
			{
				MusicBrainz5::CReleaseList *ReleaseList=Metadata.Disc()->ReleaseList();

				std::cout << "Found " << ReleaseList->NumItems() << " release(s)" << std::endl;

				for (int count=0;count<ReleaseList->NumItems();count++)
				{
					MusicBrainz5::CRelease *Release=ReleaseList->Item(count);

					std::cout << "Basic release: " << std::endl << (*Release) << std::endl;

					//The releases returned from LookupDiscID don't contain full information

					MusicBrainz5::CQuery::tParamMap Params;
					Params["inc"]="artists labels recordings release-groups url-rels discids artist-credits";

					std::string ReleaseID=Release->ID();

					MusicBrainz5::CMetadata Metadata2=Query.Query("release",ReleaseID,"",Params);
					if (Metadata2.Release())
					{
						MusicBrainz5::CRelease *FullRelease=Metadata2.Release();

						//However, these releases will include information for all media in the release
						//So we need to filter out the only the media we want.

						MusicBrainz5::CMediumList MediaList=FullRelease->MediaMatchingDiscID(DiscID);

						if (0!=MediaList.NumItems())
						{
							if (FullRelease->ReleaseGroup())
								std::cout << "Release group title: '" << FullRelease->ReleaseGroup()->Title() << "'" << std::endl;
							else
								std::cout << "No release group for this release" << std::endl;

							std::cout << "Found " << MediaList.NumItems() << " media item(s)" << std::endl;

							for (int count=0;count<MediaList.NumItems();count++)
							{
								MusicBrainz5::CMedium *Medium=MediaList.Item(count);

								std::cout << "Found media: '" << Medium->Title() << "', position " << Medium->Position() << std::endl;

								MusicBrainz5::CTrackList *TrackList=Medium->TrackList();
								if (TrackList)
								{
									for (int count=0;count<TrackList->NumItems();count++)
									{
										MusicBrainz5::CTrack *Track=TrackList->Item(count);
										MusicBrainz5::CRecording *Recording=Track->Recording();

										if (Recording)
											std::cout << "Track: " << Track->Position() << " - '" << Recording->Title() << "'" << std::endl;
										else
											std::cout << "Track: " << Track->Position() << " - '" << Track->Title() << "'" << std::endl;
									}
								}
							}
						}
					}
				}
			}
		}

		catch (MusicBrainz5::CConnectionError& Error)
		{
			std::cout << "Connection Exception: '" << Error.what() << "'" << std::endl;
			std::cout << "LastResult: " << Query.LastResult() << std::endl;
			std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
			std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
		}

		catch (MusicBrainz5::CTimeoutError& Error)
		{
			std::cout << "Timeout Exception: '" << Error.what() << "'" << std::endl;
			std::cout << "LastResult: " << Query.LastResult() << std::endl;
			std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
			std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
		}

		catch (MusicBrainz5::CAuthenticationError& Error)
		{
			std::cout << "Authentication Exception: '" << Error.what() << "'" << std::endl;
			std::cout << "LastResult: " << Query.LastResult() << std::endl;
			std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
			std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
		}

		catch (MusicBrainz5::CFetchError& Error)
		{
			std::cout << "Fetch Exception: '" << Error.what() << "'" << std::endl;
			std::cout << "LastResult: " << Query.LastResult() << std::endl;
			std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
			std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
		}

		catch (MusicBrainz5::CRequestError& Error)
		{
			std::cout << "Request Exception: '" << Error.what() << "'" << std::endl;
			std::cout << "LastResult: " << Query.LastResult() << std::endl;
			std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
			std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
		}

		catch (MusicBrainz5::CResourceNotFoundError& Error)
		{
			std::cout << "ResourceNotFound Exception: '" << Error.what() << "'" << std::endl;
			std::cout << "LastResult: " << Query.LastResult() << std::endl;
			std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
			std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
		}
	}
	else
	{
		std::cerr << "Usage: " << argv[0] << " discid" << std::endl;
	}

	return 0;
}
