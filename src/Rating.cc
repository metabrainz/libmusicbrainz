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

#include "musicbrainz4/Rating.h"

#include <sstream>

MusicBrainz4::CRating::CRating(const XMLNode& Node)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Rating node: " << std::endl << Node.createXMLString(true) << std::endl;

		if (Node.isAttributeSet("votes-count"))
		{
			std::stringstream os;
			os << Node.getAttribute("votes-count");
			os >> m_VotesCount;
		}

		if (Node.getText())
		{
			std::stringstream os;
			os << Node.getText();
			os >> m_Rating;
		}
	}
}

MusicBrainz4::CRating::CRating(const CRating& Other)
{
	*this=Other;
}

MusicBrainz4::CRating& MusicBrainz4::CRating::operator =(const CRating& Other)
{
	if (this!=&Other)
	{
		m_VotesCount=Other.m_VotesCount;
		m_Rating=Other.m_Rating;
	}

	return *this;
}

int MusicBrainz4::CRating::VotesCount() const
{
	return m_VotesCount;
}

double MusicBrainz4::CRating::Rating() const
{
	return m_Rating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CRating& Rating)
{
	os << "Rating:" << std::endl;

	os << "\tVotes count: " << Rating.VotesCount() << std::endl;
	os << "\tRating:      " << Rating.Rating() << std::endl;

	return os;
}
