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

Mb4MediumList mb4_release_media_matching_discid(Mb4Release Release, const char *DiscID)
{
	if (Release)
	{
		MusicBrainz4::CRelease *TheRelease=reinterpret_cast<MusicBrainz4::CRelease *>(Release);
		if (TheRelease)
			return new MusicBrainz4::CMediumList(TheRelease->MediaMatchingDiscID(DiscID));
	}

	return 0;
}

