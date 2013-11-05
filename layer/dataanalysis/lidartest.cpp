#include "layer/dataanalysis/lidartest.h"
#include "layer/dataanalysis/lidarimpl.h"
#include "layer/hardware/lidarmock.h"
#include "layer/hardware/lidarstub.h"
#include "common/compare.h"
#include <math.h>

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
	hardwareLidar.setValueForAngle(81, 3.04);
	hardwareLidar.setValueForAngle(82, 3.02);
	hardwareLidar.setValueForAngle(83, 2.99);
	hardwareLidar.setValueForAngle(84, 2.97);
	hardwareLidar.setValueForAngle(85, 2.94);
	hardwareLidar.setValueForAngle(86, 2.92);
	hardwareLidar.setValueForAngle(87, 2.89);
	hardwareLidar.setValueForAngle(88, 2.87);
	hardwareLidar.setValueForAngle(89, 2.84);
	hardwareLidar.setValueForAngle(90, 2.81);
	hardwareLidar.setValueForAngle(91, 2.77);
	hardwareLidar.setValueForAngle(92, 2.74);
	hardwareLidar.setValueForAngle(93, 2.71);
	hardwareLidar.setValueForAngle(94, 2.68);
	hardwareLidar.setValueForAngle(95, 2.65);
	hardwareLidar.setValueForAngle(96, 2.62);
	hardwareLidar.setValueForAngle(97, 2.59);
	hardwareLidar.setValueForAngle(98, 2.56);
	hardwareLidar.setValueForAngle(99, 2.53);
	hardwareLidar.setValueForAngle(100, 2.5);
	hardwareLidar.setValueForAngle(101, 2.53);
	hardwareLidar.setValueForAngle(102, 2.56);
	hardwareLidar.setValueForAngle(103, 2.59);
	hardwareLidar.setValueForAngle(104, 2.62);
	hardwareLidar.setValueForAngle(105, 2.65);
	hardwareLidar.setValueForAngle(106, 2.68);
	hardwareLidar.setValueForAngle(107, 2.71);
	hardwareLidar.setValueForAngle(108, 2.74);
	hardwareLidar.setValueForAngle(109, 2.77);
	hardwareLidar.setValueForAngle(110, 2.81);
	hardwareLidar.setValueForAngle(111, 2.84);
	hardwareLidar.setValueForAngle(112, 2.87);
	hardwareLidar.setValueForAngle(113, 2.89);
	hardwareLidar.setValueForAngle(114, 2.92);
	hardwareLidar.setValueForAngle(115, 2.94);
	hardwareLidar.setValueForAngle(116, 2.97);
	hardwareLidar.setValueForAngle(117, 2.99);
	hardwareLidar.setValueForAngle(118, 3.02);
	hardwareLidar.setValueForAngle(119, 3.04);
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(1, 1);

	LidarObjects allObjects = lidar.getAllObjects(ownPosition, 0);

	vector<LidarObject> objects = allObjects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT_EQUAL((size_t)1, objects.size());
	LidarObject object = objects.front();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(2.56, object.getDiameter(), 0.05);
	CPPUNIT_ASSERT(Point(4.75, 0.37).fuzzyEqual(object.getCenter(), 0.05));
}

void LidarTest::getAllObjects_lookingIntoLeftUpperDirectionAndObjectSlightlyLeft_onlyObjectIsCorrect()
{
	Hardware::LidarStub hardwareLidar(10);
	hardwareLidar.setValueForAngle(40, 3.04);
	hardwareLidar.setValueForAngle(41, 3.02);
	hardwareLidar.setValueForAngle(42, 2.99);
	hardwareLidar.setValueForAngle(43, 3.02);
	hardwareLidar.setValueForAngle(44, 3.04);
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(1, 2);

	LidarObjects allObjects = lidar.getAllObjects(ownPosition, M_PI*0.7);

	vector<LidarObject> objects = allObjects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT_EQUAL((size_t)1, objects.size());
	LidarObject object = objects.front();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.15, object.getDiameter(), 0.1);
	CPPUNIT_ASSERT(Point(-2.08, 2.28).fuzzyEqual(object.getCenter(), 0.1));
}

void LidarTest::getAllObjects_twoObjects_objectCountIs2()
{
	Hardware::LidarStub hardwareLidar(10);
	hardwareLidar.setValueForAngle(150, 3.04);
	hardwareLidar.setValueForAngle(151, 3.02);
	hardwareLidar.setValueForAngle(152, 2.99);
	hardwareLidar.setValueForAngle(153, 3.02);
	hardwareLidar.setValueForAngle(154, 3.04);
	hardwareLidar.setValueForAngle(80, 1.04);
	hardwareLidar.setValueForAngle(81, 1.02);
	hardwareLidar.setValueForAngle(82, 0.99);
	hardwareLidar.setValueForAngle(83, 1.02);
	hardwareLidar.setValueForAngle(84, 1.04);
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(1, 2);

	LidarObjects objects = lidar.getAllObjects(ownPosition, M_PI*0.7);

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT_EQUAL((size_t)2, objectsInForeground.size());
}

void LidarTest::getAllObjects_oneObjectBehindAnotherOneLeft_objectCountIs2()
{
	Hardware::LidarStub hardwareLidar(10);
	hardwareLidar.setValueForAngle(50, 3.04);
	hardwareLidar.setValueForAngle(51, 3.02);
	hardwareLidar.setValueForAngle(52, 2.99);
	hardwareLidar.setValueForAngle(53, 3.02);
	hardwareLidar.setValueForAngle(54, 3.04);
	hardwareLidar.setValueForAngle(55, 1.04);
	hardwareLidar.setValueForAngle(56, 1.02);
	hardwareLidar.setValueForAngle(57, 0.99);
	hardwareLidar.setValueForAngle(58, 1.02);
	hardwareLidar.setValueForAngle(59, 1.04);
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(1, 2);

	LidarObjects objects = lidar.getAllObjects(ownPosition, M_PI*(-0.5));

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT_EQUAL((size_t)2, objectsInForeground.size());
}

void LidarTest::getAllObjects_oneObjectBehindAnotherOneRight_objectCountIs2()
{
	Hardware::LidarStub hardwareLidar(10);
	hardwareLidar.setValueForAngle(50, 2.04);
	hardwareLidar.setValueForAngle(51, 2.02);
	hardwareLidar.setValueForAngle(52, 1.99);
	hardwareLidar.setValueForAngle(53, 2.02);
	hardwareLidar.setValueForAngle(54, 2.04);
	hardwareLidar.setValueForAngle(55, 4.04);
	hardwareLidar.setValueForAngle(56, 4.02);
	hardwareLidar.setValueForAngle(57, 3.99);
	hardwareLidar.setValueForAngle(58, 4.02);
	hardwareLidar.setValueForAngle(59, 4.04);
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(1, 2);

	LidarObjects objects = lidar.getAllObjects(ownPosition, M_PI*(-0.5));

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT_EQUAL((size_t)2, objectsInForeground.size());
}

void LidarTest::getAllObjects_objectAtLeftBorder_objectCountIs1()
{
	Hardware::LidarStub hardwareLidar(10);
	hardwareLidar.setValueForAngle(0, 2.5);
	hardwareLidar.setValueForAngle(1, 2.5);
	hardwareLidar.setValueForAngle(2, 2.5);
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(1, 2);

	LidarObjects objects = lidar.getAllObjects(ownPosition, M_PI*(-0.5));

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT_EQUAL((size_t)1, objectsInForeground.size());
}

void LidarTest::getAllObjects_objectAtRightBorder_objectCountIs1()
{
	Hardware::LidarStub hardwareLidar(10);
	hardwareLidar.setValueForAngle(177, 2.5);
	hardwareLidar.setValueForAngle(178, 2.5);
	hardwareLidar.setValueForAngle(179, 2.5);
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(1, 2);

	LidarObjects objects = lidar.getAllObjects(ownPosition, M_PI*(-0.5));

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT_EQUAL((size_t)1, objectsInForeground.size());
}
