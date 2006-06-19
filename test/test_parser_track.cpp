#include <fstream>
#include <string>
#include <iostream>
#include <cppunit/extensions/HelperMacros.h>
#include <musicbrainz3/mbxmlparser.h>
#include <musicbrainz3/metadata.h>
#include <musicbrainz3/model.h>

using namespace std;
using namespace MusicBrainz;

#include "read_file.h"

class ParseTrackTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ParseTrackTest);
	CPPUNIT_TEST(testTrackBasic);
	CPPUNIT_TEST(testTrackSearch);
	CPPUNIT_TEST_SUITE_END();
	
protected:

	void testTrackBasic()
	{
		Metadata *md = MbXmlParser().parse(get_file_contents("../test-data/valid/track/Silent_All_These_Years_1.xml"));
		Track *track = md->getTrack();
		
		CPPUNIT_ASSERT(track);
		CPPUNIT_ASSERT_EQUAL(string("http://musicbrainz.org/track/d6118046-407d-4e06-a1ba-49c399a4c42f"), track->getId());
		CPPUNIT_ASSERT_EQUAL(string("Silent All These Years"), track->getTitle());
		CPPUNIT_ASSERT_EQUAL(253466, track->getDuration());
	}
	
	void testTrackSearch()
	{
		Metadata *md = MbXmlParser().parse(get_file_contents("../test-data/valid/track/search_result_1.xml"));
		TrackResultList r = md->getTrackResults();
		
		CPPUNIT_ASSERT_EQUAL(3, int(r.size()));
		CPPUNIT_ASSERT_EQUAL(100, r[0]->getScore());
		CPPUNIT_ASSERT_EQUAL(99, r[1]->getScore());
		CPPUNIT_ASSERT_EQUAL(80, r[2]->getScore());
		CPPUNIT_ASSERT_EQUAL(string("http://musicbrainz.org/track/1954d2a1-d021-4426-b818-b5a5bce1ca07"), r[2]->getTrack()->getId());
	}
	
};

CPPUNIT_TEST_SUITE_REGISTRATION(ParseTrackTest); 

