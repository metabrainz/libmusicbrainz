/* (PD) 2001 The Bitzi Corporation
 * Please see file COPYING or http://bitzi.com/publicdomain 
 * for more info.
 *
 * $Id$
 */
#ifndef MP3_H
#define MP3_H

class MP3Info
{
    public:

        MP3Info(void) {};
       ~MP3Info(void) {};

         bool analyze(const string &fileName);

         int  getBitrate(void) { return bitrate; };
         int  getSamplerate(void) { return samplerate; };
         int  getStereo(void) { return stereo; };
         int  getDuration(void) { return duration; };
         int  getFrames(void) { return frames; };
         int  getMpegVer(void) { return mpegVer; };
         int  getAvgBitrate(void) { return avgBitrate; };

    private:

         int   findStart(FILE *fp);

         int   framesync(const unsigned char *header);
         int   padding(const unsigned char *header);
         int   mpeg_layer(const unsigned char *header);
         int   mpeg_ver(const unsigned char *header);
         int   stereo(const unsigned char *header);
         int   samplerate(const unsigned char *header);
         int   bitrate(const unsigned char *header);

         bool  isFrame(char *ptr, int &layer, int &sampleRate, 
                       int &mpegVer, int &bitRate, int &frameSize);

         int   goodBytes, badBytes;
         int   bitrate, samplerate, stereo, duration, 
               frames, mpegVer, avgBitrate;
};

#define MP3_HEADER_SIZE 4

#endif
