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
 
#include <musicbrainz3/results.h>

using namespace MusicBrainz;

Result::Result(int score)
	: score(score)
{
}

int
Result::getScore()
{
	return score;
}

void
Result::setScore(int value)
{
	score = value;
}

ArtistResult::ArtistResult(Artist *artist, int score)
	: Result(score), artist(artist)
{
}

Artist *
ArtistResult::getArtist()
{
	return artist;
}

void
ArtistResult::setArtist(Artist *value)
{
	artist = value;
}

ReleaseResult::ReleaseResult(Release *release, int score)
	: Result(score), release(release)
{
}

Release *
ReleaseResult::getRelease()
{
	return release;
}

void
ReleaseResult::setRelease(Release *value)
{
	release = value;
}

TrackResult::TrackResult(Track *track, int score)
	: Result(score), track(track)
{
}

Track *
TrackResult::getTrack()
{
	return track;
}

void
TrackResult::setTrack(Track *value)
{
	track = value;
}

