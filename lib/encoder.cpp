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

#include <unicode/utypes.h>
#include <unicode/unistr.h>
#include <string>
#include "encoder.h"
using namespace std;

Encoder::Encoder() {
  m_converter = 0;
  m_errorCode = U_ZERO_ERROR;
  m_useUTF8 = false;
}

Encoder::~Encoder() {
  if (m_converter != 0) {
    ucnv_close(m_converter);
    ucnv_flushCache();
  }
}

bool Encoder::SetEncoding(const char *charSetName) {
  // Destroy the old converter first.
  if (m_converter != 0) {
    ucnv_close(m_converter);
  }
  
  m_converter = ucnv_open(charSetName, &m_errorCode);
  m_encoding = GetAlias(ucnv_getName(m_converter, &m_errorCode));
  if (m_encoding == "UTF-8") {
    m_useUTF8 = true;
  } 
  else {
    m_useUTF8 = false;
  }
 
  if (U_FAILURE(m_errorCode)) {
    return false;
  }

  return true;
}

bool Encoder::ConvertData(string& dest, const string &src) {
  if (m_converter == 0) {
    // Set the encoding to use the default encoding
    if (SetEncoding(0) == false) { return 0; }
  }
  if (m_useUTF8) { 
    dest = src; 
    return true;
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
  return true;
}

bool Encoder::ConvertToUTF8(string &dest, const string &src) {
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
  return true;
}

string Encoder::GetCurrentEncoding() {
  if (m_converter == 0) { 
    if (SetEncoding(0) == false) { return 0; }
  }
  return m_encoding;
}

bool Encoder::GetAvailableEncodings(vector<string> &encodings) {
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
  return true;
}

int Encoder::GetTotalEncodings() {
  return (ucnv_countAvailable());
}

string Encoder::GetLastError() { 
  if ((string)u_errorName(m_errorCode) == "U_FILE_ACCESS_ERROR") {
    return (string)"The specified character set is not supported.";
  }
  return (string)u_errorName(m_errorCode); 
}

string Encoder::GetAlias(const char *cnvName) {
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
}




