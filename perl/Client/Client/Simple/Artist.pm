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
__END__

=head1 NAME

MusicBrainz::Client::Simple::Artist - MusicBrainz Artist Information

=head1 SYNOPSIS


=head1 DESCRIPTION

I<MusicBrainz::Client::Simple::Artist> is a class providing access to
artist information.


=head1 CONSTRUCTOR

Users of this class need no constructor. Instances are made available
through I<MusicBrainz::Client::Simple>.


=head1 METHODS

=over 4

=item get_id()

Returns the I<ArtistID> that uniquely identifies this artist at MusicBrainz.


=item get_name()

Returns the artist's name.


=item get_sortname()

Returns the artist's name in a way suitable for sorting. E. g for
"Tori Amos", "Amos, Tori" is returned.


=head1 EXPORT

None by default.


=head1 SEE ALSO

 MusicBrainz::Client::Simple
 MusicBrainz::Client::Simple::Album
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
