package MusicBrainz::Client::Simple;

use strict;
use warnings;

use MusicBrainz::Client;
use MusicBrainz::Queries qw(:all);
use MusicBrainz::Client::Simple::Album;
use MusicBrainz::Client::Simple::Artist;
use MusicBrainz::Client::Simple::Track;


require Exporter;

our @ISA = qw(Exporter);

# Items to export into callers namespace by default. Note: do not export
# names by default without a very good reason. Use EXPORT_OK instead.
# Do not simply export all your public functions/methods/constants.

# This allows declaration	use MusicBrainz::Client::Simple ':all';
# If you do not need this, moving things directly into @EXPORT or @EXPORT_OK
# will save memory.
our %EXPORT_TAGS = ( 'all' => [ qw(
	
) ] );

our @EXPORT_OK = ( @{ $EXPORT_TAGS{'all'} } );

our @EXPORT = qw(
	
);

our $VERSION = do { my @r = (q$Revision$ =~ /\d+/g); $r[0]--;sprintf "%d."."%02d" x $#r, @r }; # must be all one line, for MakeMaker

# Preloaded methods go here.

#
#	Args:
#		device		=> 
#		debug		=> 
#		utf8		=> 
#		max_items	=>
#		proxy_host	=> 
#		proxy_port	=> 
#
sub new
{
	my $proto = shift;
	my %args = @_;
	my $class = ref($proto) || $proto;
	my $self = {};

	my $mb = MusicBrainz::Client->new;

	$mb->set_device($args{device}) if defined $args{device};
	$mb->set_debug($args{debug}) if defined $args{debug};
	$mb->use_utf8($args{utf8}) if defined $args{utf8};
	$mb->set_max_items($args{max_items}) if defined $args{max_items};

	if ( defined $args{proxy_host} and defined $args{proxy_port} ) {
		$mb->set_proxy($args{proxy_host}, $args{proxy_port});
	}

	$self->{OPTS} = { %args };
	$self->{MB_HANDLE} = $mb;
	$self->{MB_SUCCESS} = 1;

	bless($self, $class);

	return $self;
}


sub get_error($)
{
	my $self = shift;
	my $mb = $self->{MB_HANDLE};

	return $mb->get_query_error;
}

sub success($)
{
	my $self = shift;

	return $self->{MB_SUCCESS};
}

#
# backend for lookup_cd() and lookup_by_cdindex()
#
sub _lookup_disc($$)
{
	my $self = shift;
	my $mb = $self->{MB_HANDLE};

	my $num_albums = $mb->get_result_int(MBE_GetNumAlbums);

	# This is the list of albums that we get.
	#
	my @albums;

	for ( my $i = 1; $i <= $num_albums; $i++ ) {

		# Select an album.
		#
		$mb->select(MBS_Rewind);
		$mb->select1(MBS_SelectAlbum, $i);

		push @albums, MusicBrainz::Client::Simple::Album
						->create_from_album_query($mb);
	}

	return @albums;
}


sub lookup_by_cdindex($$)
{
	my $self = shift;
	my $cdindexid = shift;

	my $mb = $self->{MB_HANDLE};

	$self->{MB_SUCCESS} = 1;

	unless ( $mb->query_with_args(
			MBQ_GetCDInfoFromCDIndexId, [ $cdindexid ]) ) {

		$self->{MB_SUCCESS} = 0;
		return ( );	# empty list
	}

	return $self->_lookup_disc();
}

sub lookup_cd($)
{
	my $self = shift;

	my $mb = $self->{MB_HANDLE};

	$self->{MB_SUCCESS} = 1;

	unless ( $mb->query(MBQ_GetCDInfo) ) {
		$self->{MB_SUCCESS} = 0;
		return ( );	# empty list
	}

	return $self->_lookup_disc();
}

sub find_artist_by_name($$)
{
	my $self = shift;
	my $name = shift;

	my $mb = $self->{MB_HANDLE};

	$self->{MB_SUCCESS} = 1;

	unless ( $mb->query_with_args(MBQ_FindArtistByName, [ $name ]) ) {

		$self->{MB_SUCCESS} = 0;
		return ( );	# empty list
	}

	my $num = $mb->get_result_int(MBE_GetNumArtists);

	my @artists;
	for ( my $i = 1; $i <= $num; $i++ ) {

		# Select an album.
		#
		$mb->select(MBS_Rewind);
		$mb->select1(MBS_SelectArtist, $i);

		push @artists, MusicBrainz::Client::Simple::Artist
					->create_from_artist_query($mb);
	}

	return @artists;
}


1;
__END__

=head1 NAME

MusicBrainz::Client::Simple - Perlish Interface to MusicBrainz Client API

=head1 SYNOPSIS

  use MusicBrainz::Client::Simple;

  my $mb = MusicBrainz::Client::Simple->new( debug => 1, utf8 => 0 );

  my @result = $mb->lookup_cd;
  die "error: " . $mb->get_error unless $mb->success;

  foreach my $album ( @result ) {
      print $album->get_name, "\n";
  }


=head1 DESCRIPTION

I<MusicBrainz::Client::Simple> is a class providing access to the meta
data of L<http://www.musicbrainz.org>. This class aims to be as easy to
use as possible while still offering the most important functionality.
If you need a more powerful interface, try I<MusicBrainz::Client>
instead.


=head1 CONSTRUCTOR

=over 4

=item new( [ OPTIONS ] )

The constructor for a new MusicBrainz::Client::Simple object. To adjust
the object's behaviour, you can pass options in a hash like style as
illustrated in the above example. The following options are possible:

B<device> - The device name of your CD-ROM/DVD-ROM drive. (default: depends
on libmusicbrainz installation)

B<debug> - Print the client's query and the server's response on standard
output. (default: 0)

B<utf8> - If set, strings are in UTF-8 instead of ISO-8859-1 (latin1).
(default: 0)

B<max_items> - The maximum number of records (Artists, Albums, Tracks
etc.) the server returns for one query. (default: 25)

B<proxy_host> - The hostname of a HTTP proxy server. (default: unused)

B<proxy_port> - The port number of a HTTP proxy server. (default: unused)

=back

=head1 METHODS

=over 4

=item lookup_cd()

Queries the CD-ROM/DVD-ROM drive to calculate a I<CDIndexID>. The ID is
then sent to the musicbrainz server. C<lookup_cd> returns a list of
MusicBrainz::Client::Simple::Album objects which contain various
information about album, artist and tracks of your CD.

The reason why you might get I<multiple> Album objects under some rare
circumstances is the following: A I<CDIndexID> is not necessarily
unique, so there is a small probability that two or more albums have
the same I<CDIndexID>.

After L<lookup_cd>, the L<success> method should be called. In case of
an error, L<success> returns false. You can then use L<get_error> to get
a printable error message.


=item lookup_by_cdindex( CDINDEXID )

This method does the same as L<lookup_cd> except for the difference that
you have to pass a valid C<CDIndexID> as an argument. The CD-ROM/DVD-ROM
drive is not used.


=item success()

Returns a I<true> value if the previous operation was successful and
I<false> otherwise.


=item get_error()

Returns a printable string describing the last error that occurred. This
method should only be used if the L<success> method returned I<false>.

=back

=head1 EXPORT

None by default.


=head1 SEE ALSO

 MusicBrainz::Client::Simple::Album
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
