package MusicBrainz::Client;
# --------------------------------------------------------------------------
#
#   MusicBrainz::Client -- The Internet music metadatabase
#
#   Copyright (C) 2003 Alexander van Zoest
#   
#   $Id$
#
#----------------------------------------------------------------------------*/

require 5.6.1;
use strict;
use warnings;
use Carp;

require Exporter;
require DynaLoader;
use AutoLoader;

our @ISA = qw(Exporter);

# Items to export into callers namespace by default. Note: do not export
# names by default without a very good reason. Use EXPORT_OK instead.
# Do not simply export all your public functions/methods/constants.

# This allows declaration	use MusicBrainz::Client ':all';
# If you do not need this, moving things directly into @EXPORT or @EXPORT_OK
# will save memory.
our %EXPORT_TAGS = ( 'all' => [ qw(MB_CDINDEX_ID_LEN MB_ID_LEN
) ] );

our @EXPORT_OK = ( @{ $EXPORT_TAGS{'all'} } );

our @EXPORT = qw(
);

our $VERSION = do { my @r = (q$Revision$ =~ /\d+/g); $r[0]--;sprintf "%d."."%02d" x $#r, @r }; # must be all one line, for MakeMaker


sub AUTOLOAD {
    # This AUTOLOAD is used to 'autoload' constants from the constant()
    # XS function.

    my $constname;
    our $AUTOLOAD;
    ($constname = $AUTOLOAD) =~ s/.*:://;
    croak "&MusicBrainz::Client::constant not defined" if $constname eq 'constant';
    my ($error, $val) = constant($constname);
    if ($error) { croak $error; }
    {
        no strict 'refs';
        # Fixed between 5.005_53 and 5.005_61
#XXX    if ($] >= 5.00561) {
#XXX        *$AUTOLOAD = sub () { $val };
#XXX    }
#XXX    else {
            *$AUTOLOAD = sub { $val };
#XXX    }
    }
    goto &$AUTOLOAD;
}

require XSLoader;
XSLoader::load('MusicBrainz::Client', $VERSION);

# Preloaded methods go here.

# Autoload methods go after =cut, and are processed by the autosplit program.

1;
__END__

=head1 NAME

MusicBrainz::Client - Perl extension for MusicBrainz Client Library

=head1 SYNOPSIS

  use MusicBrainz::Client;
  use MusicBrainz::Queries qw(:all);

  my $mb = MusicBrainz::Client->new(); 
  if(! $mb->query_with_args( MBQ_FindArtistByName, [ "Pink Floyd" ]) ) {
    die("Query failed: ", $mb->get_query_error(), "\n");
  }
  print "Found ", $mb->get_result_int(MBE_GetNumArtists), " artists\n";
    

=head1 DESCRIPTION

This module provides access to the musicbrainz client API using a perl-ish
OO interface.

=head2 Methods

$mb->new()

($major, $minor, $revision) = $mb->get_version()

$success = $mb->set_server($serverAddr, $serverPort)

$mb->set_debug($debug)
 
$success = $mb->set_proxy($serverAddr, $serverPort)

$success = $mb->authenticate($userName, $password) 

$success = $mb->set_device($device)

$mb->use_utf8($useUTF8)

$mb->set_depth($depth)

$mb->set_max_items($maxItems)

$success = $mb->query($rdfObject)

$sucess = $mb->query_with_args($rdfObject, \@args)

$url = $mb->get_web_submit_url()

$error = $mb->get_query_error()

$success = $mb->select($selectQuery)
 
$success = j$mb->select1($selectQuery, $ord)

$data =  $mb->get_result_data($resultName)

$data1 = $mb->get_result_data1($resultName, $ordinal)

$success = $mb->does_result_exist($resultName)

$success $mb->does_result_exist1($resultName, $ordinal)

$result = $mb->get_result_int($resultName)

$result = $mb->get_result_int1($resultName, $ordinal)

$rdfstr = $mb->get_result_rdf()

$success = $mb->set_result_rdf($rdfstr)

$id = $mb->get_id_from_url($url)

$fragment = $mb->get_fragment_from_url($url)

$ord = $mb->get_ordinal_from_list($resultList, $URI)

$sha1 = $mb->calculate_sha1($filename)

($duration, $bitrate, $stereo, $samplerate) =  $mb->get_mp3_info($filename)

=head2 Examples

For examples on how to use this API please see the test scripts provided and the
C client library documentation at http://www.musicbrainz.org/client_howto.html

=head2 EXPORT

None by default.

=head2 Exportable constants
    
  MB_CDINDEX_ID_LEN
  MB_ID_LEN

=head1 SEE ALSO

perl(1). http://www.musicbrainz.org/

=head1 AUTHOR

Sander van Zoest <svanzoest@cpan.org>

=head1 COPYRIGHT AND LICENSE

Copyright 2003 by Alexander van Zoest.

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself.

=cut
