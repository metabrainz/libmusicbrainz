
use 5.6.1;
use ExtUtils::MakeMaker;

# $Id$

sub MY::postamble {

  return <<'EOT';
ck_version :
	@perl -MExtUtils::MakeMaker -le 'print "Version: " . MM->parse_version(shift)' $(VERSION_FROM)

cvs_export :
	cvs export -r$(NAME_SYM)_$(VERSION_SYM) -d$(DISTVNAME) $(CVS_PACKAGE)

cvs_tag :
	cvs tag $(NAME_SYM)_$(VERSION_SYM) .
	@echo tagged all files with $(NAME_SYM)_$(VERSION_SYM)

EOT
}

# See lib/ExtUtils/MakeMaker.pm for details of how to influence
# the contents of the Makefile that is written.
WriteMakefile(
    'NAME'              => 'MusicBrainz::Client',
    'VERSION_FROM'      => 'Client.pm', # finds $VERSION
    'PREREQ_PM'	        => {'MusicBrainz::Queries' => 0.01,
                            'Test::More'           => 0 }, 
    ($] >= 5.005 ?    ## Add these new keywords supported since 5.005
      (ABSTRACT_FROM => 'Client.pm', # retrieve abstract from module
       AUTHOR     => 'Sander van Zoest <svanzoest@cpan.org>') : ()),

    'LIBS'		=> ['-L/usr/local/lib -lstdc++ -lm -lmusicbrainz'], 
    'PMLIBDIRS'         => ['Client'],
    'DEFINE'		=> '', # e.g., '-DHAVE_SOMETHING'
    'CCFLAGS'           => '',
    'INC'		=> '-I/usr/local/include -I.',
    'dist'		=> {
	COMPRESS	=> 'gzip -9f',
	SUFFIX		=> 'gz',
	CI		=> 'cvs commit'
			   },
     'realclean'	=> {
	FILES 		=> 'const-c.inc const-xs.inc MANIFEST.bak'
		           },
     macro	        => {
	CVS_PACKAGE	=> ''
			   },
);
if  (eval {require ExtUtils::Constant; 1}) {
  # If you edit these definitions to change the constants used by this module,
  # you will need to use the generated const-c.inc and const-xs.inc
  # files to replace their "fallback" counterparts before distributing your
  # changes.
  my @names = (qw(MB_CDINDEX_ID_LEN MB_ID_LEN));
  ExtUtils::Constant::WriteConstants(
                                     NAME         => 'MusicBrainz::Client',
                                     NAMES        => \@names,
                                     DEFAULT_TYPE => 'IV',
                                     C_FILE       => 'const-c.inc',
                                     XS_FILE      => 'const-xs.inc',
                                  );

}
else {
  use File::Copy;
  use File::Spec;
  foreach my $file ('const-c.inc', 'const-xs.inc') {
    my $fallback = File::Spec->catfile('fallback', $file);
    copy ($fallback, $file) or die "Can't copy $fallback to $file: $!";
  }
}

