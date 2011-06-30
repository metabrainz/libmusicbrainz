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
#include "musicbrainz4/Collection.h"

int main(int argc, const char *argv[])
{
	MusicBrainz4::CQuery MB("MBTest/v1.0");

	if (argc>1)
	{
		std::cout << "Setting username: '" << argv[1] << "'" << std::endl;
		MB.SetUserName(argv[1]);
	}

	if (argc>2)
	{
		std::cout << "Setting password: '" << argv[2] << "'" << std::endl;
		MB.SetPassword(argv[2]);
	}

	MusicBrainz4::CMetadata Metadata=MB.Query("collection");
	MusicBrainz4::CGenericList<MusicBrainz4::CCollection> *CollectionList=Metadata.CollectionList();
	if (CollectionList)
	{
		std::list<MusicBrainz4::CCollection> Collections=CollectionList->Items();
		MusicBrainz4::CCollection Collection=*(Collections.begin());
		std::cout << "ID is " << Collection.ID() << std::endl;

		MB.Query("collection",Collection.ID(),"releases");

		std::vector<std::string> Releases;
		Releases.push_back("b5748ac9-f38e-48f7-a8a4-8b43cab025bc");
		Releases.push_back("f6335672-c521-4129-86c3-490d20533e08");
		bool Ret=MB.AddCollectionEntries(Collection.ID(),Releases);
		std::cout << "AddCollectionEntries returns " << std::boolalpha << Ret << std::endl;

		MB.Query("collection",Collection.ID(),"releases");

		Releases.clear();
		Releases.push_back("b5748ac9-f38e-48f7-a8a4-8b43cab025bc");
		Ret=MB.DeleteCollectionEntries(Collection.ID(),Releases);
		std::cout << "DeleteCollectionEntries returns " << std::boolalpha << Ret << std::endl;

		MB.Query("collection",Collection.ID(),"releases");
	}

	return 0;

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

