#include "common/linetest.h"
#include "common/line.h"
#include "common/circle.h"
#include "common/compare.h"

using namespace RoboHockey::Common;

void LineTest::getIntersectPoints_circleWithNoIntersects_intersectPointsCountIs0()
{
	Line line(Point(-2,2), Point(2,2));

	CPPUNIT_ASSERT_EQUAL((size_t)0, line.getIntersectPoints(Circle(Point(0,0), 1)).size());
}

void LineTest::getIntersectPoints_circleToutchesLine_intersectPointsCountIs1()
{
	Line line(Point(-2,2), Point(2,2));

	CPPUNIT_ASSERT_EQUAL((size_t)1, line.getIntersectPoints(Circle(Point(0,0), 4)).size());
}

void LineTest::getIntersectPoints_circleIntersectsLine_intersectPointsCountIs2()
{
	Line line(Point(-2,2), Point(2,2));

	CPPUNIT_ASSERT_EQUAL((size_t)2, line.getIntersectPoints(Circle(Point(0,0), 5)).size());
}

void LineTest::getIntersectPoints_circleToutchesLineAt0And2_intersectPointsIs0And2()
{

	Line line(Point(-2,2), Point(2,2));

	CPPUNIT_ASSERT(Point(0,2) == line.getIntersectPoints(Circle(Point(0,0), 4)).front());
}

void LineTest::getIntersectPoints_circleIntersectsLineAtMinus1And1_intersectPointsIsMinus1And1()
{
	Compare compare(0.0001);
	Line line(Point(-2,1), Point(2,1));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(-1,1), line.getIntersectPoints(Circle(Point(0,0), 2.8284)).back()));
}

void LineTest::getIntersectPoints_circleIntersectsLineAt1And1_intersectPointsIs1And1()
{
	Compare compare(0.0001);
	Line line(Point(-2,1), Point(2,1));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1,1), line.getIntersectPoints(Circle(Point(0,0), 2.8284)).front()));
}

void LineTest::getIntersectPoints_circleAt1And1IntersectsLineAt2And2_intersectPointsIs2And2()
{
	Compare compare(0.0001);
	Line line(Point(-2,2), Point(3,2));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2,2), line.getIntersectPoints(Circle(Point(1,1), 2.8284)).front()));
}

void LineTest::getIntersectPoints_lineIsVertical_intersectPointIsMinus1AndMinus1()
{
	Compare compare(0.0001);
	Line line(Point(-1,-2), Point(-1,3));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(-1,-1), line.getIntersectPoints(Circle(Point(0,0), 2.8284)).back()));
}

void LineTest::getIntersectPoints_lineIsVerticalAndCircleIsNotAt0And0_intersectPointIs2And2()
{
	Compare compare(0.0001);
	Line line(Point(2,0), Point(2,5));

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2,2), line.getIntersectPoints(Circle(Point(3,3), 2.8284)).back()));
}

void LineTest::getIntersectPoints_circleBehindEndPointWithNoIntersects_intersectPointsCountIs0()
{
	Line line(Point(-2,2), Point(2,2));

	CPPUNIT_ASSERT_EQUAL((size_t)0, line.getIntersectPoints(Circle(Point(4,2), 1)).size());
}

void LineTest::getIntersectPoints_circleOverEndPointWithNoIntersects_intersectPointsCountIs0()
{
	Line line(Point(3.7,0), Point(4,1.9));

	CPPUNIT_ASSERT_EQUAL((size_t)0, line.getIntersectPoints(Circle(Point(4,2), 1)).size());
}
