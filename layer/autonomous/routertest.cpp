#include "layer/autonomous/routertest.h"
#include "layer/autonomous/routerimpl.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/autonomous/route.h"
#include "common/compare.h"
#include "common/path.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

void RouterTest::calculateRoute_emptyField_validRoute()
{
	FieldMock field;
	RouterImpl router(0.5);

	Route route = router.calculateRoute(Point(1, 1), Point(1, 2), field);

	CPPUNIT_ASSERT(route.isValid());
}

void RouterTest::calculateRoute_emptyField_routeHasTwoPoints()
{
	FieldMock field;
	RouterImpl router(0.5);

	Route route = router.calculateRoute(Point(1, 1), Point(1, 2), field);

	CPPUNIT_ASSERT_EQUAL((size_t)2, route.getPointCount());
}

void RouterTest::calculateRoute_emptyField_routeHasSameWidthAsRobot()
{
	FieldMock field;
	RouterImpl router(0.5);

	Route route = router.calculateRoute(Point(1, 1), Point(1, 2), field);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, route.getWidth(), 0.00001);
}

void RouterTest::calculateRoute_obstacleAtStartOfRoute_invalidRoute()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1, 1), 0.1));
	field.setObstacles(obstacles);

	Route route = router.calculateRoute(Point(1, 1), Point(1, 10), field);

	CPPUNIT_ASSERT(!route.isValid());
}

void RouterTest::calculateRoute_obstacleAtEndOfRoute_invalidRoute()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1, 10), 0.1));
	field.setObstacles(obstacles);

	Route route = router.calculateRoute(Point(1, 1), Point(1, 10), field);

	CPPUNIT_ASSERT(!route.isValid());
}

void RouterTest::calculateRoute_oneObstacleBetween_validRoute()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1, 5), 0.1));
	field.setObstacles(obstacles);

	Route route = router.calculateRoute(Point(1, 1), Point(1, 10), field);

	CPPUNIT_ASSERT(route.isValid());
}

void RouterTest::calculateRoute_oneObstacleBetween_routeIsNotTooLong()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1, 5), 0.1));
	field.setObstacles(obstacles);

	Route route = router.calculateRoute(Point(1, 1), Point(1, 10), field);

	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 9.5);
}

void RouterTest::calculateRoute_oneObstacleBetween_routeIsNotIntersectingWithObstacles()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1, 5), 0.1));
	field.setObstacles(obstacles);

	Route route = router.calculateRoute(Point(1, 1), Point(1, 10), field);

	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
}

void RouterTest::calculateRoute_oneBigObstacleCloseToStart_validRoute()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1.3, 0), 2));
	field.setObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(5, 0), field);

	CPPUNIT_ASSERT(route.isValid());
}

void RouterTest::calculateRoute_oneBigObstacleCloseToStart_routeIsNotTooLong()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1.3, 0), 2));
	field.setObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(5, 0), field);

	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 6.5);
}

void RouterTest::calculateRoute_oneBigObstacleCloseToStart_routeIsNotIntersectingWithObstacles()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1.3, 0), 2));
	field.setObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(5, 0), field);

	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
}

void RouterTest::calculateRoute_oneBigObstacleCloseToEnd_validRoute()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3.7, 0), 2));
	field.setObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(5, 0), field);

	CPPUNIT_ASSERT(route.isValid());
}

void RouterTest::calculateRoute_oneBigObstacleCloseToEnd_routeIsNotTooLong()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3.7, 0), 2));
	field.setObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(5, 0), field);

	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 6.5);
}

void RouterTest::calculateRoute_oneBigObstacleCloseToEnd_routeIsNotIntersectingWithObstacles()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3.7, 0), 2));
	field.setObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(5, 0), field);

	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
}

void RouterTest::calculateRoute_oneBigObstacleOnRightSideOfDirectPath_reasonableRoute()
{
	CPPUNIT_ASSERT(false);

	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(2, -0.7), 2));
	field.setObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(5, 0), field);

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 5.5);
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIs2AndMinus1()
{
	Compare compare(0.0001);
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,2), 2.8284);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2,-1), router.getPointsBesideObstacle(currentPath, obstacle).front()));
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_longPointIs2And6p4142()
{
	Compare compare(0.0001);
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,2), 2.8284);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2,6.4142), router.getPointsBesideObstacle(currentPath, obstacle).back()));
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIs2And3()
{
	Compare compare(0.0001);
	RouterImpl router(2);
	Path currentPath(Point(0,2), Point(4,2), 2);
	Circle obstacle(Point(2,0), 2.8284);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2,3), router.getPointsBesideObstacle(currentPath, obstacle).front()));
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_longPointIs2AndMinus4p4142()
{
	Compare compare(0.0001);
	RouterImpl router(2);
	Path currentPath(Point(0,2), Point(4,2), 2);
	Circle obstacle(Point(2,0), 2.8284);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2,-4.4142), router.getPointsBesideObstacle(currentPath, obstacle).back()));
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIs1p5And0p5()
{
	Compare compare(0.0001);
	RouterImpl router(1.4142);
	Path currentPath(Point(0,0), Point(3,3), 1.4142);
	Circle obstacle(Point(0,2), 2);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1.5,0.5), router.getPointsBesideObstacle(currentPath, obstacle).front()));
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIs0p5And1p5()
{
	Compare compare(0.0001);
	RouterImpl router(1.4142);
	Path currentPath(Point(0,0), Point(3,3), 1.4142);
	Circle obstacle(Point(2,0), 2);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0.5,1.5), router.getPointsBesideObstacle(currentPath, obstacle).front()));
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_shortPointIs2AndMinus3()
{
	Compare compare(0.0001);
	RouterImpl router(4);
	Path currentPath(Point(0,0), Point(4,0), 4);
	Circle obstacle(Point(2,1), 2.8284);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2,-3), router.getPointsBesideObstacle(currentPath, obstacle).front()));
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_longPointIs2And7p8284()
{
	Compare compare(0.0001);
	RouterImpl router(4);
	Path currentPath(Point(0,0), Point(4,0), 4);
	Circle obstacle(Point(2,1), 2.8284);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2,7.8284), router.getPointsBesideObstacle(currentPath, obstacle).back()));
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_shortPointIs2And3()
{
	Compare compare(0.0001);
	RouterImpl router(4);
	Path currentPath(Point(0,2), Point(4,2), 4);
	Circle obstacle(Point(2,-1), 2.8284);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2,3), router.getPointsBesideObstacle(currentPath, obstacle).front()));
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_longPointIs2AndMinus6p8282()
{
	Compare compare(0.0001);
	RouterImpl router(4);
	Path currentPath(Point(0,1), Point(4,1), 4);
	Circle obstacle(Point(2,0), 2.8284);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2,-6.8284), router.getPointsBesideObstacle(currentPath, obstacle).back()));
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_shortPointIs3And0()
{
	Compare compare(0.0001);
	RouterImpl router(2.8284);
	Path currentPath(Point(0,0), Point(3,3), 2.8284);
	Circle obstacle(Point(1,2), 2);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(3,0), router.getPointsBesideObstacle(currentPath, obstacle).front()));
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_shortPointIs0And3()
{
	Compare compare(0.0001);
	RouterImpl router(2.8284);
	Path currentPath(Point(0,0), Point(3,3), 2.8284);
	Circle obstacle(Point(2,1), 2);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(0,3), router.getPointsBesideObstacle(currentPath, obstacle).front()));
}

void RouterTest::getPointsBesideObstacle_pathFrom1And1To1And10AndSmallObstacleBetween_resultSizeIs2()
{
	RouterImpl router(0.5);
	Path path(Point(1, 1), Point(1, 10), 0.5);
	Circle obstacle(Point(1, 5), 0.1);

	vector<Point> pointsBeside = router.getPointsBesideObstacle(path, obstacle);

	CPPUNIT_ASSERT_EQUAL((size_t)2, pointsBeside.size());
}

void RouterTest::getPointsBesideObstacle_smallObstacleBetweenAt2And0p5_shortPointIs()
{
	Compare compare(0.0001);
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,0.5), 0.5);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2,3.2677), router.getPointsBesideObstacle(currentPath, obstacle).front()));
}

void RouterTest::getPointsBesideObstacle_smallObstacleBetweenAt2And0p5_longPointIs()
{
	Compare compare(0.0001);
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,0.5), 0.5);

	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(2,-2.2677), router.getPointsBesideObstacle(currentPath, obstacle).back()));
}
