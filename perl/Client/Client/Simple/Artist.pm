package MusicBrainz::Client::Simple::Artist;
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

# This allows declaration       use MusicBrainz::Client::Simple::Artist ':all';
# If you do not need this, moving things directly into @EXPORT or @EXPORT_OK
# will save memory.
our %EXPORT_TAGS = ( 'all' => [ qw() ] );

our @EXPORT_OK = ( @{ $EXPORT_TAGS{'all'} } );

our @EXPORT = qw(
);

our $VERSION = do { my @r = (q$Revision$ =~ /\d+/g); $r[0]--;sprintf "%d." ."%02d" x $#r, @r }; # must be all one line, for MakeMaker

#
#		id		=> 
#		name
#		sortname	=> 
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


sub create_from_album_query($$$)
{
	my $self = shift;
	my $mb = shift;
	my $tracknum = shift;

	my $buf = $mb->get_result_data1(MBE_AlbumGetArtistId, $tracknum); 
	my $id = $mb->get_id_from_url($buf);
	my $name = $mb->get_result_data1(MBE_AlbumGetArtistName, $tracknum);
	my $sortname = $mb->get_result_data1(MBE_AlbumGetArtistSortName,
								$tracknum);
	
	my $artist = $self->new(
		id		=> $id,
		name		=> $name,
		sortname	=> $sortname,
	);

	return $artist;
}

sub create_from_artist_query($$)
{
	my $self = shift;
	my $mb = shift;

	my $buf = $mb->get_result_data(MBE_ArtistGetArtistId);
	my $id = $mb->get_id_from_url($buf);
	my $name = $mb->get_result_data(MBE_ArtistGetArtistName);
	my $sortname = $mb->get_result_data(MBE_ArtistGetArtistSortName);

	my $artist = $self->new(
		id		=> $id,
		name		=> $name,
		sortname	=> $sortname
	);

	return $artist;
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

sub get_sortname($)
{
	my $self = shift;

	return $self->{DATA}->{sortname};
}

1;
