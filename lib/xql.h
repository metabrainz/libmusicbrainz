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
#ifndef INCLUDED_XMLPATHLIST_H__
#define INCLUDED_XMLPATHLIST_H__

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include <string>
#include <vector>
#include <map>

using namespace std;

#include "parse.h"

class XQL : public MBParse
{
    public:

               XQL(void);
      virtual ~XQL(void);

      const string &Query(const string &oKey);

    protected:
     
      virtual Error BeginElement(const string &oElement, AttrMap &oAttrMap); 
      virtual Error EndElement(const string &oElement);
      virtual Error PCData(const string &oData);

      string              m_oPath;
      map<string, string> m_oList;
      map<string, int>    m_oNodeHist;
      string              m_oEmpty;
};

#endif
