#!/usr/bin/perl -w

use strict;
use LWP;
use HTTP::Request::Common;
use XML::Parser;
use XML::DOM;
use XML::XQL;
use XML::XQL::DOM;

use constant ServerName => "http://musicbrainz.eorbit.net";
use constant ServerPort => 80;
use constant ServerURL =>  "/cgi-bin/rquery.pl";
use constant RDFHeader =>
  q\<?xml version="1.0" encoding="ISO-8859-1"?>
    <rdf:RDF xmlns = "http://w3.org/TR/1999/PR-rdf-syntax-19990105#"
             xmlns:DC = "http://purl.org/DC#"
             xmlns:MM = "http://musicbrainz.org/MM#"
             xmlns:MQ = "http://musicbrainz.org/MQ#">
    <rdf:Description>\;
use constant RDFFooter =>
  q\</rdf:Description>
    </rdf:RDF>
   \;

use constant MB_SubmitTrack =>
     q\<MQ:Query>SubmitTrack</MQ:Query>
       <DC:Title>@1@</DC:Title>
       <DC:Identifier guid="@2@"/>
       <DC:Creator>@3@</DC:Creator>
       <MM:Album>@4@</MM:Album>
       <DC:Relation track="@5@"/>
       <DC:Format duration="@6@"/>
       <DC:Date issued="@7@"/>
       <MM:Genre>@8@</MM:Genre>
       <DC:Description>@9@</DC:Description>\;

sub SubstituteArgs
{
    my ($query, @args) = @_;
    my ($arg, $replace, $i);

    for($i = 1; ; $i++)
    {
        $arg = shift @args;
        last if not defined $arg;

        $replace = "\@$i\@";
        $query =~ s/$replace/$arg/;
    }
    return $query;
}

sub SolveXQL
{
    my ($doc, $xql) = @_;
    my ($data, $node, @result);

    @result = XML::XQL::solve ($xql, $doc);
    $node = $result[0];

    if (defined $node)
    {
        if ($node->getNodeType == XML::DOM::ELEMENT_NODE)
        {
            $data = $node->getFirstChild->getData
                if (defined $node->getFirstChild);
        }
        elsif ($node->getNodeType == XML::DOM::ATTRIBUTE_NODE)
        {
            $data = $node->getValue
                if (defined $node->getNodeType);
        }
    }

    return $data;
}

sub CheckReturnContent
{
    my ($xml) = @_;
    my ($parser, $doc, $value, $len);

    if ($xml =~ m/^Content-Length: (\d+)$/m)
    {
       $len = $1;
       $xml = substr($xml, length($xml) - $len);
    }
    $parser = new XML::DOM::Parser;
    eval
    {
        $doc = $parser->parse($xml);
    };
    if ($@)
    {
        return (0, "Server resonse parse failed: $@");
    }
    $value = SolveXQL($doc, "/rdf:RDF/rdf:Description/MQ:Status");
    if (!defined $value)
    {
        $value = SolveXQL($doc, "/rdf:RDF/rdf:Description/MQ:Error");
    }

    return ($value eq 'OK', $value);
}  

sub SubmitMetadata
{
    my ($m) = @_;
    my ($query, $ua, $url, $request, $ret, $status);

    $query = SubstituteArgs(MB_SubmitTrack, 
                $m->{title}, $m->{guid}, $m->{artist}, $m->{album},
                $m->{tracknum}, $m->{duration}, $m->{size}, 
                $m->{genre}, $m->{comment});
    $query = RDFHeader . $query . RDFFooter;

    $url = ServerName . ":" . ServerPort . ServerURL;
    $request = new HTTP::Request POST => $url;
    $request->content($query);
    $ua = LWP::UserAgent->new;
    $ret = $ua->request($request);
    if ($ret->is_success)
    {
       return CheckReturnContent($ret->content);
    }
    else
    {
       return (0, "HTTP POST failed");  
    }
}

# Sample test driver
my %data;
my ($ret, $error);

$data{title} = "title";
$data{guid} = "guid";
$data{artist} = "artist";
$data{album} = "album";
$data{tracknum} = "69";
$data{duration} = "duration";
$data{size} = "size";
$data{genre} = "genre";
$data{comment} = "comment";

($ret, $error) = SubmitMetadata(\%data);
if ($ret)
{
    print "Submission ok.\n";
}
else
{
    print "Submission failed: $error\n";
}
