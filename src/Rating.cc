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

#include "musicbrainz4/Rating.h"

class MusicBrainz4::CRatingPrivate
{
	public:
		CRatingPrivate()
		:	m_VotesCount(0),
			m_Rating(0.0)
		{
		}

		int m_VotesCount;
		double m_Rating;
};

MusicBrainz4::CRating::CRating(const XMLNode& Node)
:	CEntity(),
	m_d(new CRatingPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "Rating node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);

		if (Node.getText())
		{
			ProcessItem(Node,m_d->m_Rating);
		}
	}
}

MusicBrainz4::CRating::CRating(const CRating& Other)
:	CEntity(),
	m_d(new CRatingPrivate)
{
	*this=Other;
}

MusicBrainz4::CRating& MusicBrainz4::CRating::operator =(const CRating& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_VotesCount=Other.m_d->m_VotesCount;
		m_d->m_Rating=Other.m_d->m_Rating;
	}

	return *this;
}

MusicBrainz4::CRating::~CRating()
{
	delete m_d;
}

MusicBrainz4::CRating *MusicBrainz4::CRating::Clone()
{
	return new CRating(*this);
}

bool MusicBrainz4::CRating::ParseAttribute(const std::string& Name, const std::string& Value)
{
	bool RetVal=true;

	if ("votes-count"==Name)
	{
		RetVal=ProcessItem(Value,m_d->m_VotesCount);
	}
	else
	{
		std::cerr << "Unrecognised rating attribute: '" << Name << "'" << std::endl;
		RetVal=false;
	}

	return RetVal;
}

bool MusicBrainz4::CRating::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string NodeName=Node.getName();

	std::cerr << "Unrecognised rating attribute: '" << NodeName << "'" << std::endl;
	RetVal=false;

	return RetVal;
}

std::string MusicBrainz4::CRating::ElementName() const
{
	return "rating";
}

int MusicBrainz4::CRating::VotesCount() const
{
	return m_d->m_VotesCount;
}

double MusicBrainz4::CRating::Rating() const
{
	return m_d->m_Rating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CRating& Rating)
{
	os << "Rating:" << std::endl;

	MusicBrainz4::CEntity *Base=(MusicBrainz4::CEntity *)&Rating;

	os << *Base << std::endl;

	os << "\tVotes count: " << Rating.VotesCount() << std::endl;
	os << "\tRating:      " << Rating.Rating() << std::endl;

	return os;
}
