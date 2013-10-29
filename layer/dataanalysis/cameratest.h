#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERATEST_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_CAMERATEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
class CameraTest :
		public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CameraTest);
	CPPUNIT_TEST(getColor_mockHardwareCamera_atLeastOneCallToGetFrame);
	CPPUNIT_TEST_SUITE_END();

private:
	void getColor_mockHardwareCamera_atLeastOneCallToGetFrame();
};
}
}
}

#endif
