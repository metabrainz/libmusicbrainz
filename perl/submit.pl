#!/usr/bin/perl -w

use MusicBrainzClient;

# Sample test driver
my %data;
my ($ret, $error);

$data{title} = "Te\"t";
$data{guid} = "";
$data{artist} = "Blüm'hen";
$data{album} = "Te\"st";
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
