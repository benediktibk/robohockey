#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ODOMETRYTEST_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ODOMETRYTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class OdometryTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(OdometryTest);
		CPPUNIT_TEST(setCurrentPosition_mockHardwareOdometry_atLeastOneCallToSetCurrentPosition);
		CPPUNIT_TEST(getCurrentPosition_mockHardwareOdometry_atLeastOneCallToGetCurrentPosition);
		CPPUNIT_TEST_SUITE_END();

	private:
		void setCurrentPosition_mockHardwareOdometry_atLeastOneCallToSetCurrentPosition();
		void getCurrentPosition_mockHardwareOdometry_atLeastOneCallToGetCurrentPosition();
	};
}
}
}

#endif
