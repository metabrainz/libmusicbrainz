/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libmusicbrainz5 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id: Lifespan.cc 13211 2012-07-20 16:15:03Z adhawkins $

----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "musicbrainz5/mb5_c.h"

int main(int argc, const char *argv[])
{
	Mb5Query Query;

	argc=argc;
	argv=argv;

	Query=mb5_query_new("searchcexample-1.0",NULL,0);
	if (Query)
	{
		char **ParamNames;
		char **ParamValues;
		Mb5Metadata Metadata;
		char ErrorMessage[256];
		tQueryResult Result;
		int HTTPCode;

		ParamNames=malloc(2*sizeof(char *));
		ParamNames[0]=malloc(256);
		ParamNames[1]=malloc(256);
		ParamValues=malloc(2*sizeof(char *));
		ParamValues[0]=malloc(256);
		ParamValues[1]=malloc(256);

		strcpy(ParamNames[0],"query");
		strcpy(ParamValues[0],"artist:john");

		strcpy(ParamNames[1],"limit");
		strcpy(ParamValues[1],"10");

		Metadata=mb5_query_query(Query,"artist","","",2,ParamNames,ParamValues);

		Result=mb5_query_get_lastresult(Query);
		HTTPCode=mb5_query_get_lasthttpcode(Query);

		mb5_query_get_lasterrormessage(Query,ErrorMessage,sizeof(ErrorMessage));
		printf("Result: %d\nHTTPCode: %d\nErrorMessage: '%s'\n",Result,HTTPCode,ErrorMessage);

		if (Metadata)
		{
			int ThisArtist;
			Mb5ArtistList ArtistList=mb5_metadata_get_artistlist(Metadata);

			printf("Found %d artist(s)\n",mb5_artist_list_size(ArtistList));

			for (ThisArtist=0;ThisArtist<mb5_artist_list_size(ArtistList);ThisArtist++)
			{
				Mb5Artist Artist=mb5_artist_list_item(ArtistList,ThisArtist);
				if (Artist)
				{
					int count;
					char Name[256];
					char Value[256];
					int NumExtAttrs=mb5_entity_ext_attributes_size(Artist);
					int NumExtElements=mb5_entity_ext_elements_size(Artist);

					printf("%d attrs, %d elements\n",NumExtAttrs,NumExtElements);

					for (count=0;count<NumExtAttrs;count++)
					{
						mb5_entity_ext_attribute_name(Artist,count,Name,sizeof(Name));
						mb5_entity_ext_attribute_value(Artist,count,Value,sizeof(Value));

						printf("Attr '%s' = '%s'\n",Name,Value);
					}

					for (count=0;count<NumExtElements;count++)
					{
						mb5_entity_ext_element_name(Artist,count,Name,sizeof(Name));
						mb5_entity_ext_element_value(Artist,count,Value,sizeof(Value));

						printf("Element '%s' = '%s'\n",Name,Value);
					}

					mb5_artist_get_name(Artist,Name,sizeof(Name));
					printf("Artist is '%s'\n",Name);

					mb5_artist_get_sortname(Artist,Name,sizeof(Name));
					printf("Artist sort is '%s'\n",Name);
				}
				else
				{
					printf("Couldn't get artist %d\n",ThisArtist);
				}
			}

			mb5_metadata_delete(Metadata);
		}

		free(ParamValues[1]);
		free(ParamValues[0]);
		free(ParamValues);
		free(ParamNames[1]);
		free(ParamNames[0]);
		free(ParamNames);

		mb5_query_delete(Query);
	}

	return 0;
}
