#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mb_c.h"

#define MAX_PATH 255

int main(int argc, char *argv[])
{
    musicbrainz_t o;
    int    ret;
    char   *args[19];
    char    result[4096], temp[255];
    int     i;
    BitprintInfo  info;

    if (argc < 2)
    {
        printf("Usage: mbtest <mp3 file>\n");
        exit(0);
    }

    memset(args, 0, sizeof(args));
    memset(&info, 0, sizeof(info));
    o = mb_New();

    // Calculate the bitzi bitprint for this file.
    mb_CalculateBitprint(o, argv[1], &info);
    return 0;

    mb_UseUTF8(o, 0);
    mb_SetServer(o, "musicbrainz.eorbit.net", 80);

    args[0] = strdup("");
    args[1] = strdup("");
    args[2] = strdup("");
    args[3] = strdup("");
    args[4] = strdup("GUID");
    args[5] = strdup(argv[1]);
    args[6] = strdup("1999");
    args[7] = strdup("Fusssing");
    args[8] = strdup("This is fuss!");

    // These are the bitzi bitpint metadata items
    args[9] = strdup(info.bitprint);
    args[10] = strdup(info.first20);
    sprintf(temp, "%d", info.length);
    args[11] = strdup(temp);

    if (info.audioSha1[0])
    {
        args[12] = strdup(info.audioSha1);
        sprintf(temp, "%d", info.duration);
        args[13] = strdup(temp);
        sprintf(temp, "%d", info.samplerate);
        args[14] = strdup(temp);
        sprintf(temp, "%d", info.bitrate);
        args[15] = strdup(temp);
        sprintf(temp, "%d", info.stereo);
        args[16] = strdup(temp);
        sprintf(temp, "%d", info.vbr);
        args[17] = strdup(temp);
        args[18] = NULL;
    }
    else
    {
        args[12] = NULL;
    }

    ret = mb_QueryWithArgs(o, MB_ExchangeMetadata, args);
    for(i = 0; i < 11; i++)
    {
       if (args[i])
          free(args[i]);
    }

    if (!ret)
    {
        char err[1024];

        mb_GetQueryError(o, err, 1024);
        printf("Query returned: %s\n", err);
        return -1;
    }

    // This query should always return one item
    if (mb_GetNumItems(o) == 0)
    {
        printf("Query returned 0 items.\n");
        return -1;
    }

    if (mb_GetResultRDF(o, result, 4096))
        printf("%s\n", result);
    else
        printf("Could not get result.\n");

    mb_Delete(o);

    return 0;
}
