#include "layer/autonomous/routelengthcomparetest.h"
#include "layer/autonomous/routelengthcompare.h"
#include "layer/autonomous/route.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

void RouteLengthCompareTest::evaluation_firstOneShorter_true()
{
	RouteLengthCompare compare;
	Route one(0.1);
	one.addPoint(Point(0, 0));
	one.addPoint(Point(0, 1));
	one.addPoint(Point(2, 2));
	Route two(0.1);
	two.addPoint(Point(-1, 2));
	two.addPoint(Point(10, 10));

	CPPUNIT_ASSERT(compare(one, two));
}

void RouteLengthCompareTest::evaulation_secondOneShorter_false()
{
	RouteLengthCompare compare;
	Route one(0.1);
	one.addPoint(Point(0, 0));
	one.addPoint(Point(0, 1));
	one.addPoint(Point(2, 2));
	Route two(0.1);
	two.addPoint(Point(-1, 2));
	two.addPoint(Point(-2, 3));

	CPPUNIT_ASSERT(!compare(one, two));
}
