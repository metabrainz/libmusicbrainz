#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "musicbrainz4/mb4_c.h"

int main(int argc, const char *argv[])
{
	if (argc==2)
	{
		const char *DiscID=argv[1];

		Mb4Query Query=mb4_query_new("cdlookuptest/v1.0",NULL,0);
		if (Query)
		{
			Mb4Metadata Metadata1=mb4_query_query(Query,"discid",DiscID,"",0,NULL,NULL);
			if (Metadata1)
			{
				Mb4Disc Disc=mb4_metadata_get_disc(Metadata1);
				if (Disc)
				{
					Mb4ReleaseList ReleaseList=mb4_disc_get_releaselist(Disc);
					if (ReleaseList)
					{
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
														char MediumTitle[256];

														Mb4TrackList TrackList=mb4_medium_get_tracklist(Medium);

														mb4_medium_get_title(Medium,MediumTitle,sizeof(MediumTitle));
														printf("Found media: '%s', position %d\n",MediumTitle,mb4_medium_get_position(Medium));

														if (TrackList)
														{
															int ThisTrack=0;

															for (ThisTrack=0;ThisTrack<mb4_track_list_size(TrackList);ThisTrack++)
															{
																char TrackTitle[256];
																Mb4Track Track=mb4_track_list_item(TrackList,ThisTrack);
																Mb4Recording Recording=mb4_track_get_recording(Track);

																if (Recording)
																	mb4_recording_get_title(Recording,TrackTitle,sizeof(TrackTitle));
																else
																	mb4_track_get_title(Track,TrackTitle,sizeof(TrackTitle));

																printf("Track: %d - '%s'\n",mb4_track_get_position(Track),TrackTitle);

																mb4_track_delete(Track);
															}
														}

														mb4_medium_delete(Medium);
													}
												}
											}

											mb4_medium_list_delete(MediumList);
										}
									}

									mb4_metadata_delete(Metadata2);
								}

								free(ParamValues[0]);
								free(ParamValues);
								free(ParamNames[0]);
								free(ParamNames);

								mb4_release_delete(Release);
							}
						}
					}
				}

				mb4_metadata_delete(Metadata1);
			}

			mb4_query_delete(Query);
		}
	}
	else
		fprintf(stderr,"Usage: %s discid\n",argv[0]);

	return 0;
}