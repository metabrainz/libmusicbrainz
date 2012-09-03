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

unsigned char mb5_medium_contains_discid(Mb5Medium Medium, const char *DiscID)
{
	unsigned char Ret=0;

	if (Medium)
	{
		MusicBrainz5::CMedium *TheMedium=reinterpret_cast<MusicBrainz5::CMedium *>(Medium);
		if (TheMedium)
			Ret=TheMedium->ContainsDiscID(DiscID);
	}

	return Ret;
}
