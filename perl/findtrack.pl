#!/usr/bin/perl -w

use MusicBrainzClient;
use strict;

my ($ret, $ref, @data);

if (scalar(@ARGV) < 3)
{
    print "Usage: findtrack.pl <trackname> <artistname> [albumname]\n";
    print "To not specify an albumname, just enter \"\" on the command line.\n";
    exit(0);
}

($ret, @data) = MusicBrainzClient::FindTrack(shift, shift, shift);
if ($ret)
{
    print "Query ok: " . scalar(@data) . " items returned:\n";
    foreach $ref (@data)
    {
        print "   Track: $$ref[0]\n";
        print "     Num: $$ref[1]\n";
        print "   Album: $$ref[3]\n";
        print "  Artist: $$ref[5]\n";
        print " TrackID: $$ref[2]\n";
        print " AlbumID: $$ref[4]\n";
        print "ArtistID: $$ref[6]\n\n";
    }
}
else
{
    print "Query failed: $data[0]\n";
}
