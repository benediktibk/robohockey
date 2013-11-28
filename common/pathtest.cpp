#include "common/pathtest.h"
#include "common/path.h"
#include "common/circle.h"

using namespace RoboHockey::Common;

void PathTest::intersectsWith_circleIntersectsPathFromLeft_resultIsTrue()
{
	Path path(Point(0,0), Point(3,0), 0.4);

	CPPUNIT_ASSERT(path.intersectsWith(Circle(Point(1.5,0.5),0.3)));
}

void PathTest::intersectsWith_circleIntersectsPathFromRight_resultIsTrue()
{
	Path path(Point(0,0), Point(3,0), 0.4);

	CPPUNIT_ASSERT(path.intersectsWith(Circle(Point(1.5,-0.5),0.3)));
}

void PathTest::intersectsWith_circleIntersectsPathFromStart_resultIsTrue()
{
	Path path(Point(0,0), Point(3,0), 0.4);

	CPPUNIT_ASSERT(path.intersectsWith(Circle(Point(-0.1,0),0.3)));
}

void PathTest::intersectsWith_circleIntersectsPathFromEnd_resultIsTrue()
{
	Path path(Point(0,0), Point(3,0), 0.4);

	CPPUNIT_ASSERT(path.intersectsWith(Circle(Point(3.1,0),0.3)));
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

