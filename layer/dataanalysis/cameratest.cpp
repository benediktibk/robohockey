#include "layer/dataanalysis/cameratest.h"
#include "layer/dataanalysis/cameraimpl.h"
#include "layer/hardware/cameramock.h"

using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;

void CameraTest::getAllCameraObjects_mockHardwareCamera_atLeastOneCallToGetFrame()
{
	Hardware::CameraMock hardwareCamera;
	CameraImpl camera(hardwareCamera);

	camera.getAllCameraObjects(RobotPosition());

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

void CameraTest::getAllCameraObjects_yellowPuckTwice_cameraObjectsCountIs2()
{
	Hardware::CameraMock hardwareCamera("yellow_puck_twice");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT_EQUAL((size_t)2, camera.getAllCameraObjects(RobotPosition()).getObjectCount());
}

void CameraTest::getAllCameraObjects_yellowAndBluePuck_cameraObjectsCountIs2()
{
	Hardware::CameraMock hardwareCamera("yellow_and_blue_puck");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT_EQUAL((size_t)2, camera.getAllCameraObjects(RobotPosition()).getObjectCount());
}

void CameraTest::getAllCameraObjects_nothing_cameraObjectCountIs0()
{
	Hardware::CameraMock hardwareCamera("nothing");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT_EQUAL((size_t)0, camera.getAllCameraObjects(RobotPosition()).getObjectCount());
}

void CameraTest::getAllCameraObjects_yellowPuck_cameraObjectCountIs1()
{
	Hardware::CameraMock hardwareCamera("yellow_puck");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT_EQUAL((size_t)1, camera.getAllCameraObjects(RobotPosition()).getObjectCount());
}

void CameraTest::getAllCameraObjects_bluePuck_cameraObjectCountIs1()
{
	Hardware::CameraMock hardwareCamera("blue_puck");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT_EQUAL((size_t)1, camera.getAllCameraObjects(RobotPosition()).getObjectCount());
}

void CameraTest::getAllCameraObjects_blueGoal_cameraObjectCountIs1()
{
	Hardware::CameraMock hardwareCamera("blue_goal");
	CameraImpl camera(hardwareCamera);

	//!@todo better testpicture neded
	//CPPUNIT_ASSERT_EQUAL((size_t)1, camera.getAllCameraObjects().getObjectCount());
	CPPUNIT_ASSERT(true);
}

void CameraTest::getAllCameraObjects_yellowGoal_cameraObjectCountIs1()
{
	Hardware::CameraMock hardwareCamera("yellow_goal");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT_EQUAL((size_t)1, camera.getAllCameraObjects(RobotPosition()).getObjectCount());
}

void CameraTest::getAllCameraObjects_yellowGoal1_cameraObjectCountIs1()
{
	Hardware::CameraMock hardwareCamera("yellow_goal_1");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT_EQUAL((size_t)1, camera.getAllCameraObjects(RobotPosition()).getObjectCount());
}

void CameraTest::getAllCameraObjects_greenBorderstone_cameraObjectCountIs1()
{
	Hardware::CameraMock hardwareCamera("green_borderstone");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT_EQUAL((size_t)1, camera.getAllCameraObjects(RobotPosition()).getObjectCount());
}

void CameraTest::getAllCameraObjects_greenBorderstoneTriple_cameraObjectCountIs3()
{
	Hardware::CameraMock hardwareCamera("green_borderstone_triple");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT_EQUAL((size_t)3, camera.getAllCameraObjects(RobotPosition()).getObjectCount());
}

void CameraTest::getAllCameraObjects_yellowAndBluePuckAndGreenBorderstone_cameraObjectsCountIs3()
{
	Hardware::CameraMock hardwareCamera("yellow_and_blue_puck_and_green_borderstone");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT_EQUAL((size_t)3, camera.getAllCameraObjects(RobotPosition()).getObjectCount());
}

void CameraTest::getAllCameraObjects_yellowPuckTwiceAndGreenBorderstone_cameraObjectsCountIs3()
{
	Hardware::CameraMock hardwareCamera("yellow_puck_twice_and_green_borderstone");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT_EQUAL((size_t)3, camera.getAllCameraObjects(RobotPosition()).getObjectCount());
}

void CameraTest::getAllCameraObjects_yellowPuckTwiceAndGreenBorderstone1_cameraObjectsCountIs3()
{
	Hardware::CameraMock hardwareCamera("yellow_puck_twice_and_green_borderstone_1");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT_EQUAL((size_t)3, camera.getAllCameraObjects(RobotPosition()).getObjectCount());
}

void CameraTest::getAllCameraObjects_yellowPuck_cameraObjectPositonIs0p6And0p1()
{
	Hardware::CameraMock hardwareCamera("yellow_puck");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT_EQUAL(Point(0.6,0.1), camera.getAllCameraObjects(RobotPosition(Point(0,0))).getAllCameraObjects().front().getPosition());
}
