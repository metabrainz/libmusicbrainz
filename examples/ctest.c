#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "musicbrainz4/mb_c.h"

int main(int argc, const char *argv[])
{
	Mb4Query Query=0;
	char DiscID[256]="tLGBAiCflG8ZI6lFcOt87vXjEcI-";

	if (argc==2)
	{
		strncpy(DiscID,argv[1],sizeof(DiscID));
		DiscID[sizeof(DiscID)-1]='\0';
	}

	Query=mb4_query_new("www.musicbrainz.org");
	if (Query)
	{
		Mb4Metadata Metadata=NULL;

		printf("Got query\n");

		Metadata=mb4_query_query(Query,"discid",DiscID,0,NULL,NULL);
		if (Metadata)
		{
			Mb4Disc *Disc=mb4_metadata_get_disc(Metadata);
			printf("Got metadata\n");

			if (Disc)
			{
				Mb4ReleaseList ReleaseList=mb4_disc_get_releaselist(Disc);

				printf("Got disc\n");

				if (ReleaseList)
				{
					int count;

					printf("Got release list\n");

					printf("%d items\n",mb4_release_list_size(ReleaseList));

					for (count=0;count<mb4_release_list_size(ReleaseList);count++)
					{
						char ID[256];
						Mb4Release Release=mb4_release_list_item(ReleaseList,count);

						printf("Got release %d\n",count);

						mb4_release_get_id(Release,ID,sizeof(ID));
						printf("ID is '%s'\n",ID);

						mb4_release_delete(Release);
					}
				}
			}

			mb4_metadata_delete(Metadata);
		}

		mb4_query_delete(Query);
	}

	return 0;
}