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
    <rdf:Description>
\;
use constant RDFFooter =>
  q\</rdf:Description>
    </rdf:RDF>
\;

use constant MB_SubmitTrack =>
     q\<MQ:Query>SubmitTrack</MQ:Query>
       <DC:Title>@1@</DC:Title>
       <DC:Identifier guid="@2@"/>
       <DC:Creator>@3@</DC:Creator>
       <DC:Relation>
          <rdf:Description>
             <DC:Title>@4@</DC:Title>
          </rdf:Description>
       </DC:Relation>
       <MM:TrackNum>@5@</MM:TrackNum>
       <DC:Format duration="@6@"/>
       <DC:Date issued="@7@"/>
       <MM:Genre>@8@</MM:Genre>
       <DC:Description>@9@</DC:Description>
\;
use constant MB_FindArtistByName =>     
     q\<MQ:Query>FindArtistByName</MQ:Query>
       <MQ:Args artist="@1@"/>
\;
use constant MB_FindAlbumByName =>
     q\<MQ:Query>FindAlbumByName</MQ:Query>
       <MQ:Args album="@1@" artist="@2@"/>
\;
use constant MB_FindTrackByName =>
     q\<MQ:Query>FindTrackByName</MQ:Query>
       <MQ:Args album="@3@" artist="@2@" track="@1@"/>
\;

use constant MB_GetArtistName => 'DC:Creator';
use constant MB_GetArtistID   => 'DC:Identifier/@artistId';

use constant MB_GetAlbumName  => 'DC:Relation/rdf:Description/DC:Title';
use constant MB_GetAlbumID    => 'DC:Relation/rdf:Description/DC:Identifier/@albumId';

use constant MB_GetTrackID    => 'DC:Identifier/@trackId';
use constant MB_GetTrackNum   => 'DC:Relation/@track';
use constant MB_GetTrackName  => 'DC:Title';

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

    #print "xql: $xql\n";
    @result = XML::XQL::solve ($xql, $doc);
    $node = $result[0];

    if (defined $node)
    {
        if ($node->getNodeType == XML::DOM::ELEMENT_NODE)
        {
            $data = $node->getFirstChild->getData
                if (defined $node->getFirstChild);
            #print "Query got element: $data\n";
        }
        elsif ($node->getNodeType == XML::DOM::ATTRIBUTE_NODE)
        {
            $data = $node->getValue
                if (defined $node->getNodeType);
            #print "Query got attr: $data\n";
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

    return (0, $value) if ($value ne 'OK');
    return (1, $doc);
}  

sub _Query
{
    my ($query) = @_;
    my ($ua, $url, $request, $ret, $status);

    #print "$query\n";
    $url = ServerName . ":" . ServerPort . ServerURL;
    $request = new HTTP::Request POST => $url;
    $request->content($query);
    $ua = LWP::UserAgent->new;
    $ret = $ua->request($request);
    if ($ret->is_success)
    {
       #print $ret->content . "\n";
       return _CheckReturnContent($ret->content);
    }
    else
    {
       return (0, $ret->status_line);  
    }
}

sub _ParseData
{
    my ($doc, @args) = @_;
    my ($i, $j, $max, @data, @ret, $context);

    $max = scalar(@args);
    for($i = 0;; $i++)
    {
        $context = "/rdf:RDF/rdf:Description/MC:Collection/rdf:Bag/rdf:li[$i]/rdf:Description/";
        for($j = 0; $j < $max; $j++)
        {
            $data[$j] = _SolveXQL($doc, $context . $args[$j]); 
            return @ret if (!defined $data[$j] || $data[$j] eq '');
        }
        push @ret, [@data];
    }

    return @ret;
}

sub SubmitMetadata
{
    my ($m) = @_;
    my ($query);

    $query = _SubstituteArgs(MB_SubmitTrack, 
                $m->{title}, $m->{guid}, $m->{artist}, $m->{album},
                $m->{tracknum}, $m->{duration}, $m->{size}, 
                $m->{genre}, $m->{comment});
    $query = RDFHeader . $query . RDFFooter;

    return _Query($query);
}

sub FindArtist
{
    my ($artist) = @_;
    my ($ret, $doc, $query); 

    $query = _SubstituteArgs(MB_FindArtistByName, $artist);
    $query = RDFHeader . $query . RDFFooter;
    ($ret, $doc) = _Query($query);
    if ($ret)
    {
        return ($ret, _ParseData($doc, MB_GetArtistName, MB_GetArtistID));
    }

    return ($ret, $doc);;
}

sub FindAlbum
{
    my ($album, $artist) = @_;
    my ($ret, $doc, $query); 

    $query = _SubstituteArgs(MB_FindAlbumByName, $album, $artist);
    $query = RDFHeader . $query . RDFFooter;
    ($ret, $doc) = _Query($query);
    if ($ret)
    {
        return ($ret, _ParseData($doc, 
                                 MB_GetAlbumName, 
                                 MB_GetAlbumID, 
                                 MB_GetArtistName, 
                                 MB_GetArtistID));
    }

    return ($ret, $doc);;
}

sub FindTrack
{
    my ($album, $artist, $track) = @_;
    my ($ret, $doc, $query); 

    $query = _SubstituteArgs(MB_FindTrackByName, $album, $artist, $track);
    $query = RDFHeader . $query . RDFFooter;
    ($ret, $doc) = _Query($query);
    if ($ret)
    {
        return ($ret, _ParseData($doc, 
                                 MB_GetTrackName, 
                                 MB_GetTrackNum, 
                                 MB_GetTrackID, 
                                 MB_GetAlbumName, 
                                 MB_GetAlbumID, 
                                 MB_GetArtistName, 
                                 MB_GetArtistID));
    }

    return ($ret, $doc);;
}
