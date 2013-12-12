#include "common/pathtest.h"
#include "common/path.h"
#include "common/circle.h"
#include "common/pathintersectpoints.h"
#include "common/compare.h"
#include "common/angle.h"

using namespace RoboHockey::Common;

void PathTest::intersectsWith_circleIntersectsPathFromLeft_resultIsTrue()
{
	Path path(Point(0,0), Point(3,0), 0.4);

	CPPUNIT_ASSERT(path.intersectsWith(Circle(Point(1.5,0.3),0.3)));
}

void PathTest::intersectsWith_circleIntersectsPathFromRight_resultIsTrue()
{
	Path path(Point(0,0), Point(3,0), 0.4);

	CPPUNIT_ASSERT(path.intersectsWith(Circle(Point(1.5,-0.3),0.3)));
}

void PathTest::intersectsWith_circleIntersectsPathFromStart_resultIsTrue()
{
	Path path(Point(0,0), Point(3,0), 0.4);

	CPPUNIT_ASSERT(path.intersectsWith(Circle(Point(-0.3,0),0.3)));
}

void PathTest::intersectsWith_circleIntersectsPathFromEnd_resultIsTrue()
{
	Path path(Point(0,0), Point(3,0), 0.4);

	CPPUNIT_ASSERT(path.intersectsWith(Circle(Point(3.3,0),0.3)));
}

void PathTest::intersectsWith_circleIsInThePath_resultIsTrue()
{
	Path path(Point(0,0), Point(3,0), 0.4);

	CPPUNIT_ASSERT(path.intersectsWith(Circle(Point(1,0.05),0.1)));
}

void PathTest::intersectsWith_circlePassesThePath_resultIsFalse()
{
	Path path(Point(0,0), Point(3,0), 0.4);

	CPPUNIT_ASSERT(!path.intersectsWith(Circle(Point(2,2),0.1)));
}

void PathTest::intersectsWith_pathFromRightToLeftAndCircleFarAwayRight_false()
{
	Path path(Point(0, 0), Point(-10, 0), 0.5);

	CPPUNIT_ASSERT(!path.intersectsWith(Circle(Point(10, 0), 2)));
}

void PathTest::intersectsWith_oneBoundaryPostFarAway_false()
{
	Path path(Point(0, 0), Point(-0.4625, 1.625), 0.38);

	CPPUNIT_ASSERT(!path.intersectsWith(Circle(Point(0.8796, 0.738), 0.0702)));
}

void PathTest::intersectsWith_oneBoundaryPostFarAwaySimplified_false()
{
	Path path(Point(0, 0), Point(-0.5, 2), 0.4);

	CPPUNIT_ASSERT(!path.intersectsWith(Circle(Point(1, 1), 0.1)));
}

void PathTest::isCircleOnPath_circleOnPath_true()
{
	Path path(Point(0,0), Point(-3,0), 0.4);

	CPPUNIT_ASSERT(path.isCircleCenterOnPath(Circle(Point(-1,0.05),0.1)));
}

void PathTest::isCircleOnPath_circleCenterIsNotOnPath_false()
{
	Path path(Point(0,0), Point(3,0), 0.4);

	CPPUNIT_ASSERT(!path.isCircleCenterOnPath(Circle(Point(1.5,0.3),0.3)));
}

void PathTest::getIntersectPoints_circleWithNoIntersects_intersectPointsCountIs0()
{
	Path path(Point(-2,2), Point(2,2), 0.2);

	CPPUNIT_ASSERT_EQUAL((size_t)0, path.getIntersectPoints(Circle(Point(0,0), 1)).getIntersectPointsCount());
}

void PathTest::getIntersectPoints_circleToutchesLine_intersectPointsCountIs1()
{
	Path path(Point(-2,2), Point(2,2), 1);

	CPPUNIT_ASSERT_EQUAL((size_t)1, path.getIntersectPoints(Circle(Point(0,0), 3)).getIntersectPointsCount());
}

void PathTest::getIntersectPoints_circleIntersectsLine_intersectPointsCountIs2()
{
	Path path(Point(-2,2), Point(2,2), 1);

	CPPUNIT_ASSERT_EQUAL((size_t)2, path.getIntersectPoints(Circle(Point(0,0), 4)).getIntersectPointsCount());
}

void PathTest::getIntersectPoints_circleIntersectsLineFromRight_intersectTypeFromRight()
{
	Path path(Point(-2,2), Point(2,2), 1);

	CPPUNIT_ASSERT_EQUAL(PathIntersectPoints::IntersectTypeFromRight, path.getIntersectPoints(Circle(Point(0,0), 4)).getIntersectTypeFrom());
}

void PathTest::getIntersectPoints_circleIntersectsLineFromRight_intersectPointIs()
{
	Compare compare(0.0001);
	Path path(Point(-2,2.5), Point(3,2.5), 1);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2,2), path.getIntersectPoints(Circle(Point(1,1), 2.8284)).getIntersectPoints().front()));
}

void PathTest::getAngleBetweenStartAndEnd_StartIs0And0EndIs1And1_AngleIsPiQuarter()
{
	Compare compare(0.0001);
	Path path(Point(0,0), Point(1,1), 1);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getEighthRotation(), path.getAngleBetweenStartAndEnd()));
}

void PathTest::getAngleBetweenStartAndEnd_StartIs1And1EndIs0And0_AngleIsMinusPiQuarter()
{
	Compare compare(0.0001);
	Path path(Point(1,1), Point(0,0), 1);
	Angle angle = Angle::getHalfRotation() + Angle::getEighthRotation();

	CPPUNIT_ASSERT(compare.isFuzzyEqual(angle.getValueBetweenMinusPiAndPi(), path.getAngleBetweenStartAndEnd()));
}

void PathTest::getLeftPerpendicularPoint_pointIs1And2_resultIsCorrect()
{
	Path path(Point(1,1), Point(4,4), 2.8284);
	Point target(1,2);

	CPPUNIT_ASSERT_EQUAL(Point(0.5,2.5), path.getLeftPerpendicularPoint(target));
}

void PathTest::getRightPerpendicularPoint_pointIs1And2_resultIsCorrect()
{
	Path path(Point(1,1), Point(4,4), 2.8284);
	Point target(1,2);

	CPPUNIT_ASSERT_EQUAL(Point(2.5,0.5), path.getRightPerpendicularPoint(target));
}

void PathTest::getDistanceToLeftPerpendicularPoint_pointIs1And2_resultIsCorrect()
{
	Path path(Point(1,1), Point(4,4), 2.8284);
	Point target(1,2);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.707, path.getDistanceToLeftPerpendicularPoint(target), 0.001);
}

void PathTest::getDistanceToRightPerpendicularPoint_pointIs1And2_resultIsCorrect()
{
	Path path(Point(1,1), Point(4,4), 2.8284);
	Point target(1,2);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(2.121, path.getDistanceToRightPerpendicularPoint(target), 0.001);
}
