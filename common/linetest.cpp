#include "common/linetest.h"
#include "common/line.h"
#include "common/circle.h"

using namespace RoboHockey::Common;

void LineTest::getIntersectPoints_circleWithNoIntersects_intersectPointsCountIs0()
{
	Line line(Point(-2,2), Point(2,2));

	CPPUNIT_ASSERT_EQUAL((size_t)0, line.getIntersectPoints(Circle(Point(0, 0), 1)).size());
}

void LineTest::getIntersectPoints_circleToutchesLine_intersectPointsCountIs1()
{
	Line line(Point(-2,2), Point(2,2));

	CPPUNIT_ASSERT_EQUAL((size_t)1, line.getIntersectPoints(Circle(Point(0, 0), 4)).size());
}

void LineTest::getIntersectPoints_circleIntersectsLine_intersectPointsCountIs2()
{
	Line line(Point(-2,2), Point(2,2));

	CPPUNIT_ASSERT_EQUAL((size_t)2, line.getIntersectPoints(Circle(Point(0, 0), 5)).size());
}
