#include "common/pathintersectpointstest.h"
#include "common/pathintersectpoints.h"

using namespace RoboHockey::Common;
using namespace std;

void PathIntersectPointsTest::constructor_createDefaultObject_intersectPointsCountIs2()
{
	vector<Point> intersectPoints;
	intersectPoints.push_back(Point(0,0));
	intersectPoints.push_back(Point(1,1));
	PathIntersectPoints pathIntersectPoints(intersectPoints, PathIntersectPoints::IntersectTypeFromLeft);

	CPPUNIT_ASSERT_EQUAL((size_t)2, pathIntersectPoints.getIntersectPoints().size());
}


