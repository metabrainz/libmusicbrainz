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

#ifndef _MUSICBRAINZ4_ISRC_H
#define _MUSICBRAINZ4_ISRC_H

#include "musicbrainz4/GenericList.h"

#include "musicbrainz4/Recording.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CISRC
	{
	public:
		CISRC(const XMLNode& Node=XMLNode::emptyNode());
		CISRC(const CISRC& Other);
		CISRC& operator =(const CISRC& Other);
		~CISRC();

		std::string ID() const;
		CGenericList<CRecording> *RecordingList() const;

	private:
		void Cleanup();

		std::string m_ID;
		CGenericList<CRecording> *m_RecordingList;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CISRC& ISRC);

#endif
