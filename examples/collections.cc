#include <iostream>

#include "musicbrainz4/Query.h"
#include "musicbrainz4/Collection.h"
#include "musicbrainz4/HTTPFetch.h"

void ListCollection(MusicBrainz4::CQuery& Query, const std::string& CollectionID)
{
		MusicBrainz4::CMetadata Metadata=Query.Query("collection",CollectionID,"releases");
		std::cout << Metadata << std::endl;
}

int main(int argc, const char *argv[])
{
	MusicBrainz4::CQuery Query("collectionexample/v1.0","test.musicbrainz.org");

	if (argc>1)
	{
		if (argc>1)
			Query.SetUserName(argv[1]);

		if (argc>2)
			Query.SetPassword(argv[2]);

		try
		{
			MusicBrainz4::CMetadata Metadata=Query.Query("collection");
			MusicBrainz4::CGenericList<MusicBrainz4::CCollection> *CollectionList=Metadata.CollectionList();
			if (CollectionList)
			{
				std::list<MusicBrainz4::CCollection> Collections=CollectionList->Items();
				MusicBrainz4::CCollection Collection=*(Collections.begin());
				std::cout << "Collection ID is " << Collection.ID() << std::endl;

				ListCollection(Query,Collection.ID());

				std::vector<std::string> Releases;
				Releases.push_back("b5748ac9-f38e-48f7-a8a4-8b43cab025bc");
				Releases.push_back("f6335672-c521-4129-86c3-490d20533e08");
				bool Ret=Query.AddCollectionEntries(Collection.ID(),Releases);

				std::cout << "AddCollectionEntries returns " << std::boolalpha << Ret << std::endl;

				ListCollection(Query,Collection.ID());

				Releases.clear();
				Releases.push_back("b5748ac9-f38e-48f7-a8a4-8b43cab025bc");
				Ret=Query.DeleteCollectionEntries(Collection.ID(),Releases);

				std::cout << "DeleteCollectionEntries returns " << std::boolalpha << Ret << std::endl;

				ListCollection(Query,Collection.ID());
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
		std::cout << "Usage: " << argv[0] << " username [password]" << std::endl << std::endl <<
			"Note that this example uses test.musicbrainz.org by default." << std::endl <<
			"You may need to create an account there." << std::endl;
	}


	return 0;
}
