/* --------------------------------------------------------------------------

   MusicBrainz -- The Internet music metadatabase

   Copyright (C) 2000 Robert Kaye
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "mb_c.h"
#include "bitzi/bitcollider.h"
#include "bitzi/browser.h"

int main(int argc, char *argv[])
{
    musicbrainz_t o;
    char          url[1025];
    BrowserEnum   browser = eBrowserNetscape;
    int           argIndex = 1;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
    {
        printf("Usage: cdlookup [options] [device]\n");
        printf("\nDefault drive is /dev/cdrom\n");
        printf("\nOptions:\n");
        printf(" -k       - use the Konqueror to submit\n");
        printf(" -m       - use the Mozilla to submit\n");
        printf(" -o       - use the Opera to submit\n");
        printf(" -l       - use the lynx to submit\n");
        printf("\nBy default Netscape will be used. You may also set the\n");
        printf("BROWSER environment variable to specify your browser of "
               "choice. Check http://www.tuxedo.org/~esr/BROWSER/index.html "
               "for details.\n");
        exit(0);
    }

    // Create the musicbrainz object, which will be needed for subsequent calls
    o = mb_New();

    // Set the proper server to use. Defaults to www.musicbrainz.org:80
    if (getenv("MB_SERVER"))
        mb_SetServer(o, getenv("MB_SERVER"), 80);

    // If a device was specified on the command line, then pass on 
    if (argc > 1)

    for(; argIndex < argc; argIndex++)

    {
        if (strcmp(argv[argIndex], "-m") == 0)
        {
            browser = eBrowserMozilla;
        }
        else
        if (strcmp(argv[argIndex], "-k") == 0)
        {
            browser = eBrowserKonqueror;
        }
        else
        if (strcmp(argv[argIndex], "-o") == 0)
        {
            browser = eBrowserOpera;
        }
        else
        if (strcmp(argv[argIndex], "-l") == 0)
        {
            browser = eBrowserLynx;
        }
        else
        {
            printf("Using device: %s\n", argv[argIndex]);
            mb_SetDevice(o, argv[argIndex]);
            break;
        }
    } 

    // Tell the client library to return data in ISO8859-1 and not UTF-8
    mb_UseUTF8(o, 0);

    // Now get the web submit url
    if (mb_GetWebSubmitURL(o, url, 1024))
    {
        printf("URL: %s\n", url);
        launch_browser(url, browser);
    }
    else
        printf("Could read CD-ROM parameters. Is there a CD in the drive?\n");

    // and clean up the musicbrainz object
    mb_Delete(o);

    return 0;
}
