/* --------------------------------------------------------------------------

   MusicBrainz -- The Internet music metadatabase

   Copyright (C) 2000 Robert Kaye
   Copyright (C) 1999 Marc E E van Woerkom
   
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
#include <errno.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <IOKit/storage/IOCDTypes.h>
#include <IOKit/storage/IOCDMediaBSDClient.h>

#include "mb.h"
#include "diskid.h"
#include "config.h"


MUSICBRAINZ_DEVICE DEFAULT_DEVICE = "/dev/rdisk1";

bool DiskId::ReadTOC(MUSICBRAINZ_DEVICE device, 
                     MUSICBRAINZ_CDINFO& cdinfo)
{
   int fd;
   int first;
   int last;
   int lba;
   int i;
   dk_cd_read_disc_info_t  discInfo;
   dk_cd_read_track_info_t trackInfo;
   CDTrackInfo toc[100];
   CDDiscInfo hdr;

   if (device == NULL)
   {
       device = DEFAULT_DEVICE;
   }

   fd = open(device, O_RDONLY | O_NONBLOCK);
   if (fd < 0)
   {
       char err[256];

       sprintf(err, "Cannot open '%s'", device);
       ReportError(err);

       return false;
   }

   // Initialize cdinfo to all zeroes.
   memset(&cdinfo, 0, sizeof(MUSICBRAINZ_CDINFO));
   memset(&discInfo, 0, sizeof(discInfo));

   discInfo.buffer = &hdr;
   discInfo.bufferLength = sizeof(hdr);
   if (ioctl(fd, DKIOCCDREADDISCINFO, &discInfo) < 0
           || discInfo.bufferLength != sizeof(hdr)) 
   {
      ReportError("Reading CD-ROM table of contents failed.");
      close(fd);	
      return false;
   }

   first = hdr.numberOfFirstTrack;
   last = hdr.lastTrackNumberInLastSessionLSB; 

   // Do some basic error checking.
   if (last==0)
   {
      ReportError("This disk has no tracks.");
      close(fd);	
      return false;
   }

   memset(&trackInfo, 0, sizeof(trackInfo));
   trackInfo.addressType = kCDTrackInfoAddressTypeTrackNumber;
   trackInfo.bufferLength = sizeof(*toc);
   
   for (i = 0; i <= last; i++) 
   {
       trackInfo.address = i;
       trackInfo.buffer = &toc[i];

       if (ioctl(fd, DKIOCCDREADTRACKINFO, &trackInfo) < 0) 
       {
           ReportError("Reading CD-ROM table of contents failed.");
           close(fd);	
           return false;
       }
       printf("toc[%d]: %d\n", i, toc[i].lastRecordedAddress + 151);
   }

   cdinfo.FrameOffset[0] = toc[last].lastRecordedAddress + 151;
   cdinfo.FrameOffset[1] = toc[0].lastRecordedAddress + 150;

   // Now, for every track, find out the block address where it starts.
   for (i = 1; i < last; i++)
   {
      cdinfo.FrameOffset[i + 1] = toc[i].lastRecordedAddress + 151;
   }

   cdinfo.FirstTrack = first;
   cdinfo.LastTrack = last;

   close(fd);

   return true;
}
