/* --------------------------------------------------------------------------

   libmusicbrainz4 - Client library to access MusicBrainz

   Copyright (C) 2011 Andrew Hawkins

   This file is part of libmusicbrainz4.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libmusicbrainz4 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#ifndef _MUSICBRAINZ4_MEDIUM_H
#define _MUSICBRAINZ4_MEDIUM_H

#include <string>
#include <iostream>

#include "musicbrainz4/Entity.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CMediumPrivate;

	class CDiscList;
	class CTrackList;

	class CMedium: public CEntity
	{
	public:
		CMedium(const XMLNode& Node=XMLNode::emptyNode());
		CMedium(const CMedium& Other);
		CMedium& operator =(const CMedium& Other);
		virtual ~CMedium();

		virtual CMedium *Clone();

		std::string Title() const;
		int Position() const;
		std::string Format() const;
		CDiscList *DiscList() const;
		CTrackList *TrackList() const;

		bool ContainsDiscID(const std::string& DiscID) const;

		virtual std::string ElementName() const;

	protected:
		virtual bool ParseAttribute(const std::string& Name, const std::string& Value);
		virtual bool ParseElement(const XMLNode& Node);

	private:
		void Cleanup();

		CMediumPrivate * const m_d;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CMedium& Medium);

#endif
