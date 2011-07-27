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

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

#include "musicbrainz4/UserRating.h"

class MusicBrainz4::CUserRatingPrivate
{
	public:
		CUserRatingPrivate()
		:	m_UserRating(0)
		{
		}

		int m_UserRating;
};

MusicBrainz4::CUserRating::CUserRating(const XMLNode& Node)
:	CEntity(),
	m_d(new CUserRatingPrivate)
{
	if (!Node.isEmpty())
	{
		//std::cout << "User rating node: " << std::endl << Node.createXMLString(true) << std::endl;

		Parse(Node);

		if (Node.getText())
		{
			ProcessItem(Node,m_d->m_UserRating);
		}
	}
}

MusicBrainz4::CUserRating::CUserRating(const CUserRating& Other)
:	CEntity(),
	m_d(new CUserRatingPrivate)
{
	*this=Other;
}

MusicBrainz4::CUserRating& MusicBrainz4::CUserRating::operator =(const CUserRating& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_UserRating=Other.m_d->m_UserRating;
	}

	return *this;
}

MusicBrainz4::CUserRating::~CUserRating()
{
	delete m_d;
}

MusicBrainz4::CUserRating *MusicBrainz4::CUserRating::Clone()
{
	return new CUserRating(*this);
}

bool MusicBrainz4::CUserRating::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	bool RetVal=true;

	std::cerr << "Unrecognised userrating attribute: '" << Name << "'" << std::endl;
	RetVal=false;

	return RetVal;
}

bool MusicBrainz4::CUserRating::ParseElement(const XMLNode& Node)
{
	bool RetVal=true;

	std::string Name=Node.getName();

	std::cerr << "Unrecognised userrating element: '" << Name << "'" << std::endl;
	RetVal=false;

	return RetVal;
}

std::string MusicBrainz4::CUserRating::ElementName() const
{
	return "user-rating";
}

int MusicBrainz4::CUserRating::UserRating() const
{
	return m_d->m_UserRating;
}

std::ostream& operator << (std::ostream& os, const MusicBrainz4::CUserRating& UserRating)
{
	os << "User rating:" << std::endl;

	MusicBrainz4::CEntity *Base=(MusicBrainz4::CEntity *)&UserRating;

	os << *Base << std::endl;

	os << "\tRating: " << UserRating.UserRating() << std::endl;

	return os;
}
