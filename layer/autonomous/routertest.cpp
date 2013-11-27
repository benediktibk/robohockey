#include "layer/autonomous/routertest.h"
#include "layer/autonomous/router.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/autonomous/route.h"

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
