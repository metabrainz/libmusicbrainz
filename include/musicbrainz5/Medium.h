/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   libmusicbrainz5 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#ifndef _MUSICBRAINZ5_MEDIUM_H
#define _MUSICBRAINZ5_MEDIUM_H

#include <string>
#include <iostream>

#include "musicbrainz5/Entity.h"
#include "musicbrainz5/DiscList.h"
#include "musicbrainz5/TrackList.h"

#include "musicbrainz5/xmlParser.h"

namespace MusicBrainz5
{
	class CMediumPrivate;

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

		virtual std::ostream& Serialise(std::ostream& os) const;
		static std::string GetElementName();

	protected:
		virtual void ParseAttribute(const std::string& Name, const std::string& Value);
		virtual void ParseElement(const XMLNode& Node);

	private:
		void Cleanup();

		CMediumPrivate * const m_d;
	};
}

#endif
