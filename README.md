============================
 MusicBrainz Client Library
============================

Documentation
-------------

To get started quickly have a look at the examples directory which
contains various sample programs. API documentation can be generated
using [Doxygen] (http://www.stack.nl/~dimitri/doxygen/). The online version of
the API documentation can be found at:

    http://metabrainz.github.com/libmusicbrainz/

Compiling and Linking
---------------------

This package provides a pkg-config script that returns the necessary compiler
and linker flags, as well as the version number.  To build a small sample
program one would use:

    g++ -o test_app test_app.cpp `pkg-config libmusicbrainz5 --cflags --libs`

If you don't want/can't use pkg-config and you are using the C API, make sure
you link in the C++ standard library:

    gcc -o test_app test_app.c -lmusicbrainz5 -lm -lstdc++

	
Generating the libmusicbrainz5 Visual Studio solution using CMake GUI
---------------------------------------------------------------------
1. Download [Neon] (http://www.webdav.org/neon/) and extract it.
2. In Visual Studio command prompt (not regular cmd.exe), navigate to the Neon extract folder and execute: 
	nmake /f neon.mak
3. Point CMake at the libmusicbrainz source. Specify a build location and click Configure. Specify the appropriate generator.
4. CMake should complain that it cannot find Neon. Set NEON_INCLUDE_DIR to {neon_extract}\src and NEON_LIBRARIES to {neon_extract}\libneon.lib
5. Click Configure again and then Generate. This will have generated a VS solution for you which should build without issue.

	
Contact
-------

If you have any questions about this library, feel free to ask on the
MusicBrainz development mailing list:

    http://lists.musicbrainz.org/mailman/listinfo/musicbrainz-devel

Please submit bug reports to the MusicBrainz bug tracking system:

    http://tickets.musicbrainz.org/browse/LMB

You can find out more about the MusicBrainz project by visiting its
site:

    http://musicbrainz.org/
