#!/usr/bin/perl -w

use MusicBrainzClient;

# Sample test driver
my %data;
my ($ret, $error);

$data{title} = "Test";
$data{guid} = "";
$data{artist} = "Blümchen";
$data{album} = "Test";
$data{tracknum} = "1";
$data{duration} = "";
$data{size} = "";
$data{genre} = "";
$data{comment} = "";

($ret, $error) = MusicBrainzClient::SubmitMetadata(\%data);
if ($ret)
{
    print "Submission ok.\n";
}
else
{
    print "Submission failed: $error\n";
}
