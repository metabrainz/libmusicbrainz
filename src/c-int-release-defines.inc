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

/**
 * @see MusicBrainz5::CRelease::MediaMatchingDiscID
 *
 * @param Release #Mb5Release object
 * @param DiscID DiscID to match
 *
 * @return #Mb5MediumList.  This object <b>must</b> be deleted once
 *				finished with.
 */
	Mb5MediumList mb5_release_media_matching_discid(Mb5Release Release, const char *DiscID);

