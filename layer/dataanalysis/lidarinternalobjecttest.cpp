#include "layer/dataanalysis/lidarinternalobjecttest.h"
#include "layer/dataanalysis/lidarinternalobject.h"
#include "common/compare.h"
#include "common/point.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::DataAnalysis;

void LidarInternalObjectTest::getWidthInMeter_angleWidthIs04AndDistanceIs1_0508497647()
{
	LidarInternalObject object(Angle(0.4), Angle(0), 1);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.508497647, object.getWidthInMeter(), 0.00001);
}

void LidarInternalObjectTest::getWidthInMeter_angleWidthIs0_0()
{
	LidarInternalObject object(Angle(0), Angle(0), 1);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, object.getWidthInMeter(), 0.00001);
}

void LidarInternalObjectTest::getPositionRelativeToRobot_objectInFrontOneMeterAway_1And0()
{
	LidarInternalObject object(Angle(0), Angle(0), 1);

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1, 0), object.getPositionRelativeToRobot()));
}

void LidarInternalObjectTest::getPositionRelativeToRobot_objectInFrontOneMeterAwayAndCertainWidth_1254248824And0()
{
	LidarInternalObject object(Angle(0.4), Angle(0), 1);

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1.254248824, 0), object.getPositionRelativeToRobot()));
}

void LidarInternalObjectTest::getPositionRelativeToRobot_objectALittleBitRight_positionIsCorrect()
{
	LidarInternalObject object(Angle(0.4), Angle(-1.2), 1);

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0.454486787260465, -1.16900892708698), object.getPositionRelativeToRobot()));
}
