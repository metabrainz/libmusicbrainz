/***************************************************************************
                          MBCOMHTTPSocket.cpp  -  description
                             -------------------
    begin                : Sat Sep 29 2000
    copyright            : (C) 2000 by Relatable 
    written by           : Sean Ward
    email                : sward@relatable.com
 ***************************************************************************/
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include "comhttpsocket.h"
#ifdef WIN32
#include "../config_win32.h"
#include "wincomsocket.h"
#else
#include "../config.h"
#include "comsocket.h"
#endif
#include <stdlib.h>
#include <assert.h>

extern "C" {
   #include "base64.h"
   #include "md5.h"
}

const char* g_strCOMVer = "libmusicbrainz/"VERSION;

MBCOMHTTPSocket::MBCOMHTTPSocket()
{
    m_pSock = new MBCOMSocket;
    m_pTempBuf = NULL;
    m_nBufLen = 0;
    memset(m_hostname, 0x00, 65);
    memset(m_proxyname, 0x00, 1025);
    m_pFile = NULL;
    m_bUseProxy = false;
    m_bProxyCredsUsed = true; // set to false when credentials are needed.
}
MBCOMHTTPSocket::~MBCOMHTTPSocket()
{
    if (m_pSock->IsConnected()) m_pSock->Disconnect();
    delete m_pSock;
    if (m_pTempBuf != NULL) delete [] m_pTempBuf;
}

/** Connects a socket to pIP, on nPort, of type nType. */
int MBCOMHTTPSocket::Connect(const char* pURL)
{
    assert(pURL != NULL);
    if (this->IsConnected()) this->Disconnect();
    if (m_pTempBuf != NULL)
    {
        delete [] m_pTempBuf;
        m_pTempBuf = NULL;
        m_nBufLen = 0;
    }
    // if its not an http:// based url, this can't deal with it
    if (strncasecmp(pURL, "http://", 7)) 
        return -1;

    m_strURL = pURL;

    int nRes = 0;
    memset(m_hostname, 0x00, 65);
        memset(m_proxyname, 0x00, 1025);
        m_pFile = NULL;
    unsigned short nPort = 80;
    int nNumFields = 0;
    
    if (!m_strProxyAddr.empty())
    {
        nNumFields = sscanf(m_strProxyAddr.c_str(), 
                "http://%[^:/]:%hu", m_hostname, &nPort);
        strcpy(m_proxyname, pURL);
        
        m_pFile = m_proxyname;
    }
    else
    {
        nNumFields = sscanf(m_strURL.c_str(), 
                "http://%[^:/]:%hu", m_hostname, &nPort);
        
        m_pFile = strchr(m_strURL.c_str() + 7, '/');
    }
    
    if (nNumFields < 1)
    {
        return -1; // screwed url
    }
    if (nNumFields < 2)
    {
        nPort = 80;
    }
    
    nRes = m_pSock->Connect((const char*)m_hostname, nPort, SOCK_STREAM);
    return nRes;    
}

/** Disconnects the current socket */
int MBCOMHTTPSocket::Disconnect()
{
    return m_pSock->Disconnect();
}

/** Checks if there is a current open connection */
bool MBCOMHTTPSocket::IsConnected()
{
    return m_pSock->IsConnected();
}

/** Writes to a socket, from buffer pBuffer, up to nLen bytes, and returns the number of written bytes in pnBytesWritten. */
int MBCOMHTTPSocket::Write(const char* pBuffer, int nLen, int* pnBytesWritten)
{
    if (!m_pSock->IsConnected()) return -1; // no connection
    const char* pRequest = "POST %s HTTP/1.0\r\n"
                                "Host: %s\r\n"
                                "Accept: */*\r\n"
                                "User-Agent: %s\r\n"
                                "Content-type: application/octet-stream\r\n"
                                "Content-length: %d\r\n";
    
    int nReqLen = strlen(pRequest) + strlen(m_pFile)
            + strlen(m_hostname)
            + strlen(g_strCOMVer)
            + nLen + 2;
    char* pReq = new char[nReqLen];
        memset(pReq, 0, nReqLen);
    assert(pReq != NULL);
    
    sprintf(pReq, pRequest, m_pFile, m_hostname, g_strCOMVer, nLen);
    if (m_bUseProxy && !m_bProxyCredsUsed)
    { 
        // buffer the data we will need when resending the request after authorization...
        string file = m_pFile;
        m_strHttpRequestBuf[0] = pReq; 
        if (string::npos != file.find_first_of("/", 7)) { m_strHttpRequestBuf[1] = file.substr(file.find_first_of("/", 7));  }
        else { m_strHttpRequestBuf[1] = "/"; }
        m_strHttpRequestBuf[2] = pBuffer;
    }
    
    
    strcat(pReq, "\r\n");
    
    memcpy(pReq + strlen(pReq), pBuffer, nLen);
    int nBytes = 0;
    int nRes = m_pSock->Write(pReq, nReqLen, &nBytes);
    delete [] pReq;
    
    if ((nRes == 0) && (nBytes == nReqLen))
    {
        *pnBytesWritten = nLen;
    }
    else
    {
        *pnBytesWritten = 0; // something weird happened
    }
    return nRes;
}

/** Reads in a non blocking fashion (ie, selects and polls) for nTimeout seconds */
int MBCOMHTTPSocket::NBRead(char* pBuffer, int nLen, int* nBytesWritten, int nTimeout)
{
    if (!m_pSock->IsConnected()) return -1; // no connection
    
    char HeaderBuffer[1024];    // read up to 1024 bytes for the header
    memset(HeaderBuffer, 0x00, 1024);
    int nBytes = 0;
    int nTotal = 0;
    
    int nRes = m_pSock->NBRead(HeaderBuffer, 1023, &nBytes, nTimeout);
    if (nRes != 0) return -1;   // error reading from socket. server crash?
    
    nTotal = nBytes;
    if (!IsHTTPHeaderComplete(HeaderBuffer, nTotal))
    {
        if (nTotal == 1023) 
        {   // the header is larger than the header buffer. TODO: deal with this case 
            return -1;
        }
        // get more data since there isn't a complete header yet
        while (!IsHTTPHeaderComplete(HeaderBuffer, nTotal) && (nTotal <= 1023) && (nRes == 0))
        {
            nRes = m_pSock->NBRead(HeaderBuffer + nTotal, 1023 - nTotal, &nBytes, nTimeout);
            nTotal += nBytes;
        }
        
        if ((nRes != 0) || (!IsHTTPHeaderComplete(HeaderBuffer, nTotal))) // socket error or bad header
        {
            return -1;
        }
    }
    if (m_bUseProxy && !m_bProxyCredsUsed) 
    {
       // check to see if we have received a proxy authentication header
       string info = HeaderBuffer;
       if (string::npos != info.find("407 Proxy Authentication Required")) 
       {
          int result = ProxyAuthenticate(info);
          if (result != -1) 
          {
             m_bProxyCredsUsed = true;
             m_strHttpRequestBuf[0] = ""; 
             m_strHttpRequestBuf[1] = ""; 
             m_strHttpRequestBuf[2] = "";
             // Call NBRead again. It will return the real data...
             return NBRead(pBuffer, nLen, nBytesWritten, nTimeout);
          }
          else 
          { 
              return result; 
          }
       }
    }
    

        // Check to see if the sigserver is happy/busy
        char *ptr = strchr(HeaderBuffer, ' ');
        if (ptr)
        {
             int status;

             ptr++;
             status = atoi(ptr);
             if (status == 503)
                 return -2;
             if (status != 200)
                 return -1;
        }
        else
             return -1;
    
    // advance to the data now, if there is any in this first buffer. 
    char* pData = strstr(HeaderBuffer, "\r\n\r\n");
    if (pData) pData += 4;
    int nOffset = (int)pData - (int)HeaderBuffer;
    if (nTotal - nOffset >= nLen) // case 1: entire requested read is in header chunk
    {
        memcpy(pBuffer, pData, nLen);
        *nBytesWritten = nLen;
        
        // case 1: b. if excess data, store for the next read.
        if (nTotal > (nOffset + nLen))
        {
            m_nBufLen = nTotal - (nOffset + nLen);
            m_pTempBuf = new char[m_nBufLen]; // could clobber if non null already
            memcpy(m_pTempBuf, pData + nLen, m_nBufLen);
        }
        return 0;
    }
    else
    {   // case 2: entire requested read is NOT in header chunk
        memcpy(pBuffer, pData, nTotal - nOffset);
        nOffset = nTotal - nOffset;

        // only try one attempt to finish the read request
        nRes = m_pSock->NBRead(pBuffer + nOffset, nLen - nOffset, &nBytes, nTimeout);
        if (nRes != 0) return -1;   // socket error
        
        *nBytesWritten = nBytes + nOffset;
        return 0;
    }
}

/** Reads from a socket, into pbuffer, up to a max of nLen byte, and writes how many were actually written to nBytesWritten. */
int MBCOMHTTPSocket::Read(char* pBuffer, int nLen, int* nBytesWritten)
{
    if (!m_pSock->IsConnected()) return -1; // no connection
    int nOffset = 0;
    int nRes = 0;

    if (m_pTempBuf != NULL) // case 1: leftover bits from header stripping
    {
        if (m_nBufLen >= nLen)  // easy case: just copy from bit bucket and reduce its size
        {
            memcpy(pBuffer, m_pTempBuf, nLen);
            *nBytesWritten = nLen;
            if (nLen < m_nBufLen) // shift the bit bucket
            {
                memmove(m_pTempBuf, m_pTempBuf + nLen, m_nBufLen - nLen);
                m_nBufLen -= nLen;
            }
            else
            {
                delete [] m_pTempBuf;
                m_pTempBuf = NULL;
                m_nBufLen = 0;
            }
            return 0;   // success from bit bucket
    // Not sure if this is where this goes....
    if (m_bUseProxy && !m_bProxyCredsUsed)  
    {
       // check to see if we have received a proxy authentication header
       string info = pBuffer;
       if (string::npos != info.find("407 Proxy Authentication Required")) {
          int result = ProxyAuthenticate(info);
          if (result != -1) 
          {
             m_bProxyCredsUsed = true;
             m_strHttpRequestBuf[0] = ""; 
             m_strHttpRequestBuf[1] = ""; 
             m_strHttpRequestBuf[2] = "";
             // Call Read again, when it returns this will contain the real data...
             return Read(pBuffer, nLen, nBytesWritten);
          }
          else 
          { 
             return result; 
          }
       }
    }
    
        }
        else // bit bucket doesn't store it all
        {
            memcpy(pBuffer, m_pTempBuf, m_nBufLen);
            nOffset = m_nBufLen;
            *nBytesWritten = nOffset;
            
            delete [] m_pTempBuf;
            m_pTempBuf = NULL;
    m_bUseProxy = true;
            m_nBufLen = 0;
        }
    }
    
    // general case: more bits are needed
    nRes = m_pSock->Read(pBuffer + nOffset, nLen - nOffset, nBytesWritten);
    *nBytesWritten += nOffset;
    
    return nRes;
}

/** Sets the proxy credentials. */
int MBCOMHTTPSocket::SetProxyCreds(const string &username, const string &password) 
{
    if (!(username.length() > 0 && password.length() > 0) || (string::npos != username.find(":"))) 
    { 
       return -1; 
    }
    m_strProxyUID = username;
    m_strProxyPWD = password;
    m_bProxyCredsUsed = false;
    return 0;
}
 
/** Sets the proxy address. Use NULL to disable. */
int MBCOMHTTPSocket::SetProxy(const char* pURL)
{
    if (pURL == NULL) m_strProxyAddr = ""; // empty string
    else
    m_strProxyAddr = pURL;
    return 0;
}

/** Generates the proxy authorization header and sends the response back to the server. */
int MBCOMHTTPSocket::ProxyAuthenticate(const string &header) 
{
   // Find out whether this is a basic or digest authentication..
   string authString, httpResponse;

   if (string::npos != header.find("Proxy-Authenticate: Basic")) 
   {
       // Generate the base64 hash
       unsigned char *hash = NULL;
       char *proxyCreds = new char[m_strProxyUID.length() + 1 + m_strProxyPWD.length() + 1];
       long unsigned int hashLength; 

       strcpy(proxyCreds, m_strProxyUID.c_str());
       strcat(proxyCreds, ":");
       strcat(proxyCreds, m_strProxyPWD.c_str());
       hash = rfc822_binary(proxyCreds, strlen(proxyCreds), &hashLength);
       delete [] proxyCreds;

       // Need to replace the _ . and - symbols with the original characters...
       for (unsigned int x = 0; x < hashLength; x++) 
       {
          if (hash[x] == '_') { hash[x] = '/'; }
          else if (hash[x] == '.') { hash[x] = '+'; }
          else if (hash[x] == '-') { hash[x] = '='; }
       } 
       authString = "Proxy-Authorization: Basic ";
       authString += (char*)hash;
       free(hash);
   }
   else if (string::npos != header.find("Proxy-Authenticate: Digest")) 
   {
       // Parse out the stuff we will need first..
       string realm, nonce, opaque, cnonce, requestDigest;
       bool bQopAuth = false, bQopAuthInt = false, bMD5Sess = false;
       size_t index = header.find("Proxy-Authorization: Digest");
       size_t beginIndex = header.find("realm=\"", index) + 7;
       size_t endIndex = header.find_first_of('\"', beginIndex);
       realm = header.substr(beginIndex, endIndex - beginIndex);

       beginIndex = header.find("nonce=\"", index) + 7;
       endIndex = header.find_first_of('\"', beginIndex);
       nonce = header.substr(beginIndex, endIndex - beginIndex);

       if (string::npos != header.find("opaque=\"", index)) 
       {
          beginIndex = header.find("opaque=\"", index) + 8;
          endIndex = header.find_first_of('\"', beginIndex);
          opaque = header.substr(beginIndex, endIndex - beginIndex); 
       }

       // Generate the cnonce value real quick
       unsigned char *cnonceval = NULL;
       time_t currentTime = time(0);
       char *timeString = asctime(localtime(&currentTime));
       long unsigned int cnonceSize;
       cnonceval = rfc822_binary(timeString, strlen(timeString), &cnonceSize);
       cnonce = (char*)cnonceval;
       free(cnonceval);
       
       for (unsigned int x = 0; x < cnonce.length(); x++) 
       {
          if (cnonce[x] == '_') { cnonce[x] = '/'; }
          else if (cnonce[x] == '.') { cnonce[x] = '+'; } 
          else if (cnonce[x] == '-') { cnonce[x] = '='; }
       } 
       
       // Check to see if there is an qop
       if (string::npos != header.find("qop=\"", index)) 
       {
          if (string::npos != header.find("auth-int", index)) { bQopAuthInt = true; }
          else if (string::npos != header.find("auth", index)) { bQopAuth = true; }
       }
       
       // Check to see if we have to do the special MD5-Sess hash
       if (string::npos != header.find("MD5-Sess", index)) { bMD5Sess = true; }
       
       // Create the MD5 hash 
       string A1, A2;
       string A1Hash, A2Hash;
      
       MD5Context md5cont;
       unsigned char tempHashBuf[16];
 
       // Generate the A1 hash..
       MD5Init(&md5cont);
       MD5Update(&md5cont, (unsigned char*)m_strProxyUID.c_str(), m_strProxyUID.length());
       MD5Update(&md5cont, (unsigned char *)":", 1);
       MD5Update(&md5cont, (unsigned char*)realm.c_str(), realm.length());
       MD5Update(&md5cont, (unsigned char *) ":", 1);
       MD5Update(&md5cont, (unsigned char*)m_strProxyPWD.c_str(), m_strProxyPWD.length());
       MD5Final(tempHashBuf, &md5cont);
       A1 = (char*)tempHashBuf;
   
       if (bMD5Sess) 
       {
          MD5Init(&md5cont);
          MD5Update(&md5cont, (unsigned char *)A1.c_str(), A1.length());
          MD5Update(&md5cont, (unsigned char *)":", 1);
          MD5Update(&md5cont, (unsigned char *)nonce.c_str(), nonce.length());
          MD5Update(&md5cont, (unsigned char *)":", 1);
          MD5Update(&md5cont, (unsigned char *)cnonce.c_str(), cnonce.length());
          MD5Final(tempHashBuf, &md5cont);
          A1 = (char*)tempHashBuf;
       }
       A1Hash = ConvertToHex(A1);
       
       // Generate the A2 hash..
       MD5Init(&md5cont);
       MD5Update(&md5cont, (unsigned char *)"POST", 4);
       MD5Update(&md5cont, (unsigned char *)":", 1);
       MD5Update(&md5cont, (unsigned char*)m_strHttpRequestBuf[1].c_str(), m_strHttpRequestBuf[1].length()); 
       
       if (bQopAuthInt) 
       {
          MD5Update(&md5cont, (unsigned char*)":", 1);
          MD5Update(&md5cont, (unsigned char*)m_strHttpRequestBuf[2].c_str(), m_strHttpRequestBuf[2].length());
       }
       MD5Final(tempHashBuf, &md5cont);
       A2Hash = ConvertToHex((char*)tempHashBuf);
       
       // Generate the request digest
       string finalInput;
       MD5Init(&md5cont);
       MD5Update(&md5cont, (unsigned char*)A1Hash.c_str(), A1Hash.length());
       MD5Update(&md5cont, (unsigned char*)":", 1);
       MD5Update(&md5cont, (unsigned char*)nonce.c_str(), nonce.length());
       if (bQopAuth || bQopAuthInt) 
       {
          MD5Update(&md5cont, (unsigned char*)":", 1);
          MD5Update(&md5cont, (unsigned char*)"00000001", 8);
          MD5Update(&md5cont, (unsigned char*)":", 1);
          MD5Update(&md5cont, (unsigned char*)cnonce.c_str(), cnonce.length());
          MD5Update(&md5cont, (unsigned char*)":", 1);
          if (bQopAuthInt) 
          { 
              MD5Update(&md5cont, (unsigned char *)"auth-int", 8); 
          }
          else 
          { 
              MD5Update(&md5cont, (unsigned char *)"auth", 4); 
          }  
       }
       MD5Update(&md5cont, (unsigned char*)":", 1);
       MD5Update(&md5cont, (unsigned char*)A2Hash.c_str(), A2Hash.length());
       MD5Final(tempHashBuf, &md5cont);
       requestDigest = ConvertToHex((char*)tempHashBuf);
       
       authString = "Proxy-Authorization: Digest username=\"" + m_strProxyUID + "\", realm=\"" + realm + "\", nonce=\"" + nonce + "\", uri=\"" + m_strHttpRequestBuf[1] + "\"" +
                    ", response=\"" + requestDigest + "\"";
       
       if (opaque.length() > 0) {
          authString += ", opaque=\"" + opaque + "\"";
       }       
       if (bQopAuth || bQopAuthInt) {
          authString += ", qop=";
          if (bQopAuthInt) { authString += "\"auth-int\""; }
          else { authString += "\"auth\""; }
          authString += ", nc=00000001";
          authString += ", cnonce=\"" + cnonce + "\"";
       }
       
   }
   else 
   {
      return -1; // Don't know the authentication used.
   }

   // Finally send the http response back...
   httpResponse = m_strHttpRequestBuf[0] + authString + (string)"\r\n\r\n" + m_strHttpRequestBuf[2];
   int nBytes = 0;
   return m_pSock->Write(httpResponse.c_str(), httpResponse.length(), &nBytes);
}

string MBCOMHTTPSocket::ConvertToHex(const string &ascii) 
{
   unsigned char character;
   string hexString(ascii.length() * 2, '\0');
   for (unsigned int x = 0; x < ascii.length(); x++) 
   {
      character = (ascii[x] >> 4) & 0xf;
      if (character < 10) { hexString[x * 2] = (character + '0'); }
      else { hexString[x * 2] = (character + 'a' - 10); }
      
      character = ascii[x] & 0xf;
      if (character < 10) { hexString[x * 2 + 1] = (character + '0'); }
      else { hexString[x * 2 + 1] = (character + 'a' - 10); }   
   }
   return hexString;
}




bool MBCOMHTTPSocket::IsHTTPHeaderComplete(char* buffer, unsigned int length)
{
    bool result = false;

    for(char* cp = buffer; cp < buffer + length; cp++)
    {
        if(!strncmp(cp, "\n\n", 2) || !strncmp(cp, "\r\n\r\n", 4))
        {
            result = true;
            break;
        }
    }

    return result;
}

