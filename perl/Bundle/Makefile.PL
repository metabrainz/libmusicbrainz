# $Id$

use ExtUtils::MakeMaker;
use strict;

WriteMakefile(
              NAME	   => 'Bundle::MusicBrainz::Client',
              VERSION_FROM => 'Client.pm',
              'dist'       => {
                               COMPRESS => 'gzip -9f',
                               SUFFIX   => '.gz',
                              },
             );
