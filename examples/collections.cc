#include <iostream>

#include "musicbrainz4/Query.h"
#include "musicbrainz4/Collection.h"

void ListCollection(MusicBrainz4::CQuery& MB, const std::string& CollectionID)
{
		MusicBrainz4::CMetadata Metadata=MB.Query("collection",CollectionID,"releases");
		std::cout << Metadata << std::endl;
}

int main(int argc, const char *argv[])
{
	MusicBrainz4::CQuery MB("collectionexample/v1.0","test.musicbrainz.org");

	if (argc>1)
	{
		if (argc>1)
			MB.SetUserName(argv[1]);

		if (argc>2)
			MB.SetPassword(argv[2]);

		MusicBrainz4::CMetadata Metadata=MB.Query("collection");
		MusicBrainz4::CGenericList<MusicBrainz4::CCollection> *CollectionList=Metadata.CollectionList();
		if (CollectionList)
		{
			std::list<MusicBrainz4::CCollection> Collections=CollectionList->Items();
			MusicBrainz4::CCollection Collection=*(Collections.begin());
			std::cout << "Collection ID is " << Collection.ID() << std::endl;

			ListCollection(MB,Collection.ID());

			std::vector<std::string> Releases;
			Releases.push_back("b5748ac9-f38e-48f7-a8a4-8b43cab025bc");
			Releases.push_back("f6335672-c521-4129-86c3-490d20533e08");
			bool Ret=MB.AddCollectionEntries(Collection.ID(),Releases);

			std::cout << "AddCollectionEntries returns " << std::boolalpha << Ret << std::endl;

			ListCollection(MB,Collection.ID());

			Releases.clear();
			Releases.push_back("b5748ac9-f38e-48f7-a8a4-8b43cab025bc");
			Ret=MB.DeleteCollectionEntries(Collection.ID(),Releases);

			std::cout << "DeleteCollectionEntries returns " << std::boolalpha << Ret << std::endl;

			ListCollection(MB,Collection.ID());
		}
	}
	else
	{
		std::cout << "Usage: " << argv[0] << " username [password]" << std::endl << std::endl <<
			"Note that this example uses test.musicbrainz.org by default." << std::endl <<
			"You may need to create an account there." << std::endl;
	}


	return 0;
}
