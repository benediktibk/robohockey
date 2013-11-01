#include "layer/dataanalysis/lidartest.h"
#include "layer/dataanalysis/lidarimpl.h"
#include "layer/hardware/lidarmock.h"
#include "common/compare.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace std;

void LidarTest::getAllObjects_mockHardwareLidar_atLeastOneCallToGetDistance()
{
	Hardware::LidarMock hardwareLidar;
	LidarImpl lidar(hardwareLidar);

	lidar.getAllObjects(Point(), 0);

	CPPUNIT_ASSERT(hardwareLidar.getCallsToGetDistance() > 0);
}

void LidarTest::getAllObjects_oneObjectInFront_onlyObjectIsCorrect()
{
	Hardware::LidarMock hardwareLidar;
	LidarImpl lidar(hardwareLidar);

	LidarObjects allObjects = lidar.getAllObjects(Point(1, 1), 0);

	vector<LidarObject> objects = allObjects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT_EQUAL((size_t)1, objects.size());
	LidarObject object = objects.front();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, object.getDiameter(), 0.01);
	CPPUNIT_ASSERT(Point(1, 4).fuzzyEqual(object.getPosition(), 0.01));
}
