/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   libmusicbrainz4 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include <string>

#include "musicbrainz4/Query.h"
#include "musicbrainz4/Medium.h"
#include "musicbrainz4/MediumList.h"
#include "musicbrainz4/ReleaseGroup.h"
#include "musicbrainz4/Track.h"
#include "musicbrainz4/TrackList.h"
#include "musicbrainz4/Recording.h"
#include "musicbrainz4/Disc.h"
#include "musicbrainz4/HTTPFetch.h"
#include "musicbrainz4/Release.h"

int main(int argc, const char *argv[])
{
	if (argc==2)
	{
		std::string DiscID=argv[1];

		MusicBrainz4::CQuery Query("cdlookupexample-1.0");

		std::cout << "Library version: '" << Query.Version() << "'" << std::endl;

		try
		{
			MusicBrainz4::CMetadata Metadata=Query.Query("discid",DiscID);
			if (Metadata.Disc() && Metadata.Disc()->ReleaseList())
			{
				MusicBrainz4::CReleaseList *ReleaseList=Metadata.Disc()->ReleaseList();

				std::cout << "Found " << ReleaseList->NumItems() << " release(s)" << std::endl;

				for (int count=0;count<ReleaseList->NumItems();count++)
				{
					MusicBrainz4::CRelease *Release=ReleaseList->Item(count);

					std::cout << "Basic release: " << std::endl << (*Release) << std::endl;

					//The releases returned from LookupDiscID don't contain full information

					MusicBrainz4::CQuery::tParamMap Params;
					Params["inc"]="artists labels recordings release-groups url-rels discids artist-credits";

					std::string ReleaseID=Release->ID();

					MusicBrainz4::CMetadata Metadata2=Query.Query("release",ReleaseID,"",Params);
					if (Metadata2.Release())
					{
						MusicBrainz4::CRelease *FullRelease=Metadata2.Release();

						//However, these releases will include information for all media in the release
						//So we need to filter out the only the media we want.

						MusicBrainz4::CMediumList MediaList=FullRelease->MediaMatchingDiscID(DiscID);

						if (0!=MediaList.NumItems())
						{
							if (FullRelease->ReleaseGroup())
								std::cout << "Release group title: '" << FullRelease->ReleaseGroup()->Title() << "'" << std::endl;
							else
								std::cout << "No release group for this release" << std::endl;

							std::cout << "Found " << MediaList.NumItems() << " media item(s)" << std::endl;

							for (int count=0;count<MediaList.NumItems();count++)
							{
								MusicBrainz4::CMedium *Medium=MediaList.Item(count);

								std::cout << "Found media: '" << Medium->Title() << "', position " << Medium->Position() << std::endl;

								MusicBrainz4::CTrackList *TrackList=Medium->TrackList();
								if (TrackList)
								{
									for (int count=0;count<TrackList->NumItems();count++)
									{
										MusicBrainz4::CTrack *Track=TrackList->Item(count);
										MusicBrainz4::CRecording *Recording=Track->Recording();

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

		catch (MusicBrainz4::CConnectionError& Error)
		{
			std::cout << "Connection Exception: '" << Error.what() << "'" << std::endl;
			std::cout << "LastResult: " << Query.LastResult() << std::endl;
			std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
			std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
		}

		catch (MusicBrainz4::CTimeoutError& Error)
		{
			std::cout << "Timeout Exception: '" << Error.what() << "'" << std::endl;
			std::cout << "LastResult: " << Query.LastResult() << std::endl;
			std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
			std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
		}

		catch (MusicBrainz4::CAuthenticationError& Error)
		{
			std::cout << "Authentication Exception: '" << Error.what() << "'" << std::endl;
			std::cout << "LastResult: " << Query.LastResult() << std::endl;
			std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
			std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
		}

		catch (MusicBrainz4::CFetchError& Error)
		{
			std::cout << "Fetch Exception: '" << Error.what() << "'" << std::endl;
			std::cout << "LastResult: " << Query.LastResult() << std::endl;
			std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
			std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
		}

		catch (MusicBrainz4::CRequestError& Error)
		{
			std::cout << "Request Exception: '" << Error.what() << "'" << std::endl;
			std::cout << "LastResult: " << Query.LastResult() << std::endl;
			std::cout << "LastHTTPCode: " << Query.LastHTTPCode() << std::endl;
			std::cout << "LastErrorMessage: " << Query.LastErrorMessage() << std::endl;
		}

		catch (MusicBrainz4::CResourceNotFoundError& Error)
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
