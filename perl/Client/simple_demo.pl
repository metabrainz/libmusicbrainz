#
# $Id$
#
use MusicBrainz::Client::Simple;
use strict;

my $mb = new MusicBrainz::Client::Simple->new( debug => 0, utf8 => 0 );

#
# For this query a CD in the CDROM drive is needed.
#
#my @result = $mb->lookup_cd;

#
# This query needs a CDIndexId as it's argument.
#
#my @result = $mb->lookup_by_cdindex('ejdrdtX1ZyvCb0g6vfJejVaLIK8-');
my @result = $mb->lookup_by_cdindex('kbOKXociW89enol.uRCowqenx7s-');

#
# Check if there was an error.
#
die "error: " . $mb->get_error unless $mb->success;


#
# Process the returned data.
# @result contains a list of MusicBrainz::Album instances.
#
foreach my $album ( @result ) {

	#
	# Print information about album and artist.
	#
	print $album->get_id, ' ', $album->get_name, "\n";

	printf "Status: %s\n", $album->get_status;
	printf "Type: %s\n", $album->get_type;

	printf "%s; %s; %s\n", $album->get_artist()->get_name(),
				$album->get_artist()->get_sortname(),
				$album->get_artist()->get_id();

	#
	# An album object contains a list of MusicBrainz::Client::Simple::Track objects.
	# Each track object contains a MusicBrainz::Client::Simple::Artist object, which
	# is necessary for 'Various Artists' albums.
	#
	foreach my $track ( $album->get_tracks() ) {

		printf "%2d. ", $track->get_num;

		if ( $album->has_various_artists ) {
			print $track->get_artist->get_name, ' - ';
		}

		printf "%s (%d)\n", $track->get_name, $track->get_duration;
	}
}


print "----------------\n";

my @artists = $mb->find_artist_by_name('Tori Amos');

foreach my $artist ( @artists ) {
	printf "%-35s %-40s\n", $artist->get_name, $artist->get_sortname;
}
