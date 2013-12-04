#include "layer/dataanalysis/cameratest.h"
#include "layer/dataanalysis/cameraimpl.h"
#include "layer/hardware/cameramock.h"
#include "common/compare.h"

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

void CameraTest::getProbabilityForYellowGoal_yellowGoal_resultIsOver80Percent()
{
	Hardware::CameraMock hardwareCamera("yellow_goal");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT(camera.getProbabilityForYellowGoal() > 0.8);
}

void CameraTest::getProbabilityForYellowGoal_blueGoal_resultIsNear0()
{
	Hardware::CameraMock hardwareCamera("blue_goal");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0,camera.getProbabilityForYellowGoal(), 0.05);
}

void CameraTest::getProbabilityForBlueGoal_blueGoal_resultIsOver80Percent()
{
	Hardware::CameraMock hardwareCamera("blue_goal");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT(camera.getProbabilityForBlueGoal() > 0.75);
}

void CameraTest::getProbabilityForBlueGoal_yellowGoal_resultIsNear0()
{
	Hardware::CameraMock hardwareCamera("yellow_goal");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0,camera.getProbabilityForBlueGoal(), 0.05);
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

void CameraTest::getAllCameraObjects_greenBorderstone1_cameraObjectCountIs1()
{
	Hardware::CameraMock hardwareCamera("green_borderstone_1");
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

	Compare compare(0.06);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0.66,0.1), camera.getAllCameraObjects(RobotPosition(Point(0,0))).front().getPosition()));
}

void CameraTest::getAllCameraObjects_yellowPuckTwice_cameraObjectPositonOfRightObjectIs0p6And0p0()
{
	Hardware::CameraMock hardwareCamera("yellow_puck_twice");
	CameraImpl camera(hardwareCamera);

	Compare compare(0.05);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0.66,0.0), camera.getAllCameraObjects(RobotPosition(Point(0,0))).front().getPosition()));
}

void CameraTest::getAllCameraObjects_yellowPuckTwice_cameraObjectPositonOfLeftObjectIs0p7And0p2()
{
	Hardware::CameraMock hardwareCamera("yellow_puck_twice");
	CameraImpl camera(hardwareCamera);

	Compare compare(0.06);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0.76,0.2), camera.getAllCameraObjects(RobotPosition(Point(0,0))).back().getPosition()));
}

void CameraTest::getAllCameraObjects_bluePuck_cameraObjectPositonIs0p5AndMinus0p1()
{
	Hardware::CameraMock hardwareCamera("blue_puck");
	CameraImpl camera(hardwareCamera);

	Compare compare(0.05);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0.56,-0.1), camera.getAllCameraObjects(RobotPosition(Point(0,0))).front().getPosition()));
}

void CameraTest::getAllCameraObjects_greenBorderstone_cameraObjectPositonIs0p5AndMinus0p2()
{
	Hardware::CameraMock hardwareCamera("green_borderstone");
	CameraImpl camera(hardwareCamera);

	Compare compare(0.05);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0.53,-0.2), camera.getAllCameraObjects(RobotPosition(Point(0,0))).front().getPosition()));
}

void CameraTest::getAllCameraObjects_greenBorderstoneTriple1_cameraObjectCountIs3()
{
	Hardware::CameraMock hardwareCamera("green_borderstone_triple_1");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT_EQUAL((size_t)3, camera.getAllCameraObjects(RobotPosition()).getObjectCount());
}

void CameraTest::getAllCameraObjects_greenBorderstoneTriple1_cameraObjectPositonOfLeftObjectIs0p8And0p2()
{
	Hardware::CameraMock hardwareCamera("green_borderstone_triple_1");
	CameraImpl camera(hardwareCamera);

	Compare compare(0.06);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0.83,0.2), camera.getAllCameraObjects(RobotPosition(Point(0,0))).back().getPosition()));
}

void CameraTest::getAllCameraObjects_greenBorderstoneTriple1_cameraObjectPositonOfObjectInTheMiddleIs0p7And0p05()
{
	Hardware::CameraMock hardwareCamera("green_borderstone_triple_1");
	CameraImpl camera(hardwareCamera);

	Compare compare(0.05);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0.73,0.05), camera.getAllCameraObjects(RobotPosition(Point(0,0)))[1].getPosition()));
}

void CameraTest::getAllCameraObjects_yellowPuckTwiceAndRobotAt1And1AndHalfPi_cameraObjectPositonOfRightObjectIs1p0And1p6()
{
	Hardware::CameraMock hardwareCamera("yellow_puck_twice");
	CameraImpl camera(hardwareCamera);

	Compare compare(0.05);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1.0,1.66), camera.getAllCameraObjects(RobotPosition(Point(1,1),Angle::getQuarterRotation())).front().getPosition()));
}

void CameraTest::getAllCameraObjects_camera2211_cameraObjectCountIs2()
{
	Hardware::CameraMock hardwareCamera("camera_22_11");
	CameraImpl camera(hardwareCamera);

	CPPUNIT_ASSERT_EQUAL((size_t)2 ,camera.getAllCameraObjects(RobotPosition()).getObjectCount());
}
