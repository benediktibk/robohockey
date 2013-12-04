#include "layer/autonomous/routertest.h"
#include "layer/autonomous/router.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/autonomous/route.h"
#include "common/compare.h"
#include "common/path.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

void RouterTest::calculateRoute_emptyField_validRoute()
{
	FieldMock field;
	Router router(0.5, field);

	Route route = router.calculateRoute(Point(1, 1), Point(1, 2));

	CPPUNIT_ASSERT(route.isValid());
}

void RouterTest::calculateRoute_emptyField_onlyPointOfRouteIsTarget()
{
	FieldMock field;
	Router router(0.5, field);

	Route route = router.calculateRoute(Point(1, 1), Point(1, 2));

	CPPUNIT_ASSERT_EQUAL((size_t)1, route.getPointCount());
}

void RouterTest::calculateRoute_emptyField_routeHasSameWidthAsRobot()
{
	FieldMock field;
	Router router(0.5, field);

	Route route = router.calculateRoute(Point(1, 1), Point(1, 2));

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, route.getWidth(), 0.00001);
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIs2AndMinus0p25()
{
	Compare compare(0.0001);
	FieldMock field;
	Router router(0.5, field);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,2), 2.8284);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2,-0.25), router.getPointsBesideObstacle(currentPath, obstacle).front()));
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIs2And2p25()
{
	Compare compare(0.0001);
	FieldMock field;
	Router router(0.5, field);
	Path currentPath(Point(0,2), Point(4,2), 2);
	Circle obstacle(Point(2,0), 2.8284);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2,2.25), router.getPointsBesideObstacle(currentPath, obstacle).front()));
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIs1p1767And0p8232()
{
	Compare compare(0.0001);
	FieldMock field;
	Router router(0.5, field);
	Path currentPath(Point(0,0), Point(3,3), 1.4142);
	Circle obstacle(Point(0,2), 2);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1.1767,0.8232), router.getPointsBesideObstacle(currentPath, obstacle).front()));
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIs0p8232And1p1767()
{
	Compare compare(0.0001);
	FieldMock field;
	Router router(0.5, field);
	Path currentPath(Point(0,0), Point(3,3), 1.4142);
	Circle obstacle(Point(2,0), 2);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0.8232,1.1767), router.getPointsBesideObstacle(currentPath, obstacle).front()));
}
