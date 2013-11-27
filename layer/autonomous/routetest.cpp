#include "layer/autonomous/routetest.h"
#include "layer/autonomous/route.h"
#include "common/compare.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

void RouteTest::constructor_empty_isNotValid()
{
	Route route;

	CPPUNIT_ASSERT(!route.isValid());
}

void RouteTest::constructor_empty_pointCountIs0()
{
	Route route;

	CPPUNIT_ASSERT_EQUAL((size_t)0, route.getPointCount());
}

void RouteTest::addPoint_onceCalled_pointCountIs1()
{
	Route route;

	route.addPoint(Point(1, 2));

	CPPUNIT_ASSERT_EQUAL((size_t)1, route.getPointCount());
}

void RouteTest::addPoint_twiceCalled_pointCountIs2()
{
	Route route;

	route.addPoint(Point(1, 2));
	route.addPoint(Point(3, 2));

	CPPUNIT_ASSERT_EQUAL((size_t)2, route.getPointCount());
}

void RouteTest::isValid_onePointAdded_true()
{
	Route route;

	route.addPoint(Point(1, 2));

	CPPUNIT_ASSERT(route.isValid());
}

void RouteTest::getLastPoint_onePointAdded_lastAddedPoint()
{
	Route route;

	route.addPoint(Point(1, 2));

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1, 2), route.getLastPoint()));
}

void RouteTest::getLastPoint_twoPointsAdded_lastAddedPoint()
{
	Route route;

	route.addPoint(Point(1, 2));
	route.addPoint(Point(3, 2));

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(3, 2), route.getLastPoint()));
}
