#include "layer/autonomous/routingresulttest.h"
#include "layer/autonomous/routingresult.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

void RoutingResultTest::constructor_empty_isNotValid()
{
	RoutingResult routingResult;

	CPPUNIT_ASSERT(!routingResult.isValid());
}

void RoutingResultTest::constructor_validParam_isValid()
{
	Route route(0.5);
	route.addPoint(Point(0, 3));
	route.addPoint(Point(1, 4));
	RoutingResult routingResult(route, list<RoutingObstacle>());

	CPPUNIT_ASSERT(routingResult.isValid());
}