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

#ifndef _MUSICBRAINZ4_LABEL_INFO_H
#define _MUSICBRAINZ4_LABEL_INFO_H

#include <string>
#include <iostream>

#include "musicbrainz4/Entity.h"

#include "musicbrainz4/xmlParser.h"

namespace MusicBrainz4
{
	class CLabelInfoPrivate;

	class CLabel;

	class CLabelInfo: public CEntity
	{
	public:
		CLabelInfo(const XMLNode& Node=XMLNode::emptyNode());
		CLabelInfo(const CLabelInfo& Other);
		CLabelInfo& operator =(const CLabelInfo& Other);
		virtual ~CLabelInfo();

		virtual CLabelInfo *Clone();

		std::string CatalogNumber() const;
		CLabel *Label() const;

		virtual std::string ElementName() const;

	protected:
		virtual bool ParseAttribute(const std::string& Name, const std::string& Value);
		virtual bool ParseElement(const XMLNode& Node);

	private:
		void Cleanup();

		CLabelInfoPrivate * const m_d;
	};
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CLabelInfo& LabelInfo);

#endif

