#!/usr/bin/perl -w

use MusicBrainzClient;
use strict;

my ($ret, $ref, @data);

if (scalar(@ARGV) < 2)
{
    print "Usage: findalbum.pl <albumname> <artistname>\n";
    exit(0);
}

($ret, @data) = MusicBrainzClient::FindAlbum(shift, shift);
if ($ret)
{
    print "Query ok: " . scalar(@data) . " items returned:\n\n";
    foreach $ref (@data)
    {
        print "   Album: $$ref[0]\n";
        print "  Artist: $$ref[2]\n";
        print " AlbumID: $$ref[1]\n";
        print "ArtistID: $$ref[3]\n\n";
    }
}
else
{
    print "Query failed: $data[0]\n";
}
