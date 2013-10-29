#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARTEST_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_LIDARTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
class LidarTest :
		public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(LidarTest);
	CPPUNIT_TEST(getAllObjects_mockHardwareLidar_atLeastOneCallToGetDistance);
	CPPUNIT_TEST_SUITE_END();

private:
	void getAllObjects_mockHardwareLidar_atLeastOneCallToGetDistance();
};
}
}
}

#endif
