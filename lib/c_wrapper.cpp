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
#include "mb_c.h"

extern "C"
{

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

int mb_Query(musicbrainz_t o, char *xmlObject)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    if (o == NULL)
       return 0;

    return (int)obj->Query(string(xmlObject));
}

int mb_QueryWithArgs(musicbrainz_t o, char *xmlObject, char **args)
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
        
    ret = obj->Query(string(xmlObject), argList);

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

int mb_DoesResultExist(musicbrainz_t o, char *resultName)
{
    MusicBrainz *obj = (MusicBrainz *)o;

    if (o == NULL)
       return 0;

    return obj->DoesResultExist(string(resultName));
}

int mb_GetResultRDF(musicbrainz_t o,char *xml, int maxXMLLen)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    string   xmlString;

    if (o == NULL)
       return 0;

    if (!obj->GetResultRDF(xmlString))
       return 0;

    strncpy(xml, xmlString.c_str(), maxXMLLen);
    xml[maxXMLLen - 1] = 0;

    return 1;
}

int mb_GetResultRDFLen(musicbrainz_t o)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    string   xmlString;

    if (o == NULL)
       return 0;

    if (!obj->GetResultRDF(xmlString))
       return 0;

    return xmlString.length();
}

int mb_SetResultRDF(musicbrainz_t o,char *xml)
{
    MusicBrainz *obj = (MusicBrainz *)o;
    string   xmlString(xml);

    if (o == NULL)
       return 0;

    return obj->SetResultRDF(xmlString);
}

int mb_GetNumItems(musicbrainz_t o)
{
    MusicBrainz *obj = (MusicBrainz *)o;

    if (o == NULL)
       return 0;

    return obj->GetNumItems();
}

void mb_SetPCMDataInfo(musicbrainz_t o, int samplesPerSecond, int numChannels,
                   int bitsPerSample)
{
    MusicBrainz *obj = (MusicBrainz *)o;
     
    if (o == NULL)
       return;

    obj->SetPCMDataInfo(samplesPerSecond, numChannels, bitsPerSample);
}

int mb_GenerateSignature(musicbrainz_t o, char *data, int size, 
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

   MusicBrainz *obj = (MusicBrainz *)o;
   
   bool retvalue = obj->GenerateSignature(data, size, strGUID, collID);

   if (retvalue) {
       memset(signature, '\0', 17);
       strncpy(signature, strGUID.c_str(), 16);

       return 1; 
   }
   return 0;
} 

void mb_GenerateSignatureNow(musicbrainz_t o, 
                             char signature[17], 
                             char *collectionID)
{
   string strGUID;
   string collID;

   if (o == NULL)
      return;

   if (!collectionID)
       collID = "EMPTY_COLLECTION";
   else
       collID = string(collectionID, 16);

   MusicBrainz *obj = (MusicBrainz *)o;

   obj->GenerateSignatureNow(strGUID, collID);

   memset(signature, '\0', 17);
   strncpy(signature, strGUID.c_str(), 16);
}

void mb_ConvertSigToASCII(musicbrainz_t o, char sig[17], char ascii_sig[37])
{
   MusicBrainz *obj = (MusicBrainz *)o;

   if (o == NULL)
      return;

   obj->ConvertSigToASCII(sig, ascii_sig);
}

}
