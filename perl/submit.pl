#!/usr/bin/perl -w

use MusicBrainzClient;

# Sample test driver
my %data;
my ($ret, $error);

$data{title} = "Test";
$data{guid} = "[test]";
$data{artist} = "Blümchen";
$data{album} = "Test";
$data{tracknum} = "1";
$data{duration} = "123";
$data{size} = "123";
$data{genre} = "genre";
$data{comment} = "comment";

($ret, $error) = MusicBrainzClient::SubmitMetadata(\%data);
if ($ret)
{
    print "Submission ok.\n";
}
else
{
    print "Submission failed: $error\n";
}
