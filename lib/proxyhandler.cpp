/* --------------------------------------------------------------------------

   MusicBrainz -- The Internet music metadatabase

   Copyright (C) 2000 Emusic.com
   
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

----------------------------------------------------------------------------*/
#include <string>
#include "proxyHandler.h"
#include "http.h"
extern "C" {
   #include "base64.h"
   #include "md5.h"
}
using namespace std;

ProxyHandler::ProxyHandler() {
  m_server = "";
  m_port = 0;
  m_username = "";
  m_password = "";
  m_status = true; // set to false when credentials are needed
}

ProxyHandler::ProxyHandler(const string &proxyUrl, unsigned int port) {
  m_server = proxyUrl;
  m_port = port;
  m_username = "";
  m_password = "";
  m_status = true;
}

ProxyHandler::~ProxyHandler() {

}

void ProxyHandler::SetUrl(const string &proxyUrl) {
  m_server = proxyUrl;
}

string ProxyHandler::GetUrl() {
  return m_server;
}

void ProxyHandler::SetPort(unsigned int port) {
  m_port = port;
}

unsigned int ProxyHandler::GetPort() {
  return m_port;
}

Error ProxyHandler::SetCredentials(const string &username, const string &password) {
  if (!(username.length() > 0 && password.length() > 0) || (string::npos != username.find(":"))) {
     return kError_InvalidProxyCreds;
  }
  m_username = username;
  m_password = password;
  m_status = false;
  return kError_NoErr;
}

void ProxyHandler::SaveRequestInfo(const string& query, const string& file, const string& data) {
  m_httpRequestBuf[0] = query;
  m_httpRequestBuf[1] = file;
  m_httpRequestBuf[2] = data;
}

void ProxyHandler::SetAuthenticated(bool status) {
  m_status = status;
}

bool ProxyHandler::IsAuthenticated() {
  return m_status;
}

Error ProxyHandler::Authenticate(const string &headerInfo, string &httpResponse) {
  // Find out whether this is a basic or digest authentication..
  string authString;
 
  if (string::npos != headerInfo.find("Proxy-Authenticate: Basic")) {
    authString = DoBasicAuthentication();    
  }
  else if (string::npos != headerInfo.find("Proxy-Authenticate: Digest")) {
    authString = DoMD5DigestAuthentication(headerInfo);
  }
  else {
    return kError_UnknownProxyAuth; // Don't know the authentication used.
  }

  // Finally send the http response back...
  httpResponse = m_httpRequestBuf[0] + authString + (string)"\r\n\r\n" + m_httpRequestBuf[2];
  return kError_NoErr;
}

string ProxyHandler::DoBasicAuthentication() {
   string authString;

   // Generate the basic-credentials hash

   // basic-credentials = base64-user-pass
   // base64-user-pass  = <base64 [4] encoding of user-pass, except not limited to 76 char/line>
   // user-pass   = userid ":" password
   // userid      = *<TEXT excluding ":">
   // password    = *TEXT

   unsigned char *hash = 0;
   char *proxyCreds = new char[m_username.length() + 1 + m_password.length() + 1];
   long unsigned int hashLength; 

   strcpy(proxyCreds, m_username.c_str());
   strcat(proxyCreds, ":");
   strcat(proxyCreds, m_password.c_str());
   hash = rfc822_binary(proxyCreds, strlen(proxyCreds), &hashLength);
   delete [] proxyCreds;

   // Need to replace the _ . and - symbols with the original characters...
   for (unsigned int x = 0; x < hashLength; x++) {
      if (hash[x] == '_') { hash[x] = '/'; }
      else if (hash[x] == '.') { hash[x] = '+'; }
      else if (hash[x] == '-') { hash[x] = '='; }
   } 
   
   authString = "Proxy-Authorization: Basic ";
   authString += (char*)hash;
   free(hash);  

   return authString;
}

string ProxyHandler::DoMD5DigestAuthentication(const string &headerInfo) {
   string realm;  // A string displayed to users so they know which username and password to use.
   string nonce;  // A server-specified data string uniquely generated each time a 401 response is made.
   string opaque; // A string of data, specified by the server, which should be returned by the client unchanged in 
                  // the Authorization header
   string cnonce; // The cnonce-value is an opaque quoted string value provided by the client and used by both client
                  // and server to avoid chosen plaintext attacks, to provide mutual authentication, and to provide 
                  // some message integrity protection.
   string requestDigest; // Known as "response", it is a string of 32 hex digits which proves that the user knows a password.
   
   // QOP - Indicates what "quality of protection" the client has applied to the message.
   bool qopAuth = false, 
        qopAuthInt = false;
   
   //  The "MD5-sess" algorithm is intended to allow efficient 3rd party authentication servers. If this is
   //  not used, the normal "MD5" algorithm is used to make a normal checksum value.
   bool md5Sess = false;

   // Parse out the realm value
   size_t index = headerInfo.find("Proxy-Authenticate: Digest");
   size_t beginIndex = headerInfo.find("realm=\"", index) + 7;
   size_t endIndex = headerInfo.find_first_of('\"', beginIndex);
   realm = headerInfo.substr(beginIndex, endIndex - beginIndex);

   // Parse out the nonce value
   beginIndex = headerInfo.find("nonce=\"", index) + 7;
   endIndex = headerInfo.find_first_of('\"', beginIndex);
   nonce = headerInfo.substr(beginIndex, endIndex - beginIndex);

   // Parse out the opaque value
   if (string::npos != headerInfo.find("opaque=\"", index)) 
   {
      beginIndex = headerInfo.find("opaque=\"", index) + 8;
      endIndex = headerInfo.find_first_of('\"', beginIndex);
      opaque = headerInfo.substr(beginIndex, endIndex - beginIndex); 
   }
       
   // Generate the cnonce value real quick
   unsigned char *cnonceval = 0;
   time_t currentTime = time(0);
   char *timeString = asctime(localtime(&currentTime));
   long unsigned int cnonceSize;
   cnonceval = rfc822_binary(timeString, strlen(timeString), &cnonceSize);
   cnonce = (char*)cnonceval;
   free(cnonceval);       

   // Replace characters with the actual base64 characters
   for (unsigned int x = 0; x < cnonce.length(); x++) {
      if (cnonce[x] == '_') { cnonce[x] = '/'; }
      else if (cnonce[x] == '.') { cnonce[x] = '+'; } 
      else if (cnonce[x] == '-') { cnonce[x] = '='; }
   } 
       
   // Check to see if there is an qop and it has at least "auth"
   if (string::npos != headerInfo.find("qop=\"", index)) {
      if (string::npos != headerInfo.find("auth-int", index)) { 
         qopAuthInt = true; 
      }
      else if (string::npos != headerInfo.find("auth", index)) { 
	 qopAuth = true; 
      }
   }
       
   // Check to see if we have to do the special MD5-Sess hash
   if (string::npos != headerInfo.find("MD5-Sess", index)) { 
       md5Sess = true;
   }
   
   // Create the MD5 hash 
   string A1, A2;
   string A1Hash, A2Hash;
     
   MD5Context md5cont;
   unsigned char tempHashBuf[16];
 
   // First, generate the A1 hash..
   // A1 := unq(username-value) ":" unq(realm-value) ":" passwd
   MD5Init(&md5cont);
   MD5Update(&md5cont, (unsigned char*)m_username.c_str(), m_username.length());
   MD5Update(&md5cont, (unsigned char*)":", 1);
   MD5Update(&md5cont, (unsigned char*)realm.c_str(), realm.length());
   MD5Update(&md5cont, (unsigned char*)":", 1);
   MD5Update(&md5cont, (unsigned char*)m_password.c_str(), m_password.length());
   MD5Final(tempHashBuf, &md5cont);
   A1 = (char*)tempHashBuf;
   
   if (md5Sess) {
      // If MD5Session algorithm is used, append extra data into the digest...
      // A1 := H( unq(username-value) ":" unq(realm-value) ":" passwd ) ":" unq(nonce-value) ":" unq(cnonce-value) 
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
   // A2 := Method ":" digest-uri-value
   MD5Init(&md5cont);
   if (m_httpRequestBuf[2].length() == 0) { 
      MD5Update(&md5cont, (unsigned char *)"GET", 3); 
   }
   else { 
      MD5Update(&md5cont, (unsigned char *)"POST", 4); 
   }
   MD5Update(&md5cont, (unsigned char *)":", 1);
   MD5Update(&md5cont, (unsigned char*)m_httpRequestBuf[1].c_str(), m_httpRequestBuf[1].length()); 
   
   if (qopAuthInt) {
      // If the QOP is "auth-int" then we append the entity-body on to the end...
      // A2 := Method ":" digest-uri-value ":" H(entity-body) 
      MD5Update(&md5cont, (unsigned char*)":", 1);
      MD5Update(&md5cont, (unsigned char*)m_httpRequestBuf[2].c_str(), m_httpRequestBuf[2].length());
   }
   MD5Final(tempHashBuf, &md5cont);
   A2Hash = ConvertToHex((char*)tempHashBuf);
       
   // Generate the request digest
   // If the QOP value is present the hash will be
   //    request-digest := " KD ( H(A1), unq(nonce-value) ":" nc-value ":" unq(cnonce-value) ":" unq(qop-value) ":" H(A2) ) <"
   // If the QOP value is NOT present then it will be
   //    request-digest := " KD ( H(A1), unq(nonce-value) ":" H(A2) ) "
   string finalInput;
   MD5Init(&md5cont);
   MD5Update(&md5cont, (unsigned char*)A1Hash.c_str(), A1Hash.length());
   MD5Update(&md5cont, (unsigned char*)":", 1);
   MD5Update(&md5cont, (unsigned char*)nonce.c_str(), nonce.length());
   if (qopAuth || qopAuthInt) {
      MD5Update(&md5cont, (unsigned char*)":", 1);
      MD5Update(&md5cont, (unsigned char*)"00000001", 8); // nonce-value
      MD5Update(&md5cont, (unsigned char*)":", 1);
      MD5Update(&md5cont, (unsigned char*)cnonce.c_str(), cnonce.length());
      MD5Update(&md5cont, (unsigned char*)":", 1);
      if (qopAuthInt) { 
         MD5Update(&md5cont, (unsigned char *)"auth-int", 8);
      }
      else { 
         MD5Update(&md5cont, (unsigned char *)"auth", 4); 
      }  
   }
   MD5Update(&md5cont, (unsigned char*)":", 1);
   MD5Update(&md5cont, (unsigned char*)A2Hash.c_str(), A2Hash.length());
   MD5Final(tempHashBuf, &md5cont);
   requestDigest = ConvertToHex((char*)tempHashBuf);
   
   // Create the Authorization header for replying back to server
   string authString;
   authString = "Proxy-Authorization: Digest username=\"" + m_username + 
                "\", realm=\"" + realm + 
                "\", nonce=\"" + nonce + 
                "\", uri=\"" + m_httpRequestBuf[1] + 
                "\", response=\"" + requestDigest + "\"";
       
   if (opaque.length() > 0) {
      authString += ", opaque=\"" + opaque + "\"";
   }       

   if (qopAuth || qopAuthInt) {
      authString += ", qop=";
      if (qopAuthInt) { 
         authString += "\"auth-int\""; 
      }
      else { 
         authString += "\"auth\""; 
      }
      authString += ", nc=00000001";
      authString += ", cnonce=\"" + cnonce + "\"";
   }

   return authString;
}

string ProxyHandler::ConvertToHex(const string &ascii) 
{
  unsigned char character;
  string hexString(ascii.length() * 2, '\0');
  for (unsigned int x = 0; x < ascii.length(); x++) {
    character = (ascii[x] >> 4) & 0xf;
    if (character < 10) { 
      hexString[x * 2] = (character + '0'); 
    }
    else { 
      hexString[x * 2] = (character + 'a' - 10); 
    }
    character = ascii[x] & 0xf;
    if (character < 10) { 
      hexString[x * 2 + 1] = (character + '0'); 
    }
    else { 
      hexString[x * 2 + 1] = (character + 'a' - 10); 
    }   
  }
  return hexString;
}
