/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id: Lifespan.cc 13211 2011-07-20 16:15:03Z adhawkins $

----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "musicbrainz4/mb4_c.h"

int main(int argc, const char *argv[])
{
	if (argc==2)
	{
		const char *DiscID=argv[1];

		Mb4Query Query=mb4_query_new("cdlookupcexample-1.0",NULL,0);
		if (Query)
		{
			Mb4Metadata Metadata1=mb4_query_query(Query,"discid",DiscID,"",0,NULL,NULL);
			char ErrorMessage[256];

			tQueryResult Result=mb4_query_get_lastresult(Query);
			int HTTPCode=mb4_query_get_lasthttpcode(Query);

			mb4_query_get_lasterrormessage(Query,ErrorMessage,sizeof(ErrorMessage));
			printf("Result: %d\nHTTPCode: %d\nErrorMessage: '%s'\n",Result,HTTPCode,ErrorMessage);

			if (Metadata1)
			{
				Mb4Disc Disc=mb4_metadata_get_disc(Metadata1);
				if (Disc)
				{
					Mb4ReleaseList ReleaseList=mb4_disc_get_releaselist(Disc);
					if (ReleaseList)
					{
						/*
						 *if we want to keep an object around for a while, we can
						 *clone it. We are now responsible for deleting the object
						*/

						Mb4ReleaseList CloneReleaseList=mb4_release_list_clone(ReleaseList);
						int ThisRelease=0;

						printf("Found %d release(s)\n",mb4_release_list_size(ReleaseList));

						for (ThisRelease=0;ThisRelease<mb4_release_list_size(ReleaseList);ThisRelease++)
						{
							Mb4Metadata Metadata2=0;
							Mb4Release Release=mb4_release_list_item(ReleaseList,ThisRelease);

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

								mb4_release_get_id(Release,ReleaseID,sizeof(ReleaseID));

								Metadata2=mb4_query_query(Query,"release",ReleaseID,"",1,ParamNames,ParamValues);

								if (Metadata2)
								{
									Mb4Release FullRelease=mb4_metadata_get_release(Metadata2);
									if (FullRelease)
									{
										/*
										 * However, these releases will include information for all media in the release
										 * So we need to filter out the only the media we want.
										 */

										Mb4MediumList MediumList=mb4_release_media_matching_discid(FullRelease,DiscID);
										if (MediumList)
										{
											if (mb4_medium_list_size(MediumList))
											{
												int ThisMedium=0;

												Mb4ReleaseGroup ReleaseGroup=mb4_release_get_releasegroup(FullRelease);
												if (ReleaseGroup)
												{
													/* One way of getting a string, just use a buffer that
													 * you're pretty sure will accomodate the whole string
													 */

													char Title[256];

													mb4_releasegroup_get_title(ReleaseGroup,Title,sizeof(Title));
													printf("Release group title: '%s'\n",Title);
												}
												else
													printf("No release group for this release\n");

												printf("Found %d media item(s)\n",mb4_medium_list_size(MediumList));

												for (ThisMedium=0;ThisMedium<mb4_medium_list_size(MediumList);ThisMedium++)
												{
													Mb4Medium Medium=mb4_medium_list_item(MediumList,ThisMedium);
													if (Medium)
													{
														int AllocSize=10;
														char *MediumTitle=malloc(AllocSize);
														int RequiredSize;

														Mb4TrackList TrackList=mb4_medium_get_tracklist(Medium);

														/* Another way of getting a string. Preallocate a buffer
														 * and check if if was big enough when retrieving string.
														 * If not, reallocate it to be big enough and get it again.
														 */

														RequiredSize=mb4_medium_get_title(Medium,MediumTitle,AllocSize);
														if (RequiredSize>AllocSize)
														{
															MediumTitle=realloc(MediumTitle,RequiredSize+1);
															mb4_medium_get_title(Medium,MediumTitle,RequiredSize+1);
														}

														printf("Found media: '%s', position %d\n",MediumTitle,mb4_medium_get_position(Medium));

														if (TrackList)
														{
															int ThisTrack=0;

															for (ThisTrack=0;ThisTrack<mb4_track_list_size(TrackList);ThisTrack++)
															{
																char *TrackTitle=0;
																int RequiredLength=0;

																Mb4Track Track=mb4_track_list_item(TrackList,ThisTrack);
																Mb4Recording Recording=mb4_track_get_recording(Track);

																/* Yet another way of getting string. Call it once to
																 * find out how long the buffer needs to be, allocate
																 * enough space and then call again.
																 */

																if (Recording)
																{
																	RequiredLength=mb4_recording_get_title(Recording,TrackTitle,0);
																	TrackTitle=malloc(RequiredLength+1);
																	mb4_recording_get_title(Recording,TrackTitle,RequiredLength+1);
																}
																else
																{
																	RequiredLength=mb4_track_get_title(Track,TrackTitle,0);
																	TrackTitle=malloc(RequiredLength+1);
																	mb4_track_get_title(Track,TrackTitle,RequiredLength+1);
																}

																printf("Track: %d - '%s'\n",mb4_track_get_position(Track),TrackTitle);

																free(TrackTitle);
															}
														}

														free(MediumTitle);
													}
												}
											}

											/* We must delete the result of 'media_matching_discid' */

											mb4_medium_list_delete(MediumList);
										}
									}

									/* We must delete anything returned from the query methods */

									mb4_metadata_delete(Metadata2);
								}

								free(ParamValues[0]);
								free(ParamValues);
								free(ParamNames[0]);
								free(ParamNames);
							}
						}

						/* We must delete anything we have cloned */

						mb4_release_list_delete(CloneReleaseList);
					}
				}

				/* We must delete anything returned from the query methods */

				mb4_metadata_delete(Metadata1);
			}

			/* We must delete the original query object */
			mb4_query_delete(Query);
		}
	}
	else
		fprintf(stderr,"Usage: %s discid\n",argv[0]);

	return 0;
}
