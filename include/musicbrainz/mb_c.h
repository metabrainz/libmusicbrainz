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
#ifndef _MB_C_H_
#define _MB_C_H_

#include "errors.h"
#include "queries.h"
#include "bitprint.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Basic C abstraction types for the interfaces */
typedef void * musicbrainz_t;
typedef void * trm_t;

/* The interface to the main MusicBrainz object */
musicbrainz_t mb_New           (void);
void      mb_Delete            (musicbrainz_t o);

int       mb_SetServer         (musicbrainz_t o, char *serverAddr, 
                                short serverPort);
int       mb_SetProxy          (musicbrainz_t o, char *serverAddr, 
                                short serverPort);
#ifdef WIN32
void      mb_WSAInit           (musicbrainz_t o);
void      mb_WSAStop           (musicbrainz_t o);
#endif 

int       mb_SetDevice         (musicbrainz_t o, char *device);
void      mb_UseUTF8           (musicbrainz_t o, int useUTF8);
void      mb_SetDepth          (musicbrainz_t o, int depth);

int       mb_Query             (musicbrainz_t o, char *rdfObject);
int       mb_QueryWithArgs     (musicbrainz_t o, char *rdfObject, char **args);
int       mb_GetWebSubmitURL   (musicbrainz_t o, char *url, int urlLen);
void      mb_GetQueryError     (musicbrainz_t o, char *error, int maxErrorLen);

int       mb_Select            (musicbrainz_t o, char *selectQuery);
int       mb_Select1           (musicbrainz_t o, char *selectQuery, int ord);
int       mb_SelectWithArgs    (musicbrainz_t o, char *selectQuery, int **args);

int       mb_DoesResultExist   (musicbrainz_t o, char *resultName);
int       mb_DoesResultExist1  (musicbrainz_t o, char *resultName, int ordinal);
int       mb_GetResultData     (musicbrainz_t o, char *resultName, 
                                char *data, int maxDataLen);
int       mb_GetResultData1    (musicbrainz_t o, char *resultName, 
                                char *data, int maxDataLen, int ordinal);
int       mb_GetResultInt1     (musicbrainz_t o, char *resultName, int ordinal);

int       mb_GetResultRDF      (musicbrainz_t o, char *RDF, int maxRDFLen);
int       mb_GetResultRDFLen   (musicbrainz_t o);
int       mb_SetResultRDF      (musicbrainz_t o, char *RDF);
void      mb_GetIDFromURL      (musicbrainz_t o, char *url, char *id, 
                                int maxIdLen);
int       mb_CalculateBitprint (musicbrainz_t o, char *fileName, 
                                BitprintInfo *info);

/* The interface to the Relatable TRM signature generator */

/**
 * The contructor for the TRM class.
 * Call trm_Delete() when done with the object.
 * @see trm_Delete()
 * @return the trm_t object used to refer to the class instance.
 */
trm_t trm_New                 (void);

/**
 * The destructor for the TRM class.
 * @see trm_New()
 * @param o the trm_t object to delete
 */
void  trm_Delete              (trm_t o);

/**
 * Called to set a proxy server to use for Internet access.
 * @param o the trm_t object returned by trm_New()
 * @param proxyAddr the name of the proxy server to use. eg. proxy.domain.com
 * @param proxyPort the port number that the proxy server uses. eg. 8080
 * @return 1 on success, 0 on failure
 */
int   trm_SetProxy            (trm_t o, char *proxyAddr, short proxyPort);

/**
 * Called to set the type of audio being sent to be signatured.
 * This MUST be called before attempting to generate a signature.
 * @see trm_GenerateSignature()
 * @see trm_GenerateSignatureNow()
 * @param o the trm_t object returned by trm_New()
 * @param samplesPerSecond the sampling rate of the audio. eg. 44100
 * @param numChannels the number of audio channels in the audio. 
 * 1 or 2 for mono or stereo respectively.
 * @param bitsPerSample the number of bits per audio sample.  generally 8 or 16.
 */
void  trm_SetPCMDataInfo      (trm_t o, int samplesPerSecond, 
                               int numChannels, int bitsPerSample);
/**
 * The main functionality of the TRM class.  Audio is passed to this function
 * and stored for analysis. trm_SetPCMDataInfo() needs to be called before
 * calling this function.
 * @see trm_SetPCMDataInfo()
 * @see trm_GenerateSignatureNow()
 * @param o the trm_t object returned by trm_New()
 * @param data a pointer to the block of audio data being sent to the function. 
 * It needs to be raw PCM data in the format specified by the call to 
 * trm_SetPCMDataInfo()
 * @param size the size in bytes of the data block.
 * @param signature a 17 character array to store the signature, if generated,
 * in.
 * @param collectionID an optional 16-byte string to associate the signature
 * with a particular collection in the Relatable Engine.  Generally, pass in 
 * NULL.
 * @return returns 1 if enough data has been sent to generate a signature, 
 * or 0 if more data is still needed.  After it returns a '1', the array
 * 'signature' should contain the raw signature.
 */
int   trm_GenerateSignature   (trm_t o, char *data, int size,
                               char signature[17], char *collectionID);
/**
 * Used when there is no more audio data available and trm_GenerateSignature() 
 * has not yet returned a '1'.  This function forces the generation of a 
 * signature from the data already sent via trm_GenerateSignature().
 * @see trm_SetPCMDataInfo()
 * @see trm_GenerateSignature()
 * @param o the trm_t object returned by trm_New()
 * @param signature a 17 character array to store the signature in.
 * @param collectionID an optional 16-byte string to associate the signature
 * with a particular collection in the Relatable Engine.  Generally, pass in 
 * NULL.
 */
void  trm_GenerateSignatureNow(trm_t o, char signature[17],
                               char *collectionID);
/**
 * This translates the 16 character raw signature into a 36 character 
 * human-readable string containing only letters and numbers.  Used after 
 * trm_GenerateSignature() or trm_GenerateSignatureNow() has generated a 
 * signature.
 * @param o the trm_t object returned by trm_New()
 * @param sig the raw 16 character signature returned by one of the Generate
 * functions.
 * @param ascii_sig the more human readable form of the signature.
 */
void  trm_ConvertSigToASCII   (trm_t o, char sig[17], 
                               char ascii_sig[37]);

#ifdef __cplusplus
}
#endif

#endif
