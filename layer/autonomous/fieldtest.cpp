#include "layer/autonomous/fieldtest.h"
#include "layer/autonomous/fieldimpl.h"
#include "layer/autonomous/robotmock.h"
#include "layer/dataanalysis/odometrymock.h"
#include "layer/dataanalysis/lidarmock.h"
#include "layer/dataanalysis/cameramock.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/hardware/robotmock.h"
#include "common/compare.h"
#include "common/robotposition.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

void FieldTest::update_noLidarObjects_noFieldObjects()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_oneObjectFromLidarInView_oneObject()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidar.setAllObjects(lidarObjects);

	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
}

void FieldTest::update_oneObjectFromLidarNotInViewAnymoreDuringSecondCall_noFieldObjects()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidar.setAllObjects(lidarObjects);

	field.update();
	lidar.setAllObjects(DataAnalysis::LidarObjects(Point()));
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_oneObjectFromLidarLeftNotInViewAnymoreDuringSecondCall_noFieldObjects()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.1));
	lidar.setAllObjects(lidarObjects);

	field.update();
	lidar.setAllObjects(DataAnalysis::LidarObjects(Point()));
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_oneObjectFromLidarRightNotInViewAnymoreDuringSecondCall_noFieldObjects()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, -1), 0.1));
	lidar.setAllObjects(lidarObjects);

	field.update();
	lidar.setAllObjects(DataAnalysis::LidarObjects(Point()));
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_objectFromLidarNotInViewAnymoreThroughRotation_oneFieldObject()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, -1), 0.1));
	lidar.setAllObjects(lidarObjects);

	field.update();
	lidar.setAllObjects(DataAnalysis::LidarObjects(Point()));
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
}

void FieldTest::update_oneObjectFromLidarAndNoObjectFromCamera_noColor()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidar.setAllObjects(lidarObjects);

	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();

	CPPUNIT_ASSERT_EQUAL(FieldColorUnknown, fieldObjects.front().getColor());
}

void FieldTest::update_twoObjectsFromLidarAndOneFromCamera_correctColor()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidar.setAllObjects(lidarObjects);

	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1,0)));
	camera.setAllObjects(cameraObjects);

	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();

	CPPUNIT_ASSERT_EQUAL(FieldColorYellow, fieldObjects.front().getColor());
}

void FieldTest::update_twoObjectsFromLidarAndOneFromCameraNoColorAnymoreDuringSecondCall_stillCorrectColor()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidar.setAllObjects(lidarObjects);

	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1,0)));
	camera.setAllObjects(cameraObjects);

	field.update();

	camera.setAllObjects(DataAnalysis::CameraObjects());

	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();

	CPPUNIT_ASSERT_EQUAL(FieldColorYellow, fieldObjects.front().getColor());
}

void FieldTest::update_oneObjectOutAndOneObjectInsideOfCalibratedField_correctObjectAddedToField()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidar.setAllObjects(lidarObjects);

	field.update();

	CPPUNIT_ASSERT_EQUAL((size_t) 4, field.getAllFieldObjects().size());

	CPPUNIT_ASSERT(field.calibratePosition());

	DataAnalysis::LidarObjects lidarObjectsAfterCalibration(odometry.getCurrentPosition().getPosition());
	lidarObjectsAfterCalibration.addObject(DataAnalysis::LidarObject(Point(1,1), 0.06));
	lidarObjectsAfterCalibration.addObject(DataAnalysis::LidarObject(Point(-2, 2.6), 0.06));
	lidar.setAllObjects(lidarObjectsAfterCalibration);

	field.update();

	CPPUNIT_ASSERT_EQUAL((size_t) 1, field.getAllFieldObjects().size());
    CPPUNIT_ASSERT_EQUAL(Point(1,1), field.getAllFieldObjects().front().getCircle().getCenter());
}

void FieldTest::update_threeObjectsAndTwoObjectsInGoal_twoAchievedGoals()
{
    DataAnalysis::OdometryMock odometry;
    DataAnalysis::LidarMock lidar;
    DataAnalysis::CameraMock camera;
    Autonomous::RobotMock autonomousRobot;
    FieldImpl field(odometry, lidar, camera, autonomousRobot);

    field.setTrueTeamColor(FieldColorYellow);
    DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
    lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2), 0.1));
    lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.3, 1.5), 0.1));
    lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.6, 1.8), 0.1));
    lidar.setAllObjects(lidarObjects);
    DataAnalysis::CameraObjects cameraObjects;
    cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 2)));
    cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.3, 1.5)));
    cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(4.6, 1.8)));
    camera.setAllObjects(cameraObjects);

    field.update();

    CPPUNIT_ASSERT(field.achievedGoals() == 2);

}

void FieldTest::calibratePosition_noValidPattern_false()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.4, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3, -4), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.5, -1), 0.1));
	lidar.setAllObjects(lidarObjects);

	field.update();

	CPPUNIT_ASSERT(!field.calibratePosition());
}

void FieldTest::calibratePosition_validPattern_true()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidar.setAllObjects(lidarObjects);

	field.update();

	CPPUNIT_ASSERT(field.calibratePosition());
}

void FieldTest::calibratePosition_noValidPattern_noTransformation()
{
	Compare compare(0.01);
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.4, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3, -4), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.5, -1), 0.1));
	lidar.setAllObjects(lidarObjects);

	field.update();
	field.calibratePosition();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	vector<DataAnalysis::LidarObject> lidarObjectsVector = lidarObjects.getObjectsWithDistanceBelow(10);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(fieldObjects.front().getCircle(), lidarObjectsVector.front()));
}

void FieldTest::calibratePosition_validPattern_transformed()
{
	Compare compare(0.01);
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidar.setAllObjects(lidarObjects);

	field.update();
	field.calibratePosition();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	vector<DataAnalysis::LidarObject> lidarObjectsVector = lidarObjects.getObjectsWithDistanceBelow(10);

	CPPUNIT_ASSERT(!compare.isFuzzyEqual(fieldObjects.front().getCircle(), lidarObjectsVector.front()));
}

void FieldTest::calibratePosition_validPattern_correctNumberOfFieldObjects()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidar.setAllObjects(lidarObjects);

	field.update();
	field.calibratePosition();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	vector<DataAnalysis::LidarObject> lidarObjectsVector = lidarObjects.getObjectsWithDistanceBelow(10);

	CPPUNIT_ASSERT_EQUAL(lidarObjectsVector.size(), fieldObjects.size());
}

void FieldTest::calibratePosition_validPattern_correctTransformation()
{
	Compare compare(0.05);
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidar.setAllObjects(lidarObjects);

	field.update();
	field.calibratePosition();

	bool result = true;
	vector<FieldObject> fieldObjects = field.getAllFieldObjects();

	result = result && compare.isFuzzyEqual(fieldObjects.at(0).getCircle().getCenter(), Point(1.666, 0));
	result = result && compare.isFuzzyEqual(fieldObjects.at(1).getCircle().getCenter(), Point(2.5, 0));
	result = result && compare.isFuzzyEqual(fieldObjects.at(2).getCircle().getCenter(), Point(3.333, 0));
	result = result && compare.isFuzzyEqual(fieldObjects.at(3).getCircle().getCenter(), Point(4.582, 0));

	CPPUNIT_ASSERT(result);
}

void FieldTest::calibratePosition_realWorldExample_positionIsCorrect()
{
	Hardware::RobotMock *hardwareRobot = new Hardware::RobotMock();
	DataAnalysis::DataAnalyserImpl dataAnalyser(hardwareRobot);
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(dataAnalyser.getOdometry(), dataAnalyser.getLidar(), dataAnalyser.getCamera(), autonomousRobot);
	Hardware::OdometryMock &odometry = hardwareRobot->getOdometryMock();
	Hardware::LidarMock &lidar = hardwareRobot->getLidarMock();
	lidar.readSensorDataFromFile("resources/testfiles/lidar_35.txt");

	dataAnalyser.updateSensorData();

	field.update();
	field.calibratePosition();

	Compare compare(0.5);
	RobotPosition position = odometry.getCurrentPosition();
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2.5, 1.5), position.getPosition()));
}

void FieldTest::calibratePosition_validPattern_objectsOutsideFieldAreDeleted()
{
	Compare compare(0.05);
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(5.7, 1.3), 0.06));
	lidar.setAllObjects(lidarObjects);

	field.update();
	CPPUNIT_ASSERT_EQUAL((size_t) 5, field.getAllFieldObjects().size());

	field.calibratePosition();
	CPPUNIT_ASSERT_EQUAL((size_t) 4, field.getAllFieldObjects().size());
}

void FieldTest::getObjectsWithColorOrderedByDistance_oneObjectWithCorrectColorAndOneWithNoColor_resultSizeIsCorrect()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, 1), 0.1));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 0)));
	camera.setAllObjects(cameraObjects);
	field.update();

	vector<FieldObject> fieldObjects = field.getObjectsWithColorOrderdByDistance(FieldColorYellow, Point(0, 0));

	CPPUNIT_ASSERT_EQUAL((size_t)1, fieldObjects.size());
}

void FieldTest::getObjectsWithColorOrderedByDistance_twoObjectsWithCorrectColorInAscendingOrder_orderIsCorrect()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	Point ownPosition(0, 0);
	DataAnalysis::LidarObjects lidarObjects(ownPosition);
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.12));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, -1), 0.12));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 0)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(2, -1)));
	camera.setAllObjects(cameraObjects);
	field.update();

	vector<FieldObject> fieldObjects = field.getObjectsWithColorOrderdByDistance(FieldColorYellow, ownPosition);

	CPPUNIT_ASSERT_EQUAL((size_t)2, fieldObjects.size());
	const FieldObject &firstObject = fieldObjects.front();
	const FieldObject &secondObject = fieldObjects.back();
	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Circle(Point(1, 0), 0.12), firstObject.getCircle()));
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Circle(Point(2, -1), 0.12), secondObject.getCircle()));
}

void FieldTest::getObjectsWithColorOrderedByDistance_twoObjectsWithCorrectColorInDescendingOrder_orderIsCorrect()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	Point ownPosition(0, 0);
	DataAnalysis::LidarObjects lidarObjects(ownPosition);
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, -1), 0.12));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.12));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(2, -1)));
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(1, 0)));
	camera.setAllObjects(cameraObjects);
	field.update();

	vector<FieldObject> fieldObjects = field.getObjectsWithColorOrderdByDistance(FieldColorYellow, ownPosition);

	CPPUNIT_ASSERT_EQUAL((size_t)2, fieldObjects.size());
	const FieldObject &firstObject = fieldObjects.front();
	const FieldObject &secondObject = fieldObjects.back();
	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Circle(Point(1, 0), 0.12), firstObject.getCircle()));
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Circle(Point(2, -1), 0.12), secondObject.getCircle()));
}

void FieldTest::isPointInsideField_notCalibrated_true()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	field.update();

	CPPUNIT_ASSERT(field.isPointInsideField(Point(-1,-3)));
}

void FieldTest::isPointInsideField_pointIsInside_true()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidar.setAllObjects(lidarObjects);

	field.update();
	field.calibratePosition();

	CPPUNIT_ASSERT(field.isPointInsideField(Point(2,1.5)));
}

void FieldTest::isPointInsideField_pointIsOutside_false()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidar.setAllObjects(lidarObjects);

	field.update();
	field.calibratePosition();

	CPPUNIT_ASSERT(!field.isPointInsideField(Point(0.8,3.2)));
}

void FieldTest::isPointInsideField_pointIsUnderField_false()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidar.setAllObjects(lidarObjects);

	field.update();
	field.calibratePosition();

	CPPUNIT_ASSERT(!field.isPointInsideField(Point(-1,-3)));
}

void FieldTest::numberOfPucksChanged_emptyField_false()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	field.update();

	CPPUNIT_ASSERT(!field.numberOfPucksChanged());
}

void FieldTest::numberOfPucksChanged_onePuckAdded_true()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	Point ownPosition(0, 0);

	DataAnalysis::LidarObjects lidarObjects(ownPosition);
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, -1), 0.12));
	lidar.setAllObjects(lidarObjects);

	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(2, -1)));
	camera.setAllObjects(cameraObjects);

	field.update();
	CPPUNIT_ASSERT(field.numberOfPucksChanged());

	field.update();
	CPPUNIT_ASSERT(!field.numberOfPucksChanged());
}

void FieldTest::numberOfPucksChanged_onePuckRemoved_true()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	Point ownPosition(0, 0);

	DataAnalysis::LidarObjects lidarObjects(ownPosition);
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, -1), 0.12));
	lidar.setAllObjects(lidarObjects);

	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(2, -1)));
	camera.setAllObjects(cameraObjects);

	field.update();
	CPPUNIT_ASSERT(field.numberOfPucksChanged());

	field.update();
	CPPUNIT_ASSERT(!field.numberOfPucksChanged());

	lidar.setAllObjects(DataAnalysis::LidarObjects(Point::zero()));
	field.update();
	CPPUNIT_ASSERT(field.numberOfPucksChanged());
}


void FieldTest::numberOfPucksChanged_onePuckAddedOnePuckRemoved_true()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	Point ownPosition(0, 0);

	DataAnalysis::LidarObjects lidarObjects(ownPosition);
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(2, -1), 0.12));
	lidar.setAllObjects(lidarObjects);

	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(2, -1)));
	camera.setAllObjects(cameraObjects);

	field.update();
	CPPUNIT_ASSERT(field.numberOfPucksChanged());

	field.update();
	CPPUNIT_ASSERT(!field.numberOfPucksChanged());

	DataAnalysis::LidarObjects lidarObjectsSecondRun(ownPosition);
	lidarObjectsSecondRun.addObject(DataAnalysis::LidarObject(Point(-3, 2), 0.12));
	lidar.setAllObjects(lidarObjectsSecondRun);

	DataAnalysis::CameraObjects cameraObjectsSecondRun;
	cameraObjectsSecondRun.addObject(DataAnalysis::CameraObject(FieldColorYellow, Point(-3, 2)));
	camera.setAllObjects(cameraObjectsSecondRun);

	field.update();
	CPPUNIT_ASSERT(field.numberOfPucksChanged());
}

void FieldTest::getTargetsForGoalDetection_correctPosition()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	CPPUNIT_ASSERT_EQUAL(RobotPosition(Point(1.17333333333, 1.5), Angle::getHalfRotation()), field.getTargetsForGoalDetection().front());
}

void FieldTest::getAllSoftObstacles_oneBluePuck_resultSizeIs1()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(1, 0)));
	camera.setAllObjects(cameraObjects);

	field.update();
	vector<Circle> obstacles = field.getAllSoftObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
}

void FieldTest::getAllSoftObstacles_oneSmallObstacleWithUnknownColor_resultSizeIs1()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	lidar.setAllObjects(lidarObjects);

	field.update();
	vector<Circle> obstacles = field.getAllSoftObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
}

void FieldTest::getAllSoftObstacles_oneGreenObstacle_resultSizeIs0()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorGreen, Point(1, 0)));
	camera.setAllObjects(cameraObjects);

	field.update();
	vector<Circle> obstacles = field.getAllSoftObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getAllSoftObstacles_oneBigObstacle_resultSizeIs0()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.5));
	lidar.setAllObjects(lidarObjects);

	field.update();
	vector<Circle> obstacles = field.getAllSoftObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getAllSoftObstacles_onePuckDisappeared_resultSizeIs0()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorBlue, Point(1, 0)));
	camera.setAllObjects(cameraObjects);

	field.update();
	lidarObjects.clear();
	cameraObjects.clear();
	lidar.setAllObjects(lidarObjects);
	camera.setAllObjects(cameraObjects);
	field.update();
	vector<Circle> obstacles = field.getAllSoftObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getAllHardObstacles_oneGreenObject_resultSizeIs1()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	lidar.setAllObjects(lidarObjects);
	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldColorGreen, Point(1, 0)));
	camera.setAllObjects(cameraObjects);

	field.update();
	vector<Circle> obstacles = field.getAllHardObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
}

void FieldTest::getAllHardObstacles_oneBigObstacle_resultSizeIs1()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.5));
	lidar.setAllObjects(lidarObjects);

	field.update();
	vector<Circle> obstacles = field.getAllHardObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
}

void FieldTest::getAllHardObstacles_oneSmallObstacleWithUnknownColor_resultSizeIs0()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.06));
	lidar.setAllObjects(lidarObjects);

	field.update();
	vector<Circle> obstacles = field.getAllHardObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getAllHardObstacles_oneBigObstacleDisappeared_resultSizeIs0()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);
	RobotPosition ownPosition(Point(0, 0), 0);
	odometry.setCurrentPosition(ownPosition);
	DataAnalysis::LidarObjects lidarObjects(ownPosition.getPosition());
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.5));
	lidar.setAllObjects(lidarObjects);

	field.update();
	lidarObjects.clear();
	lidar.setAllObjects(lidarObjects);
	field.update();
	vector<Circle> obstacles = field.getAllHardObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)0, obstacles.size());
}

void FieldTest::getTargetsForScoringGoals_always_numberOfPositionsBigger4()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	CPPUNIT_ASSERT((size_t) 4 < field.getTargetsForScoringGoals().size());
}

void FieldTest::getTargetsForFinalPosition_always_numberOfPositionsBigger1()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	CPPUNIT_ASSERT((size_t) 1 < field.getTargetsForFinalPosition().size());

}

void FieldTest::getTargetsForSearchingPucks_always_numberOfPositionsBigger5()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	CPPUNIT_ASSERT((size_t) 5 < field.getTargetsForSearchingPucks().size());
}

void FieldTest::detectTeamColorWithGoalInFront_yellowMuchBiggerBlue_teamYellow()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	camera.setProbabilityForYellowGoal(0.82);
	camera.setProbabilityForBlueGoal(0.27);

	field.detectTeamColorWithGoalInFront();

	CPPUNIT_ASSERT_EQUAL(FieldColorYellow, field.getOwnTeamColor());
}

void FieldTest::detectTeamColorWithGoalInFront_yellowMuchSmallerBlue_teamBlue()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	camera.setProbabilityForYellowGoal(0.13);
	camera.setProbabilityForBlueGoal(0.77);

	field.detectTeamColorWithGoalInFront();

	CPPUNIT_ASSERT_EQUAL(FieldColorBlue, field.getOwnTeamColor());
}

void FieldTest::detectTeamColorWithGoalInFront_yellowAndBlueFuzzyEqual_teamUnknown()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	Autonomous::RobotMock autonomousRobot;
	FieldImpl field(odometry, lidar, camera, autonomousRobot);

	camera.setProbabilityForYellowGoal(0.43);
	camera.setProbabilityForBlueGoal(0.47);

	field.detectTeamColorWithGoalInFront();

	CPPUNIT_ASSERT_EQUAL(FieldColorUnknown, field.getOwnTeamColor());
}
