#include <iostream>

#include "musicbrainz4/Query.h"

void DoSearch(const std::string& Entity, const std::string Search)
{
	MusicBrainz4::CQuery Query("queryexample/v1.0");

	//Search for all releases by Kate Bush

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

	DoSearch("release","artist:\"Kate Bush\"");
	DoSearch("release","release:sensual");
	DoSearch("artist","artist:john");
}
