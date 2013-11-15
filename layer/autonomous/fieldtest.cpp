#include "layer/autonomous/fieldtest.h"
#include "layer/autonomous/fieldimpl.h"
#include "layer/dataanalysis/odometrymock.h"
#include "layer/dataanalysis/lidarmock.h"
#include "layer/dataanalysis/cameramock.h"

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
