/*_______________________________________________________________________
  MusicBrainz -- The Internet music metadatabase

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
 ________________________________________________________________________*/

#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#ifdef USE_ICU
  #include <unicode/utypes.h>
  #include <unicode/unistr.h>
#else
  #include <ctype.h>
#endif

#include <string>
#include "encoder.h"
using namespace std;

Encoder::Encoder() {
#ifdef USE_ICU
  m_converter = 0;
  m_errorCode = U_ZERO_ERROR;
#else
  m_encoding = "ISO-8859-1";
  m_errorCode = "";
#endif
  m_useUTF8 = false;
}

Encoder::~Encoder() {
#ifdef USE_ICU
  if (m_converter != 0) {
    ucnv_close(m_converter);
    ucnv_flushCache();
  }
#endif
}

bool Encoder::SetEncoding(const char *charSetName) {
#ifdef USE_ICU
  // Destroy the old converter first.
  if (m_converter != 0) {
    ucnv_close(m_converter);
  } 
  if (charSetName == 0) {
     m_converter = ucnv_open("iso-8859-1", &m_errorCode);
  }
  else {
     m_converter = ucnv_open(charSetName, &m_errorCode);
  }

  if (U_FAILURE(m_errorCode)) {
    return false;
  }
  m_encoding = GetAlias(ucnv_getName(m_converter, &m_errorCode));
  if (U_FAILURE(m_errorCode)) {
    return false;
  }
#else
  string csName; 
  int length = strlen(charSetName);
  if (length < 0) { 
    m_errorCode = "Invalid character set name.";
    return false; 
  }
  for (int x = 0; x < length; x++) {
    csName += tolower(charSetName[x]);
  }

  // Check to see if the character set is UTF-8 or ISO-8859-1
  if (csName == "utf-8" || csName == "utf8" || csName == "ibm-1208" || csName == "ibm-1209" || 
      csName == "ibm-5304" || csName == "ibm-5305" || csName == "windows-65001" || csName == "cp1208") 
  {
    m_encoding = "UTF-8";
  }
  else if (csName == "iso-8859-1" || csName == "iso88591" || csName == "ibm-819" || csName == "ibm819" ||
           csName == "cp819" || csName == "latin1" || csName == "8859_1" || csName == "csisolatin1" ||
           csName == "iso-ir-100" || csName == "iso_8859-1:1987" || csName == "l1" || csName == "819") 
  {
    m_encoding = "ISO-8859-1";
  }
  else {
    m_errorCode = "The specified character set is not supported. UTF-8 and ISO-8859-1 are only supported.";
    return false;
  }
#endif
  if (m_encoding == "UTF-8") {
    m_useUTF8 = true;
  } 
  else {
    m_useUTF8 = false;
  }
  return true;
}

bool Encoder::ConvertData(string& dest, const string &src) {
  // If the encoding to convert to is UTF-8 just return the original data
  if (m_useUTF8) {
    dest = src;
    return true;
  }

#ifdef USE_ICU
  if (m_converter == 0) {
    // Set the encoding to use the default encoding
    if (SetEncoding(0) == false) { return 0; }
  }
  
  UnicodeString ucString(src.c_str(), "UTF-8");
  int32_t outputLength = UCNV_GET_MAX_BYTES_FOR_STRING(ucString.length(), ucnv_getMaxCharSize(m_converter));
  char* output = new char[outputLength];
  ucnv_fromUChars(m_converter, output, outputLength, ucString.getBuffer(), ucString.length(), &m_errorCode);
  if (U_FAILURE(m_errorCode)) {
    return false;
  }
  dest = output;
  delete[] output;
#else
  dest = ConvertToISO(src);
#endif
  return true;
}

bool Encoder::ConvertToUTF8(string &dest, const string &src) {
  if (m_useUTF8) {
    dest = src;
    return true;
  }

#ifdef USE_ICU
  if (m_converter == 0) {
    // Set the encoding to use the default encoding
    if (SetEncoding(0) == false) { return 0; }
  }  

  UnicodeString ucString(src.c_str(), m_encoding.c_str());
  UConverter *utfConverter = ucnv_open("UTF-8", &m_errorCode);
  if (U_FAILURE(m_errorCode)) {
    return false;
  }
  int32_t outputLength = UCNV_GET_MAX_BYTES_FOR_STRING(ucString.length(), ucnv_getMaxCharSize(utfConverter));
  char* output = new char[outputLength];
  ucnv_fromUChars(utfConverter, output, outputLength, ucString.getBuffer(), ucString.length(), &m_errorCode);
  if (U_FAILURE(m_errorCode)) {
    delete[] output;
    ucnv_close(utfConverter);
    return false;
  }
  dest = output;
  delete[] output;
  ucnv_close(utfConverter);
#else 
  // Don't know if this is right...
  dest = src;    
#endif
  return true;
}

bool Encoder::GetCurrentEncoding(string &encoding) {
#ifdef USE_ICU
  if (m_converter == 0) { 
    if (SetEncoding(0) == false) { return false; }
  }
#endif
  encoding = m_encoding;
  return true;
}

bool Encoder::GetAvailableEncodings(vector<string> &encodings) {
#ifdef USE_ICU
  int numEncodings = ucnv_countAvailable();
  if (numEncodings < 1) { return true; }
  
  for (int x = 0; x < numEncodings; x++) {
    const char *cnvName = ucnv_getAvailableName(x);
    string name = GetAlias(cnvName);
    if (name.length() == 0) {
      return false;
    }
    encodings.push_back(name);
  }
#else
  encodings.push_back("UTF-8");
  encodings.push_back("ISO-8859-1");
#endif
  return true;
}

int Encoder::GetTotalEncodings() {
#ifdef USE_ICU
  return (ucnv_countAvailable());
#endif
  return (2);
}

string Encoder::GetLastError() { 
#ifdef USE_ICU
  if ((string)u_errorName(m_errorCode) == "U_FILE_ACCESS_ERROR") {
    return (string)"The specified character set is not supported.";
  }
  return (string)u_errorName(m_errorCode); 
#else
  return m_errorCode;
#endif
}

string Encoder::GetAlias(const char *cnvName) {
#ifdef USE_ICU
  /* If the character set name has a MIME alias, return that. */
  const char *name = ucnv_getStandardName(cnvName, "MIME", &m_errorCode);
  if (U_FAILURE(m_errorCode)) { return ""; }
  if (name != 0) { return name; }

  /* If the character set name has a IANA alias, return that. */
  name = ucnv_getStandardName(cnvName, "IANA", &m_errorCode);
  if (U_FAILURE(m_errorCode)) { return ""; } 
  if (name != 0) { return name; }

  /* Otherwise return the internal converter name. */ 
  return cnvName;
#endif
  return ""; // not usable unless with ICU
}

string Encoder::ConvertToISO(const string &UTF8) 
{
   unsigned char *in = (unsigned char *)UTF8.c_str();
   unsigned char *out = new unsigned char [UTF8.length() + 1];
   unsigned char *buf = out;
   unsigned char *end = in + UTF8.length();
   string ret;

   for(;*in != 0x00 && in <= end; in++, out++) {
      if (*in < 0x80) {  
         /* lower 7-bits unchanged */
         *out = *in;
      }
      else if (*in > 0xC3) { 
         /* discard anything above 0xFF */
         *out = '?';
      }
      else if (*in & 0xC0) { 
         /* parse upper 7-bits */
         if (in >= end) {
            *out = 0;
	 }
         else {
	    /* The following used to be in one block, but the math would end up 
	       wrong if compiled with MSVC++ in release mode. Using the left and right
	       intermediates fixes the problem. Gotta love M$ crap. */
            unsigned char left, right;
            left = (((*in) & 0x1F) << 6); 
	    right = (0x3F & (*(++in)));
            *out = right | left;
         }
      }
      else {
         *out = '?';  /* this should never happen */
      }
   }
   *out = 0x00; /* append null */
   ret = string((char *)buf);
   delete[] buf;
   return ret;
}
