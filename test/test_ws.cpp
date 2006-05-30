#include <vector>
#include <algorithm>
#include <cppunit/extensions/HelperMacros.h>
#include <musicbrainz3/filters.h>
#include <musicbrainz3/webservice.h>
#include <musicbrainz3/query.h>

using namespace std;
using namespace MusicBrainz;

#ifdef BUILD_WS_TESTS

class WebServiceTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(WebServiceTest);
	CPPUNIT_TEST(testGetArtistById);
	CPPUNIT_TEST(testGetUserByName);
	CPPUNIT_TEST_SUITE_END();
	
protected:

	void testGetArtistById()
	{
		WebService::init();
		WebService ws("test.musicbrainz.org");
		Query q(&ws, "test-1");
		Artist *a = q.getArtistById("72c536dc-7137-4477-a521-567eeb840fa8");
		CPPUNIT_ASSERT(a != NULL);
		CPPUNIT_ASSERT_EQUAL(string("Bob Dylan"), a->getName());
		WebService::cleanup();
	}
		
	void testGetUserByName()
	{
		WebService::init();
		WebService ws("test.musicbrainz.org", 80, "/ws", "libmb_test", "libmb_test");
		Query q(&ws, "test-1");
		User *a = q.getUserByName("libmb_test");
		CPPUNIT_ASSERT(a != NULL);
		CPPUNIT_ASSERT_EQUAL(string("libmb_test"), a->getName());
		WebService::cleanup();
	}
		
};

CPPUNIT_TEST_SUITE_REGISTRATION(WebServiceTest); 

#endif
