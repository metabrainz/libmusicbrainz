package MusicBrainz::Client::Simple::Track;
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

# This allows declaration       use MusicBrainz::Client::Simple::Track ':all';
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
#		num		=>
#		duration	=>
#		artist		=>
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

sub create_from_track_query($$$)
{
	my $self = shift;
	my $mb = shift;
	my $tracknum = shift;

	my $buf = $mb->get_result_data1(MBE_AlbumGetTrackId, $tracknum);
	my $id = $mb->get_id_from_url($buf);

	my $name = $mb->get_result_data1(MBE_AlbumGetTrackName, $tracknum);

	my $duration = $mb->get_result_data1(MBE_AlbumGetTrackDuration,
						$tracknum);

	my $artist = MusicBrainz::Artist->create_from_album_query($mb,
								$tracknum);

	my $track = $self->new(
		id		=> $id,
		name		=> $name,
		duration 	=> $duration,
		num		=> $tracknum,
		artist		=> $artist
	);

	return $track;
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

sub get_num($)
{
	my $self = shift;

	return $self->{DATA}->{num};
}

sub get_duration($)
{
	my $self = shift;

	return $self->{DATA}->{duration};
}

sub get_artist($)
{
	my $self = shift;

	return $self->{DATA}->{artist};
}

1;
