#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTERTEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class RouterTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RouterTest);
		CPPUNIT_TEST(calculateRoute_emptyField_validRoute);
		CPPUNIT_TEST(calculateRoute_emptyField_routeHasTwoPoints);
		CPPUNIT_TEST(calculateRoute_emptyField_routeHasSameWidthAsRobot);
		CPPUNIT_TEST(calculateRoute_obstacleAtStartOfRoute_invalidRoute);
		CPPUNIT_TEST(calculateRoute_obstacleAtEndOfRoute_invalidRoute);
		CPPUNIT_TEST(calculateRoute_oneObstacleBetween_validRoute);
		CPPUNIT_TEST(calculateRoute_oneObstacleBetween_routeIsNotTooLong);
		CPPUNIT_TEST(calculateRoute_oneObstacleBetween_routeIsNotIntersectingWithObstacles);
		CPPUNIT_TEST(calculateRoute_oneBigObstacleCloseToStart_validRoute);
		CPPUNIT_TEST(calculateRoute_oneBigObstacleCloseToStart_routeIsNotTooLong);
		CPPUNIT_TEST(calculateRoute_oneBigObstacleCloseToStart_routeIsNotIntersectingWithObstacles);
		CPPUNIT_TEST(calculateRoute_oneBigObstacleCloseToEnd_validRoute);
		CPPUNIT_TEST(calculateRoute_oneBigObstacleCloseToEnd_routeIsNotTooLong);
		CPPUNIT_TEST(calculateRoute_oneBigObstacleCloseToEnd_routeIsNotIntersectingWithObstacles);
		CPPUNIT_TEST(calculateRoute_oneBigObstacleOnRightSideOfDirectPath_reasonableRoute);
		CPPUNIT_TEST(calculateRoute_oneBigObstacleOnLeftSideOfDirectPath_reasonableRoute);
		CPPUNIT_TEST(calculateRoute_obstacleOnWayToPointBesideObstacle_reasonableRoute);
		CPPUNIT_TEST(calculateRoute_obstacleOnWayToTargetFromPointBesideObstacle_reasonableRoute);
		CPPUNIT_TEST(calculateRoute_obstacleOnWayToAndFromPointBesideObstacle_reasonableRoute);
		CPPUNIT_TEST(calculateRoute_goingBetweenTwoObstacles_directRoute);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIs2AndMinus1);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_longPointIs2And6p4142);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIs2And3);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_longPointIs2AndMinus4p4142);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIs1p5And0p5);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIs0p5And1p5);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_shortPointIs2AndMinus3);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_longPointIs2And7p8284);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_shortPointIs2And3);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_longPointIs2AndMinus6p8282);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_shortPointIs3And0);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_shortPointIs0And3);
		CPPUNIT_TEST(getPointsBesideObstacle_pathFrom1And1To1And10AndSmallObstacleBetween_resultSizeIs2);
		CPPUNIT_TEST(getPointsBesideObstacle_smallObstacleBetweenAt2And0p5_shortPointIsCorrect);
		CPPUNIT_TEST(getPointsBesideObstacle_smallObstacleBetweenAt2And0p5_longPointIsCorrect);
		CPPUNIT_TEST(getPointsBesideObstacle_bigObstacleOnRightSide_resultSizeIs2);
		CPPUNIT_TEST(getPointsBesideObstacle_bigObstacleOnRightSide_bothPointsDoNotIntersectWithTheObstacle);
		CPPUNIT_TEST(getPointsBesideObstacle_bigObstacleOnRightSide_bothPointsHaveReasonableCoordinates);
		CPPUNIT_TEST_SUITE_END();

	private:
		void calculateRoute_emptyField_validRoute();
		void calculateRoute_emptyField_routeHasTwoPoints();
		void calculateRoute_emptyField_routeHasSameWidthAsRobot();
		void calculateRoute_obstacleAtStartOfRoute_invalidRoute();
		void calculateRoute_obstacleAtEndOfRoute_invalidRoute();
		void calculateRoute_oneObstacleBetween_validRoute();
		void calculateRoute_oneObstacleBetween_routeIsNotTooLong();
		void calculateRoute_oneObstacleBetween_routeIsNotIntersectingWithObstacles();
		void calculateRoute_oneBigObstacleCloseToStart_validRoute();
		void calculateRoute_oneBigObstacleCloseToStart_routeIsNotTooLong();
		void calculateRoute_oneBigObstacleCloseToStart_routeIsNotIntersectingWithObstacles();
		void calculateRoute_oneBigObstacleCloseToEnd_validRoute();
		void calculateRoute_oneBigObstacleCloseToEnd_routeIsNotTooLong();
		void calculateRoute_oneBigObstacleCloseToEnd_routeIsNotIntersectingWithObstacles();
		void calculateRoute_oneBigObstacleOnRightSideOfDirectPath_reasonableRoute();
		void calculateRoute_oneBigObstacleOnLeftSideOfDirectPath_reasonableRoute();
		void calculateRoute_obstacleOnWayToPointBesideObstacle_reasonableRoute();
		void calculateRoute_obstacleOnWayToTargetFromPointBesideObstacle_reasonableRoute();
		void calculateRoute_obstacleOnWayToAndFromPointBesideObstacle_reasonableRoute();
		void calculateRoute_goingBetweenTwoObstacles_directRoute();
		void getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIs2AndMinus1();
		void getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_longPointIs2And6p4142();
		void getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIs2And3();
		void getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_longPointIs2AndMinus4p4142();
		void getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIs1p5And0p5();
		void getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIs0p5And1p5();
		void getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_shortPointIs2AndMinus3();
		void getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_longPointIs2And7p8284();
		void getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_shortPointIs2And3();
		void getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_longPointIs2AndMinus6p8282();
		void getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_shortPointIs3And0();
		void getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_shortPointIs0And3();
		void getPointsBesideObstacle_pathFrom1And1To1And10AndSmallObstacleBetween_resultSizeIs2();
		void getPointsBesideObstacle_smallObstacleBetweenAt2And0p5_shortPointIsCorrect();
		void getPointsBesideObstacle_smallObstacleBetweenAt2And0p5_longPointIsCorrect();
		void getPointsBesideObstacle_bigObstacleOnRightSide_resultSizeIs2();
		void getPointsBesideObstacle_bigObstacleOnRightSide_bothPointsDoNotIntersectWithTheObstacle();
		void getPointsBesideObstacle_bigObstacleOnRightSide_bothPointsHaveReasonableCoordinates();
	};
}
}
}

#endif
