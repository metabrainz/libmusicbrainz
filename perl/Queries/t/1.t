# Before `make install' is performed this script should be runnable with
# `make test'. After `make install' it should work as `perl 1.t'

#########################

# change 'tests => 2' to 'tests => last_test_to_print';

use Test;
BEGIN { plan tests => 2 };
use MusicBrainz::Queries;
ok(1); # If we made it this far, we're ok.


my $fail;
foreach my $constname (qw(
	MBE_AlbumGetAlbumArtistId MBE_AlbumGetAlbumId MBE_AlbumGetAlbumName
	MBE_AlbumGetAlbumStatus MBE_AlbumGetAlbumType MBE_AlbumGetArtistId
	MBE_AlbumGetArtistName MBE_AlbumGetArtistSortName
	MBE_AlbumGetNumCdindexIds MBE_AlbumGetNumTracks
	MBE_AlbumGetTrackDuration MBE_AlbumGetTrackId MBE_AlbumGetTrackList
	MBE_AlbumGetTrackName MBE_AlbumGetTrackNum MBE_ArtistGetAlbumId
	MBE_ArtistGetAlbumName MBE_ArtistGetArtistId MBE_ArtistGetArtistName
	MBE_ArtistGetArtistSortName MBE_AuthGetChallenge MBE_AuthGetSessionId
	MBE_GetError MBE_GetNumAlbums MBE_GetNumArtists MBE_GetNumLookupResults
	MBE_GetNumTracks MBE_GetNumTrmids MBE_GetStatus MBE_LookupGetAlbumId
	MBE_LookupGetArtistId MBE_LookupGetRelevance MBE_LookupGetTrackId
	MBE_LookupGetType MBE_QuerySubject MBE_QuickGetAlbumName
	MBE_QuickGetArtistName MBE_QuickGetTrackDuration MBE_QuickGetTrackId
	MBE_QuickGetTrackName MBE_QuickGetTrackNum MBE_TOCGetCDIndexId
	MBE_TOCGetFirstTrack MBE_TOCGetLastTrack MBE_TOCGetTrackNumSectors
	MBE_TOCGetTrackSectorOffset MBE_TrackGetArtistId MBE_TrackGetArtistName
	MBE_TrackGetArtistSortName MBE_TrackGetTrackDuration
	MBE_TrackGetTrackId MBE_TrackGetTrackName MBE_TrackGetTrackNum
	MBI_VARIOUS_ARTIST_ID MBQ_AssociateCD MBQ_Authenticate
	MBQ_FileInfoLookup MBQ_FindAlbumByName MBQ_FindArtistByName
	MBQ_FindDistinctTRMId MBQ_FindTrackByName MBQ_GetAlbumById
	MBQ_GetArtistById MBQ_GetCDInfo MBQ_GetCDInfoFromCDIndexId MBQ_GetCDTOC
	MBQ_GetTrackById MBQ_GetTrackByTRMId MBQ_QuickTrackInfoFromTrackId
	MBQ_SubmitTrack MBQ_SubmitTrackTRMId MBQ_TrackInfoFromTRMId MBS_Back
	MBS_Rewind MBS_SelectAlbum MBS_SelectArtist MBS_SelectCdindexid
	MBS_SelectLookupResult MBS_SelectLookupResultAlbum
	MBS_SelectLookupResultArtist MBS_SelectLookupResultTrack
	MBS_SelectTrack MBS_SelectTrackAlbum MBS_SelectTrackArtist
	MBS_SelectTrmid)) {
  next if (eval "my \$a = $constname; 1");
  if ($@ =~ /^Your vendor has not defined MusicBrainz::Queries macro $constname/) {
    print "# pass: $@";
  } else {
    print "# fail: $@";
    $fail = 1;    
  }
}
if ($fail) {
  print "not ok 2\n";
} else {
  print "ok 2\n";
}

#########################

# Insert your test code below, the Test::More module is use()ed here so read
# its man page ( perldoc Test::More ) for help writing this test script.

