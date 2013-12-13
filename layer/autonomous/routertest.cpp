#include "layer/autonomous/routertest.h"
#include "layer/autonomous/routerimpl.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/autonomous/route.h"
#include "common/compare.h"
#include "common/path.h"
#include "common/watch.h"
#include "common/angle.h"
#include "common/robotposition.h"
#include "common/line.h"
#include <assert.h>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;

void RouterTest::calculateRoute_emptyField_validRoute()
{
	FieldMock field;
	RouterImpl router(0.5);
	RobotPosition start(Point(1, 1), Angle::getQuarterRotation());
	RobotPosition end(Point(1, 2), Angle::getQuarterRotation());

	Route route = router.calculateRoute(start, end, field);

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
	field.setHardObstacles(obstacles);

	Route route = router.calculateRoute(Point(1, 1), Point(1, 10), field);

	CPPUNIT_ASSERT(!route.isValid());
}

void RouterTest::calculateRoute_softObstacleAtEndOfRoute_invalidRoute()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1, 10), 0.1));
	field.setSoftObstacles(obstacles);

	Route route = router.calculateRoute(Point(1, 1), Point(1, 10), field);

	CPPUNIT_ASSERT(!route.isValid());
}

void RouterTest::calculateRoute_oneObstacleBetween_validRoute()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1, 5), 0.1));
	field.setSoftObstacles(obstacles);

	Route route = router.calculateRoute(Point(1, 1), Point(1, 10), field);

	CPPUNIT_ASSERT(route.isValid());
}

void RouterTest::calculateRoute_oneObstacleBetween_routeIsNotTooLong()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1, 5), 0.1));
	field.setSoftObstacles(obstacles);

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
	field.setSoftObstacles(obstacles);

	Route route = router.calculateRoute(Point(1, 1), Point(1, 10), field);

	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
}

void RouterTest::calculateRoute_oneBigObstacleCloseToStart_validRoute()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1.3, 0), 2));
	field.setSoftObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(5, 0), field);

	CPPUNIT_ASSERT(route.isValid());
}

void RouterTest::calculateRoute_oneBigObstacleCloseToStart_routeIsNotTooLong()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1.3, 0), 2));
	field.setSoftObstacles(obstacles);

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
	field.setHardObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(5, 0), field);

	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
}

void RouterTest::calculateRoute_oneBigObstacleCloseToEnd_validRoute()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3.7, 0), 2));
	field.setHardObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(5.5, 0), field);

	CPPUNIT_ASSERT(route.isValid());
}

void RouterTest::calculateRoute_oneBigObstacleCloseToEnd_routeIsNotTooLong()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3.7, 0), 2));
	field.setSoftObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(5.5, 0), field);

	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 6.5);
}

void RouterTest::calculateRoute_oneBigObstacleCloseToEnd_routeIsNotIntersectingWithObstacles()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3.7, 0), 2));
	field.setSoftObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(5.5, 0), field);

	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
}

void RouterTest::calculateRoute_oneBigObstacleOnRightSideOfDirectPath_reasonableRoute()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(2, -0.7), 2));
	field.setSoftObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(5, 0), field);

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 5.5);
}

void RouterTest::calculateRoute_oneBigObstacleOnLeftSideOfDirectPath_reasonableRoute()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(2, 0.7), 2));
	field.setSoftObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(5, 0), field);

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 5.5);
}

void RouterTest::calculateRoute_obstacleOnWayToPointBesideObstacle_reasonableRoute()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3, 0), 2));
	obstacles.push_back(Circle(Point(1, -1), 1));
	obstacles.push_back(Circle(Point(1, 1), 1));
	field.setSoftObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(5, 0), field);

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 6.5);
}

void RouterTest::calculateRoute_obstacleOnWayToTargetFromPointBesideObstacle_reasonableRoute()
{
	CPPUNIT_ASSERT(false);

	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3, 0), 2));
	obstacles.push_back(Circle(Point(5, -1), 1));
	obstacles.push_back(Circle(Point(5, 1), 1));
	field.setSoftObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(10, 0), field);

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 11);
}

void RouterTest::calculateRoute_obstacleOnWayToAndFromPointBesideObstacle_reasonableRoute()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3, 0), 2));
	obstacles.push_back(Circle(Point(1, -1), 1));
	obstacles.push_back(Circle(Point(1, 1), 1));
	obstacles.push_back(Circle(Point(5, -1), 1));
	obstacles.push_back(Circle(Point(5, 1), 1));
	field.setSoftObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(10, 0), field);

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	double routeLength = route.getLength();
	CPPUNIT_ASSERT(routeLength < 11.5);
}

void RouterTest::calculateRoute_goingBetweenTwoObstacles_directRoute()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1, -0.8), 1));
	obstacles.push_back(Circle(Point(1, 0.8), 1));
	field.setSoftObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(2, 0), field);

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	double routeLength = route.getLength();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, routeLength, 0.01);
}

void RouterTest::calculateRoute_severalObjectsAndOneOnTheWay_calculationIsNotTooSlow()
{
	FieldMock field;
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(0, 0), 0.1));
	obstacles.push_back(Circle(Point(0.5, 0), 0.1));
	obstacles.push_back(Circle(Point(2, 0), 0.1));
	obstacles.push_back(Circle(Point(3.5, 0), 0.1));
	obstacles.push_back(Circle(Point(4, 0), 0.1));
	obstacles.push_back(Circle(Point(0, 7), 0.1));
	obstacles.push_back(Circle(Point(0.5, 7), 0.1));
	obstacles.push_back(Circle(Point(2, 7), 0.1));
	obstacles.push_back(Circle(Point(3.5, 7), 0.1));
	obstacles.push_back(Circle(Point(4, 7), 0.1));
	obstacles.push_back(Circle(Point(2, 2), 0.1));
	obstacles.push_back(Circle(Point(0, 5), 0.1));
	obstacles.push_back(Circle(Point(0.5, 5), 0.1));
	obstacles.push_back(Circle(Point(2, 5), 0.1));
	obstacles.push_back(Circle(Point(3.5, 5), 0.1));
	obstacles.push_back(Circle(Point(4, 5), 0.1));
	field.setSoftObstacles(obstacles);
	RobotPosition start(Point(1, 2), 0);
	RobotPosition end(Point(3, 2), 0);

	Watch watch;
	Route route = router.calculateRoute(start, end, field);
	double time = watch.getTimeAndRestart();

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	CPPUNIT_ASSERT(time < 0.2);
}

void RouterTest::calculateRoute_shortWayOutsideField_noPointOfRouteIsOutside()
{
	FieldMock field;
	field.setNegativeCoordinatesOutside(true);
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(5, 1), 2));
	field.setSoftObstacles(obstacles);

	Route route = router.calculateRoute(Point(0, 0), Point(10, 0), field);

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	CPPUNIT_ASSERT(routeIsInsideField(route, field));
}

void RouterTest::calculateRoute_onlyPossiblePointBesideIsBlockedByAnotherObstacle_reasonableRoute()
{
	FieldMock field;
	field.setNegativeCoordinatesOutside(true);
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(5, 1), 2));
	obstacles.push_back(Circle(Point(5, 2.5), 1));
	field.setSoftObstacles(obstacles);
	RobotPosition start(Point(0, 0), 0);
	RobotPosition end(Point(10, 0), 0);

	Route route = router.calculateRoute(start, end, field);

	CPPUNIT_ASSERT(route.isValid());
	CPPUNIT_ASSERT(!route.intersectsWith(obstacles));
	double routeLength = route.getLength();
	//! 10 is definitely too small, but I have not yet found a reasonable value for this test case.
	CPPUNIT_ASSERT(routeLength < 10);
}

void RouterTest::calculateRoute_softObstacleAtOwnPosition_validRoute()
{
	FieldMock field;
	field.setNegativeCoordinatesOutside(true);
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(0, 0), 0.1));
	field.setSoftObstacles(obstacles);
	RobotPosition start(Point(0, 0), 0);
	RobotPosition end(Point(10, 0), 0);

	Route route = router.calculateRoute(start, end, field);

	CPPUNIT_ASSERT(route.isValid());
}

void RouterTest::calculateRoute_hardObstacleAtOwnPosition_invalidRoute()
{
	FieldMock field;
	field.setNegativeCoordinatesOutside(true);
	RouterImpl router(0.5);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(0, 0), 0.1));
	field.setHardObstacles(obstacles);
	RobotPosition start(Point(0, 0), 0);
	RobotPosition end(Point(10, 0), 0);

	Route route = router.calculateRoute(start, end, field);

	CPPUNIT_ASSERT(!route.isValid());
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,2), 2.8284);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_longPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,2), 2.8284);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).back();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,2), Point(4,2), 2);
	Circle obstacle(Point(2,0), 2.8284);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_longPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,2), Point(4,2), 2);
	Circle obstacle(Point(2,0), 2.8284);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).back();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIsOk()
{
	RouterImpl router(1.4142);
	Path currentPath(Point(0,0), Point(3,3), 1.4142);
	Circle obstacle(Point(0,2), 2);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 2);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.1);
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIsOk()
{
	RouterImpl router(1.4142);
	Path currentPath(Point(0,0), Point(3,3), 1.4142);
	Circle obstacle(Point(2,0), 2);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 2);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.1);
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_shortPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,1), 2.8284);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_longPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,1), 2.8284);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).back();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_shortPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,1), 2.8284);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_longPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,1), 2.8284);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).back();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_shortPointIsOk()
{
	RouterImpl router(1.4142);
	Path currentPath(Point(0,0), Point(3,3), 1.4142);
	Circle obstacle(Point(1,2), 2);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 2);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.1);
}

void RouterTest::getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_shortPointIsOk()
{
	RouterImpl router(1.4142);
	Path currentPath(Point(0,0), Point(3,3), 1.4142);
	Circle obstacle(Point(2,1), 2);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 2);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.1);
}

void RouterTest::getPointsBesideObstacle_pathFrom1And1To1And10AndSmallObstacleBetween_resultSizeIs2()
{
	RouterImpl router(0.5);
	Path path(Point(1, 1), Point(1, 10), 0.5);
	Circle obstacle(Point(1, 5), 0.1);

	vector<Point> pointsBeside = router.getPointsBesideObstacle(path, obstacle);

	CPPUNIT_ASSERT_EQUAL((size_t)2, pointsBeside.size());
}

void RouterTest::getPointsBesideObstacle_smallObstacleBetweenAt2And0p5_shortPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,0.5), 0.5);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 0.35);
}

void RouterTest::getPointsBesideObstacle_smallObstacleBetweenAt2And0p5_longPointIsCorrect()
{
	RouterImpl router(2);
	Path currentPath(Point(0,0), Point(4,0), 2);
	Circle obstacle(Point(2,0.5), 0.5);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).back();
	Circle robotBesideObstacle(pointBesideObstacle, 2.8284);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 0.35);
}

void RouterTest::getPointsBesideObstacle_bigObstacleOnRightSide_resultSizeIs2()
{
	RouterImpl router(0.5);
	Path path(Point(0, 0), Point(5, 0), 0.5);
	Circle obstacle(Point(2, -0.7), 2);

	vector<Point> pointsBeside = router.getPointsBesideObstacle(path, obstacle);

	CPPUNIT_ASSERT_EQUAL((size_t)2, pointsBeside.size());
}

void RouterTest::getPointsBesideObstacle_bigObstacleOnRightSide_bothPointsDoNotIntersectWithTheObstacle()
{
	RouterImpl router(0.5);
	Path path(Point(0, 0), Point(5, 0), 0.5);
	Circle obstacle(Point(2, -0.7), 2);

	vector<Point> pointsBeside = router.getPointsBesideObstacle(path, obstacle);

	Circle one(pointsBeside.front(), 0.707);
	Circle two(pointsBeside.back(), 0.707);
	CPPUNIT_ASSERT(!one.overlapsWith(obstacle));
	CPPUNIT_ASSERT(!two.overlapsWith(obstacle));
}

void RouterTest::getPointsBesideObstacle_bigObstacleOnRightSide_bothPointsHaveReasonableCoordinates()
{
	RouterImpl router(0.5);
	Path path(Point(0, 0), Point(5, 0), 0.5);
	Circle obstacle(Point(2, -0.7), 2);

	vector<Point> pointsBeside = router.getPointsBesideObstacle(path, obstacle);

	const Point &one = pointsBeside.front();
	const Point &two = pointsBeside.back();
	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, one.getX(), 0.0001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, two.getX(), 0.0001);
	CPPUNIT_ASSERT(one.getY() > 0.3 || one.getY() < -1.7);
	CPPUNIT_ASSERT(two.getY() > 0.3 || two.getY() < -1.7);
}

bool RouterTest::routeIsInsideField(const Route &route, const Field &field)
{
	assert(route.isValid());
	list<Point> points = route.getAllPoints();

	for (list<Point>::const_iterator i = points.begin(); i != points.end(); ++i)
		if (!field.isPointInsideField(*i))
			return false;

	return true;
}

void RouterTest::getPointsBesideObstacle_bigObstacleOnRightSide_shortPointIsCorrect()
{
	RouterImpl router(0.5);
	Path currentPath(Point(0,0), Point(4,0), 0.5);
	Circle obstacle(Point(2,-0.5), 2);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).front();
	Circle robotBesideObstacle(pointBesideObstacle, 0.707);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_bigObstacleOnRightSide_longPointIsCorrect()
{
	RouterImpl router(0.5);
	Path currentPath(Point(0,0), Point(4,0), 0.5);
	Circle obstacle(Point(2,-0.5), 2);
	Point pointBesideObstacle = router.getPointsBesideObstacle(currentPath, obstacle).back();
	Circle robotBesideObstacle(pointBesideObstacle, 0.707);

	CPPUNIT_ASSERT(!robotBesideObstacle.overlapsWith(obstacle));
	CPPUNIT_ASSERT(robotBesideObstacle.getDistanceTo(obstacle.getCenter()) < 1.5);
}

void RouterTest::getPointsBesideObstacle_bigObstacleCloseOnLeftSide_onePointIsLeftAndOneRight()
{
	RouterImpl router(0.5);
	Point start(3, -1.3606);
	Point end(5, 0);
	Circle obstacle(Point(3, 0), 2);
	Path path(start, end, 0.5);

	vector<Point> points = router.getPointsBesideObstacle(path, obstacle);

	Circle robotShortObstacle(points.front(), 0.707);
	CPPUNIT_ASSERT(!robotShortObstacle.overlapsWith(obstacle));
	Circle robotLongObstacle(points.back(), 0.707);
	CPPUNIT_ASSERT(!robotLongObstacle.overlapsWith(obstacle));

	Line line(start, end);
	CPPUNIT_ASSERT(path.intersectsWith(obstacle));
	CPPUNIT_ASSERT_EQUAL((size_t)2, points.size());
	CPPUNIT_ASSERT(line.isOnePointLeftAndOneRightOfLine(points[0], points[1]));
}

void RouterTest::detectLoopInConsideredObstacles_noObstacles_false()
{
	RouterImpl router(0.5);
	list<Circle> obstacles;

	CPPUNIT_ASSERT(!router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_oneObstacle_false()
{
	RouterImpl router(0.5);
	list<Circle> obstacles;
	obstacles.push_back(Circle(Point(2, 3), 1));

	CPPUNIT_ASSERT(!router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_twiceTheSameObstacle_false()
{
	RouterImpl router(0.5);
	list<Circle> obstacles;
	obstacles.push_back(Circle(Point(2, 3), 1));
	obstacles.push_back(Circle(Point(2, 3), 1));

	CPPUNIT_ASSERT(!router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_twiceTheSameObstacleAtEnd_false()
{
	RouterImpl router(0.5);
	list<Circle> obstacles;
	obstacles.push_back(Circle(Point(-2, 3), 1));
	obstacles.push_back(Circle(Point(2, 5), 1));
	obstacles.push_back(Circle(Point(2, 3), 1));
	obstacles.push_back(Circle(Point(2, 3), 1));

	CPPUNIT_ASSERT(!router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_thriceTheSameObstacle_false()
{
	RouterImpl router(0.5);
	list<Circle> obstacles;
	obstacles.push_back(Circle(Point(2, 3), 1));
	obstacles.push_back(Circle(Point(2, 3), 1));
	obstacles.push_back(Circle(Point(2, 3), 1));

	CPPUNIT_ASSERT(!router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_twiceTheSameObstacleInTheMiddle_false()
{
	RouterImpl router(0.5);
	list<Circle> obstacles;
	obstacles.push_back(Circle(Point(-3, 3), 2));
	obstacles.push_back(Circle(Point(2, 3), 1));
	obstacles.push_back(Circle(Point(2, 3), 1));
	obstacles.push_back(Circle(Point(2, 4), 0.5));

	CPPUNIT_ASSERT(!router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_twiceTheSameObstacleAtBegin_false()
{
	RouterImpl router(0.5);
	list<Circle> obstacles;
	obstacles.push_back(Circle(Point(2, 3), 1));
	obstacles.push_back(Circle(Point(2, 3), 1));
	obstacles.push_back(Circle(Point(2, 4), 0.5));

	CPPUNIT_ASSERT(!router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_loopOverOne_true()
{
	RouterImpl router(0.5);
	list<Circle> obstacles;
	obstacles.push_back(Circle(Point(2, 3), 1));
	obstacles.push_back(Circle(Point(2, 4), 0.5));
	obstacles.push_back(Circle(Point(2, 3), 1));

	CPPUNIT_ASSERT(router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_loopOverTwo_true()
{
	RouterImpl router(0.5);
	list<Circle> obstacles;
	obstacles.push_back(Circle(Point(2, 3), 1));
	obstacles.push_back(Circle(Point(2, 4), 0.5));
	obstacles.push_back(Circle(Point(2, 4), 0.5));
	obstacles.push_back(Circle(Point(2, 3), 1));

	CPPUNIT_ASSERT(router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_sameAsSecond_true()
{
	RouterImpl router(0.5);
	list<Circle> obstacles;
	obstacles.push_back(Circle(Point(1, 1), 0.5));
	obstacles.push_back(Circle(Point(2, 3), 1));
	obstacles.push_back(Circle(Point(2, 4), 0.5));
	obstacles.push_back(Circle(Point(2, 4), 0.5));
	obstacles.push_back(Circle(Point(1, 1), 0.25));
	obstacles.push_back(Circle(Point(2, 3), 1));

	CPPUNIT_ASSERT(router.detectLoopInConsideredObstacles(obstacles));
}

void RouterTest::detectLoopInConsideredObstacles_somewhereInBetweenALoop_false()
{
	RouterImpl router(0.5);
	list<Circle> obstacles;
	obstacles.push_back(Circle(Point(1, 1), 0.5));
	obstacles.push_back(Circle(Point(2, 3), 1));
	obstacles.push_back(Circle(Point(2, 4), 0.5));
	obstacles.push_back(Circle(Point(2, 3), 1));
	obstacles.push_back(Circle(Point(2, 4), 0.5));
	obstacles.push_back(Circle(Point(1, 1), 0.25));

	CPPUNIT_ASSERT(!router.detectLoopInConsideredObstacles(obstacles));
}
