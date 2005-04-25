package MusicBrainz::Client::Simple::Album;
# --------------------------------------------------------------------------
#
#   $Id$
#
#----------------------------------------------------------------------------

use strict;
use warnings;

use MusicBrainz::Client;
use MusicBrainz::Queries qw(:all);

require Exporter;
require DynaLoader;

our @ISA = qw(Exporter);

# Items to export into callers namespace by default. Note: do not export
# names by default without a very good reason. Use EXPORT_OK instead.
# Do not simply export all your public functions/methods/constants.

# This allows declaration       use MusicBrainz::Client::Simple::Album ':all';
# If you do not need this, moving things directly into @EXPORT or @EXPORT_OK
# will save memory.
our %EXPORT_TAGS = ( 'all' => [ qw() ] );

our @EXPORT_OK = ( @{ $EXPORT_TAGS{'all'} } );

our @EXPORT = qw(
);

our $VERSION = do { my @r = (q$Revision$ =~ /\d+/g); $r[0]--;sprintf "%d." ."%02d" x $#r, @r }; # must be all one line, for MakeMaker




#
#		id		=> 
#		name		=>
#
sub new
{
	my $proto = shift;
	my %args = @_;
	my $class = ref($proto) || $proto;
	my $self = {};

	$self->{DATA} = { %args };

	bless($self, $class);

	return $self;
}

sub create_from_album_query($$)
{
	my $self = shift;
	my $mb = shift;

	#
	# Get name and id of this album.
	#
	my $buf = $mb->get_result_data(MBE_AlbumGetAlbumId);
	my $album_id = $mb->get_id_from_url($buf);

	my $album_name = $mb->get_result_data(MBE_AlbumGetAlbumName);

	my $album_type = undef;
	$buf = $mb->get_result_data(MBE_AlbumGetAlbumType);
	if ( $buf ) {
		$album_type = $mb->get_fragment_from_url($buf);
		$album_type =~ s/^Type//;
	}

	my $album_status = undef;
	$buf = $mb->get_result_data(MBE_AlbumGetAlbumStatus);
	if ( $buf ) {
		$album_status = $mb->get_fragment_from_url($buf);
		$album_status =~ s/^Status//;
	}

	#
	# Get the album's artist.
	#
	$buf = $mb->get_result_data(MBE_AlbumGetAlbumArtistId);
	my $artist_id = $mb->get_id_from_url($buf);

	my $artist_name;
	my $artist_sortname;

	my $has_various_artists = $artist_id eq MBI_VARIOUS_ARTIST_ID;

	if ( $has_various_artists ) {
		$artist_name = $artist_sortname = 'Various Artists';
	}
	else {
		# This is no various artists album so all artist names are
		# equal. We pick the first one.
		#
		$artist_name = $mb->get_result_data1(
					MBE_AlbumGetArtistName, 1);
		$artist_sortname = $mb->get_result_data1(
					MBE_AlbumGetArtistSortName, 1);
	}

	my $artist = MusicBrainz::Client::Simple::Artist->new(
		id		=> $artist_id,
		name		=> $artist_name,
		sortname	=> $artist_sortname,
	);


	#
	# Amazon shop IDs (ASIN)
	#
	my $amazon_asin = $mb->get_result_data(MBE_AlbumGetAmazonAsin);

	#
	# Read all release dates.
	#
	my $num_dates = $mb->get_result_int(MBE_AlbumGetNumReleaseDates);
	my %release_dates;
	foreach my $i ( 1 .. $num_dates ) {
		$mb->select1(MBS_SelectReleaseDate, $i) or last;

		my $date = $mb->get_result_data(MBE_ReleaseGetDate);
		my $country = $mb->get_result_data(MBE_ReleaseGetCountry);

		$release_dates{$country} = $date;

		$mb->select(MBS_Back);
	}

	#
	# Compile a list of all tracks.
	#
	my $num_tracks = $mb->get_result_int(MBE_GetNumTracks);
	my @tracks;
	foreach my $i ( 1 .. $num_tracks ) {
		push @tracks, MusicBrainz::Client::Simple::Track
					->create_from_track_query($mb, $i);
	}

	#
	# Finally, put it all together.
	#
	my $album = $self->new(
		id			=> $album_id,
		name			=> $album_name,
		type			=> $album_type,
		status			=> $album_status,

		artist			=> $artist,
		has_various_artists	=> $has_various_artists,
		tracks			=> [ @tracks ],
		release_dates		=> \%release_dates,
		amazon_asin		=> $amazon_asin,
	);

	return $album;
}


sub get_id($)
{
	my $self = shift;

	return $self->{DATA}->{id};
}

sub get_name($)
{
	my $self = shift;

	return $self->{DATA}->{name};
}

sub get_release_status($)
{
	my $self = shift;

	return $self->{DATA}->{status};
}

sub get_release_type($)
{
	my $self = shift;

	return $self->{DATA}->{type};
}

sub get_release_dates($)
{
	my $self = shift;

	return %{ $self->{DATA}->{release_dates} };
}

sub get_artist($)
{
	my $self = shift;

	return $self->{DATA}->{artist};
}

sub get_amazon_asin($)
{
	my $self = shift;

	return $self->{DATA}->{amazon_asin};
}

sub get_tracks($)
{
	my $self = shift;

	return @{ $self->{DATA}->{tracks} };
}

sub has_various_artists($)
{
	my $self = shift;

	return $self->{DATA}->{has_various_artists};
}


1;
__END__

=head1 NAME

MusicBrainz::Client::Simple::Album - MusicBrainz Album Information

=head1 SYNOPSIS


=head1 DESCRIPTION

I<MusicBrainz::Client::Simple::Album> is a class providing access to
album information.


=head1 CONSTRUCTOR

Users of this class need no constructor. Instances are made available
through I<MusicBrainz::Client::Simple>.


=head1 METHODS

=over 4

=item get_artist()

Returns a I<MusicBrainz::Client::Simple::Artist> object that contains
artist information for this album.

See also: L<has_various_artists>


=item get_id()

Returns the I<AlbumID> that uniquely identifies this album at MusicBrainz.


=item get_name()

Returns the album's name.


=item get_release_status()

Returns the release status of this album. Possible values are "Official",
"Promotion" and "Bootleg". If this information is not available, C<undef>
is returned.

See also: L<get_release_type>


=item get_release_dates()

Returns a hash with release dates. Keys are two-letter country codes,
values are dates as strings. A date string can be of the format
"YYYY-MM-DD", "YYYY-MM" or "YYYY".


=item get_tracks()

Returns a list of I<MusicBrainz::Client::Simple::Track> objects, one for
each track on this album.


=item get_release_type()

Returns the release type of this album. Possible values are "Album",
"Single", "EP", "Compilation", "Soundtrack", "Spokenword", "Interview",
"Audiobook", "Live", "Remix" and "Other". If this information is not
available (not all albums in the MusicBrainz database have a release
type yet), C<undef> is returned.

See also: L<get_release_status>


=item has_various_artists()

Returns I<true> if this is a various artists album and I<false> otherwise.


=item get_amazon_asin()

Returns the Amazon.com shop identifier (ASIN) for this album. If there
is none, C<undef> is returned.


=head1 EXPORT

None by default.


=head1 SEE ALSO

 MusicBrainz::Client::Simple
 MusicBrainz::Client::Simple::Artist
 MusicBrainz::Client::Simple::Track
 MusicBrainz::Client
 http://www.musicbrainz.org
 perl(1)


=head1 AUTHORS

 Matthias Friedrich, <matt@mafr.de>
 Sander van Zoest, <svanzoest@cpan.org>


=head1 COPYRIGHT AND LICENSE

Copyright 2003 by Matthias Friedrich E<lt>matt@mafr.deE<gt>

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself. 

=cut
