/*__________________________________________________________________________

        FreeAmp - The Free MP3 Player

        Portions Copyright (C) 2000 Relatable

        This program is free software; you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation; either version 2 of the License, or
        (at your option) any later version.

        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with this program; if not, Write to the Free Software
        Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
        
        $Id$
____________________________________________________________________________*/

#include "wincomsocket.h"

#if !defined(WIN32) && !defined(__BEOS__)
#define closesocket(s) close(s)
#endif

COMSocket::COMSocket(int nSocket, int nSockType)
{
    m_nSocket = nSocket;
    if (m_nSocket != INVALID_SOCKET) 
        m_bConnected = true;
    m_nSockType = nSockType;
}

COMSocket::~COMSocket()
{
    if (IsConnected()) Disconnect();
}

/** Connects a socket to pIP, on nPort, of type nType. */
int COMSocket::Connect(const char* pIP, int nPort, int nType, bool bBroadcast)
{
    if (IsConnected()) 
        Disconnect();

    sockaddr_in addr;
    //hostent* pServer;
    unsigned long uAddr = inet_addr(pIP);
    int nErr = 0;
    m_nSockType = nType;
    m_nSocket = socket(AF_INET, nType, 0);
    if (m_nSocket == INVALID_SOCKET) 
        return INVALID_SOCKET;
    /*
    pServer = gethostbyname(pIP);
    if (pServer == NULL)
    {
        closesocket(m_nSocket);
        m_nSocket = INVALID_SOCKET;
        return INVALID_SOCKET;
    }
    */
    memset((char*)&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = uAddr;
    //memcpy((char *)&addr.sin_addr.s_addr, (char*)(pServer->h_addr), pServer->h_length);   /* set address */
    //bcopy((char*)(pServer->h_addr), (char*)&(addr.sin_addr.s_addr), pServer->h_length);
    addr.sin_port = htons(nPort);

    nErr = connect(m_nSocket, (sockaddr*)&addr, sizeof(sockaddr_in));
    if (nErr == SOCKET_ERROR)
    {
        closesocket(m_nSocket);
        m_nSocket = INVALID_SOCKET;
        return INVALID_SOCKET;
    }

    m_bConnected = true;
    return 0;
}

/** Disconnects the current socket */
int COMSocket::Disconnect()
{
    int nErr = 0;
    if (!IsConnected()) 
        return SOCKET_ERROR;

    if (m_nSockType == SOCK_STREAM)
    {
        nErr = shutdown(m_nSocket, 2);
    }

    nErr = closesocket(m_nSocket);
    m_nSocket = INVALID_SOCKET;
    m_bConnected = false;
    return (nErr != SOCKET_ERROR) - 1;
}

/** Checks if there is a current open connection */
bool COMSocket::IsConnected()
{
    return m_bConnected;
}

/** Reads from a socket, into pbuffer, up to a max of nLen byte, and writes 
  * how many were actually written to nBytesWritten. */
int COMSocket::Read(char* pBuffer, int nLen, int* nBytesWritten)
{
    if (!IsConnected()) 
        return SOCKET_ERROR;  // no connection
    int nErr = 0;

    nErr = recv(m_nSocket, pBuffer, nLen, 0);
    //nErr = recv(m_nSocket, (void*)pBuffer, nLen, 0);
    if ((nErr != SOCKET_ERROR) && (nBytesWritten != NULL))
    {
        *nBytesWritten = nErr;
    }
    return (nErr != SOCKET_ERROR) - 1;
}

/** Reads in a non blocking fashion (ie, selects and polls) for nTimeout seconds */
int COMSocket::NBRead(char* pBuffer, int nLen, int* nBytesWritten, int nTimeout)
{
    timeval tval;
    tval.tv_sec = nTimeout;
    tval.tv_usec = 0;
    fd_set rset;
    int nErr = 0;

    FD_ZERO(&rset);
    FD_SET(m_nSocket, &rset);
    int nResSelect = select(m_nSocket + 1, &rset, NULL, NULL, &tval);
    if ((nResSelect != 0) && (nResSelect != SOCKET_ERROR) && 
        (FD_ISSET(m_nSocket, &rset)))
    {
        if ((nErr = Read(pBuffer, nLen, nBytesWritten)) == 0)
        {
            //cout << "ERROR: Server terminated prematurely" << endl;
            return 0;
        }
    }
    else
    {
        return -1;  // FD_ISSET failed.
    }
    return 0;
}

/** Writes to a socket, from buffer pBuffer, up to nLen bytes, and returns the number of written bytes in pnBytesWritten. */
int COMSocket::Write(const char* pBuffer, int nLen, int* pnBytesWritten)
{
    if (!IsConnected()) 
        return SOCKET_ERROR; // no connection
    int nErr = 0;

    nErr = send(m_nSocket, pBuffer, nLen, 0);
    //nErr = send(m_nSocket, (void*)pBuffer, nLen, 0);
    if ((nErr != SOCKET_ERROR) && (pnBytesWritten != NULL))
    {
        *pnBytesWritten = nErr;
    }
    return (nErr != SOCKET_ERROR) - 1;
}
