/*________________________________________________________________________        

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

/// TODO: implement multicast connections (to allow single packet, multiple receiver connections)

#ifndef WINCOMSOCKET_H
#define WINCOMSOCKET_H
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netdb.h>
//#include "mutex.h"
#include <stdio.h>
#include <string>
#include "apsutility.h"

//class COMServerSocket;

/**Wraps the OS specifics of a client socket.
  *@author Sean Ward
  */
class COMSocket {
public:
    COMSocket(int nSocket = INVALID_SOCKET, int nSockType = SOCK_STREAM);
   ~COMSocket();

friend class COMServerSocket;
    /** Connects a socket to pIP, on nPort, of type nType. */
    int Connect(const char* pIP, int nPort, int nType, 
                bool bBroadcast = false);
    /** Checks if there is a current open connection */
    bool IsConnected();
    /** Disconnects the current socket */
    int Disconnect();
    /** Reads from a socket, into pbuffer, up to a max of nLen byte, and writes 
      * how many were actually written to nBytesWritten. */
    int Read(char* pBuffer, int nLen, int* nBytesWritten);
    /** Reads in a non blocking fashion (ie, selects and polls) for nTimeout 
      * seconds */
    int NBRead(char* pBuffer, int nLen, int* nBytesWritten, int nTimeout);
    /** Writes to a socket, from buffer pBuffer, up to nLen bytes, and returns 
      * the number of written bytes in pnBytesWritten. */
    int Write(const char* pBuffer, int nLen, int* pnBytesWritten);
    int GetSocket() { return m_nSocket; }

private: // Private attributes

    /** The file descriptor for this socket */
    int m_nSocket;
    /** boolean to store connected state */
    bool m_bConnected;
    /** Stores the type of socket connection. IE, multicast, stream, datagram */
    int m_nSockType;
    /** Stores the sockaddr describing this socket */
    sockaddr_in m_SockAddr;
};

#endif
