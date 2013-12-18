#include "layer/dataanalysis/lidartest.h"
#include "layer/dataanalysis/lidarimpl.h"
#include "layer/hardware/lidarmock.h"
#include "common/compare.h"
#include "common/robotposition.h"
#include <math.h>
#include <assert.h>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

const double LidarTest::m_maximumDistance = 0.5;
const Angle LidarTest::m_maximumAngle = 10.0/180*M_PI;

void LidarTest::constructor_empty_maximumAngleLeftIs0()
{
	Hardware::LidarMock hardwareLidar;
	LidarImpl lidar(hardwareLidar);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, lidar.getMaximumAngleLeft().getValueBetweenMinusPiAndPi(), 0.0001);
}

void LidarTest::constructor_empty_maximumAngleRightIs0()
{
	Hardware::LidarMock hardwareLidar;
	LidarImpl lidar(hardwareLidar);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, lidar.getMaximumAngleRight().getValueBetweenMinusPiAndPi(), 0.0001);
}

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

void LidarTest::getAllObjects_oneObjectBehindAnotherOneLeft_objectCountIsAtLeast1()
{
	Hardware::LidarMock hardwareLidar(10);
	hardwareLidar.setValueForAngle(150, 2.010);
	hardwareLidar.setValueForAngle(151, 2.005);
	hardwareLidar.setValueForAngle(152, 2.000);
	hardwareLidar.setValueForAngle(153, 2.005);
	hardwareLidar.setValueForAngle(154, 2.010);
	hardwareLidar.setValueForAngle(155, 4.010);
	hardwareLidar.setValueForAngle(156, 4.005);
	hardwareLidar.setValueForAngle(157, 4.000);
	hardwareLidar.setValueForAngle(158, 4.005);
	hardwareLidar.setValueForAngle(159, 4.010);
	LidarImpl lidar(hardwareLidar);
	RobotPosition ownPosition(Point(1, 2), M_PI*(-0.5));

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(ownPosition);

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(5);
	CPPUNIT_ASSERT(objectsInForeground.size() >= 1);
}

void LidarTest::getAllObjects_oneObjectBehindAnotherOneRight_objectCountIsAtLeast1()
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
	CPPUNIT_ASSERT(objectsInForeground.size() >= 1);
}

void LidarTest::getAllObjects_objectAtLeftBorder_objectCountIs0()
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
	CPPUNIT_ASSERT_EQUAL((size_t)0, objectsInForeground.size());
}

void LidarTest::getAllObjects_objectAtRightBorder_objectCountIs0()
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
	CPPUNIT_ASSERT_EQUAL((size_t)0, objectsInForeground.size());
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
		double distance = ownPosition.getPosition().distanceTo(i->getCenter());
		if (distance > 2.5)
			farDistantObjects.push_back(*i);
	}

	CPPUNIT_ASSERT_EQUAL((size_t)1, farDistantObjects.size());
	const LidarObject &object = farDistantObjects.front();
	double distance = ownPosition.getPosition().distanceTo(object.getCenter());
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

void LidarTest::getAllObjects_twoBorderStonesInFrontOfWall_objectCountIs2()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_36.txt");
	LidarImpl lidar(hardwareLidar);
	RobotPosition ownPosition(Point(0, 0), 0);

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(ownPosition);

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(1);
	CPPUNIT_ASSERT_EQUAL((size_t)2, objectsInForeground.size());
}

void LidarTest::getAllObjects_puckInFrontOfOtherRobot_puckIsDetetected()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_37.txt");
	LidarImpl lidar(hardwareLidar);
	RobotPosition ownPosition(Point(0, 0), 0);

	lidar.updateSensorData();
	LidarObjects objects = lidar.getAllObjects(ownPosition);

	vector<LidarObject> objectsInForeground = objects.getObjectsWithDistanceBelow(1);
	CPPUNIT_ASSERT_EQUAL((size_t)1, objectsInForeground.size());
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

	CPPUNIT_ASSERT(!lidar.isObstacleInFront(0.5));
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

	CPPUNIT_ASSERT(lidar.isObstacleInFront(0));
}

void LidarTest::isObstacleInFront_robotVeryCloseAheadAtTheSide_true()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_15.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(lidar.isObstacleInFront(0.5));
}

void LidarTest::isObstacleInFront_robotFarDistance_false()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_16.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(!lidar.isObstacleInFront(0.5));
}

void LidarTest::isObstacleInFront_robotAtTheSide_false()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_38.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(!lidar.isObstacleInFront(0.5));
}

void LidarTest::isPuckCollected_noPuckInCloseDistance_false()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_17.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(!lidar.isPuckCollected());
}

void LidarTest::isPuckCollected_closeEnough_true()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_18.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(lidar.isPuckCollected());
}

void LidarTest::isPuckCollected_directInTheMiddle_true()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_19.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(lidar.isPuckCollected());
}

void LidarTest::isPuckCollected_atLeftEndOfClutch_true()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_20.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(lidar.isPuckCollected());
}

void LidarTest::isPuckCollected_atRightEndOfClutch_true()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_21.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(lidar.isPuckCollected());
}

void LidarTest::isPuckCollected_rightOfClutch_false()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_22.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(!lidar.isPuckCollected());
}

void LidarTest::isPuckCollected_leftOfClutch_false()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_23.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(!lidar.isPuckCollected());
}

void LidarTest::isPuckCollected_asDistantAsAfterOneQuarterTurn_true()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_24.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(lidar.isPuckCollected());
}

void LidarTest::isPuckCollected_slightlyMoreDistantThanOneQuarterTurn_false()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_25.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(!lidar.isPuckCollected());
}

void LidarTest::isPuckCollectable_noPuckInCloseDistance_false()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_17.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(!lidar.isPuckCollectable(m_maximumDistance, m_maximumAngle));
}

void LidarTest::isPuckCollectable_puckCollected_true()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_21.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(lidar.isPuckCollectable(m_maximumDistance, m_maximumAngle));
}

void LidarTest::isPuckCollectable_puckStraightAheadCloseEnough_true()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_26.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(lidar.isPuckCollectable(m_maximumDistance, m_maximumAngle));
}

void LidarTest::isPuckCollectable_puckStraightAheadButTooDistant_false()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_27.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(!lidar.isPuckCollectable(m_maximumDistance, m_maximumAngle));
}

void LidarTest::isPuckCollectable_puckCloseAndALittleBitLeft_true()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_28.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(lidar.isPuckCollectable(m_maximumDistance, m_maximumAngle));
}

void LidarTest::isPuckCollectable_puckCloseAndALittleBitRight_true()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_29.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(lidar.isPuckCollectable(m_maximumDistance, m_maximumAngle));
}

void LidarTest::isPuckCollectable_puckCloseButTooMuchLeft_false()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_30.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(!lidar.isPuckCollectable(m_maximumDistance, m_maximumAngle));
}

void LidarTest::isPuckCollectable_puckCloseButTooMuchRight_false()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_31.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(!lidar.isPuckCollectable(m_maximumDistance, m_maximumAngle));
}

void LidarTest::isPuckCollectable_twoPucksBeside_true()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_32.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(lidar.isPuckCollectable(m_maximumDistance, m_maximumAngle));
}

void LidarTest::isPuckCollectable_onePuckCloseEnoughtAndAnotherOneStraightAhead_false()
{
	Hardware::LidarMock hardwareLidar;
	hardwareLidar.readSensorDataFromFile("resources/testfiles/lidar_33.txt");
	LidarImpl lidar(hardwareLidar);
	lidar.updateSensorData();

	CPPUNIT_ASSERT(!lidar.isPuckCollectable(m_maximumDistance, m_maximumAngle));
}

void LidarTest::getMaximumAngleLeft_noObjects_piHalf()
{
	Hardware::LidarMock hardwareLidar;
	LidarImpl lidar(hardwareLidar);

	lidar.updateSensorData();
	Angle angle = lidar.getMaximumAngleLeft();

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), angle));
}

void LidarTest::getMaximumAngleRight_noObjects_minusPiHalf()
{
	Hardware::LidarMock hardwareLidar;
	LidarImpl lidar(hardwareLidar);

	lidar.updateSensorData();
	Angle angle = lidar.getMaximumAngleRight();

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getThreeQuarterRotation(), angle));
}

void LidarTest::getMaximumAngleLeft_objectAtLeftBorder_reducedViewArea()
{
	Hardware::LidarMock hardwareLidar(10);
	hardwareLidar.setValueForAngle(358, 2.5);
	hardwareLidar.setValueForAngle(359, 2.5);
	hardwareLidar.setValueForAngle(360, 2.5);
	LidarImpl lidar(hardwareLidar);

	lidar.updateSensorData();
	Angle angle = lidar.getMaximumAngleLeft();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1.545, angle.getValueBetweenMinusPiAndPi(), 0.01);
}

void LidarTest::getMaximumAngleRight_objectAtRightBorder_reducedViewArea()
{
	Hardware::LidarMock hardwareLidar(10);
	hardwareLidar.setValueForAngle(0, 2.5);
	hardwareLidar.setValueForAngle(1, 2.5);
	hardwareLidar.setValueForAngle(2, 2.5);
	LidarImpl lidar(hardwareLidar);

	lidar.updateSensorData();
	Angle angle = lidar.getMaximumAngleRight();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.545, angle.getValueBetweenMinusPiAndPi(), 0.01);
}

void LidarTest::canBeSeen_noObjectBetween_true()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(1, 0), 0.5);
	RobotPosition ownPosition(Point(0, 0), Angle(0));

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(canBeSeen);
}

void LidarTest::canBeSeen_atLeftEdgeOfViewArea_true()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(-0.1, 1), 0.5);
	RobotPosition ownPosition(Point(0, 0), Angle(0));

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(canBeSeen);
}

void LidarTest::canBeSeen_atRightEdgeOfViewArea_true()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(-0.1, -1), 0.5);
	RobotPosition ownPosition(Point(0, 0), Angle(0));

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(canBeSeen);
}

void LidarTest::canBeSeen_outsideOfViewArea_false()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(-1, 1), 0.5);
	RobotPosition ownPosition(Point(0, 0), Angle(0));

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(!canBeSeen);
}

void LidarTest::canBeSeen_totallyCoveredByOtherObject_false()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(2, 0), 0.1);
	RobotPosition ownPosition(Point(0, 0), Angle(0));
	hardwareLidar.setValueForAngle(0, 3);
	hardwareLidar.setValueForAngle(175, 0.5);
	hardwareLidar.setValueForAngle(176, 0.5);
	hardwareLidar.setValueForAngle(177, 0.5);
	hardwareLidar.setValueForAngle(178, 0.5);
	hardwareLidar.setValueForAngle(179, 0.5);
	hardwareLidar.setValueForAngle(180, 0.5);
	hardwareLidar.setValueForAngle(181, 0.5);
	hardwareLidar.setValueForAngle(182, 0.5);
	hardwareLidar.setValueForAngle(183, 0.5);
	hardwareLidar.setValueForAngle(184, 0.5);
	hardwareLidar.setValueForAngle(185, 0.5);
	hardwareLidar.setValueForAngle(360, 3);

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(!canBeSeen);
}

void LidarTest::canBeSeen_fromRightSideCoveredByOtherObject_true()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(2, 0), 0.1);
	RobotPosition ownPosition(Point(0, 0), Angle(0));
	hardwareLidar.setValueForAngle(0, 3);
	hardwareLidar.setValueForAngle(175, 0.5);
	hardwareLidar.setValueForAngle(176, 0.5);
	hardwareLidar.setValueForAngle(177, 0.5);
	hardwareLidar.setValueForAngle(178, 0.5);
	hardwareLidar.setValueForAngle(179, 0.5);
	hardwareLidar.setValueForAngle(180, 0.5);
	hardwareLidar.setValueForAngle(181, 0.5);
	hardwareLidar.setValueForAngle(360, 3);

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(canBeSeen);
}

void LidarTest::canBeSeen_fromLeftSideCoveredByOtherObject_true()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(2, 0), 0.1);
	RobotPosition ownPosition(Point(0, 0), Angle(0));
	hardwareLidar.setValueForAngle(0, 3);
	hardwareLidar.setValueForAngle(179, 0.5);
	hardwareLidar.setValueForAngle(180, 0.5);
	hardwareLidar.setValueForAngle(181, 0.5);
	hardwareLidar.setValueForAngle(182, 0.5);
	hardwareLidar.setValueForAngle(183, 0.5);
	hardwareLidar.setValueForAngle(184, 0.5);
	hardwareLidar.setValueForAngle(185, 0.5);
	hardwareLidar.setValueForAngle(360, 3);

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(canBeSeen);
}

void LidarTest::canBeSeen_partlyCoveredFromBothSides_true()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(2, 0), 0.1);
	RobotPosition ownPosition(Point(0, 0), Angle(0));
	hardwareLidar.setValueForAngle(0, 3);
	hardwareLidar.setValueForAngle(175, 0.5);
	hardwareLidar.setValueForAngle(176, 0.5);
	hardwareLidar.setValueForAngle(177, 0.5);
	hardwareLidar.setValueForAngle(178, 0.5);
	hardwareLidar.setValueForAngle(179, 0.5);
	hardwareLidar.setValueForAngle(181, 0.5);
	hardwareLidar.setValueForAngle(182, 0.5);
	hardwareLidar.setValueForAngle(183, 0.5);
	hardwareLidar.setValueForAngle(184, 0.5);
	hardwareLidar.setValueForAngle(185, 0.5);
	hardwareLidar.setValueForAngle(360, 3);

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(canBeSeen);
}

void LidarTest::canBeSeen_totallyCoveredFromBothSides_false()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(2, 0), 0.1);
	RobotPosition ownPosition(Point(0, 0), Angle(0));
	hardwareLidar.setValueForAngle(0, 3);
	hardwareLidar.setValueForAngle(175, 1);
	hardwareLidar.setValueForAngle(176, 1);
	hardwareLidar.setValueForAngle(177, 1);
	hardwareLidar.setValueForAngle(178, 1);
	hardwareLidar.setValueForAngle(179, 1);
	hardwareLidar.setValueForAngle(180, 1);
	hardwareLidar.setValueForAngle(181, 1);
	hardwareLidar.setValueForAngle(182, 0.5);
	hardwareLidar.setValueForAngle(183, 0.5);
	hardwareLidar.setValueForAngle(184, 0.5);
	hardwareLidar.setValueForAngle(185, 0.5);
	hardwareLidar.setValueForAngle(360, 3);

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(!canBeSeen);
}

void LidarTest::canBeSeen_inFrontOfObject_true()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(1.9, 0), 0.1);
	RobotPosition ownPosition(Point(0, 0), Angle(0));
	hardwareLidar.setValueForAngle(0, 3);
	hardwareLidar.setValueForAngle(170, 2);
	hardwareLidar.setValueForAngle(171, 2);
	hardwareLidar.setValueForAngle(172, 2);
	hardwareLidar.setValueForAngle(173, 2);
	hardwareLidar.setValueForAngle(174, 2);
	hardwareLidar.setValueForAngle(175, 2);
	hardwareLidar.setValueForAngle(176, 2);
	hardwareLidar.setValueForAngle(177, 2);
	hardwareLidar.setValueForAngle(178, 2);
	hardwareLidar.setValueForAngle(179, 2);
	hardwareLidar.setValueForAngle(180, 2);
	hardwareLidar.setValueForAngle(181, 2);
	hardwareLidar.setValueForAngle(182, 2);
	hardwareLidar.setValueForAngle(183, 2);
	hardwareLidar.setValueForAngle(184, 2);
	hardwareLidar.setValueForAngle(185, 2);
	hardwareLidar.setValueForAngle(186, 2);
	hardwareLidar.setValueForAngle(187, 2);
	hardwareLidar.setValueForAngle(188, 2);
	hardwareLidar.setValueForAngle(189, 2);
	hardwareLidar.setValueForAngle(190, 2);
	hardwareLidar.setValueForAngle(360, 3);

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(canBeSeen);
}

void LidarTest::canBeSeen_inFrontOfObjectShiftedAndRotated_true()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(1, 2.9), 0.1);
	RobotPosition ownPosition(Point(1, 1), Angle::getQuarterRotation());
	hardwareLidar.setValueForAngle(0, 3);
	hardwareLidar.setValueForAngle(170, 2);
	hardwareLidar.setValueForAngle(171, 2);
	hardwareLidar.setValueForAngle(172, 2);
	hardwareLidar.setValueForAngle(173, 2);
	hardwareLidar.setValueForAngle(174, 2);
	hardwareLidar.setValueForAngle(175, 2);
	hardwareLidar.setValueForAngle(176, 2);
	hardwareLidar.setValueForAngle(177, 2);
	hardwareLidar.setValueForAngle(178, 2);
	hardwareLidar.setValueForAngle(179, 2);
	hardwareLidar.setValueForAngle(180, 2);
	hardwareLidar.setValueForAngle(181, 2);
	hardwareLidar.setValueForAngle(182, 2);
	hardwareLidar.setValueForAngle(183, 2);
	hardwareLidar.setValueForAngle(184, 2);
	hardwareLidar.setValueForAngle(185, 2);
	hardwareLidar.setValueForAngle(186, 2);
	hardwareLidar.setValueForAngle(187, 2);
	hardwareLidar.setValueForAngle(188, 2);
	hardwareLidar.setValueForAngle(189, 2);
	hardwareLidar.setValueForAngle(190, 2);
	hardwareLidar.setValueForAngle(360, 3);

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(canBeSeen);
}

void LidarTest::canBeSeen_behindObjectShiftedAndRotated_false()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(1, 4), 0.1);
	RobotPosition ownPosition(Point(1, 1), Angle::getQuarterRotation());
	hardwareLidar.setValueForAngle(0, 3);
	hardwareLidar.setValueForAngle(170, 2);
	hardwareLidar.setValueForAngle(171, 2);
	hardwareLidar.setValueForAngle(172, 2);
	hardwareLidar.setValueForAngle(173, 2);
	hardwareLidar.setValueForAngle(174, 2);
	hardwareLidar.setValueForAngle(175, 2);
	hardwareLidar.setValueForAngle(176, 2);
	hardwareLidar.setValueForAngle(177, 2);
	hardwareLidar.setValueForAngle(178, 2);
	hardwareLidar.setValueForAngle(179, 2);
	hardwareLidar.setValueForAngle(180, 2);
	hardwareLidar.setValueForAngle(181, 2);
	hardwareLidar.setValueForAngle(182, 2);
	hardwareLidar.setValueForAngle(183, 2);
	hardwareLidar.setValueForAngle(184, 2);
	hardwareLidar.setValueForAngle(185, 2);
	hardwareLidar.setValueForAngle(186, 2);
	hardwareLidar.setValueForAngle(187, 2);
	hardwareLidar.setValueForAngle(188, 2);
	hardwareLidar.setValueForAngle(189, 2);
	hardwareLidar.setValueForAngle(190, 2);
	hardwareLidar.setValueForAngle(360, 3);

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(!canBeSeen);
}

void LidarTest::canBeSeen_tooBigObject_true()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(0.5, 0), 2);
	RobotPosition ownPosition(Point(0, 0), Angle(0));

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(canBeSeen);
}

void LidarTest::canBeSeen_objectWithRadius0_true()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(3, 0), 0);
	RobotPosition ownPosition(Point(0, 0), Angle(0));
	hardwareLidar.setValueForAngle(0, 3);
	hardwareLidar.setValueForAngle(170, 2);
	hardwareLidar.setValueForAngle(171, 2);
	hardwareLidar.setValueForAngle(172, 2);
	hardwareLidar.setValueForAngle(173, 2);
	hardwareLidar.setValueForAngle(174, 2);
	hardwareLidar.setValueForAngle(175, 2);
	hardwareLidar.setValueForAngle(176, 2);
	hardwareLidar.setValueForAngle(177, 2);
	hardwareLidar.setValueForAngle(178, 2);
	hardwareLidar.setValueForAngle(179, 2);
	hardwareLidar.setValueForAngle(180, 2);
	hardwareLidar.setValueForAngle(181, 2);
	hardwareLidar.setValueForAngle(182, 2);
	hardwareLidar.setValueForAngle(183, 2);
	hardwareLidar.setValueForAngle(184, 2);
	hardwareLidar.setValueForAngle(185, 2);
	hardwareLidar.setValueForAngle(186, 2);
	hardwareLidar.setValueForAngle(187, 2);
	hardwareLidar.setValueForAngle(188, 2);
	hardwareLidar.setValueForAngle(189, 2);
	hardwareLidar.setValueForAngle(190, 2);
	hardwareLidar.setValueForAngle(360, 3);

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(canBeSeen);
}

void LidarTest::canBeSeen_obstacleRightLowerInFront_true()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(0.5, -0.5), 0.1);
	RobotPosition ownPosition(Point(0, 0), Angle(0));
	hardwareLidar.setValueForAngle(0, 3);
	hardwareLidar.setValueForAngle(80, 2);
	hardwareLidar.setValueForAngle(81, 2);
	hardwareLidar.setValueForAngle(82, 2);
	hardwareLidar.setValueForAngle(83, 2);
	hardwareLidar.setValueForAngle(84, 2);
	hardwareLidar.setValueForAngle(85, 2);
	hardwareLidar.setValueForAngle(86, 2);
	hardwareLidar.setValueForAngle(87, 2);
	hardwareLidar.setValueForAngle(88, 2);
	hardwareLidar.setValueForAngle(89, 2);
	hardwareLidar.setValueForAngle(90, 2);
	hardwareLidar.setValueForAngle(91, 2);
	hardwareLidar.setValueForAngle(92, 2);
	hardwareLidar.setValueForAngle(93, 2);
	hardwareLidar.setValueForAngle(94, 2);
	hardwareLidar.setValueForAngle(95, 2);
	hardwareLidar.setValueForAngle(96, 2);
	hardwareLidar.setValueForAngle(97, 2);
	hardwareLidar.setValueForAngle(98, 2);
	hardwareLidar.setValueForAngle(99, 2);
	hardwareLidar.setValueForAngle(100, 2);
	hardwareLidar.setValueForAngle(360, 3);

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(canBeSeen);
}

void LidarTest::canBeSeen_obstacleRightLowerBehind_false()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(2, -2), 0.1);
	RobotPosition ownPosition(Point(0, 0), Angle(0));
	hardwareLidar.setValueForAngle(0, 3);
	hardwareLidar.setValueForAngle(80, 1);
	hardwareLidar.setValueForAngle(81, 1);
	hardwareLidar.setValueForAngle(82, 1);
	hardwareLidar.setValueForAngle(83, 1);
	hardwareLidar.setValueForAngle(84, 1);
	hardwareLidar.setValueForAngle(85, 1);
	hardwareLidar.setValueForAngle(86, 1);
	hardwareLidar.setValueForAngle(87, 1);
	hardwareLidar.setValueForAngle(88, 1);
	hardwareLidar.setValueForAngle(89, 1);
	hardwareLidar.setValueForAngle(90, 1);
	hardwareLidar.setValueForAngle(91, 1);
	hardwareLidar.setValueForAngle(92, 1);
	hardwareLidar.setValueForAngle(93, 1);
	hardwareLidar.setValueForAngle(94, 1);
	hardwareLidar.setValueForAngle(95, 1);
	hardwareLidar.setValueForAngle(96, 1);
	hardwareLidar.setValueForAngle(97, 1);
	hardwareLidar.setValueForAngle(98, 1);
	hardwareLidar.setValueForAngle(99, 1);
	hardwareLidar.setValueForAngle(100, 1);
	hardwareLidar.setValueForAngle(360, 3);

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(!canBeSeen);
}

void LidarTest::canBeSeen_objectMoreThanFourMetersAway_false()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(4.06, 0), 0.1);
	RobotPosition ownPosition(Point(0, 0), Angle(0));
	hardwareLidar.setValueForAngle(0, 3);
	hardwareLidar.setValueForAngle(360, 3);

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(!canBeSeen);
}

void LidarTest::canBeSeen_objectLessThanFourMetersAway_true()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(4.04, 0), 0.1);
	RobotPosition ownPosition(Point(0, 0), Angle(0));
	hardwareLidar.setValueForAngle(0, 3);
	hardwareLidar.setValueForAngle(360, 3);

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(canBeSeen);
}

void LidarTest::canBeSeen_objectRightAndLookingLeft_false()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(1, 0), 0.1);
	RobotPosition ownPosition(Point(0, 0), Angle::getHalfRotation());
	hardwareLidar.setValueForAngle(0, 3);
	hardwareLidar.setValueForAngle(360, 3);

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(!canBeSeen);
}

void LidarTest::canBeSeen_objectRightLowerAndLookingLeft_false()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(1, -1), 0.1);
	RobotPosition ownPosition(Point(0, 0), Angle::getHalfRotation());
	hardwareLidar.setValueForAngle(0, 3);
	hardwareLidar.setValueForAngle(360, 3);

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(!canBeSeen);
}

void LidarTest::canBeSeen_objectDirectBehindOtherObstacle_true()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(2.1, 0), 0.1);
	RobotPosition ownPosition(Point(0, 0), Angle(0));
	hardwareLidar.setValueForAngle(0, 3);
	hardwareLidar.setValueForAngle(170, 2);
	hardwareLidar.setValueForAngle(171, 2);
	hardwareLidar.setValueForAngle(172, 2);
	hardwareLidar.setValueForAngle(173, 2);
	hardwareLidar.setValueForAngle(174, 2);
	hardwareLidar.setValueForAngle(175, 2);
	hardwareLidar.setValueForAngle(176, 2);
	hardwareLidar.setValueForAngle(177, 2);
	hardwareLidar.setValueForAngle(178, 2);
	hardwareLidar.setValueForAngle(179, 2);
	hardwareLidar.setValueForAngle(180, 2);
	hardwareLidar.setValueForAngle(181, 2);
	hardwareLidar.setValueForAngle(182, 2);
	hardwareLidar.setValueForAngle(183, 2);
	hardwareLidar.setValueForAngle(184, 2);
	hardwareLidar.setValueForAngle(185, 2);
	hardwareLidar.setValueForAngle(186, 2);
	hardwareLidar.setValueForAngle(187, 2);
	hardwareLidar.setValueForAngle(188, 2);
	hardwareLidar.setValueForAngle(189, 2);
	hardwareLidar.setValueForAngle(190, 2);
	hardwareLidar.setValueForAngle(360, 3);

	lidar.updateSensorData();
	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(canBeSeen);
}

void LidarTest::canBeSeen_robotNotInOriginObjectVisible_true()
{
	Hardware::LidarMock hardwareLidar(10);
	LidarImpl lidar(hardwareLidar);
	Circle circle(Point(2.18, 3.51), 0.07);
	RobotPosition ownPosition(Point(1, 2), Angle(0));
	hardwareLidar.setValueForAngle(0, 3);
	hardwareLidar.setValueForAngle(360, 3);

	hardwareLidar.setValueForAngle(282, 1.88);
	hardwareLidar.setValueForAngle(283, 1.88);
	hardwareLidar.setValueForAngle(284, 1.88);
	hardwareLidar.setValueForAngle(285, 1.88);
	hardwareLidar.setValueForAngle(286, 1.88);

	lidar.updateSensorData();

	bool canBeSeen = lidar.canBeSeen(circle, ownPosition);

	CPPUNIT_ASSERT(canBeSeen);
}
