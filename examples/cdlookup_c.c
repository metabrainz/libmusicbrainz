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
	if (argc==2)
	{
		const char *DiscID=argv[1];

		Mb5Query Query=mb5_query_new("cdlookupcexample-1.0",NULL,0);
		if (Query)
		{
			Mb5Metadata Metadata1=mb5_query_query(Query,"discid",DiscID,"",0,NULL,NULL);
			char ErrorMessage[256];

			tQueryResult Result=mb5_query_get_lastresult(Query);
			int HTTPCode=mb5_query_get_lasthttpcode(Query);

			mb5_query_get_lasterrormessage(Query,ErrorMessage,sizeof(ErrorMessage));
			printf("Result: %d\nHTTPCode: %d\nErrorMessage: '%s'\n",Result,HTTPCode,ErrorMessage);

			if (Metadata1)
			{
				Mb5Disc Disc=mb5_metadata_get_disc(Metadata1);
				if (Disc)
				{
					Mb5ReleaseList ReleaseList=mb5_disc_get_releaselist(Disc);
					if (ReleaseList)
					{
						/*
						 *if we want to keep an object around for a while, we can
						 *clone it. We are now responsible for deleting the object
						*/

						Mb5ReleaseList CloneReleaseList=mb5_release_list_clone(ReleaseList);
						int ThisRelease=0;

						printf("Found %d release(s)\n",mb5_release_list_size(ReleaseList));

						for (ThisRelease=0;ThisRelease<mb5_release_list_size(ReleaseList);ThisRelease++)
						{
							Mb5Metadata Metadata2=0;
							Mb5Release Release=mb5_release_list_item(ReleaseList,ThisRelease);

							if (Release)
							{
								/* The releases returned from LookupDiscID don't contain full information */

								char **ParamNames;
								char **ParamValues;
								char ReleaseID[256];

								ParamNames=malloc(sizeof(char *));
								ParamNames[0]=malloc(256);
								ParamValues=malloc(sizeof(char *));
								ParamValues[0]=malloc(256);

								strcpy(ParamNames[0],"inc");
								strcpy(ParamValues[0],"artists labels recordings release-groups url-rels discids artist-credits");

								mb5_release_get_id(Release,ReleaseID,sizeof(ReleaseID));

								Metadata2=mb5_query_query(Query,"release",ReleaseID,"",1,ParamNames,ParamValues);

								if (Metadata2)
								{
									Mb5Release FullRelease=mb5_metadata_get_release(Metadata2);
									if (FullRelease)
									{
										/*
										 * However, these releases will include information for all media in the release
										 * So we need to filter out the only the media we want.
										 */

										Mb5MediumList MediumList=mb5_release_media_matching_discid(FullRelease,DiscID);
										if (MediumList)
										{
											if (mb5_medium_list_size(MediumList))
											{
												int ThisMedium=0;

												Mb5ReleaseGroup ReleaseGroup=mb5_release_get_releasegroup(FullRelease);
												if (ReleaseGroup)
												{
													/* One way of getting a string, just use a buffer that
													 * you're pretty sure will accomodate the whole string
													 */

													char Title[256];

													mb5_releasegroup_get_title(ReleaseGroup,Title,sizeof(Title));
													printf("Release group title: '%s'\n",Title);
												}
												else
													printf("No release group for this release\n");

												printf("Found %d media item(s)\n",mb5_medium_list_size(MediumList));

												for (ThisMedium=0;ThisMedium<mb5_medium_list_size(MediumList);ThisMedium++)
												{
													Mb5Medium Medium=mb5_medium_list_item(MediumList,ThisMedium);
													if (Medium)
													{
														int AllocSize=10;
														char *MediumTitle=malloc(AllocSize);
														int RequiredSize;

														Mb5TrackList TrackList=mb5_medium_get_tracklist(Medium);

														/* Another way of getting a string. Preallocate a buffer
														 * and check if if was big enough when retrieving string.
														 * If not, reallocate it to be big enough and get it again.
														 */

														RequiredSize=mb5_medium_get_title(Medium,MediumTitle,AllocSize);
														if (RequiredSize>AllocSize)
														{
															MediumTitle=realloc(MediumTitle,RequiredSize+1);
															mb5_medium_get_title(Medium,MediumTitle,RequiredSize+1);
														}

														printf("Found media: '%s', position %d\n",MediumTitle,mb5_medium_get_position(Medium));

														if (TrackList)
														{
															int ThisTrack=0;

															for (ThisTrack=0;ThisTrack<mb5_track_list_size(TrackList);ThisTrack++)
															{
																char *TrackTitle=0;
																int RequiredLength=0;

																Mb5Track Track=mb5_track_list_item(TrackList,ThisTrack);
																Mb5Recording Recording=mb5_track_get_recording(Track);

																/* Yet another way of getting string. Call it once to
																 * find out how long the buffer needs to be, allocate
																 * enough space and then call again.
																 */

																if (Recording)
																{
																	RequiredLength=mb5_recording_get_title(Recording,TrackTitle,0);
																	TrackTitle=malloc(RequiredLength+1);
																	mb5_recording_get_title(Recording,TrackTitle,RequiredLength+1);
																}
																else
																{
																	RequiredLength=mb5_track_get_title(Track,TrackTitle,0);
																	TrackTitle=malloc(RequiredLength+1);
																	mb5_track_get_title(Track,TrackTitle,RequiredLength+1);
																}

																printf("Track: %d - '%s'\n",mb5_track_get_position(Track),TrackTitle);

																free(TrackTitle);
															}
														}

														free(MediumTitle);
													}
												}
											}

											/* We must delete the result of 'media_matching_discid' */

											mb5_medium_list_delete(MediumList);
										}
									}

									/* We must delete anything returned from the query methods */

									mb5_metadata_delete(Metadata2);
								}

								free(ParamValues[0]);
								free(ParamValues);
								free(ParamNames[0]);
								free(ParamNames);
							}
						}

						/* We must delete anything we have cloned */

						mb5_release_list_delete(CloneReleaseList);
					}
				}

				/* We must delete anything returned from the query methods */

				mb5_metadata_delete(Metadata1);
			}

			/* We must delete the original query object */
			mb5_query_delete(Query);
		}
	}
	else
		fprintf(stderr,"Usage: %s discid\n",argv[0]);

	return 0;
}
