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

#include "config.h"
#include "musicbrainz5/defines.h"

#include "musicbrainz5/UserRating.h"

class MusicBrainz5::CUserRatingPrivate
{
	public:
		CUserRatingPrivate()
		:	m_UserRating(0)
		{
		}

		int m_UserRating;
};

MusicBrainz5::CUserRating::CUserRating(const XMLNode& Node)
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

MusicBrainz5::CUserRating::CUserRating(const CUserRating& Other)
:	CEntity(),
	m_d(new CUserRatingPrivate)
{
	*this=Other;
}

MusicBrainz5::CUserRating& MusicBrainz5::CUserRating::operator =(const CUserRating& Other)
{
	if (this!=&Other)
	{
		CEntity::operator =(Other);

		m_d->m_UserRating=Other.m_d->m_UserRating;
	}

	return *this;
}

MusicBrainz5::CUserRating::~CUserRating()
{
	delete m_d;
}

MusicBrainz5::CUserRating *MusicBrainz5::CUserRating::Clone()
{
	return new CUserRating(*this);
}

void MusicBrainz5::CUserRating::ParseAttribute(const std::string& Name, const std::string& /*Value*/)
{
	std::cerr << "Unrecognised userrating attribute: '" << Name << "'" << std::endl;
}

void MusicBrainz5::CUserRating::ParseElement(const XMLNode& Node)
{
	std::string Name=Node.getName();

	std::cerr << "Unrecognised userrating element: '" << Name << "'" << std::endl;
}

std::string MusicBrainz5::CUserRating::GetElementName()
{
	return "user-rating";
}

int MusicBrainz5::CUserRating::UserRating() const
{
	return m_d->m_UserRating;
}

std::ostream& MusicBrainz5::CUserRating::Serialise(std::ostream& os) const
{
	os << "User rating:" << std::endl;

	CEntity::Serialise(os);

	os << "\tRating: " << UserRating() << std::endl;

	return os;
}
