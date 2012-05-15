/* --------------------------------------------------------------------------

   libmusicbrainz5 - Client library to access MusicBrainz

   Copyright (C) 2012 Andrew Hawkins

   This file is part of libmusicbrainz5.

   This library is free software; you can redistribute it and/or
   modify it under the terms of v2 of the GNU Lesser General Public
   License as published by the Free Software Foundation.

   libmusicbrainz5 is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.

     $Id$

----------------------------------------------------------------------------*/

Mb5MediumList mb5_release_media_matching_discid(Mb5Release Release, const char *DiscID)
{
	if (Release)
	{
		MusicBrainz5::CRelease *TheRelease=reinterpret_cast<MusicBrainz5::CRelease *>(Release);
		if (TheRelease)
			return new MusicBrainz5::CMediumList(TheRelease->MediaMatchingDiscID(DiscID));
	}

	return 0;
}

