/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libmusicbrainz5 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#ifndef _MUSICBRAINZ5_ISRC_H
#define _MUSICBRAINZ5_ISRC_H

#include "musicbrainz5/Entity.h"
#include "musicbrainz5/RecordingList.h"

#include "musicbrainz5/xmlParser.h"

namespace MusicBrainz5
{
	class CISRCPrivate;

	class CISRC: public CEntity
	{
	public:
		CISRC(const XMLNode& Node=XMLNode::emptyNode());
		CISRC(const CISRC& Other);
		CISRC& operator =(const CISRC& Other);
		virtual ~CISRC();

		virtual CISRC *Clone();

		std::string ID() const;
		CRecordingList *RecordingList() const;

		virtual std::ostream& Serialise(std::ostream& os) const;
		static std::string GetElementName();

	protected:
		virtual bool ParseAttribute(const std::string& Name, const std::string& Value);
		virtual bool ParseElement(const XMLNode& Node);

	private:
		void Cleanup();

		CISRCPrivate * const m_d;
	};
}

#endif
