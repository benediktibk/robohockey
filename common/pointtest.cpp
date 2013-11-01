#include "common/pointtest.h"
#include "common/point.h"
#include <sstream>

using namespace RoboHockey::Common;

void PointTest::constructor_empty_xIs0()
{
	Point point;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, point.getX(), 0.0001);
}

void PointTest::constructor_empty_yIs0()
{
	Point point;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, point.getY(), 0.0001);
}

void PointTest::constructor_xIs4_xIs4()
{
	Point point(4, 6);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(4, point.getX(), 0.0001);
}

void PointTest::constructor_yIs6_yIs6()
{
	Point point(4, 6);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(6, point.getY(), 0.0001);
}

void PointTest::setX_5_xIs5()
{
	Point point;

	point.setX(5);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, point.getX(), 0.0001);
}

void PointTest::setY_4_yIs4()
{
	Point point;

	point.setY(4);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(4, point.getY(), 0.0001);
}

void PointTest::streamOperator_3And2_32()
{
	Point point(3, 2);
	std::stringstream stream;

	stream << point;

	CPPUNIT_ASSERT_EQUAL(std::string("(3, 2)"), stream.str());
}

void PointTest::operatorMultiply_3And6With2_6And12()
{
	Point point(3, 6);

	CPPUNIT_ASSERT_EQUAL(Point(6, 12), point*2);
}

void PointTest::operatorDivide_3And6With3_1And2()
{
	Point point(3, 6);

	CPPUNIT_ASSERT_EQUAL(Point(1, 2), point/3);
}

void PointTest::operatorAdd_4And3To5And1_9And4()
{
	Point pointOne(4, 3);
	Point pointTwo(5, 1);

	Point result = pointOne + pointTwo;

	CPPUNIT_ASSERT_EQUAL(Point(9, 4), result);
}

void PointTest::operatorMinus_5And3From9And4_4And1()
{
	Point pointOne(9, 4);
	Point pointTwo(5, 3);

	Point result = pointOne - pointTwo;

	CPPUNIT_ASSERT_EQUAL(Point(4, 1), result);
}

void PointTest::fuzzyEqual_totallyEqual_true()
{
	Point pointOne(4, 3);
	Point pointTwo(4, 3);

	CPPUNIT_ASSERT(pointOne.fuzzyEqual(pointTwo, 0.001));
}

void PointTest::fuzzyEqual_totallyUnEqual_false()
{
	Point pointOne(4, 3);
	Point pointTwo(5, 1);


	CPPUNIT_ASSERT(!pointOne.fuzzyEqual(pointTwo, 0.001));
}

void PointTest::fuzzyEqual_nearlyEqual_true()
{
	Point pointOne(4, 3.0001);
	Point pointTwo(3.9999, 3);

	CPPUNIT_ASSERT(pointOne.fuzzyEqual(pointTwo, 0.001));
}

void PointTest::operatorMultpliyAndAssign_3And5With2_6And10()
{
	Point point(3, 5);

	point *= 2;

	CPPUNIT_ASSERT(Point(6, 10).fuzzyEqual(point, 0.0001));
}

void PointTest::zero_empty_bothCoordinatesZero()
{
	CPPUNIT_ASSERT_EQUAL(Point(), Point::zero());
}

void PointTest::distanceTo_from4And5To8And2_5()
{
	Point one(4, 5);
	Point two(8, 2);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, one.distanceTo(two), 0.00001);
}
