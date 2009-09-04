// Retrieve a release group by ID
//
// Usage:
//	getreleasegroup 'RG id'
//
// 

#include <iostream>
#include <musicbrainz3/webservice.h>
#include <musicbrainz3/query.h>
#include <musicbrainz3/model.h>

using namespace std;
using namespace MusicBrainz;

int
main(int argc, char **argv)
{
	if (argc < 2) {
		cout << "Usage: getreleasegroup 'RG id'" << endl;
		return 1;
	}
	
	Query q;
	ReleaseGroup *releaseGroup;
	
	try {
		ReleaseGroupIncludes inc = ReleaseGroupIncludes().artist().releases();
		releaseGroup = q.getReleaseGroupById(argv[1], &inc);
	}
	catch (WebServiceError &e) {
		cout << "Error: " << e.what() << endl;
		return 1;
	}

	cout << "Id        : " << releaseGroup->getId() << endl;
	cout << "Title     : " << releaseGroup->getTitle() << endl;
	cout << "Type      : " << releaseGroup->getType() << endl;
	cout << "Artist    : " << releaseGroup->getArtist()->getName() << endl;
	
	delete releaseGroup;
	
	return 0;
}

