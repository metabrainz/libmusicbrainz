#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <musicbrainz3/model.h>
#include <musicbrainz3/mb_c.h>

using namespace std;
using namespace MusicBrainz;

class MBCTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(MBCTest);
	CPPUNIT_TEST(testReleaseEvent);
	CPPUNIT_TEST_SUITE_END();
	
protected:

	void testReleaseEvent()
	{
		ReleaseEvent re;
		re.setCatalogNumber("ABC-123");
		re.setBarcode("0123456");
		Label *label = new Label;
		re.setLabel(label);
		char str[256];
		mb_release_event_get_catalog_number((MbReleaseEvent)(&re), str, 256);
		CPPUNIT_ASSERT_EQUAL(string("ABC-123"), string(str));
		mb_release_event_get_barcode((MbReleaseEvent)(&re), str, 256);
		CPPUNIT_ASSERT_EQUAL(string("0123456"), string(str));
		MbLabel clabel = mb_release_event_get_label((MbReleaseEvent)(&re));
		CPPUNIT_ASSERT_EQUAL((MbLabel)(label), clabel);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(MBCTest); 

