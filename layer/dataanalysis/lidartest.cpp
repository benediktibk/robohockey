#include "layer/dataanalysis/lidartest.h"
#include "layer/dataanalysis/lidarimpl.h"
#include "layer/hardware/lidarmock.h"
#include "layer/hardware/lidarstub.h"
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
	Hardware::LidarStub hardwareLidar(10);
	hardwareLidar.setValueForAngle(161, 3.04);
	hardwareLidar.setValueForAngle(162, 3.02);
	hardwareLidar.setValueForAngle(163, 2.99);
	hardwareLidar.setValueForAngle(164, 2.97);
	hardwareLidar.setValueForAngle(165, 2.94);
	hardwareLidar.setValueForAngle(166, 2.92);
	hardwareLidar.setValueForAngle(167, 2.89);
	hardwareLidar.setValueForAngle(168, 2.87);
	hardwareLidar.setValueForAngle(169, 2.84);
	hardwareLidar.setValueForAngle(170, 2.81);
	hardwareLidar.setValueForAngle(171, 2.77);
	hardwareLidar.setValueForAngle(172, 2.74);
	hardwareLidar.setValueForAngle(173, 2.71);
	hardwareLidar.setValueForAngle(174, 2.68);
	hardwareLidar.setValueForAngle(175, 2.65);
	hardwareLidar.setValueForAngle(176, 2.62);
	hardwareLidar.setValueForAngle(177, 2.59);
	hardwareLidar.setValueForAngle(178, 2.56);
	hardwareLidar.setValueForAngle(179, 2.53);
	hardwareLidar.setValueForAngle(180, 2.5);
	hardwareLidar.setValueForAngle(181, 2.53);
	hardwareLidar.setValueForAngle(182, 2.56);
	hardwareLidar.setValueForAngle(183, 2.59);
	hardwareLidar.setValueForAngle(184, 2.62);
	hardwareLidar.setValueForAngle(185, 2.65);
	hardwareLidar.setValueForAngle(186, 2.68);
	hardwareLidar.setValueForAngle(187, 2.71);
	hardwareLidar.setValueForAngle(188, 2.74);
	hardwareLidar.setValueForAngle(189, 2.77);
	hardwareLidar.setValueForAngle(190, 2.81);
	hardwareLidar.setValueForAngle(191, 2.84);
	hardwareLidar.setValueForAngle(192, 2.87);
	hardwareLidar.setValueForAngle(193, 2.89);
	hardwareLidar.setValueForAngle(194, 2.92);
	hardwareLidar.setValueForAngle(195, 2.94);
	hardwareLidar.setValueForAngle(196, 2.97);
	hardwareLidar.setValueForAngle(197, 2.99);
	hardwareLidar.setValueForAngle(198, 3.02);
	hardwareLidar.setValueForAngle(199, 3.04);
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(1, 1);

	LidarObjects allObjects = lidar.getAllObjects(ownPosition, 0);

	vector<LidarObject> objects = allObjects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT_EQUAL((size_t)1, objects.size());
	LidarObject object = objects.front();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, object.getDiameter(), 0.1);
	CPPUNIT_ASSERT(Point(4, 1).fuzzyEqual(object.getPosition(), 0.1));
}
