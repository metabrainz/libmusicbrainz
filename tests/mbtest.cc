/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libmusicbrainz4 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include <iostream>

#include <strings.h>

#include "musicbrainz4/Query.h"
#include "musicbrainz4/Release.h"
#include "musicbrainz4/ReleaseGroup.h"
#include "musicbrainz4/Medium.h"
#include "musicbrainz4/MediumList.h"
#include "musicbrainz4/NameCredit.h"
#include "musicbrainz4/ArtistCredit.h"
#include "musicbrainz4/Artist.h"
#include "musicbrainz4/Alias.h"
#include "musicbrainz4/HTTPFetch.h"
#include "musicbrainz4/Track.h"
#include "musicbrainz4/Recording.h"
#include "musicbrainz4/Collection.h"
#include "musicbrainz4/CollectionList.h"
#include "musicbrainz4/RelationListList.h"
#include "musicbrainz4/RelationList.h"
#include "musicbrainz4/Relation.h"
#include "musicbrainz4/Work.h"
#include "musicbrainz4/ISWC.h"
#include "musicbrainz4/ISWCList.h"
#include "musicbrainz4/SecondaryType.h"
#include "musicbrainz4/SecondaryTypeList.h"
#include "musicbrainz4/IPI.h"
#include "musicbrainz4/IPIList.h"

void PrintRelationList(MusicBrainz4::CRelationList *RelationList)
{
	std::cout << "Target type: '" << RelationList->TargetType() << "'" << std::endl;

	for (int count=0;count<RelationList->NumItems();count++)
	{
		MusicBrainz4::CRelation *Relation=RelationList->Item(count);
		std::cout << "Relation: " << count << " - Type '" << Relation->Type() << "', Target '" << Relation->Target() << "'" << std::endl;
	}
}

int main(int argc, const char *argv[])
{
	MusicBrainz4::CQuery MB2("MBTest/v1.0","test.musicbrainz.org");

	MusicBrainz4::CMetadata Metadata8=MB2.Query("release-group","2eefe885-f050-426d-93f0-29c5eb8b4f9a");
	std::cout << Metadata8 << std::endl;
	return 0;

	MusicBrainz4::CQuery::tParamMap Params5;
	Params5["inc"]="aliases";
	MusicBrainz4::CMetadata Metadata5=MB2.Query("artist","4b585938-f271-45e2-b19a-91c634b5e396","",Params5);
	MusicBrainz4::CArtist *Artist=Metadata5.Artist();
	if (Artist)
	{
		MusicBrainz4::CAliasList *AliasList=Artist->AliasList();
		if (AliasList)
		{
			for (int count=0;count<AliasList->NumItems();count++)
			{
				MusicBrainz4::CAlias *Alias=AliasList->Item(count);
				if (Alias)
				{
					std::cout << "Locale: " << Alias->Locale() << std::endl;
					std::cout << "Text: " << Alias->Text() << std::endl;
					std::cout << "SortName: " << Alias->SortName() << std::endl;
					std::cout << "Type: " << Alias->Type() << std::endl;
					std::cout << "Primary: " << Alias->Primary() << std::endl;
					std::cout << "BeginDate: " << Alias->BeginDate() << std::endl;
					std::cout << "EndDate: " << Alias->EndDate() << std::endl << std::endl;
				}
			}
		}
	}

	return 0;

	MusicBrainz4::CMetadata Metadata7=MB2.Query("artist","4b585938-f271-45e2-b19a-91c634b5e396");
	Artist=Metadata7.Artist();
	if (Artist)
	{
		std::cout << "IPI: " << Artist->IPI() << std::endl;

		MusicBrainz4::CIPIList *IPIList=Artist->IPIList();
		if (IPIList)
		{
			for (int count=0;count<IPIList->NumItems();count++)
			{
				MusicBrainz4::CIPI *IPI=IPIList->Item(count);
				if (IPI)
				{
					std::cout << "IPI " << count << ": " << IPI->IPI() << std::endl;
				}
			}
		}
	}

	return 0;

	MusicBrainz4::CMetadata Metadata6=MB2.Query("release-group","2eefe885-f050-426d-93f0-29c5eb8b4f9a");
	MusicBrainz4::CReleaseGroup *ReleaseGroup=Metadata6.ReleaseGroup();
	if (ReleaseGroup)
	{
		std::cout << "ID: " << ReleaseGroup->ID() << std::endl;
		std::cout << "Type: " << ReleaseGroup->Type() << std::endl;
		std::cout << "Title: " << ReleaseGroup->Title() << std::endl;
		std::cout << "Disambiguation: " << ReleaseGroup->Disambiguation() << std::endl;
		std::cout << "FirstReleaseDate: " << ReleaseGroup->FirstReleaseDate() << std::endl;

		MusicBrainz4::CSecondaryTypeList *SecondaryTypeList=ReleaseGroup->SecondaryTypeList();
		if (SecondaryTypeList)
		{
			for (int count=0;count<SecondaryTypeList->NumItems();count++)
			{
				MusicBrainz4::CSecondaryType *SecondaryType=SecondaryTypeList->Item(count);
				if (SecondaryType)
				{
					std::cout << "Secondary type " << count << " = " << SecondaryType->SecondaryType() << std::endl;
				}
			}
		}
	}

	return 0;

	MusicBrainz4::CMetadata Metadata4=MB2.Query("work","b0d17375-5593-390e-a936-1a65ce74c630");

	MusicBrainz4::CWork *ThisWork=Metadata4.Work();
	if (ThisWork)
	{
		std::cout << "ID: '" << ThisWork->ID() << "'" << std::endl;
		std::cout << "Title: '" << ThisWork->Title() << "'" << std::endl;
		std::cout << "ISWC: '" << ThisWork->ISWC() << "'" << std::endl;

		MusicBrainz4::CISWCList *ISWCList=ThisWork->ISWCList();
		if (ISWCList)
		{
			for (int count=0;count<ISWCList->NumItems();count++)
			{
				MusicBrainz4::CISWC *ISWC=ISWCList->Item(count);
				std::cout << "ISWC " << count << " - '" << ISWC->ISWC() << "'" << std::endl;
			}
		}

		std::cout << "Disambiguation: '" << ThisWork->Disambiguation() << "'" << std::endl;
		std::cout << "Language: '" << ThisWork->Language() << "'" << std::endl;
	}

	MusicBrainz4::CQuery::tParamMap Params3;
	Params3["inc"]="media recordings";

	Metadata4=MB2.Query("release","ae050d13-7f86-495e-9918-10d8c0ac58e8","",Params3);
	MusicBrainz4::CRelease *Release2=Metadata4.Release();
	if (Release2)
	{
		MusicBrainz4::CMediumList *MediumList=Release2->MediumList();
		if (MediumList)
		{
			for (int count=0;count<MediumList->NumItems();count++)
			{
				MusicBrainz4::CMedium *Medium=MediumList->Item(count);
				if (Medium)
				{
					MusicBrainz4::CTrackList *TrackList=Medium->TrackList();
					if (TrackList)
					{
						for (int track=0;track<TrackList->NumItems();track++)
						{
							MusicBrainz4::CTrack *Track=TrackList->Item(track);
							if (Track)
							{
								std::cout << "Position: " << Track->Position() << std::endl;
								std::cout << "Title: " << Track->Title() << std::endl;
								std::cout << "Length: " << Track->Length() << std::endl;
								std::cout << "Number: " << Track->Number() << std::endl;
							}
						}
					}
				}
			}
		}
	}

	return 0;

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

	MusicBrainz4::CQuery::tParamMap Params2;
	Params2["inc"]="artists release-groups url-rels work-level-rels work-rels artist-rels";
	MusicBrainz4::CMetadata Metadata3=MB.Query("recording","3631f569-520d-40ff-a1ee-076604723275","",Params2);
	MusicBrainz4::CRecording *Recording=Metadata3.Recording();
	if (Recording)
	{
		MusicBrainz4::CRelationList *RelationList=Recording->RelationList();
		PrintRelationList(RelationList);

		MusicBrainz4::CRelationListList *RelationListList=Recording->RelationListList();
		for (int count=0;count<RelationListList->NumItems();count++)
		{
			MusicBrainz4::CRelationList *RelationList=RelationListList->Item(count);
			PrintRelationList(RelationList);
		}
	}

	return 0;

	MusicBrainz4::CQuery::tParamMap Params;
	Params["inc"]="artists labels recordings release-groups url-rels discids recording-level-rels work-level-rels work-rels artist-rels";

	MusicBrainz4::CMetadata Metadata2=MB.Query("release","ef4596f0-5554-443a-aea9-247d2e250f61","",Params);

	MusicBrainz4::CRelease *Release=Metadata2.Release();
	if (Release)
	{
		MusicBrainz4::CMediumList *MediumList=Release->MediumList();

		if (MediumList)
		{
			for (int MediumNum=0;MediumNum<MediumList->NumItems();MediumNum++)
			{
				MusicBrainz4::CMedium *Medium=MediumList->Item(MediumNum);
				if (Medium)
				{
					MusicBrainz4::CTrackList *TrackList=Medium->TrackList();
					if (TrackList)
					{
						for (int TrackNum=0;TrackNum<TrackList->NumItems();TrackNum++)
						{
							MusicBrainz4::CTrack *Track=TrackList->Item(TrackNum);
							if (Track)
							{
								MusicBrainz4::CRecording *Recording=Track->Recording();
								if (Recording)
								{
									MusicBrainz4::CRelationListList *RelationListList=Recording->RelationListList();
									if (RelationListList)
									{
										std::cout << RelationListList->NumItems() << " items" << std::endl;
										for (int RelationListNum=0;RelationListNum<RelationListList->NumItems();RelationListNum++)
										{
											MusicBrainz4::CRelationList *RelationList=RelationListList->Item(RelationListNum);
											PrintRelationList(RelationList);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return 0;

	MusicBrainz4::CMetadata Metadata=MB.Query("collection");
	MusicBrainz4::CCollectionList *CollectionList=Metadata.CollectionList();
	if (CollectionList && 0!=CollectionList->NumItems())
	{
		MusicBrainz4::CCollection *Collection=CollectionList->Item(0);
		std::cout << "ID is " << Collection->ID() << std::endl;

		MB.Query("collection",Collection->ID(),"releases");

		std::vector<std::string> Releases;
		Releases.push_back("b5748ac9-f38e-48f7-a8a4-8b43cab025bc");
		Releases.push_back("f6335672-c521-4129-86c3-490d20533e08");
		bool Ret=MB.AddCollectionEntries(Collection->ID(),Releases);
		std::cout << "AddCollectionEntries returns " << std::boolalpha << Ret << std::endl;

		MB.Query("collection",Collection->ID(),"releases");

		Releases.clear();
		Releases.push_back("b5748ac9-f38e-48f7-a8a4-8b43cab025bc");
		Ret=MB.DeleteCollectionEntries(Collection->ID(),Releases);
		std::cout << "DeleteCollectionEntries returns " << std::boolalpha << Ret << std::endl;

		MB.Query("collection",Collection->ID(),"releases");
	}

	return 0;

	std::string DiscID="arIS30RPWowvwNEqsqdDnZzDGhk-";

	if (argc==2)
		DiscID=argv[1];

	MusicBrainz4::CReleaseList ReleaseList=MB.LookupDiscID(DiscID);

	for (int count=0;count<ReleaseList.NumItems();count++)
	{
		MusicBrainz4::CRelease *Release=ReleaseList.Item(count);

		MusicBrainz4::CRelease FullRelease=MB.LookupRelease(Release->ID());

		std::cout << "Full release: " << std::endl;

		std::cout << FullRelease << std::endl;

		std::cout << "Release group title: '" << FullRelease.ReleaseGroup()->Title() << "'" << std::endl;

		std::cout << std::endl << std::endl << "Media matching " << DiscID << ":" << std::endl;

		MusicBrainz4::CMediumList MediaList=FullRelease.MediaMatchingDiscID(DiscID);

		for (int count=0;count<MediaList.NumItems();count++)
		{
			MusicBrainz4::CMedium *Medium=MediaList.Item(count);

			std::cout << *Medium << std::endl;
		}

		std::cout << std::endl << std::endl;
	}

	return 0;
}
