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

#include <iostream>

#include <strings.h>

#include "musicbrainz4/Query.h"
#include "musicbrainz4/GenericList.h"
#include "musicbrainz4/Release.h"
#include "musicbrainz4/ReleaseGroup.h"
#include "musicbrainz4/Medium.h"
#include "musicbrainz4/NameCredit.h"
#include "musicbrainz4/ArtistCredit.h"
#include "musicbrainz4/Artist.h"
#include "musicbrainz4/HTTPFetch.h"
#include "musicbrainz4/Track.h"
#include "musicbrainz4/Recording.h"

int main(int argc, const char *argv[])
{
	MusicBrainz4::CQuery MB;

	std::string DiscID="arIS30RPWowvwNEqsqdDnZzDGhk-";

	if (argc==2)
		DiscID=argv[1];

	MusicBrainz4::CGenericList<MusicBrainz4::CRelease> ReleaseList=MB.LookupDiscID(DiscID);

	std::list<MusicBrainz4::CRelease>Releases=ReleaseList.Items();
	std::list<MusicBrainz4::CRelease>::const_iterator ThisRelease=Releases.begin();
	while (ThisRelease!=Releases.end())
	{
		MusicBrainz4::CRelease Release=(*ThisRelease);

		MusicBrainz4::CRelease FullRelease=MB.LookupRelease(Release.ID());

		std::cout << "Full release: " << std::endl;

		std::cout << FullRelease << std::endl;

		std::cout << "Release group title: '" << FullRelease.ReleaseGroup()->Title() << "'" << std::endl;

		std::cout << std::endl << std::endl << "Media matching " << DiscID << ":" << std::endl;

		MusicBrainz4::CGenericList<MusicBrainz4::CMedium> MediaList=FullRelease.MediaMatchingDiscID(DiscID);
		std::list<MusicBrainz4::CMedium> Media=MediaList.Items();
		std::list<MusicBrainz4::CMedium>::const_iterator ThisMedium=Media.begin();
		while (ThisMedium!=Media.end())
		{
			std::cout << *ThisMedium << std::endl;

			++ThisMedium;
		}

		std::cout << std::endl << std::endl;

		++ThisRelease;
	}

	return 0;
}

