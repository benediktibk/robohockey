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
		CPPUNIT_TEST(getAllCameraObjects_yellowPuckTwice_cameraObjectsCountIs2);
		CPPUNIT_TEST(getAllCameraObjects_yellowAndBluePuck_cameraObjectsCountIs2);
		CPPUNIT_TEST(getAllCameraObjects_nothing_cameraObjectCountIs0);
		CPPUNIT_TEST(getAllCameraObjects_yellowPuck_cameraObjectCountIs1);
		CPPUNIT_TEST(getAllCameraObjects_bluePuck_cameraObjectCountIs1);
		CPPUNIT_TEST(getAllCameraObjects_blueGoal_cameraObjectCountIs1);
		CPPUNIT_TEST(getAllCameraObjects_yellowGoal_cameraObjectCountIs1);
		CPPUNIT_TEST(getAllCameraObjects_yellowGoal1_cameraObjectCountIs1);
		CPPUNIT_TEST(getAllCameraObjects_greenBorderstone_cameraObjectCountIs1);
		CPPUNIT_TEST(getAllCameraObjects_greenBorderstoneTriple_cameraObjectCountIs3);
		CPPUNIT_TEST(getAllCameraObjects_yellowAndBluePuckAndGreenBorderstone_cameraObjectsCountIs3);
		CPPUNIT_TEST(getAllCameraObjects_yellowPuckTwiceAndGreenBorderstone_cameraObjectsCountIs3);
		CPPUNIT_TEST(getAllCameraObjects_yellowPuckTwiceAndGreenBorderstone1_cameraObjectsCountIs3);
		CPPUNIT_TEST_SUITE_END();

	private:
		void getAllCameraObjects_mockHardwareCamera_atLeastOneCallToGetFrame();
		void isGoalYellow_yellowGoal_resultIsTrue();
		void isGoalYellow_blueGoal_resultIsFalse();
		void getAllCameraObjects_yellowPuckTwice_cameraObjectsCountIs2();
		void getAllCameraObjects_yellowAndBluePuck_cameraObjectsCountIs2();
		void getAllCameraObjects_nothing_cameraObjectCountIs0();
		void getAllCameraObjects_yellowPuck_cameraObjectCountIs1();
		void getAllCameraObjects_bluePuck_cameraObjectCountIs1();
		void getAllCameraObjects_blueGoal_cameraObjectCountIs1();
		void getAllCameraObjects_yellowGoal_cameraObjectCountIs1();
		void getAllCameraObjects_yellowGoal1_cameraObjectCountIs1();
		void getAllCameraObjects_greenBorderstone_cameraObjectCountIs1();
		void getAllCameraObjects_greenBorderstoneTriple_cameraObjectCountIs3();
		void getAllCameraObjects_yellowAndBluePuckAndGreenBorderstone_cameraObjectsCountIs3();
		void getAllCameraObjects_yellowPuckTwiceAndGreenBorderstone_cameraObjectsCountIs3();
		void getAllCameraObjects_yellowPuckTwiceAndGreenBorderstone1_cameraObjectsCountIs3();

	};
}
}
}

#endif
