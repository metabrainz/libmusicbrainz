package MusicBrainz::Queries;

use 5.6.1;
use strict;
use warnings;
use Carp;

require Exporter;
use AutoLoader;

our @ISA = qw(Exporter);

# Items to export into callers namespace by default. Note: do not export
# names by default without a very good reason. Use EXPORT_OK instead.
# Do not simply export all your public functions/methods/constants.

# This allows declaration	use MusicBrainz::Queries ':all';
# If you do not need this, moving things directly into @EXPORT or @EXPORT_OK
# will save memory.
our %EXPORT_TAGS = ( 'all' => [ qw(
	MBE_AlbumGetAlbumArtistId
	MBE_AlbumGetAlbumId
	MBE_AlbumGetAlbumName
	MBE_AlbumGetAlbumStatus
	MBE_AlbumGetAlbumType
	MBE_AlbumGetArtistId
	MBE_AlbumGetArtistName
	MBE_AlbumGetArtistSortName
	MBE_AlbumGetNumCdindexIds
	MBE_AlbumGetNumTracks
	MBE_AlbumGetTrackDuration
	MBE_AlbumGetTrackId
	MBE_AlbumGetTrackList
	MBE_AlbumGetTrackName
	MBE_AlbumGetTrackNum
	MBE_ArtistGetAlbumId
	MBE_ArtistGetAlbumName
	MBE_ArtistGetArtistId
	MBE_ArtistGetArtistName
	MBE_ArtistGetArtistSortName
	MBE_AuthGetChallenge
	MBE_AuthGetSessionId
	MBE_GetError
	MBE_GetNumAlbums
	MBE_GetNumArtists
	MBE_GetNumLookupResults
	MBE_GetNumTracks
	MBE_GetNumTrmids
	MBE_GetStatus
	MBE_LookupGetAlbumId
	MBE_LookupGetArtistId
	MBE_LookupGetRelevance
	MBE_LookupGetTrackId
	MBE_LookupGetType
	MBE_QuerySubject
	MBE_QuickGetAlbumName
	MBE_QuickGetArtistName
	MBE_QuickGetTrackDuration
	MBE_QuickGetTrackId
	MBE_QuickGetTrackName
	MBE_QuickGetTrackNum
	MBE_TOCGetCDIndexId
	MBE_TOCGetFirstTrack
	MBE_TOCGetLastTrack
	MBE_TOCGetTrackNumSectors
	MBE_TOCGetTrackSectorOffset
	MBE_TrackGetArtistId
	MBE_TrackGetArtistName
	MBE_TrackGetArtistSortName
	MBE_TrackGetTrackDuration
	MBE_TrackGetTrackId
	MBE_TrackGetTrackName
	MBE_TrackGetTrackNum
	MBI_VARIOUS_ARTIST_ID
	MBQ_AssociateCD
	MBQ_Authenticate
	MBQ_FileInfoLookup
	MBQ_FindAlbumByName
	MBQ_FindArtistByName
	MBQ_FindDistinctTRMId
	MBQ_FindTrackByName
	MBQ_GetAlbumById
	MBQ_GetArtistById
	MBQ_GetCDInfo
	MBQ_GetCDInfoFromCDIndexId
	MBQ_GetCDTOC
	MBQ_GetTrackById
	MBQ_GetTrackByTRMId
	MBQ_QuickTrackInfoFromTrackId
	MBQ_SubmitTrack
	MBQ_SubmitTrackTRMId
	MBQ_TrackInfoFromTRMId
	MBS_Back
	MBS_Rewind
	MBS_SelectAlbum
	MBS_SelectArtist
	MBS_SelectCdindexid
	MBS_SelectLookupResult
	MBS_SelectLookupResultAlbum
	MBS_SelectLookupResultArtist
	MBS_SelectLookupResultTrack
	MBS_SelectTrack
	MBS_SelectTrackAlbum
	MBS_SelectTrackArtist
	MBS_SelectTrmid
) ] );

our @EXPORT_OK = ( @{ $EXPORT_TAGS{'all'} } );

our @EXPORT = qw(
	MBE_AlbumGetAlbumArtistId
	MBE_AlbumGetAlbumId
	MBE_AlbumGetAlbumName
	MBE_AlbumGetAlbumStatus
	MBE_AlbumGetAlbumType
	MBE_AlbumGetArtistId
	MBE_AlbumGetArtistName
	MBE_AlbumGetArtistSortName
	MBE_AlbumGetNumCdindexIds
	MBE_AlbumGetNumTracks
	MBE_AlbumGetTrackDuration
	MBE_AlbumGetTrackId
	MBE_AlbumGetTrackList
	MBE_AlbumGetTrackName
	MBE_AlbumGetTrackNum
	MBE_ArtistGetAlbumId
	MBE_ArtistGetAlbumName
	MBE_ArtistGetArtistId
	MBE_ArtistGetArtistName
	MBE_ArtistGetArtistSortName
	MBE_AuthGetChallenge
	MBE_AuthGetSessionId
	MBE_GetError
	MBE_GetNumAlbums
	MBE_GetNumArtists
	MBE_GetNumLookupResults
	MBE_GetNumTracks
	MBE_GetNumTrmids
	MBE_GetStatus
	MBE_LookupGetAlbumId
	MBE_LookupGetArtistId
	MBE_LookupGetRelevance
	MBE_LookupGetTrackId
	MBE_LookupGetType
	MBE_QuerySubject
	MBE_QuickGetAlbumName
	MBE_QuickGetArtistName
	MBE_QuickGetTrackDuration
	MBE_QuickGetTrackId
	MBE_QuickGetTrackName
	MBE_QuickGetTrackNum
	MBE_TOCGetCDIndexId
	MBE_TOCGetFirstTrack
	MBE_TOCGetLastTrack
	MBE_TOCGetTrackNumSectors
	MBE_TOCGetTrackSectorOffset
	MBE_TrackGetArtistId
	MBE_TrackGetArtistName
	MBE_TrackGetArtistSortName
	MBE_TrackGetTrackDuration
	MBE_TrackGetTrackId
	MBE_TrackGetTrackName
	MBE_TrackGetTrackNum
	MBI_VARIOUS_ARTIST_ID
	MBQ_AssociateCD
	MBQ_Authenticate
	MBQ_FileInfoLookup
	MBQ_FindAlbumByName
	MBQ_FindArtistByName
	MBQ_FindDistinctTRMId
	MBQ_FindTrackByName
	MBQ_GetAlbumById
	MBQ_GetArtistById
	MBQ_GetCDInfo
	MBQ_GetCDInfoFromCDIndexId
	MBQ_GetCDTOC
	MBQ_GetTrackById
	MBQ_GetTrackByTRMId
	MBQ_QuickTrackInfoFromTrackId
	MBQ_SubmitTrack
	MBQ_SubmitTrackTRMId
	MBQ_TrackInfoFromTRMId
	MBS_Back
	MBS_Rewind
	MBS_SelectAlbum
	MBS_SelectArtist
	MBS_SelectCdindexid
	MBS_SelectLookupResult
	MBS_SelectLookupResultAlbum
	MBS_SelectLookupResultArtist
	MBS_SelectLookupResultTrack
	MBS_SelectTrack
	MBS_SelectTrackAlbum
	MBS_SelectTrackArtist
	MBS_SelectTrmid
);

our $VERSION = do { my @r = (q$Revision$ =~ /\d+/g); $r[0]--;sprintf "%d."."%02d" x $#r, @r }; # must be all one line, for MakeMaker  

sub AUTOLOAD {
    # This AUTOLOAD is used to 'autoload' constants from the constant()
    # XS function.

    my $constname;
    our $AUTOLOAD;
    ($constname = $AUTOLOAD) =~ s/.*:://;
    croak "&MusicBrainz::Queries::constant not defined" if $constname eq 'constant';
    my ($error, $val) = constant($constname);
    if ($error) { croak $error; }
    {
	no strict 'refs';
	# Fixed between 5.005_53 and 5.005_61
#XXX	if ($] >= 5.00561) {
#XXX	    *$AUTOLOAD = sub () { $val };
#XXX	}
#XXX	else {
	    *$AUTOLOAD = sub { $val };
#XXX	}
    }
    goto &$AUTOLOAD;
}

require XSLoader;
XSLoader::load('MusicBrainz::Queries', $VERSION);

# Preloaded methods go here.

# Autoload methods go after =cut, and are processed by the autosplit program.

1;
__END__
# Below is stub documentation for your module. You'd better edit it!

=head1 NAME

MusicBrainz::Queries - Perl extension for the Music Brainz RDF Query Constants

=head1 SYNOPSIS

  use MusicBrainz::Queries;

=head1 ABSTRACT

  This should be the abstract for MusicBrainz::Queries.
  The abstract is used when making PPD (Perl Package Description) files.
  If you don't want an ABSTRACT you should also edit Makefile.PL to
  remove the ABSTRACT_FROM option.

=head1 DESCRIPTION

Stub documentation for MusicBrainz::Queries, created by h2xs. It looks like the
author of the extension was negligent enough to leave the stub
unedited.

=head2 EXPORT

None by default.

=head2 Exportable constants

  MBE_AlbumGetAlbumArtistId
  MBE_AlbumGetAlbumId
  MBE_AlbumGetAlbumName
  MBE_AlbumGetAlbumStatus
  MBE_AlbumGetAlbumType
  MBE_AlbumGetArtistId
  MBE_AlbumGetArtistName
  MBE_AlbumGetArtistSortName
  MBE_AlbumGetNumCdindexIds
  MBE_AlbumGetNumTracks
  MBE_AlbumGetTrackDuration
  MBE_AlbumGetTrackId
  MBE_AlbumGetTrackList
  MBE_AlbumGetTrackName
  MBE_AlbumGetTrackNum
  MBE_ArtistGetAlbumId
  MBE_ArtistGetAlbumName
  MBE_ArtistGetArtistId
  MBE_ArtistGetArtistName
  MBE_ArtistGetArtistSortName
  MBE_AuthGetChallenge
  MBE_AuthGetSessionId
  MBE_GetError
  MBE_GetNumAlbums
  MBE_GetNumArtists
  MBE_GetNumLookupResults
  MBE_GetNumTracks
  MBE_GetNumTrmids
  MBE_GetStatus
  MBE_LookupGetAlbumId
  MBE_LookupGetArtistId
  MBE_LookupGetRelevance
  MBE_LookupGetTrackId
  MBE_LookupGetType
  MBE_QuerySubject
  MBE_QuickGetAlbumName
  MBE_QuickGetArtistName
  MBE_QuickGetTrackDuration
  MBE_QuickGetTrackId
  MBE_QuickGetTrackName
  MBE_QuickGetTrackNum
  MBE_TOCGetCDIndexId
  MBE_TOCGetFirstTrack
  MBE_TOCGetLastTrack
  MBE_TOCGetTrackNumSectors
  MBE_TOCGetTrackSectorOffset
  MBE_TrackGetArtistId
  MBE_TrackGetArtistName
  MBE_TrackGetArtistSortName
  MBE_TrackGetTrackDuration
  MBE_TrackGetTrackId
  MBE_TrackGetTrackName
  MBE_TrackGetTrackNum
  MBI_VARIOUS_ARTIST_ID
  MBQ_AssociateCD
  MBQ_Authenticate
  MBQ_FileInfoLookup
  MBQ_FindAlbumByName
  MBQ_FindArtistByName
  MBQ_FindDistinctTRMId
  MBQ_FindTrackByName
  MBQ_GetAlbumById
  MBQ_GetArtistById
  MBQ_GetCDInfo
  MBQ_GetCDInfoFromCDIndexId
  MBQ_GetCDTOC
  MBQ_GetTrackById
  MBQ_GetTrackByTRMId
  MBQ_QuickTrackInfoFromTrackId
  MBQ_SubmitTrack
  MBQ_SubmitTrackTRMId
  MBQ_TrackInfoFromTRMId
  MBS_Back
  MBS_Rewind
  MBS_SelectAlbum
  MBS_SelectArtist
  MBS_SelectCdindexid
  MBS_SelectLookupResult
  MBS_SelectLookupResultAlbum
  MBS_SelectLookupResultArtist
  MBS_SelectLookupResultTrack
  MBS_SelectTrack
  MBS_SelectTrackAlbum
  MBS_SelectTrackArtist
  MBS_SelectTrmid



=head1 SEE ALSO

MusicBrainz::Client

http://www.musicbrainz.org/

=head1 AUTHOR

Sander van Zoest, E<lt>svanzoest@cpan.org<gt>

=head1 COPYRIGHT AND LICENSE

Copyright 2003 by Alexander van Zoest

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself. 

=cut
