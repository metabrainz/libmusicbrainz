/* --------------------------------------------------------------------------

   MusicBrainz -- The Internet music metadatabase

   Copyright (C) 2000 Robert Kaye
   Copyright (C) 1998 Jukka Poikolainen
   
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
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "mmsystem.h"

#include "mb_win32.h"           // can't assume symlink mb.h to cdi_win32.h
#include "diskid.h"
#include "../config_win32.h"    // a copy of a Cygwin generated config.h

MUSICBRAINZ_DEVICE DEFAULT_DEVICE = "0";

int
ReadTOCHeader(int fd, int &first, int &last)
{
   return 0;
}

int
ReadTOCEntry(int fd, int track, int &lba)
{
   return 0;
}

bool DiskId::ReadTOC(MUSICBRAINZ_DEVICE cd_desc, MUSICBRAINZ_CDINFO & disc)
{
   int       readtracks, pos, ret, numTracks;
   char      mciCommand[128];
   char      mciReturn[128];
   char      buf[256];

   if (cd_desc == NULL)
      cd_desc = "cdaudio";

   memset(&disc, 0, sizeof(disc));
   sprintf(mciCommand, "sysinfo %s quantity wait", cd_desc);
   mciSendString(mciCommand, mciReturn, sizeof(mciReturn), NULL);
   if (atoi(mciReturn) <= 0)
      return false;

   sprintf(mciCommand, "open %s shareable alias %s wait", cd_desc);
   ret = mciSendString(mciCommand, mciReturn, sizeof(mciReturn), NULL);
   if (ret != 0)
      return false;

   sprintf(mciCommand, "status %s number of tracks wait", cd_desc);
   ret = mciSendString(mciCommand, mciReturn, sizeof(mciReturn), NULL);
   mciGetErrorString(ret, buf, sizeof(buf));

   numTracks = atoi(mciReturn);
   disc.FirstTrack = 1;
   disc.LastTrack = numTracks;

   for (readtracks = 0; readtracks < disc.LastTrack; readtracks++)
   {
      sprintf(mciCommand, "set %s time format msf wait", cd_desc);
      mciSendString(mciCommand, mciReturn, sizeof(mciReturn), NULL);
      sprintf(mciCommand, "status %s position track %d wait",
              cd_desc, readtracks + 1);
      mciSendString(mciCommand, mciReturn, sizeof(mciReturn), NULL);

      pos = cd_msf_to_frames(atoi(mciReturn) * 4500, 
                             atoi(mciReturn + 3) * 75, 
                             atoi(mciReturn + 6););
      disc.FrameOffset[readtracks] = pos;
   }

   sprintf(mciCommand, "close %s wait", cd_desc);
   mciSendString(mciCommand, mciReturn, sizeof(mciReturn), NULL);

   return true;
}
