/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   Flactag is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id$

----------------------------------------------------------------------------*/

#ifndef _MUSICBRAINZ4_ANNOTATION_H
#define _MUSICBRAINZ4_ANNOTATION_H

#include <string>
#include <iostream>

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CAnnotationPrivate;
	
	class CAnnotation
	{
	public:
		CAnnotation(const XMLNode& Node);
		CAnnotation(const CAnnotation& Other);
		CAnnotation& operator =(const CAnnotation& Other);
		~CAnnotation();

		std::string Type() const;
		std::string Entity() const;
		std::string Name() const;
		std::string Text() const;

	private:
		CAnnotationPrivate * const m_d;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CAnnotation& Annotation);

#endif
