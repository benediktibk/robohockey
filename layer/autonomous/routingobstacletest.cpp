#include "layer/autonomous/routingobstacletest.h"
#include "layer/autonomous/routingobstacle.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

void RoutingObstacleTest::constructor_empty_isNotValid()
{
	RoutingObstacle routingObstacle;

	CPPUNIT_ASSERT(!routingObstacle.isValid());
}

void RoutingObstacleTest::constructor_validObstacle_isValid()
{
	RoutingObstacle routingObstacle(Circle(Point(3, 4), 1), true);

	CPPUNIT_ASSERT(routingObstacle.isValid());
}

void RoutingObstacleTest::constructor_wentRightBesideObstacle_wentRightBeside()
{
	RoutingObstacle routingObstacle(Circle(Point(3, 4), 1), true);

	CPPUNIT_ASSERT(routingObstacle.wentRightBeside());
}

void RoutingObstacleTest::constructor_wentLeftBesideObstacle_notWentRightBeside()
{
	RoutingObstacle routingObstacle(Circle(Point(3, 4), 1), false);

	CPPUNIT_ASSERT(!routingObstacle.wentRightBeside());
}

void RoutingObstacleTest::constructor_validObstacle_getObstacleIsCorrect()
{
	RoutingObstacle routingObstacle(Circle(Point(3, 4), 1), true);

	CPPUNIT_ASSERT_EQUAL(Circle(Point(3, 4), 1), routingObstacle.getObstacle());
}

void RoutingObstacleTest::operatorEqual_sameObstaclesButDifferentSide_false()
{
	RoutingObstacle one(Circle(Point(3, 4), 1), true);
	RoutingObstacle two(Circle(Point(3, 4), 1), false);

	CPPUNIT_ASSERT(!(one == two));
}

void RoutingObstacleTest::operatorEqual_differentObstacles_false()
{
	RoutingObstacle one(Circle(Point(3, 4), 1), true);
	RoutingObstacle two(Circle(Point(3, 4), 2), true);

	CPPUNIT_ASSERT(!(one == two));
}

void RoutingObstacleTest::operatorEqual_sameObstaclesAndSides_true()
{
	RoutingObstacle one(Circle(Point(3, 4), 1), true);
	RoutingObstacle two(Circle(Point(3, 4), 1), true);

	CPPUNIT_ASSERT(one == two);
}
