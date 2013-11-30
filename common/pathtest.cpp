#include "common/pathtest.h"
#include "common/path.h"
#include "common/circle.h"

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

	CPPUNIT_ASSERT(path.isCircleOnPath(Circle(Point(-1,0.05),0.1)));
}

void PathTest::isCircleOnPath_circleCenterIsNotOnPath_false()
{
	Path path(Point(0,0), Point(3,0), 0.4);

	CPPUNIT_ASSERT(!path.isCircleOnPath(Circle(Point(1.5,0.3),0.3)));
}
