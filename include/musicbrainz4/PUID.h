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

#ifndef _MUSICBRAINZ4_PUID_H
#define _MUSICBRAINZ4_PUID_H

#include <string>

#include "musicbrainz4/Entity.h"
#include "musicbrainz4/GenericList.h"
#include "musicbrainz4/Recording.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CPUIDPrivate;

	class CPUID: public CEntity
	{
	public:
		CPUID(const XMLNode& Node=XMLNode::emptyNode());
		CPUID(const CPUID& Other);
		CPUID& operator =(const CPUID& Other);
		~CPUID();

		std::string ID() const;
		CGenericList<CRecording> *RecordingList() const;

	private:
		void Cleanup();

		CPUIDPrivate * const m_d;

		virtual bool ParseAttribute(const std::string& Name, const std::string& Value);
		virtual bool ParseElement(const XMLNode& Node);
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CPUID& PUID);

#endif
