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

  my @result = $mb->lookup_cd;
  die "error: " . $mb->get_error unless $mb->success;

  foreach my $album ( @result ) {
      print $album->get_name, "\n";
  }

=head1 ABSTRACT

  This should be the abstract for MusicBrainz::Client::Simple.
  The abstract is used when making PPD (Perl Package Description) files.
  If you don't want an ABSTRACT you should also edit Makefile.PL to
  remove the ABSTRACT_FROM option.

=head1 DESCRIPTION

Stub documentation for MusicBrainz::Client::Simple, created by h2xs. It looks like the
author of the extension was negligent enough to leave the stub
unedited.

Blah blah blah.

=head2 EXPORT

None by default.



=head1 SEE ALSO

Mention other useful documentation such as the documentation of
related modules or operating system documentation (such as man pages
in UNIX), or any relevant external documentation such as RFCs or
standards.

If you have a mailing list set up for your module, mention it here.

If you have a web site set up for your module, mention it here.

=head1 AUTHORS

Matthias Friedrich, E<lt>matt@mafr.deE<gt>
Sander van Zoest, E<lt>svanzoest@cpan.orgE<gt>

=head1 COPYRIGHT AND LICENSE

Copyright 2003 by Matthias Friedrich

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself. 

=cut
