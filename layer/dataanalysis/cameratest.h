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
		CPPUNIT_TEST(getAllCameraObjects_mockHardwareCamera_atLeastOneCallToGetFrame);
		CPPUNIT_TEST(isGoalYellow_yellowGoal_resultIsTrue);
		CPPUNIT_TEST(isGoalYellow_blueGoal_resultIsFalse);
		CPPUNIT_TEST(getAllCameraObjects_yellowPukTwice_cameraObjectsCountIs2);
		CPPUNIT_TEST_SUITE_END();

	private:
		void getAllCameraObjects_mockHardwareCamera_atLeastOneCallToGetFrame();
		void isGoalYellow_yellowGoal_resultIsTrue();
		void isGoalYellow_blueGoal_resultIsFalse();
		void getAllCameraObjects_yellowPukTwice_cameraObjectsCountIs2();
	};
}
}
}

#endif
