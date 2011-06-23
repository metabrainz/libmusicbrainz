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

#include "musicbrainz4/UserRating.h"

#include <sstream>

MusicBrainz4::CUserRating::CUserRating(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "User rating node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.getText())
		{
			std::stringstream os;
			os << Node.getText();
			os >> m_UserRating;
		}
	}
}

MusicBrainz4::CUserRating::CUserRating(const CUserRating& Other)
{
	*this=Other;
}

MusicBrainz4::CUserRating& MusicBrainz4::CUserRating::operator =(const CUserRating& Other)
{
	if (this!=&Other)
	{
		m_UserRating=Other.m_UserRating;
	}

	return *this;
}

int MusicBrainz4::CUserRating::UserRating() const
{
	return m_UserRating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CUserRating& UserRating)
{
	os << "User rating:" << std::endl;

	os << "\tRating: " << UserRating.UserRating() << std::endl;

	return os;
}
