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

     $Id$

----------------------------------------------------------------------------*/
#ifndef INCLUDED_PARSE_H__
#define INCLUDED_PARSE_H__

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <string>
#include <map>

using namespace std;

#include "errors.h"
#include "types.h"
#include "../expat/xmlparse/xmlparse.h"

typedef map<string, string > AttrMap;

const string ConvertToISO(const char *utf8);

class MBParse
{
    public:

               MBParse(bool useUTF8);
      virtual ~MBParse(void);

      Error    ParseFile(const string &oFile);
      Error    ParseString(const string &oXML);
      void     GetErrorString(string &oError);
      int      GetErrorLine(void);
      bool     UseUTF8(void) { return m_useUTF8; };

      virtual Error BeginElement(const string &oElement, AttrMap &oAttrMap)=0; 
      virtual Error EndElement(const string &oElement) = 0;
      virtual Error PCData(const string &oData) = 0;

    protected:


      XML_Parser   *m_pParser;
      bool          m_useUTF8;
};

#endif
