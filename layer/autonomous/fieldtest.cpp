#include "layer/autonomous/fieldtest.h"
#include "layer/autonomous/fieldimpl.h"
#include "layer/dataanalysis/odometrymock.h"
#include "layer/dataanalysis/lidarmock.h"
#include "layer/dataanalysis/cameramock.h"
#include "common/compare.h"

using namespace RoboHockey::Common;
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

	CPPUNIT_ASSERT(!field.tryToFindField());
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

	CPPUNIT_ASSERT(field.tryToFindField());
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
	field.tryToFindField();

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
	field.tryToFindField();

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
	field.tryToFindField();

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
	field.tryToFindField();

	bool result = true;
	vector<FieldObject> fieldObjects = field.getAllFieldObjects();

	result = result && compare.isFuzzyEqual(fieldObjects.at(0).getCircle().getCenter(), Point(1.666, 0));
	result = result && compare.isFuzzyEqual(fieldObjects.at(1).getCircle().getCenter(), Point(2.5, 0));
	result = result && compare.isFuzzyEqual(fieldObjects.at(2).getCircle().getCenter(), Point(3.333, 0));
	result = result && compare.isFuzzyEqual(fieldObjects.at(3).getCircle().getCenter(), Point(4.582, 0));

	CPPUNIT_ASSERT(result);
}
