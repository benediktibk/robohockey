#include "layer/dataanalysis/lidartest.h"
#include "layer/dataanalysis/lidarimpl.h"
#include "layer/hardware/lidarmock.h"
#include "common/compare.h"
#include "common/robotposition.h"
#include <math.h>
#include <assert.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;
using namespace std;

void LidarTest::getAllObjects_mockHardwareLidar_atLeastOneCallToGetDistance()
{
	Hardware::LidarMock hardwareLidar;
	LidarImpl lidar(hardwareLidar);

	lidar.updateSensorData();
	lidar.getAllObjects(RobotPosition());

	CPPUNIT_ASSERT(hardwareLidar.getCallsToGetDistance() > 0);
}

void LidarTest::getAllObjects_oneTooBigObjectInFront_objectCountIs0()
{
	Hardware::LidarMock hardwareLidar(10);
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

	lidar.updateSensorData();
	LidarObjects allObjects = lidar.getAllObjects(RobotPosition(ownPosition, 0));

	vector<LidarObject> objects = allObjects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT_EQUAL((size_t)0, objects.size());
}

void LidarTest::getAllObjects_lookingIntoLeftUpperDirectionAndObjectSlightlyLeft_onlyObjectIsCorrect()
{
	Hardware::LidarMock hardwareLidar(10);
	hardwareLidar.setValueForAngle(206, 3.04);
	hardwareLidar.setValueForAngle(207, 3.02);
	hardwareLidar.setValueForAngle(208, 2.99);
	hardwareLidar.setValueForAngle(209, 3.02);
	hardwareLidar.setValueForAngle(210, 3.04);
	LidarImpl lidar(hardwareLidar);
	RobotPosition ownPosition(Point(1, 2), M_PI*0.7);

	lidar.updateSensorData();
	LidarObjects allObjects = lidar.getAllObjects(ownPosition);

	vector<LidarObject> objects = allObjects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT_EQUAL((size_t)1, objects.size());
	LidarObject object = objects.front();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.15, object.getDiameter(), 0.1);
	Compare compare(0.1);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(-1.4, 4), object.getCenter()));
}

void LidarTest::getAllObjects_twoObjects_objectCountIs2()
{
	Hardware::LidarMock hardwareLidar(10);
	hardwareLidar.setValueForAngle(150, 3.04);
	hardwareLidar.setValueForAngle(151, 3.02);
	hardwareLidar.setValueForAngle(152, 2.99);
	hardwareLidar.setValueForAngle(153, 3.02);
	hardwareLidar.setValueForAngle(154, 3.04);
	hardwareLidar.setValueForAngle(180, 1.04);
	hardwareLidar.setValueForAngle(181, 1.02);
	hardwareLidar.setValueForAngle(182, 0.99);
	hardwareLidar.setValueForAngle(183, 1.02);
	hardwareLidar.setValueForAngle(184, 1.04);
	LidarImpl lidar(hardwareLidar);
	RobotPosition ownPosition(Point(1, 2), M_PI*0.7);

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(ownPosition);

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT_EQUAL((size_t)2, objectsInForeground.size());
}

void LidarTest::getAllObjects_oneObjectBehindAnotherOneLeft_objectCountIs2()
{
	Hardware::LidarMock hardwareLidar(10);
	hardwareLidar.setValueForAngle(150, 2.04);
	hardwareLidar.setValueForAngle(151, 2.02);
	hardwareLidar.setValueForAngle(152, 1.99);
	hardwareLidar.setValueForAngle(153, 2.02);
	hardwareLidar.setValueForAngle(154, 2.04);
	hardwareLidar.setValueForAngle(155, 4.04);
	hardwareLidar.setValueForAngle(156, 4.02);
	hardwareLidar.setValueForAngle(157, 3.99);
	hardwareLidar.setValueForAngle(158, 4.02);
	hardwareLidar.setValueForAngle(159, 4.04);
	LidarImpl lidar(hardwareLidar);
	RobotPosition ownPosition(Point(1, 2), M_PI*(-0.5));

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(ownPosition);

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT_EQUAL((size_t)2, objectsInForeground.size());
}

void LidarTest::getAllObjects_oneObjectBehindAnotherOneRight_objectCountIs2()
{
	Hardware::LidarMock hardwareLidar(10);
	hardwareLidar.setValueForAngle(150, 3.04);
	hardwareLidar.setValueForAngle(151, 3.02);
	hardwareLidar.setValueForAngle(152, 2.99);
	hardwareLidar.setValueForAngle(153, 3.02);
	hardwareLidar.setValueForAngle(154, 3.04);
	hardwareLidar.setValueForAngle(155, 1.04);
	hardwareLidar.setValueForAngle(156, 1.02);
	hardwareLidar.setValueForAngle(157, 0.99);
	hardwareLidar.setValueForAngle(158, 1.02);
	hardwareLidar.setValueForAngle(159, 1.04);
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(1, 2);

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(RobotPosition(ownPosition, M_PI*(-0.5)));

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT_EQUAL((size_t)2, objectsInForeground.size());
}

void LidarTest::getAllObjects_objectAtLeftBorder_objectCountIs1()
{
	Hardware::LidarMock hardwareLidar(10);
	hardwareLidar.setValueForAngle(358, 2.5);
	hardwareLidar.setValueForAngle(359, 2.5);
	hardwareLidar.setValueForAngle(360, 2.5);
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(1, 2);

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(RobotPosition(ownPosition, M_PI*(-0.5)));

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT_EQUAL((size_t)1, objectsInForeground.size());
}

void LidarTest::getAllObjects_objectAtRightBorder_objectCountIs1()
{
	Hardware::LidarMock hardwareLidar(10);
	hardwareLidar.setValueForAngle(0, 2.5);
	hardwareLidar.setValueForAngle(1, 2.5);
	hardwareLidar.setValueForAngle(2, 2.5);
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(1, 2);

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(RobotPosition(ownPosition, M_PI*(-0.5)));

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT_EQUAL((size_t)1, objectsInForeground.size());
}

void LidarTest::getAllObjects_realWorldExample_runsThroughWithoutACrash()
{
	Hardware::LidarMock hardwareLidar(10);
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_1.txt");
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(0, 0);

	lidar.updateSensorData();
	lidar.getAllObjects(RobotPosition(ownPosition, 0));

	CPPUNIT_ASSERT(true);
}

void LidarTest::getAllObjects_objectRightOfView_positionOfOnlyObjectIsCorrect()
{
	Hardware::LidarMock hardwareLidar(10);
	hardwareLidar.setValueForAngle(0, 3);
	hardwareLidar.setValueForAngle(1, 3);
	hardwareLidar.setValueForAngle(2, 3);
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(0, 0);

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(RobotPosition(ownPosition, 0));

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT_EQUAL((size_t)1, objectsInForeground.size());
	const LidarObject &object = objectsInForeground.front();
	Compare compare(0.1);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0, -3), object.getCenter()));
}

void LidarTest::getAllObjects_objectLeftOfView_positionOfOnlyObjectIsCorrect()
{
	Hardware::LidarMock hardwareLidar(10);
	hardwareLidar.setValueForAngle(358, 3);
	hardwareLidar.setValueForAngle(359, 3);
	hardwareLidar.setValueForAngle(360, 3);
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(0, 0);

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(RobotPosition(ownPosition, 0));

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT_EQUAL((size_t)1, objectsInForeground.size());
	const LidarObject &object = objectsInForeground.front();
	Compare compare(0.1);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0, 3), object.getCenter()));
}

void LidarTest::getAllObjects_puckDirectInFront_onlyObjectIsCorrect()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_2.txt");
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(0, 0);

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(RobotPosition(ownPosition, 0));

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(1);
	CPPUNIT_ASSERT_EQUAL((size_t)1, objectsInForeground.size());
	const LidarObject &object = objectsInForeground.front();
	Compare compare(0.02);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0.2, 0), object.getCenter()));
	CPPUNIT_ASSERT(compare.isFuzzyEqual(0.04, object.getDiameter()));
}

void LidarTest::getAllobjects_oneBoundaryPostInRange_diameterIsCorrect()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_4.txt");
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(0, 0);

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(RobotPosition(ownPosition, 0));

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(1);
	CPPUNIT_ASSERT_EQUAL((size_t)1, objectsInForeground.size());
	const LidarObject &object = objectsInForeground.front();
	Compare compare(0.01);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(0.06, object.getDiameter()));
}

void LidarTest::getAllObjects_onePuckALittleBitDistant_diameterIsCorrect()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_5.txt");
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(0, 0);

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(RobotPosition(ownPosition, 0));

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(1);
	CPPUNIT_ASSERT_EQUAL((size_t)1, objectsInForeground.size());
	const LidarObject &object = objectsInForeground.front();
	Compare compare(0.02);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(0.04, object.getDiameter()));
}

void LidarTest::getAllObjects_onePuck_positionAndDiameterIsCorrect()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_6.txt");
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(0, 0);

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(RobotPosition(ownPosition, 0));

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(1);
	CPPUNIT_ASSERT_EQUAL((size_t)1, objectsInForeground.size());
	const LidarObject &object = objectsInForeground.front();
	Compare compare(0.04);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0.505, -0.325), object.getCenter()));
	CPPUNIT_ASSERT(compare.isFuzzyEqual(0.04, object.getDiameter()));
}

void LidarTest::getAllObjects_onePuckInQuiteADistanceVersion1_distanceAndDiameterIsCorrect()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_7.txt");
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(0, 0);

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(RobotPosition(ownPosition, 0));

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(2);
	CPPUNIT_ASSERT_EQUAL((size_t)1, objectsInForeground.size());
	const LidarObject &object = objectsInForeground.front();
	double distance = ownPosition.distanceTo(object.getCenter());
	Compare compare(0.025);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(1.375, distance));
	CPPUNIT_ASSERT(compare.isFuzzyEqual(0.04, object.getDiameter()));
}

void LidarTest::getAllObjects_onePuckInQuiteADistanceVersion2_distanceAndDiameterIsCorrect()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_8.txt");
	LidarImpl lidar(hardwareLidar);
	Point ownPosition(0, 0);

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(RobotPosition(ownPosition, 0));

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(2.5);
	CPPUNIT_ASSERT_EQUAL((size_t)1, objectsInForeground.size());
	const LidarObject &object = objectsInForeground.front();
	double distance = ownPosition.distanceTo(object.getCenter());
	Compare compare(0.05);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(2.26, distance));
	CPPUNIT_ASSERT(compare.isFuzzyEqual(0.04, object.getDiameter()));
}

void LidarTest::getAllObjects_maximumDistanceToBoundaryPostOfOwnFieldPart_distanceAndDiameterIsCorrect()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_9.txt");
	LidarImpl lidar(hardwareLidar);
	RobotPosition ownPosition(Point(0, 0), 0);

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(ownPosition);

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(3.2);
	vector<LidarObject> farDistantObjects;

	for (vector<LidarObject>::const_iterator i = objectsInForeground.begin(); i != objectsInForeground.end(); ++i)
	{
		double distance = ownPosition.distanceTo(i->getCenter());
		if (distance > 2.5)
			farDistantObjects.push_back(*i);
	}

	CPPUNIT_ASSERT_EQUAL((size_t)1, farDistantObjects.size());
	const LidarObject &object = farDistantObjects.front();
	double distance = ownPosition.distanceTo(object.getCenter());
	Compare compare(0.05);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(3.06, distance));
	CPPUNIT_ASSERT(compare.isFuzzyEqual(0.06, object.getDiameter()));
}

void LidarTest::getAllObjects_twoObjectsInFrontOfWall_objectCountIs2()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_11.txt");
	LidarImpl lidar(hardwareLidar);
	RobotPosition ownPosition(Point(0, 0), 0);

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(ownPosition);

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(2);
	vector<LidarObject> objectsWithSmallDiameter;
	for (vector<LidarObject>::const_iterator i = objectsInForeground.begin(); i != objectsInForeground.end(); ++i)
		if (i->getDiameter() < 0.1)
			objectsWithSmallDiameter.push_back(*i);
	CPPUNIT_ASSERT_EQUAL((size_t)2, objectsWithSmallDiameter.size());
}

void LidarTest::getAllObjects_twoObjectsWithADistanceOfOneMeter_objectCountIs2()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_12.txt");
	LidarImpl lidar(hardwareLidar);
	RobotPosition ownPosition(Point(0, 0), 0);

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(ownPosition);

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(1);
	vector<LidarObject> objectsWithSmallDiameter;
	for (vector<LidarObject>::const_iterator i = objectsInForeground.begin(); i != objectsInForeground.end(); ++i)
		if (i->getDiameter() < 0.1)
			objectsWithSmallDiameter.push_back(*i);
	CPPUNIT_ASSERT_EQUAL((size_t)2, objectsWithSmallDiameter.size());
}

void LidarTest::isObstacleInFront_noObstacleInFront_false()
{
	Hardware::LidarMock hardwareLidar;
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(!lidar.isObstacleInFront(1));
}

void LidarTest::isObstacleInFront_puckCollected_false()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_10.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(!lidar.isObstacleInFront(0));
}

void LidarTest::isObstacleInFront_obstacleOnLeftSide_true()
{
	Hardware::LidarMock hardwareLidar;
	LidarImpl lidar(hardwareLidar);

	for (unsigned int i = 200; i < 300; ++i)
		hardwareLidar.setValueForAngle(i, 0.1);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(lidar.isObstacleInFront(1));
}

void LidarTest::isObstacleInFront_obstacleOnRightSide_true()
{
	Hardware::LidarMock hardwareLidar;
	LidarImpl lidar(hardwareLidar);

	for (unsigned int i = 50; i < 150; ++i)
		hardwareLidar.setValueForAngle(i, 0.1);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(lidar.isObstacleInFront(1));
}

void LidarTest::isObstacleInFront_severalBoundPostsAndOtherRobotFarAway_false()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_13.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(!lidar.isObstacleInFront(0.5));
}

void LidarTest::isObstacleInFront_robotVeryCloseAtTheSide_true()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_14.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(lidar.isObstacleInFront(0.5));
}
