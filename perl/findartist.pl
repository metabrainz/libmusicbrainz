#!/usr/bin/perl -w

use MusicBrainzClient;
use strict;

my ($ret, $ref, @data);

if (scalar(@ARGV) < 1)
{
    print "Usage: findartist.pl <artistname>\n";
    exit(0);
}

($ret, @data) = MusicBrainzClient::FindArtist(shift);
if ($ret)
{
    print "Query ok: " . scalar(@data) . " items returned:\n\n";
    foreach $ref (@data)
    {
        print "  Artist: $$ref[0]\nArtistID: $$ref[1]\n\n";
    }
}
else
{
    print "Query failed: $data[0]\n";
}
