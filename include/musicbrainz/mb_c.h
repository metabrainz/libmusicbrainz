/* --------------------------------------------------------------------------

   MusicBrainz -- The Intenet music metadatabase

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
#ifndef _MB_C_H_
#define _MB_C_H_

#include "errors.h"
#include "queries.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef void * musicbrainz_t;

musicbrainz_t mb_New           (void);
void      mb_Delete            (musicbrainz_t o);
int       mb_SetServer         (musicbrainz_t o, char *serverAddr, 
                                short serverPort);
int       mb_SetProxy          (musicbrainz_t o, char *serverAddr, 
                                short serverPort);
int       mb_SetDevice         (musicbrainz_t o, char *device);

int       mb_Query             (musicbrainz_t o, char *xmlObject);
int       mb_QueryWithArgs     (musicbrainz_t o, char *xmlObject, char **args);
int       mb_GetWebSubmitURL   (musicbrainz_t o, char *url, int urlLen);
void      mb_GetQueryError     (musicbrainz_t o, char *error, int maxErrorLen);
int       mb_Select            (musicbrainz_t o, char *selectQuery);
int       mb_DoesResultExist   (musicbrainz_t o, char *resultName);
int       mb_GetResultData     (musicbrainz_t o, char *resultName, 
                                char *data, int maxDataLen);
int       mb_GetResultInt      (musicbrainz_t o, char *resultName);
int       mb_GetResultRDF      (musicbrainz_t o, char *xml, int maxXMLLen);
int       mb_GetResultRDFLen   (musicbrainz_t o);
int       mb_GetNumItems       (musicbrainz_t o);

void      mb_SetPCMData        (musicbrainz_t o, int samplesPerSecond, 
		                int numChannels, int bitsPerSample);
int       mb_GenerateSignature (musicbrainz_t o, char *data, int size,
		                char **signature, char *collectionID);
void      mb_GenerateSignatureNow(musicbrainz_t o, char **signature,
		                  char *collectionID);

#ifdef __cplusplus
}
#endif

#endif
