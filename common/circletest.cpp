#include "common/circletest.h"
#include "common/circle.h"
#include "common/compare.h"
#include <math.h>

using namespace std;
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

void CircleTest::getBoundingRectangle_validCircle_correctResult()
{
	Circle circle(Point(2, 1), 2);

	Rectangle result = circle.getBoundingRectangle();

	CPPUNIT_ASSERT_EQUAL(Point(1, 0), result.getLeftLower());
	CPPUNIT_ASSERT_EQUAL(Point(3, 2), result.getRightUpper());
}


void CircleTest::getDistanceTo_euclideanDistance5AndDiameter2_4()
{
	Circle object(Point(0, 0), 2);
	Point point(4, 3);

	double distance = object.getDistanceTo(point);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(4, distance, 0.00001);
}

void CircleTest::overlapsWith_farAway_false()
{
	Circle one(Point(-5, 2), 1);
	Circle two(Point(10, -4), 0.5);

	CPPUNIT_ASSERT(!one.overlapsWith(two));
}

void CircleTest::overlapsWith_secondOneInsideFirstOne_true()
{
	Circle one(Point(-5, 2), 10);
	Circle two(Point(-4, 1), 1);

	CPPUNIT_ASSERT(one.overlapsWith(two));
}

void CircleTest::overlapsWith_firstOneInsideSecondOne_true()
{
	Circle one(Point(0, 1), 0.25);
	Circle two(Point(0, -1), 5);

	CPPUNIT_ASSERT(one.overlapsWith(two));
}

void CircleTest::overlapsWith_touching_true()
{
	Circle one(Point(1, 0), 2);
	Circle two(Point(-1, 0), 2);

	CPPUNIT_ASSERT(one.overlapsWith(two));
}

void CircleTest::overlapsWith_crossingWithCenterOutside_true()
{
	Circle one(Point(1, 2), 3);
	Circle two(Point(1.5, 2.5), 2);

	CPPUNIT_ASSERT(one.overlapsWith(two));
}

void CircleTest::overlapsWith_crossingWithCenterInside_true()
{
	Circle one(Point(1, 2), 3);
	Circle two(Point(1.25, 2.25), 2);

	CPPUNIT_ASSERT(one.overlapsWith(two));
}

void CircleTest::overlapsWith_closeTogetherButTooSmallDiameters_false()
{
	Circle one(Point(1, 2), 0.25);
	Circle two(Point(1, 2.5), 0.2);

	CPPUNIT_ASSERT(!one.overlapsWith(two));
}

void CircleTest::getIntersectionPoints_farAway_resultSizeIs0()
{
	Circle one(Point(10, 20), 1);
	Circle two(Point(-10, 4), 2);

	vector<Point> result = one.getIntersectionPoints(two);

	CPPUNIT_ASSERT_EQUAL((size_t)0, result.size());
}

void CircleTest::getIntersectionPoints_touching_resultSizeIs1()
{
	Circle one(Point(0, 1), 2);
	Circle two(Point(0, -1), 2);

	vector<Point> result = one.getIntersectionPoints(two);

	CPPUNIT_ASSERT_EQUAL((size_t)1, result.size());
}

void CircleTest::getIntersectionPoints_intersecting_resultSizeIs2()
{
	Circle one(Point(0, 1), 2);
	Circle two(Point(0, 0.25), 1);

	vector<Point> result = one.getIntersectionPoints(two);

	CPPUNIT_ASSERT_EQUAL((size_t)2, result.size());
}

void CircleTest::getIntersectionPoints_touching_pointIsCorrect()
{
	Circle one(Point(2, 3), 1);
	Circle two(Point(3, 4), sqrt(2) - 0.5);

	vector<Point> result = one.getIntersectionPoints(two);

	Compare compare(0.01);
	CPPUNIT_ASSERT(result.size() > 0);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2 + 0.5/sqrt(2), 3 + 0.5/sqrt(2)), result.front()));
}

void CircleTest::getIntersectionPoints_intersection_pointsCorrect()
{
	Circle one(Point(-1, 2), 3);
	Circle two(Point(-0.25, 1), 1);

	vector<Point> result = one.getIntersectionPoints(two);

	Compare compare(0.01);
	CPPUNIT_ASSERT(result.size() > 0);
	CPPUNIT_ASSERT(one.isOnCircle(result[0], compare));
	CPPUNIT_ASSERT(one.isOnCircle(result[1], compare));
	CPPUNIT_ASSERT(two.isOnCircle(result[0], compare));
	CPPUNIT_ASSERT(two.isOnCircle(result[1], compare));
}

void CircleTest::isOnCircle_insideTheCircle_false()
{
	Circle circle(Point(1, 2), 0.5);

	Compare compare(0.001);
	CPPUNIT_ASSERT(!circle.isOnCircle(Point(1.2, 2.1), compare));
}

void CircleTest::isOnCircle_outsideTheCircle_false()
{
	Circle circle(Point(1, 2), 0.5);

	Compare compare(0.001);
	CPPUNIT_ASSERT(!circle.isOnCircle(Point(10, 1), compare));
}

void CircleTest::isOnCircle_onTheCircle_true()
{
	Circle circle(Point(1, 2), 0.5);

	Compare compare(0.001);
	Point point(1.15, 2.2);
	CPPUNIT_ASSERT(circle.isOnCircle(point, compare));
}
