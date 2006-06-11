/* Get artist by id. 
 * 
 * Usage:
 *  getartist 'artist id'
 *
 * $Id$
 */

#include <stdio.h>
#include <musicbrainz3/mb_c.h>

int
main(int argc, char **argv)
{
	MbQuery query;
	MbArtist artist;
	char data[256];
	
	if (argc < 2) {
		printf("Usage: getartist 'artist id'\n");
		return 1;
	}
	
	mb_webservice_init();
	
	query = mb_query_new(NULL, NULL);
	
	artist = mb_query_get_artist_by_id(query, argv[1], NULL);
	if (!artist) {
		printf("No artist returned.\n");
		mb_query_free(query);
		return 1;
	}
	
	mb_artist_get_id(artist, data, 256);
	printf("Id      : %s\n", data);
	
	mb_artist_get_type(artist, data, 256);
	printf("Type	: %s\n", data);
	
	mb_artist_get_name(artist, data, 256);
	printf("Name	: %s\n", data);
	
	mb_artist_get_sortname(artist, data, 256);
	printf("SortName: %s\n", data);

	mb_artist_free(artist);
	
	mb_query_free(query);
	
	return 0;
}

