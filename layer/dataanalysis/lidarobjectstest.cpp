#include "layer/dataanalysis/lidarobjectstest.h"
#include "layer/dataanalysis/lidarobjects.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::DataAnalysis;

void LidarObjectsTest::addObject_onceCalled_objectCountIs1()
{
	LidarObjects objects;
	LidarObject objectOne(Point(3, 4), 2);

	objects.addObject(objectOne);

	CPPUNIT_ASSERT_EQUAL((size_t)1, objects.getObjectCount());
}

void LidarObjectsTest::getObjectsWithDistanceBelow_twoObjectsBelowAndOneNot_resultSizeIs2()
{
	LidarObjects objects;
	LidarObject objectOne(Point(3, 4), 2);
	LidarObject objectTwo(Point(5, -3), 1);
	LidarObject objectThree(Point(50, 10), 1);
	objects.addObject(objectOne);
	objects.addObject(objectThree);
	objects.addObject(objectTwo);

	vector<LidarObject> result = objects.getObjectsWithDistanceBelow(Point(0, 0), 10);

	CPPUNIT_ASSERT_EQUAL((size_t)2, result.size());
}

void LidarObjectsTest::getObjectsInRegionOfInterest_twoInsideAndThreeNot_resultSizeIs2()
{
	LidarObjects objects;
	LidarObject objectOne(Point(3, 4), 2);
	LidarObject objectTwo(Point(5, 3), 1);
	LidarObject objectThree(Point(50, 10), 1);
	LidarObject objectFour(Point(0, 0), 1);
	LidarObject objectFive(Point(-10, -5), 1);
	objects.addObject(objectOne);
	objects.addObject(objectTwo);
	objects.addObject(objectThree);
	objects.addObject(objectFour);
	objects.addObject(objectFive);

	list<LidarObject> result = objects.getObjectsInRegionOfInterest(Rectangle(Point(-1, -1), Point(10, 10)));

	CPPUNIT_ASSERT_EQUAL((size_t)3, result.size());
}