package MusicBrainzClient;

BEGIN { require 5.003 }
use vars qw(@ISA @EXPORT);
@ISA    = @ISA    = '';
@EXPORT = @EXPORT = '';

use strict;
use LWP;
use HTTP::Request::Common;
use XML::Parser;
use XML::DOM;
use XML::XQL;
use XML::XQL::DOM;
use Unicode::String;

#use constant ServerName => "http://www.musicbrainz.org";
use constant ServerName => "http://musicbrainz.eorbit.net";
use constant ServerPort => 80;
use constant ServerURL =>  "/cgi-bin/cdi/rquery.pl";
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

sub _escape
{
  $_[0] =~ s/&/&amp;/g;  # & first of course
  $_[0] =~ s/</&lt;/g;
  $_[0] =~ s/>/&gt;/g;
  return $_[0];
}

sub _SubstituteArgs
{
    my ($query, @args) = @_;
    my ($arg, $replace, $i);

    for($i = 1; ; $i++)
    {
        $arg = shift @args;
        last if not defined $arg;

        $arg = _escape($arg);

        $replace = "\@$i\@";
        $query =~ s/$replace/$arg/;
    }
    return $query;
}

sub _SolveXQL
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

    if (defined $data)
    {
       my $u;
       $u = Unicode::String::utf8($data);
       $data = $u->latin1;
    }

    return $data;
}

sub _CheckReturnContent
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
    $value = _SolveXQL($doc, "/rdf:RDF/rdf:Description/MQ:Status");
    if (!defined $value)
    {
        $value = _SolveXQL($doc, "/rdf:RDF/rdf:Description/MQ:Error");
    }

    return ($value eq 'OK', $value);
}  

sub SubmitMetadata
{
    my ($m) = @_;
    my ($query, $ua, $url, $request, $ret, $status);

    $query = _SubstituteArgs(MB_SubmitTrack, 
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
       return _CheckReturnContent($ret->content);
    }
    else
    {
       return (0, $ret->status_line);  
    }
}

## Sample test driver
#my %data;
#my ($ret, $error);
#
#$data{title} = "Te\"t";
#$data{guid} = "";
#$data{artist} = "Blüm'hen";
#$data{album} = "Te\"st";
#$data{tracknum} = "1";
#$data{duration} = "";
#$data{size} = "";
#$data{genre} = "";
#$data{comment} = "";
#
#($ret, $error) = SubmitMetadata(\%data);
#if ($ret)
#{
#    print "Submission ok.\n";
#}
#else
#{
#    print "Submission failed: $error\n";
#}
