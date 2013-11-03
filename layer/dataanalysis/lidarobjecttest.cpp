#include "layer/dataanalysis/lidarobjecttest.h"
#include "layer/dataanalysis/lidarobject.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;

void LidarObjectTest::constructor_empty_diameterIs0()
{
	LidarObject object;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, object.getDiameter(), 0.00001);
}

void LidarObjectTest::constructor_validPosition_positionIsSetOne()
{
	LidarObject object(Point(4, 3), 5);

	CPPUNIT_ASSERT_EQUAL(Point(4, 3), object.getCenter());
}

void LidarObjectTest::constructor_diameterOf5_diameterIs5()
{
	LidarObject object(Point(4, 3), 5);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, object.getDiameter(), 0.00001);
}
