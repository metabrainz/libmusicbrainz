#include <iostream>

#include "musicbrainz4/Query.h"

/* For further information, see the web service search documentation:
 *
 * http://wiki.musicbrainz.org/Text_Search_Syntax
 */

void DoSearch(const std::string& Entity, const std::string Search)
{
	MusicBrainz4::CQuery Query("queryexample/v1.0");

	MusicBrainz4::CQuery::tParamMap Params;
	Params["query"]=Search;
	Params["limit"]="10";

	MusicBrainz4::CMetadata Metadata=Query.Query(Entity,"","",Params);

	std::cout << "First 10 " << Entity << "s matching: " << Search << std::endl << Metadata << std::endl;
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
