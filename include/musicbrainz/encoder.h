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

#ifndef _ENCODER_H_
#define _ENCODER_H_

#include <unicode/ucnv.h>
#include <unicode/utypes.h>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Encoder
{
public:
  /** Constructor. */
  Encoder();
  ~Encoder();

public:
  /** Initialize the encoder to use the desired encoding.
   * This will have the encoder initialize the converter to use either the
   * desired character set or the default one (NULL as character name.) The
   * converter is initialized to use that character set only. If you need to
   * change to a different one call this method again with the new character
   * set.  The old converter will be destroyed and replaced by a new one.
   * @param charSetName - The character set name to encode to. 
   * @returns True if the initialization was successful. False if an error
   *          occured, use GetLastError() to get the error code.
   */
  bool SetEncoding(const char *charSetName = NULL);
 
  /** Converts a string of data from UTF-8 encoding to the encoding desired.
   * This will convert a string of data that is in UTF-8 encoding to whatever
   * encoding was specified for the converter.
   * @param dest - the converted string of data.
   * @param src - the string of UTF-8 data to convert.
   * @return True if the conversion was successful. False if an error occured,
             use GetLastError() to get the error code.
   */
  bool ConvertData(string &dest, const string &src);
  
  /** Converts a string of data to UTF-8 encoding.
   * This will convert data that is in the current encoding to UTF-8.
   * @param dest - the string in UTF-8.
   * @param src - the string that needs to be converted.
   */
  bool ConvertToUTF8(string &dest, const string &src);

  /** Returns the current character set being used.
   * Returns the character set the encoder was initialized with. If the character
   * set has a MIME or IANA alias it will be returned, if not, the internal canonical name 
   * for it will be returned.
   * for the character set will be returned.
   * @return the character set name, if NULL is returned an error occurred. Use GetLastError() to get the error code.
   */
  string GetCurrentEncoding(); 

  /** Returns a list of available character sets.
   * This method will query the system for available character sets it can use.
   * The MIME or IANA aliases for the character sets will be used if available, otherwise the internal
   * canonical name is used. If false is returned then an error occurred.
   * Call GetLastError() to find out what error occurred.
   * @param encodings - an string vector that will hold the character set names. 
   * @return True if the encodings array was filled, false if an error occurred.
   */
  bool GetAvailableEncodings (vector<string> &encodings);

  /** Returns the total number of character sets available.
   * @return - the total number of character sets, if -1 is returned an error occurred. Use GetLastError() to get the error code.
   */
  int GetTotalEncodings();

  /** Returns the last error that occurred.
   * This will return the last error that has occurred if there was one. 
   * If there was no error code than this will return U_ZERO_ERROR. Please
   * refer to IBM's ICU Project website for the meaning of the error codes. 
   * (http://oss.software.ibm.com/icu/apiref/utypes_8h.html#a162)
   * @return - The error given by the ICU library. It will be the string representation of the code.
   */
  string GetLastError();

private:
  /** Querys the ICU library for an alias to a canonical converter name.
   * @param cnvName - The canonical converter name.
   * @return - The MIME or IANA alias for the converter name, otherwise the canonical name is returned.
   */
  string GetAlias(const char *cnvName);
 
private:
  /** The ICU converter object. */
  UConverter *m_converter;
  /** The current character set being used. */
  string m_encoding;
  /** Tells if the encoder is using UTF-8 encoding. */
  bool m_useUTF8;
  /** The last error that occurred. */
  UErrorCode m_errorCode;
};

#endif // #ifndef _ENCODER_H_
