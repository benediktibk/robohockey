#include "layer/dataanalysis/cameratest.h"
#include "layer/dataanalysis/cameraimpl.h"
#include "layer/hardware/cameramock.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

void CameraTest::getAllCameraObjects_mockHardwareCamera_atLeastOneCallToGetFrame()
{
	Hardware::CameraMock hardwareCamera;
	CameraImpl camera(hardwareCamera);

	camera.getAllCameraObjects();

	CPPUNIT_ASSERT(hardwareCamera.getCallsToGetFrame() > 0);
}

void CameraTest::isGoalYellow_yellowGoal_resultIsTrue()
{
	Hardware::CameraMock hardwareCamera("yellow_goal");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT(camera.isGoalYellow());
}

void CameraTest::isGoalYellow_blueGoal_resultIsFalse()
{
	Hardware::CameraMock hardwareCamera("blue_goal");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT(!camera.isGoalYellow());
}

void CameraTest::getAllCameraObjects_yellowPukTwice_cameraObjectsCountIs2()
{
	Hardware::CameraMock hardwareCamera("yellow_puck_twice");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT_EQUAL((size_t)2, camera.getAllCameraObjects().getObjectCount());
}
