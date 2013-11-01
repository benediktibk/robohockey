#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAROBJECTSTEST_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDAROBJECTSTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class LidarObjectsTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(LidarObjectsTest);
		CPPUNIT_TEST(addObject_onceCalled_objectCountIs1);
		CPPUNIT_TEST(getObjectsWithDistanceBelow_twoObjectsBelowAndOneNot_resultSizeIs2);
		CPPUNIT_TEST_SUITE_END();

	private:
		void addObject_onceCalled_objectCountIs1();
		void getObjectsWithDistanceBelow_twoObjectsBelowAndOneNot_resultSizeIs2();
	};
}
}
}

#endif
