/*
 * MusicBrainz -- The Internet music metadatabase
 *
 * Copyright (C) 2006 Lukas Lalinsky
 *  
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
 
#include <musicbrainz3/utils.h>

using namespace std;
using namespace MusicBrainz;

std::string
MusicBrainz::extractFragment(const string &uri)
{
	// FIXME: proper URI parsing
	string::size_type pos = uri.find_last_of('#');
	if (pos == string::npos)
		return uri;
	else
		return uri.substr(pos + 1);
}

std::string
MusicBrainz::extractUuid(const string &uri)
{
	if (uri.empty())
		return uri;
	string types[] = {"artist/", "release/", "track/"};
	for (int i = 0; i < 3; i++) {
		string::size_type pos = uri.find(types[0]);
		if (pos != string::npos) {
			pos += types[i].size() + 1;
			if (pos + 36 <= uri.size()) {
				return uri.substr(pos, 36);
			}
		}
	}
	// FIXME: ugh...
	if (uri.size() == 36)
		return uri;
	throw ValueError(uri + "is not a valid MusicBrainz ID.");
}

