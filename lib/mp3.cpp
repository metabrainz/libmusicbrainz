/* (PD) 2001 The Bitzi Corporation
 * Please see file COPYING or http://bitzi.com/publicdomain 
 * for more info.
 *
 * $Id$
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"

#define DB printf("%s:%d\n", __FILE__, __LINE__);

#define NUMBITRATES 15
static int mpeg1Bitrates[3][16] = 
{
   // Layer I
   { 0, 32, 64, 96, 128,160, 192, 224, 256, 288, 320, 352, 384, 416, 448, -1 },
   // Layer II
   { 0, 32, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384, -1 },
   // Layer III
   { 0, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, -1 }
};

static int mpeg2Bitrates[3][16] = 
{
    // Layer I
    { 0, 32, 48, 56, 64, 80, 69, 112, 128, 144, 160, 176, 192, 224, 256, -1 },
    // Layer II
    { 0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160, -1 },
    // Layer III (same as Layer II)
    { 0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160, -1 }
};

static int mpeg1SampleRates[] = { 44100, 48000, 32000 };
static int mpeg2SampleRates[] = { 22050, 24000, 16000 };
static int mpegLayer[] = { 0, 3, 2, 1 };

#define ID3_TAG_LEN 128

int MP3Info::bitrate(const unsigned char *header)
{
   int id, br, ly;

   id = (header[1] & 0x8) >> 3;
   br = (header[2] & 0xF0) >> 4;
   ly = (header[1] & 0x07) >> 1;

   if (br >= NUMBITRATES)
     return 0;

   ly = 3 - ly;
   if (ly > 3 || ly < 1)
     return 0;

   return id ? mpeg1Bitrates[ly][br] : mpeg2Bitrates[ly][br];
}

int MP3Info::samplerate(const unsigned char *header)
{
   int id, sr;

   id = (header[1] & 0x8) >> 3;
   sr = (header[2] >> 2) & 0x3;

   return id ? mpeg1SampleRates[sr] : mpeg2SampleRates[sr];
}

int MP3Info::stereo(const unsigned char *header)
{
   return ((header[3] & 0xc0) >> 6) != 3;
}

int MP3Info::mpeg_ver(const unsigned char *header)
{
    int version = (header[1] >> 3) & 0x03;
    if (version == 3)
        return 1;
    if (version == 0 || version == 2)
        return 2;
    return 0;
}

int MP3Info::mpeg_layer(const unsigned char *header)
{
   return mpegLayer[((header[1] & 0x7) >> 1)]; 
}

int MP3Info::padding(const unsigned char *header)
{
   return (header[2] >> 1) & 0x1;
}

int MP3Info::framesync(const unsigned char *header) 
{
    if  (header[0] != 0xff || header[1] >> 5 != 0x07)
        return 0;

    return 1;
}

bool MP3Info::isFrame(char *ptr, int &layer, int &sampleRate, 
                      int &mpegVer, int &bitRate, int &frameSize)
{
    /* Find the frame marker */
    if (!framesync(ptr))
        return false;

    /* Extract sample rate and layer from this first frame */
    sampleRate = samplerate(ptr);
    layer = mpeg_layer(ptr);
    mpegVer = mpeg_ver(ptr);
    bitRate = bitrate(ptr);

    /* Check for invalid sample rates */
    if (sampleRate == 0)
        return false;

    /* Check for invalid bitrates rates */
    if (bitRate == 0) 
        return false;

    /* Check for invalid layer */
    if (layer == 0) 
        return false;

    /* Calculate the size of the frame from the header components */
    if (mpegVer == 1)
        frameSize = (144000 * bitRate) / sampleRate;
    else if (mpeg_ver(ptr) == 2)
        frameSize = (72000 * bitRate) / sampleRate;
    else 
        return false;

    if (frameSize <= 1 || frameSize > 2048)
        return false;

    frameSize += padding(ptr);

    return true;
}       

int MP3Info::findStart(FILE *fp)
{
   char           ptr[4];
   unsigned       baseOffset;
   int            firstSampleRate = -1, firstLayer = -1, nextSampleRate = -1, nextLayer = -1;
   int            firstMpegVer = -1, nextMpegVer = -1;
   int            firstBitrate = -1, nextBitrate = -1;
   unsigned int   firstFrameSize = -1, nextFrameSize = -1;
   int            goodFrames;

   goodFrames = 0;
   baseOffset = 0;

   /* Loop through the buffer trying to find frames */
   for(;;)
   {       
       // If goodframes is negative than its the first time
       // through the loop or we're resetting because of an error 
       // from an earlier pass
       if (goodFrames < 0)
       {
           ptr = ++baseOffset;
           goodFrames = 0;
       }

       ret = fseek(fp, baseOffset, SEEK_SET);
       if (ret < 0)
           return -1;

       ret = fread(ptr, 4, sizeof(char), fp);
       if (ret != 4)
           return -1;

       // Check to see if we have a valid frame
       if (!isFrame(ptr, firstLayer, firstSampleRate, firstMpegVer, 
                     firstBitrate, firstFrameSize))
       {
           goodFrames = -1;
           continue;
       }

       printf("First [%x]: br: %d sr: %d mp: %d sz: %d\n",
               baseOffset, firstBitrate, firstSampleRate, 
               firstMpegVer, firstFrameSize);

       ret = fseek(fp, baseOffset + firstFrameSize, SEEK_SET);
       if (ret < 0)
           return -1;

       ret = fread(ptr, 4, sizeof(char), fp);
       if (ret != 4)
           return -1;

       // Check to see if we can find another frame where the next frame should be
       if (!isFrame(ptr, nextLayer, nextSampleRate, nextMpegVer, 
                    nextBitrate, nextFrameSize))
       {
           goodFrames = -1;
           continue;
       }
       printf("secnd [%x] br: %d sr: %d mp: %d sz: %d (%d)\n",
                 baseOffset + firstFrameSize, nextBitrate, nextSampleRate, 
                 nextMpegVer, nextFrameSize, goodFrames);

       if (firstSampleRate == nextSampleRate && 
           firstLayer == nextLayer &&
           firstMpegVer == nextMpegVer) 
       {
           // How do you move to the next iteration??
           goodFrames++;
           ptr += firstFrameSize;

           if (goodFrames == 6)
               return baseOffset;

           continue;
       }
       goodFrames = -1;
   }
   return -1;
}

void mp3_update(mp3_info      *info,
                unsigned char *buffer, 
                unsigned       len)
{
   unsigned       size, bytesLeft;
   unsigned char *ptr, *max;
   unsigned char *temp = NULL;

   /* If this is the first time in the update function, then seek to
      find the actual start of the mp3 and skip over any ID3 tags or garbage
      that might be at the beginning of the file */
   if (info->badBytes == 0 && info->goodBytes == 0)
   {
      int offset;

      offset = find_mp3_start(info, buffer, len);
      if (offset < 0)
         return;

      /* If it took more than one block to determine the start of the mp3
         file, then use the buffer that was created by the find_mp3_start
         routine, rather than the buffer that was passed in. */
      if (info->startBuffer)
      {
         buffer = info->startBuffer;
         len = info->startBytes;
      }

      /* Skip over the crap at the beginning of the file */
      buffer += offset;
      len -= offset;
      size = 0;
   }

   /* If the a header spanned the last block and this block, then
      allocate a larger buffer and copy the last header plus the new
      block into the new buffer and work on it. This shouldn't happen
      very often. */
   if (info->spanningSize > 0)
   {
      temp = malloc(len + info->spanningSize);
      memcpy(temp, info->spanningHeader, info->spanningSize);
      memcpy(temp + info->spanningSize, buffer, len);
      len += info->spanningSize;
      buffer = temp;
   }

   /* Loop through the buffer trying to find frames */
   for(ptr = buffer + info->skipSize, max = buffer + len;
       ptr < max;)
   {
      /* printf("%02X%02X\n", ptr[0], ptr[1]); */
      if ((unsigned int)max - (unsigned int)ptr < 4)
      {
         /* If we have a header that spans a block boundary, save
            up to 3 bytes and then return */
         info->spanningSize = (unsigned int)max - (unsigned int)ptr;
         memcpy(info->spanningHeader, ptr, info->spanningSize);
         info->skipSize = 0;

         if (temp)
            free(temp);

         return;
      }
 
      /* Find the frame marker */
      if (*ptr != 0xFF || ((*(ptr + 1) & 0xF0) != 0xF0 &&
                           (*(ptr + 1) & 0xF0) != 0xE0)) 
      {
          info->badBytes ++;
          ptr++;
          continue;
      }

      /* Check for invalid sample rates */
      if (samplerate(ptr) == 0)
      { 
          info->badBytes ++;
          ptr++;
          continue;
      }

      /* Calculate the size of the frame from the header components */
      if (mpeg_ver(ptr) == 1)
          size = (144000 * bitrate(ptr)) / samplerate(ptr) + padding(ptr);
      else
          size = (72000 * bitrate(ptr)) / samplerate(ptr) + padding(ptr);
      if (size <= 1 || size > 2048)
      {
          info->badBytes ++;
          ptr++;
          continue;
      }

      /* If this is the first frame, then tuck away important info */
      if (info->frames == 0)
      {
          info->samplerate = samplerate(ptr);
          info->bitrate = bitrate(ptr);
          info->mpegVer = mpeg_ver(ptr);
          info->stereo = stereo(ptr);
      }
      else
      {
          /* The sample rate inside of a file should never change. If the
             header says it did, then assume that we found a bad header 
             and skip past it. */
          if (info->samplerate != samplerate(ptr))
          {
             info->badBytes ++;
             ptr++;
             continue;
          }

          /* If the bitrate in subsequent frames is different from the
             first frame, then we have a VBR file */
          if (info->bitrate && info->bitrate != bitrate(ptr))
          {
             info->bitrate = 0;
          }
      }

      /*
      printf("%08x: [%04d] %3d %d %5d %d %d ", 
              (unsigned int)ptr - (unsigned int)buffer,
              info->frames, bitrate(ptr), mpeg_ver(ptr),
              samplerate(ptr), size, padding(ptr)); 
      printf(" (%02X %02X %02X %02X)\n", ptr[0], ptr[1], ptr[2], ptr[3]);
      */

      /* Update the sha hash with the data from this frame */
      bytesLeft = (unsigned int)max - (unsigned int)ptr;

      /* Move the memory pointer past the frame */
      info->frames++;
      info->goodBytes += size;
      info->avgBitrate += bitrate(ptr);
      ptr += size;
   }

   /* skipSize defines the number of bytes to skip in the next block,
      so that we're not searching for the frame marker inside of
      a frame, which can lead to false hits. Grrr. 
      Vielen Dank, Karl-Heinz Brandenburg! */
   info->skipSize = (unsigned int)ptr - (unsigned int)max;
   info->spanningSize = 0;
   if (temp)
      free(temp);
}

bool MP3Info::analyze(const string &fileName)
{
    FILE     *fp;
    unsigned  start = 0;

    goodBytes = 0;
    badBytes = 0;

    fp = fopen(fileName.c_str(), "rb");
    if (fp == NULL)
       return false;

    start = findStart(fp);
    if (start < 0)
    {
        fclose(fp);
        return false;
    }


    fclose(fp);

    if (badBytes > goodBytes || goodBytes == 0)
        return false;

    if (mpegVer == 1)
        duration = (frames * 1152 / (samplerate / 100)) * 10;
    else
        duration = (frames * 576 / (samplerate / 100)) * 10;

    avgBitrate /= frames;

    return true;
}
