#include <iostream>

#include "musicbrainz4/Query.h"
#include "musicbrainz4/HTTPFetch.h"

/* For further information, see the web service search documentation:
 *
 * http://wiki.musicbrainz.org/Text_Search_Syntax
 */

void DoSearch(const std::string& Entity, const std::string Search)
{
	MusicBrainz4::CQuery Query("queryexample-1.0");

	MusicBrainz4::CQuery::tParamMap Params;
	Params["query"]=Search;
	Params["limit"]="10";

	try
	{
		MusicBrainz4::CMetadata Metadata=Query.Query(Entity,"","",Params);

		std::cout << "First 10 " << Entity << "s matching: " << Search << std::endl << Metadata << std::endl;
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

int main(int argc, const char *argv[])
{
	argc=argc;
	argv=argv;

	//Search for all releases by Kate Bush

	DoSearch("release","artist:\"Kate Bush\"");

	//Search for all releases with 'sensual' in the title

	DoSearch("release","release:sensual");

	//Search for all artists with 'john' in the name

	DoSearch("artist","artist:john");
}
