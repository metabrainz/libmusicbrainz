/*____________________________________________________________________________

  MusicBrainz -- The Internet music metadatabase

  Portions Copyright (C) 2000 Relatable

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
____________________________________________________________________________*/

/***************************************************************************
sigclient.cpp  -  description
-------------------
copyright            : (C) 2000 by Relatable 
written by           : Isaac Richards
email                : ijr@relatable.com
***************************************************************************/

#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include "sigclient.h"
#include "comhttpsocket.h"

#include "sigxdr.h"

namespace SigClientVars
{
    static const char cGetGUID = 'L';
    static const char cDisconnect = 'E';

    static const int nGUIDSize = 16;
    static const int nTimeout = 15;
    static const int nVersion = 2;
    static const int nHeaderSize = sizeof(char) + sizeof(int);
}

using namespace std;

SigClient::SigClient()
{
    m_pSocket = new MBCOMHTTPSocket;
    m_nNumFailures = 0;
}

SigClient::~SigClient()
{
    if (m_pSocket->IsConnected()) 
        this->Disconnect();
    if (m_pSocket != NULL) 
        delete m_pSocket;
}

int SigClient::GetSignature(vector<AudioSig *> *sigs, string &strGUID, 
                            string strCollectionID)
{
    int nConRes = this->Connect(m_strIP, m_nPort);
    if (nConRes != 0) 
        return -1;

    SigXDR converter;

    int nOffSet = sizeof(char) + sizeof(int);
    int nGUIDLen = strCollectionID.size() * sizeof(char) + sizeof(char);
    int iSigEncodeSize = 2 * sizeof(int) + 69 * sizeof(int32) * sigs->size() +
                         nGUIDLen;
    int nTotalSize = nOffSet + iSigEncodeSize;

    char* pBuffer = new char[nTotalSize + 1];
    memset(pBuffer, 0, nTotalSize);
    memcpy(&pBuffer[0], &SigClientVars::cGetGUID, sizeof(char));
    memcpy(&pBuffer[1], &iSigEncodeSize, sizeof(int));

    memcpy(&pBuffer[nOffSet], &SigClientVars::nVersion, sizeof(int));
    nOffSet += sizeof(int);

    int tempi = sigs->size();
    memcpy(&pBuffer[nOffSet], &tempi, sizeof(int));
    nOffSet += sizeof(int);

    iSigEncodeSize = 69 * sizeof(int32);

    vector<AudioSig *>::iterator sig = sigs->begin();
    for (; sig != sigs->end(); sig++)
    {
        char *sigencode = converter.FromSig(*sig);
        memcpy(&pBuffer[nOffSet], sigencode, iSigEncodeSize);
        nOffSet += iSigEncodeSize;

        delete [] sigencode;
    }

    memcpy(&pBuffer[nOffSet], strCollectionID.c_str(), nGUIDLen - sizeof(char));
    nOffSet += (nGUIDLen - sizeof(char));
    pBuffer[nOffSet] = '\0';

    int nBytes = 0;
    int ret = m_pSocket->Write(pBuffer, nTotalSize, &nBytes);

    memset(pBuffer, 0, nTotalSize);
    int iGUIDSize = 16 * sizeof(int32);

    ret = m_pSocket->NBRead(pBuffer, iGUIDSize, &nBytes, 
                            SigClientVars::nTimeout);

    
    if ((ret != -1) && (nBytes == iGUIDSize)) {
        ret = 0;
        strGUID = converter.ToStrGUID(pBuffer, nBytes);
    }
    else {
	ret = -1;
        strGUID = "";
    }
    this->Disconnect();

    delete [] pBuffer;

    return ret;
}

int SigClient::Connect(string& strIP, int nPort)
{
    if (m_nNumFailures > 5) 
        return -1;  // server probably down.

    if (m_proxyAddr.empty())
    {
       m_pSocket->SetProxy(NULL);
    }
    else {
        char *proxyurl = new char[m_proxyAddr.size() + 128];
        sprintf(proxyurl, "%s:%d", m_proxyAddr.c_str(), m_proxyPort);
        m_pSocket->SetProxy(proxyurl);

        delete [] proxyurl;
    }
        
    char *url = new char[strIP.size() + 128]; // ample space..
    sprintf(url, "http://%s/cgi-bin/gateway/gateway?%d", strIP.c_str(), nPort);
    //sprintf(url, "http://209.249.187.200/cgi-bin/gateway?%d", nPort);
    int nErr = m_pSocket->Connect(url);
    //int nErr = m_pSocket->Connect(strIP.c_str(), nPort, SOCK_STREAM);

    delete [] url;

    if (nErr == -1)
    {
        m_nNumFailures++;
        return -1;
    }
    m_nNumFailures = 0;
    return 0;
}

int SigClient::Disconnect()
{
    if (m_pSocket->IsConnected())
    {
        char cBuffer[sizeof(char) + sizeof(int)];
        memset(cBuffer, 0, sizeof(char) + sizeof(int));
        cBuffer[0] = SigClientVars::cDisconnect;

        int nBytes = 0;
        m_pSocket->Write(cBuffer, sizeof(char) + sizeof(int), 
                         &nBytes);
        m_pSocket->Disconnect();	
    }
	
    return 0;
}
