/* --------------------------------------------------------------------------

   MusicBrainz -- The Internet music metadatabase

   Copyright (C) 2004 Robert Kaye
   
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
#include <string.h>
#include "musicbrainz/mb_c.h"

int main(int argc, char *argv[])
{
    musicbrainz_t o;
    char  id[34] = "";
    int i;
    int rc=0;
    cdtoc_t cdinfo;

    for (i=0; i<100; i++)
       cdinfo.FrameOffset[i] = 0;

    cdinfo.FirstTrack = 1;
    cdinfo.LastTrack  = 13;
    cdinfo.FrameOffset[ 0] = 179837;
    cdinfo.FrameOffset[ 1] =    150;
    cdinfo.FrameOffset[ 2] =  15702;
    cdinfo.FrameOffset[ 3] =  30155;
    cdinfo.FrameOffset[ 4] =  46240;
    cdinfo.FrameOffset[ 5] =  64115;
    cdinfo.FrameOffset[ 6] =  77532;
    cdinfo.FrameOffset[ 7] =  88120;
    cdinfo.FrameOffset[ 8] =  97945;
    cdinfo.FrameOffset[ 9] = 110045;
    cdinfo.FrameOffset[10] = 125050;
    cdinfo.FrameOffset[11] = 143712;
    cdinfo.FrameOffset[12] = 160137;
    cdinfo.FrameOffset[13] = 165605;
    
    // Create the musicbrainz object, which will be needed for subsequent calls
    o = mb_New();

    // Tell the client library to return data in ISO8859-1 and not UTF-8
    mb_UseUTF8(o, 0);

    mb_GenerateId(o, &cdinfo, id);

    printf("NOTE: This program only tests the internal disc id generation tools.\n");
    printf("      it serves no other purpose.\n\n");
    printf("id: %s\n", id);

    if (0 != strncmp(id, "oGCHTFR0Iw8QY_LkbJvngT.b5sk-", 28) )
      {
	printf("Above id is in incorrect!\n");
	rc=1;
      } else 
      {
	printf("Above id looks good!\n");
      }
	
    // and clean up the musicbrainz object
    mb_Delete(o);

    return rc;
}
