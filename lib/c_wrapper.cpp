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
#include "musicbrainz.h"
#include "trm.h"
#include "mb_c.h"

extern "C"
{

#include "bitprint.h"

musicbrainz_t mb_New(void)
{
    return (musicbrainz_t)new MusicBrainz();
}

void mb_Delete(musicbrainz_t o)
{
    delete (MusicBrainz *)o; 
}

int mb_SetServer(musicbrainz_t o, char *serverAddr, short serverPort)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    if (o == NULL)
       return 0;

    return (int)obj->SetServer(string(serverAddr), serverPort);
}

int mb_SetProxy(musicbrainz_t o,char *proxyAddr, short proxyPort)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    if (o == NULL)
       return 0;

    string addr = "";
    if (proxyAddr) 
        addr = proxyAddr;
    return (int)obj->SetProxy(addr, proxyPort);
}

int mb_SetDevice(musicbrainz_t o, char *device)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    if (o == NULL)
       return 0;

    return (int)obj->SetDevice(string(device));
}

void mb_UseUTF8(musicbrainz_t o, int useUTF8)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    if (o == NULL)
       return;

    obj->UseUTF8((bool)useUTF8);
}

#ifdef WIN32
void mb_WSAInit(musicbrainz_t o)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    if (o == NULL)
       return;

    obj->WSAInit();
}
    
void mb_WSAStop(musicbrainz_t o)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    if (o == NULL)
       return;

    obj->WSAStop();
}
#endif

int mb_GetWebSubmitURL(musicbrainz_t o, char *url, int urlLen)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    string   urlString;
    int      ret;

    if (o == NULL)
       return 0;

    ret = (int)obj->GetWebSubmitURL(urlString);
    if (ret)
    {
       strncpy(url, urlString.c_str(), urlLen - 1);
       url[urlLen - 1] = 0;
    }
    return ret;
}

int mb_Query(musicbrainz_t o, char *RDFObject)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    if (o == NULL)
       return 0;

    return (int)obj->Query(string(RDFObject));
}

int mb_QueryWithArgs(musicbrainz_t o, char *RDFObject, char **args)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    vector<string>           *argList;
    string                    temp;
    int                       ret;

    if (o == NULL)
       return 0;

    argList = new vector<string>;
    for(; *args; args++)
    {
        temp = string(*args);
        argList->push_back(temp);
    }
        
    ret = obj->Query(string(RDFObject), argList);

    delete argList;

    return (int)ret;
}

void mb_GetQueryError(musicbrainz_t o, char *error, int maxErrorLen)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    string                    err;

    if (o == NULL)
       return;

    obj->GetQueryError(err);

    strncpy(error, err.c_str(), maxErrorLen);
    error[maxErrorLen - 1] = 0;
}

int mb_GetResultData(musicbrainz_t o, char *resultName, 
                      char *data, int maxDataLen)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    string   value;

    if (o == NULL)
       return 0;

    value = obj->Data(string(resultName));
    if (value.length() == 0)
       return 0;

    strncpy(data, value.c_str(), maxDataLen);
    data[maxDataLen - 1] = 0;

    return 1;
}

int mb_GetResultInt(musicbrainz_t o, char *resultName)
{
    MusicBrainz *obj = (MusicBrainz *)o;

    if (o == NULL)
       return 0;

    return obj->DataInt(string(resultName));
}

int mb_Select(musicbrainz_t o, char *selectQuery)
{
    MusicBrainz *obj = (MusicBrainz *)o;

    if (o == NULL)
       return 0;

    return obj->Select(string(selectQuery));
}

int mb_SelectWithArgs(musicbrainz_t o, char *RDFObject, int **args)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    list<int>                *argList;
    int                       temp;
    bool                      ret;

    if (o == NULL)
       return 0;

    argList = new list<int>;
    for(; *args; args++)
    {
        temp = **args;
        argList->push_back(temp);
    }
        
    ret = obj->Select(string(RDFObject), argList);

    delete argList;

    return (int)ret;
}

int mb_DoesResultExist(musicbrainz_t o, char *resultName)
{
    MusicBrainz *obj = (MusicBrainz *)o;

    if (o == NULL)
       return 0;

    return obj->DoesResultExist(string(resultName));
}

int mb_GetResultRDF(musicbrainz_t o,char *RDF, int maxXMLLen)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    string   RDFString;

    if (o == NULL)
       return 0;

    if (!obj->GetResultRDF(RDFString))
       return 0;

    strncpy(RDF, RDFString.c_str(), maxXMLLen);
    RDF[maxXMLLen - 1] = 0;

    return 1;
}

int mb_GetResultRDFLen(musicbrainz_t o)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    string   RDFString;

    if (o == NULL)
       return 0;

    if (!obj->GetResultRDF(RDFString))
       return 0;

    return RDFString.length();
}

int mb_SetResultRDF(musicbrainz_t o,char *RDF)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    string   RDFString(RDF);

    if (o == NULL)
       return 0;

    return obj->SetResultRDF(RDFString);
}

int mb_GetNumItems(musicbrainz_t o)
{
    MusicBrainz *obj = (MusicBrainz *)o;

    if (o == NULL)
       return 0;

    return obj->GetNumItems();
}

int mb_CalculateBitprint(musicbrainz_t o, char *fileName, BitprintInfo *info)
{
    MusicBrainz *obj = (MusicBrainz *)o;

    if (o == NULL)
       return 0;

    return obj->CalculateBitprint(string(fileName), info);
}

trm_t trm_New(void)
{
    return (trm_t)new TRM();
}

void trm_Delete(trm_t o)
{
    delete (TRM *)o;
}

int trm_SetProxy(trm_t o,char *proxyAddr, short proxyPort)
{
    TRM *obj = (TRM *)o;
    if (o == NULL)
       return 0;

    string addr = "";
    if (proxyAddr)
        addr = proxyAddr;
    return (int)obj->SetProxy(addr, proxyPort);
}

void trm_SetPCMDataInfo(trm_t o, int samplesPerSecond, int numChannels,
                        int bitsPerSample)
{
    TRM *obj = (TRM *)o;
     
    if (o == NULL)
       return;

    obj->SetPCMDataInfo(samplesPerSecond, numChannels, bitsPerSample);
}

int trm_GenerateSignature(trm_t o, char *data, int size, 
                          char signature[17], char *collectionID)
{
   string strGUID;
   string collID;

   if (o == NULL)
      return 0;

   if (!collectionID)
       collID = "EMPTY_COLLECTION";
   else
        collID = string(collectionID, 16);

   TRM *obj = (TRM *)o;
   
   bool retvalue = obj->GenerateSignature(data, size, strGUID, collID);

   if (retvalue) {
       memset(signature, '\0', 17);
       strncpy(signature, strGUID.c_str(), 16);

       return 1; 
   }
   return 0;
} 

void trm_GenerateSignatureNow(trm_t o, char signature[17], char *collectionID)
{
   string strGUID;
   string collID;

   if (o == NULL)
      return;

   if (!collectionID)
       collID = "EMPTY_COLLECTION";
   else
       collID = string(collectionID, 16);

   TRM *obj = (TRM *)o;

   obj->GenerateSignatureNow(strGUID, collID);

   memset(signature, '\0', 17);
   strncpy(signature, strGUID.c_str(), 16);
}

void trm_ConvertSigToASCII(trm_t o, char sig[17], char ascii_sig[37])
{
   TRM *obj = (TRM *)o;

   if (o == NULL)
      return;

   obj->ConvertSigToASCII(sig, ascii_sig);
}

}
