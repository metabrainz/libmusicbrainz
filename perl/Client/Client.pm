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

=head1 DESCRIPTION

This exposes the musicbrainz client library to perl using an OO interface.
For examples on how to use this API please see the test scripts and the
C client library documentation at http://www.musicbrainz.org/

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
