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

	$buf = $mb->get_result_data(MBE_AlbumGetAlbumType);
	my $album_type = $mb->get_fragment_from_url($buf);

	$buf = $mb->get_result_data(MBE_AlbumGetAlbumStatus);
	my $album_status = $mb->get_fragment_from_url($buf);

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
		tracks			=> [ @tracks ]
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

sub get_status($)
{
	my $self = shift;

	return $self->{DATA}->{status};
}

sub get_type($)
{
	my $self = shift;

	return $self->{DATA}->{type};
}

sub get_artist($)
{
	my $self = shift;

	return $self->{DATA}->{artist};
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
