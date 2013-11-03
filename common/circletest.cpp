#include "common/circletest.h"
#include "common/circle.h"

using namespace RoboHockey::Common;

void CircleTest::constructor_empty_diameterIs0()
{
	Circle circle;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, circle.getDiameter(), 0.00001);
}

void CircleTest::constructor_centerAndDiameter_centerIsCorrect()
{
	Circle circle(Point(3, 6), 1);

	CPPUNIT_ASSERT_EQUAL(Point(3, 6), circle.getCenter());
}

void CircleTest::constructor_centerAndDiameter_diameterIsCorrect()
{
	Circle circle(Point(3, 6), 1);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(1, circle.getDiameter(), 0.00001);
}

void CircleTest::setCenter_4And5_centerIs4And5()
{
	Circle circle;

	circle.setCenter(Point(7, 5));

	CPPUNIT_ASSERT_EQUAL(Point(7, 5), circle.getCenter());
}

void CircleTest::setDiameter_3_diameterIs3()
{
	Circle circle;

	circle.setDiameter(3);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(3, circle.getDiameter(), 0.00001);
}
