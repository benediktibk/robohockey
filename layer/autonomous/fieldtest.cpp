#include "layer/autonomous/fieldtest.h"
#include "layer/autonomous/fieldimpl.h"
#include "layer/dataanalysis/odometrymock.h"
#include "layer/dataanalysis/lidarmock.h"
#include "layer/dataanalysis/cameramock.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/hardware/robotmock.h"
#include "common/compare.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

void FieldTest::update_noLidarObjects_noFieldObjects()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	FieldImpl field(odometry, lidar, camera);

	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();
	CPPUNIT_ASSERT_EQUAL((size_t)0, fieldObjects.size());
}

void FieldTest::update_oneObjectFromLidarInView_oneObject()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	FieldImpl field(odometry, lidar, camera);
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
	FieldImpl field(odometry, lidar, camera);
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
	FieldImpl field(odometry, lidar, camera);
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
	FieldImpl field(odometry, lidar, camera);
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
	FieldImpl field(odometry, lidar, camera);
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
	FieldImpl field(odometry, lidar, camera);
	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidar.setAllObjects(lidarObjects);

	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();

	CPPUNIT_ASSERT_EQUAL(FieldObjectColorUnknown, fieldObjects.front().getColor());
}

void FieldTest::update_twoObjectsFromLidarAndOneFromCamera_correctColor()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	FieldImpl field(odometry, lidar, camera);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidar.setAllObjects(lidarObjects);

	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldObjectColorYellow, Point(1,0)));
	camera.setAllObjects(cameraObjects);

	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();

	CPPUNIT_ASSERT_EQUAL(FieldObjectColorYellow, fieldObjects.front().getColor());
}

void FieldTest::update_twoObjectsFromLidarAndOneFromCameraNoColorAnymoreDuringSecondCall_stillCorrectColor()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	FieldImpl field(odometry, lidar, camera);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidar.setAllObjects(lidarObjects);

	DataAnalysis::CameraObjects cameraObjects;
	cameraObjects.addObject(DataAnalysis::CameraObject(FieldObjectColorYellow, Point(1,0)));
	camera.setAllObjects(cameraObjects);

	field.update();

	camera.setAllObjects(DataAnalysis::CameraObjects());

	field.update();

	vector<FieldObject> fieldObjects = field.getAllFieldObjects();

	CPPUNIT_ASSERT_EQUAL(FieldObjectColorYellow, fieldObjects.front().getColor());
}

void FieldTest::tryToDetectField_noValidPattern_false()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	FieldImpl field(odometry, lidar, camera);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 0), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3.4, 3), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(3, -4), 0.1));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(4.5, -1), 0.1));
	lidar.setAllObjects(lidarObjects);

	field.update();

	CPPUNIT_ASSERT(!field.calibratePosition());
}

void FieldTest::tryToDetectField_validPattern_true()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	FieldImpl field(odometry, lidar, camera);

	DataAnalysis::LidarObjects lidarObjects(Point(0, 0));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 1.833), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 2.666), 0.06));
	lidarObjects.addObject(DataAnalysis::LidarObject(Point(1, 3.916), 0.06));
	lidar.setAllObjects(lidarObjects);

	field.update();

	CPPUNIT_ASSERT(field.calibratePosition());
}

void FieldTest::tryToDetectField_noValidPattern_noTransformation()
{
	Compare compare(0.01);
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	FieldImpl field(odometry, lidar, camera);

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

void FieldTest::tryToDetectField_validPattern_transformed()
{
	Compare compare(0.01);
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	FieldImpl field(odometry, lidar, camera);

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

void FieldTest::tryToDetectField_validPattern_correctNumberOfFieldObjects()
{
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	FieldImpl field(odometry, lidar, camera);

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

void FieldTest::tryToDetectField_validPattern_correctTransformation()
{
	Compare compare(0.05);
	DataAnalysis::OdometryMock odometry;
	DataAnalysis::LidarMock lidar;
	DataAnalysis::CameraMock camera;
	FieldImpl field(odometry, lidar, camera);

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

void FieldTest::tryToDetectField_realWorldExample_positionIsCorrect()
{
	Hardware::RobotMock *hardwareRobot = new Hardware::RobotMock();
	DataAnalysis::DataAnalyserImpl dataAnalyser(hardwareRobot);
	FieldImpl field(dataAnalyser.getOdometry(), dataAnalyser.getLidar(), dataAnalyser.getCamera());
	Hardware::OdometryMock &odometry = hardwareRobot->getOdometryMock();
	Hardware::LidarMock &lidar = hardwareRobot->getLidarMock();
	lidar.readSensorDataFromFile("resources/testfiles/lidar_35.txt");

	field.update();
	field.calibratePosition();

	Compare compare(0.5);
	RobotPosition position = odometry.getCurrentPosition();
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2.5, 1.5), position));
}
