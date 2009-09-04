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

class ParseLabelTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ParseLabelTest);
	CPPUNIT_TEST(testLabelBasic);
	CPPUNIT_TEST(testSearchResults);
	CPPUNIT_TEST_SUITE_END();
	
protected:

	void testLabelBasic()
	{
		Metadata *md = MbXmlParser().parse(
			get_file_contents("../test-data/valid/label/Atlantic_Records_1.xml")
			);
		Label *label = md->getLabel();
		
		CPPUNIT_ASSERT(label);
		CPPUNIT_ASSERT_EQUAL(string("http://musicbrainz.org/label/50c384a2-0b44-401b-b893-8181173339c7"), label->getId());
		CPPUNIT_ASSERT_EQUAL(string("Atlantic Records"), label->getName());
		CPPUNIT_ASSERT_EQUAL(string("1947"), label->getBeginDate());
		CPPUNIT_ASSERT_EQUAL(0, int(label->getReleases().size()));
		CPPUNIT_ASSERT_EQUAL(121, label->getCode());
	}

	void testSearchResults()
	{
		Metadata *md = MbXmlParser().parse(get_file_contents("../test-data/valid/label/search_result_1.xml"));
		LabelResultList &results = md->getLabelResults();
		CPPUNIT_ASSERT_EQUAL(2, int(results.size()));
		CPPUNIT_ASSERT_EQUAL(100, results[0]->getScore());
		CPPUNIT_ASSERT_EQUAL(string("Atlantic Records"), results[0]->getLabel()->getName());
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION(ParseLabelTest); 

