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

class ParseArtistTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ParseArtistTest);
	CPPUNIT_TEST(testArtistBasic);
	CPPUNIT_TEST_SUITE_END();
	
protected:

	void testArtistBasic()
	{
		Metadata *md = MbXmlParser().parse(get_file_contents("../test-data/valid/artist/Tori_Amos_1.xml"));
		Artist *artist = md->getArtist();
		
		CPPUNIT_ASSERT(artist);
		CPPUNIT_ASSERT_EQUAL(artist->getId(), string("c0b2500e-0cef-4130-869d-732b23ed9df5"));
		CPPUNIT_ASSERT_EQUAL(artist->getName(), string("Tori Amos"));
		CPPUNIT_ASSERT_EQUAL(artist->getSortName(), string("Amos, Tori"));
		CPPUNIT_ASSERT_EQUAL(artist->getBeginDate(), string("1963-08-22"));
		CPPUNIT_ASSERT_EQUAL(int(artist->getReleases().size()), 0);
	}
	
};

CPPUNIT_TEST_SUITE_REGISTRATION(ParseArtistTest); 

