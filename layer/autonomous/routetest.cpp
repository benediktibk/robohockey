#include "layer/autonomous/routetest.h"
#include "layer/autonomous/route.h"
#include "common/compare.h"
#include "common/angle.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

void RouteTest::constructor_validWidth_isNotValid()
{
	Route route(0.5);

	CPPUNIT_ASSERT(!route.isValid());
}

void RouteTest::constructor_validWidth_pointCountIs0()
{
	Route route(0.5);

	CPPUNIT_ASSERT_EQUAL((size_t)0, route.getPointCount());
}

void RouteTest::constructor_03_widthIs03()
{
	Route route(0.3);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3, route.getWidth(), 0.00001);
}

void RouteTest::addPoint_onceCalled_pointCountIs1()
{
	Route route(0.5);

	route.addPoint(Point(1, 2));

	CPPUNIT_ASSERT_EQUAL((size_t)1, route.getPointCount());
}

void RouteTest::addPoint_twiceCalled_pointCountIs2()
{
	Route route(0.5);

	route.addPoint(Point(1, 2));
	route.addPoint(Point(3, 2));

	CPPUNIT_ASSERT_EQUAL((size_t)2, route.getPointCount());
}

void RouteTest::isValid_onePointAdded_true()
{
	Route route(0.5);

	route.addPoint(Point(1, 2));

	CPPUNIT_ASSERT(route.isValid());
}

void RouteTest::getLastPoint_onePointAdded_lastAddedPoint()
{
	Route route(0.5);

	route.addPoint(Point(1, 2));

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1, 2), route.getLastPoint()));
}

void RouteTest::getLastPoint_twoPointsAdded_lastAddedPoint()
{
	Route route(0.5);

	route.addPoint(Point(1, 2));
	route.addPoint(Point(3, 2));

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(3, 2), route.getLastPoint()));
}

void RouteTest::getFirstPoint_twoPointsAdded_firstPoint()
{
	Route route(0.5);

	route.addPoint(Point(1, 2));
	route.addPoint(Point(3, 2));

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1, 2), route.getFirstPoint()));
}

void RouteTest::removeFirstPoint_onePointAdded_pointCountIs0()
{
	Route route(0.5);
	route.addPoint(Point(1, 2));

	route.removeFirstPoint();

	CPPUNIT_ASSERT_EQUAL((size_t)0, route.getPointCount());
}

void RouteTest::removeFirstPoint_twoPointsAdded_onlyPointIsLastAddedPoint()
{
	Route route(0.5);
	route.addPoint(Point(1, 2));
	route.addPoint(Point(3, 2));

	route.removeFirstPoint();

	CPPUNIT_ASSERT_EQUAL((size_t)1, route.getPointCount());
	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(3, 2), route.getFirstPoint()));
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(3, 2), route.getLastPoint()));
}

void RouteTest::intersectsWith_noObstacles_false()
{
	vector<Circle> obstacles;
	Route route(0.5);
	route.addPoint(Point(0, 1));
	route.addPoint(Point(1, 1));

	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
}

void RouteTest::intersectsWith_oneObstacleFarAway_false()
{
	vector<Circle> obstacles;
	Route route(0.5);
	route.addPoint(Point(0, 1));
	route.addPoint(Point(1, 1));
	obstacles.push_back(Circle(Point(-5, -5), 1));

	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
}

void RouteTest::intersectsWith_oneObstacleOnTheWay_true()
{
	vector<Circle> obstacles;
	Route route(0.5);
	route.addPoint(Point(0, 1));
	route.addPoint(Point(1, 1));
	obstacles.push_back(Circle(Point(0.5, 1), 0.2));

	CPPUNIT_ASSERT(route.intersectsWith(obstacles));
}

void RouteTest::intersectsWith_oneObstacleFarAwayAndOneOnTheWay_true()
{
	vector<Circle> obstacles;
	Route route(0.5);
	route.addPoint(Point(0, 1));
	route.addPoint(Point(1, 1));
	obstacles.push_back(Circle(Point(0.5, 1), 0.2));
	obstacles.push_back(Circle(Point(-5, -5), 1));

	CPPUNIT_ASSERT(route.intersectsWith(obstacles));
}

void RouteTest::intersectsWith_bigObstacleButOnlyOneNode_false()
{
	vector<Circle> obstacles;
	Route route(0.5);
	route.addPoint(Point(0, 1));
	obstacles.push_back(Circle(Point(0.5, 1), 0.2));
	obstacles.push_back(Circle(Point(-1, -1), 10));

	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
}

void RouteTest::intersectsWith_firstRoutePartIntersectingWithObstacle_true()
{
	vector<Circle> obstacles;
	Route route(0.5);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(1, 1));
	route.addPoint(Point(1, 2));
	obstacles.push_back(Circle(Point(0.5, 0.6), 0.3));

	CPPUNIT_ASSERT(route.intersectsWith(obstacles));
}

void RouteTest::intersectsWith_secondRoutePartIntersectingWithObstacle_true()
{
	vector<Circle> obstacles;
	Route route(0.5);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(1, 1));
	route.addPoint(Point(1, 2));
	obstacles.push_back(Circle(Point(0.9, 1.5), 0.3));

	CPPUNIT_ASSERT(route.intersectsWith(obstacles));
}

void RouteTest::intersectsWith_threeRoutePartsAndOneNotDisturbingObstacle_false()
{
	vector<Circle> obstacles;
	Route route(0.5);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(1, 1));
	route.addPoint(Point(1, 2));
	route.addPoint(Point(-1, 2));
	obstacles.push_back(Circle(Point(10, 0.9), 0.3));

	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
}

void RouteTest::intersectsWith_widthTooSmallForIntersection_false()
{
	vector<Circle> obstacles;
	Route route(0.2);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(5, 0));
	obstacles.push_back(Circle(Point(2, 0.35), 0.2));

	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
}

void RouteTest::getLength_from1And2To3And2To3And5_5()
{
	Route route(0.2);
	route.addPoint(Point(1, 2));
	route.addPoint(Point(3, 2));
	route.addPoint(Point(3, 5));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(5, route.getLength(), 0.00001);
}

void RouteTest::add_validRoute_countOfPointsIsCorrect()
{
	Route one(0.2);
	one.addPoint(Point(1, 2));
	one.addPoint(Point(3, 2));
	one.addPoint(Point(3, 5));
	Route two(0.2);
	two.addPoint(Point(3, 5));
	two.addPoint(Point(7, 7));

	one.add(two);

	CPPUNIT_ASSERT_EQUAL((size_t)4, one.getPointCount());
}

void RouteTest::getMaximumBend_directConnection_0()
{
	Route route(0.5);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(1, 1));

	Angle maximumBend = route.getMaximumBend(Angle::getEighthRotation(), Angle::getEighthRotation());

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle(0), maximumBend));
}

void RouteTest::getMaximumBend_oneCompleteTurnAtStart_halfRotation()
{
	Route route(0.5);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(1, 0));

	Angle maximumBend = route.getMaximumBend(Angle::getHalfRotation(), Angle(0));

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getHalfRotation(), maximumBend));
}

void RouteTest::getMaximumBend_oneCompleteTurnAtEnd_halfRotation()
{
	Route route(0.5);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(1, 0));

	Angle maximumBend = route.getMaximumBend(Angle(0), Angle::getHalfRotation());

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getHalfRotation(), maximumBend));
}

void RouteTest::getMaximumBend_halfTurnUpwardsInBetween_quarterRotation()
{
	Route route(0.5);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(1, 0));
	route.addPoint(Point(1, 1));

	Angle maximumBend = route.getMaximumBend(Angle(0), Angle::getQuarterRotation());

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), maximumBend));
}

void RouteTest::getMaximumBend_halfTurnDownwardsInBetween_quarterRotation()
{
	Route route(0.5);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(1, 0));
	route.addPoint(Point(1, -1));

	Angle maximumBend = route.getMaximumBend(Angle(0), Angle::getQuarterRotation()*(-1));

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), maximumBend));
}

void RouteTest::getMaximumBend_turnAroundInQuarterSteps_quarterRotation()
{
	Route route(0.5);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(0, 0.1));
	route.addPoint(Point(0.1, 0.1));
	route.addPoint(Point(10, 0));

	Angle maximumBend = route.getMaximumBend(Angle::getHalfRotation(), Angle(0));

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), maximumBend));
}
