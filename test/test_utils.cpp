#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <musicbrainz3/utils.h>

using namespace std;
using namespace MusicBrainz;

class UtilsTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(UtilsTest);
	CPPUNIT_TEST(testExtractUuid);
	CPPUNIT_TEST_SUITE_END();
	
protected:

	void testExtractUuid()
	{
		string artistPrefix = "http://musicbrainz.org/artist/";
		string uuid = "c0b2500e-0cef-4130-869d-732b23ed9df5";
		string mbid = artistPrefix + uuid;
		CPPUNIT_ASSERT_EQUAL(string(), extractUuid(string()));
		CPPUNIT_ASSERT_EQUAL(uuid, extractUuid(uuid));
		CPPUNIT_ASSERT_EQUAL(uuid, extractUuid(mbid));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(UtilsTest); 

