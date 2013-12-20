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
	class Route;
	class Field;

	class RouterTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RouterTest);
		CPPUNIT_TEST(calculateRoute_emptyField_validRoute);
		CPPUNIT_TEST(calculateRoute_emptyField_routeHasTwoPoints);
		CPPUNIT_TEST(calculateRoute_emptyField_routeHasSameWidthAsRobot);
		CPPUNIT_TEST(calculateRoute_softObstacleAtEndOfRoute_invalidRoute);
		CPPUNIT_TEST(calculateRoute_oneObstacleBetween_validRoute);
		CPPUNIT_TEST(calculateRoute_oneObstacleBetween_routeIsNotTooLong);
		CPPUNIT_TEST(calculateRoute_oneObstacleBetween_routeIsNotIntersectingWithObstacles);
		CPPUNIT_TEST(calculateRoute_oneBigObstacleCloseToStart_validRoute);
		CPPUNIT_TEST(calculateRoute_oneBigObstacleCloseToStart_routeIsNotTooLong);
		CPPUNIT_TEST(calculateRoute_oneBigObstacleCloseToEnd_validRoute);
		CPPUNIT_TEST(calculateRoute_oneBigObstacleCloseToEnd_routeIsNotTooLong);
		CPPUNIT_TEST(calculateRoute_oneBigObstacleCloseToEnd_routeIsNotIntersectingWithObstacles);
		CPPUNIT_TEST(calculateRoute_oneBigObstacleOnRightSideOfDirectPath_reasonableRoute);
		CPPUNIT_TEST(calculateRoute_oneBigObstacleOnLeftSideOfDirectPath_reasonableRoute);
		CPPUNIT_TEST(calculateRoute_obstacleOnWayToPointBesideObstacle_reasonableRoute);
		CPPUNIT_TEST(calculateRoute_obstacleOnWayToTargetFromPointBesideObstacle_reasonableRoute);
		CPPUNIT_TEST(calculateRoute_obstacleOnWayToAndFromPointBesideObstacle_reasonableRoute);
		CPPUNIT_TEST(calculateRoute_goingBetweenTwoObstacles_directRoute);
		CPPUNIT_TEST(calculateRoute_severalObjectsAndOneOnTheWay_calculationIsNotTooSlow);
		CPPUNIT_TEST(calculateRoute_shortWayOutsideField_noPointOfRouteIsOutside);
		CPPUNIT_TEST(calculateRoute_onlyPossiblePointBesideIsBlockedByAnotherObstacle_reasonableRoute);
		CPPUNIT_TEST(calculateRoute_softObstacleAtOwnPosition_validRoute);
		CPPUNIT_TEST(calculateRoute_completeTurnAtStartNecessaryAndMaximumRotation_reasonableRoute);
		CPPUNIT_TEST(calculateRoute_completeTurnAtEndNecessaryAndMaximumRotation_reasonableRoute);
		CPPUNIT_TEST(calculateRoute_sharpBendBetweenNecessary_reasonableRoute);
		CPPUNIT_TEST(calculateRoute_endRotationNotPossibleBecauseOfObstacles_invalidRoute);
		CPPUNIT_TEST(calculateRoute_twoSmallObstaclesVeryClose_validRoute);
		CPPUNIT_TEST(calculateRoute_targetOutsideOfTheField_invalidRoute);
		CPPUNIT_TEST(calculateRoute_softObstacleOnTheWayAndIgnoreSoftObstacles_directConnection);
		CPPUNIT_TEST(calculateRoute_hardObstacleOnTheWayAndIgnoreSoftObstacles_reasonableRouteBesideTheObstacle);
		CPPUNIT_TEST(calculateRoute_completeTurnAtEndAndIgnoreFinalOrientation_directConnection);
		CPPUNIT_TEST(calculateRoute_hardObstacleInsideStartPosition_directConnection);
		CPPUNIT_TEST(calculateRoute_hardObstacleIntersectingWithStartPosition_reasonableRoute);
		CPPUNIT_TEST(calculateRoute_targetInsideSoftObstacle_invalidRoute);
		CPPUNIT_TEST(calculateRoute_startIsOutsideTheField_validRoute);
		CPPUNIT_TEST(calculateRoute_startIsOutsideTheFieldAndAnObstacleOnTheWay_validRoute);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIsCorrect);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_longPointIsCorrect);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIsCorrect);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_longPointIsCorrect);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIsOk);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIsOk);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_shortPointIsCorrect);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_longPointIsCorrect);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_shortPointIsCorrect);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_longPointIsCorrect);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_shortPointIsOk);
		CPPUNIT_TEST(getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_shortPointIsOk);
		CPPUNIT_TEST(getPointsBesideObstacle_pathFrom1And1To1And10AndSmallObstacleBetween_resultSizeIs2);
		CPPUNIT_TEST(getPointsBesideObstacle_smallObstacleBetweenAt2And0p5_shortPointIsCorrect);
		CPPUNIT_TEST(getPointsBesideObstacle_smallObstacleBetweenAt2And0p5_longPointIsCorrect);
		CPPUNIT_TEST(getPointsBesideObstacle_bigObstacleOnRightSide_resultSizeIs2);
		CPPUNIT_TEST(getPointsBesideObstacle_bigObstacleOnRightSide_bothPointsDoNotIntersectWithTheObstacle);
		CPPUNIT_TEST(getPointsBesideObstacle_bigObstacleOnRightSide_bothPointsHaveReasonableCoordinates);
		CPPUNIT_TEST(getPointsBesideObstacle_bigObstacleOnRightSide_shortPointIsCorrect);
		CPPUNIT_TEST(getPointsBesideObstacle_bigObstacleOnRightSide_longPointIsCorrect);
		CPPUNIT_TEST(getPointsBesideObstacle_bigObstacleCloseOnLeftSide_onePointIsLeftAndOneRight);
		CPPUNIT_TEST(getPointsBesideObstacle_bigObstacle_newStartBesideObstacleDoesntIntersectWithObstacleInWorstCaseOrientationFromStart);
		CPPUNIT_TEST(detectLoopInConsideredObstacles_noObstacles_false);
		CPPUNIT_TEST(detectLoopInConsideredObstacles_oneObstacle_false);
		CPPUNIT_TEST(detectLoopInConsideredObstacles_twiceTheSameObstacle_false);
		CPPUNIT_TEST(detectLoopInConsideredObstacles_twiceTheSameObstacleAtEnd_false);
		CPPUNIT_TEST(detectLoopInConsideredObstacles_thriceTheSameObstacle_false);
		CPPUNIT_TEST(detectLoopInConsideredObstacles_twiceTheSameObstacleInTheMiddle_false);
		CPPUNIT_TEST(detectLoopInConsideredObstacles_twiceTheSameObstacleAtBegin_false);
		CPPUNIT_TEST(detectLoopInConsideredObstacles_loopOverOne_true);
		CPPUNIT_TEST(detectLoopInConsideredObstacles_loopOverTwo_true);
		CPPUNIT_TEST(detectLoopInConsideredObstacles_sameAsSecond_true);
		CPPUNIT_TEST(detectLoopInConsideredObstacles_somewhereInBetweenALoop_false);
		CPPUNIT_TEST(detectLoopInConsideredObstacles_triedOnceLeftAndRightBesideSameObstacleDirectFollowed_true);
		CPPUNIT_TEST(detectLoopInConsideredObstacles_triedOnceLeftAndRightBesideSameObstacle_true);
		CPPUNIT_TEST(getPointsBesideObstacle_obstacleAtStart_resultSizeIs0);
		CPPUNIT_TEST(getPointsBesideObstacle_obstacleAtEnd_resultSizeIs0);
		CPPUNIT_TEST_SUITE_END();

	private:
		void calculateRoute_emptyField_validRoute();
		void calculateRoute_emptyField_routeHasTwoPoints();
		void calculateRoute_emptyField_routeHasSameWidthAsRobot();
		void calculateRoute_softObstacleAtEndOfRoute_invalidRoute();
		void calculateRoute_oneObstacleBetween_validRoute();
		void calculateRoute_oneObstacleBetween_routeIsNotTooLong();
		void calculateRoute_oneObstacleBetween_routeIsNotIntersectingWithObstacles();
		void calculateRoute_oneBigObstacleCloseToStart_validRoute();
		void calculateRoute_oneBigObstacleCloseToStart_routeIsNotTooLong();
		void calculateRoute_oneBigObstacleCloseToEnd_validRoute();
		void calculateRoute_oneBigObstacleCloseToEnd_routeIsNotTooLong();
		void calculateRoute_oneBigObstacleCloseToEnd_routeIsNotIntersectingWithObstacles();
		void calculateRoute_oneBigObstacleOnRightSideOfDirectPath_reasonableRoute();
		void calculateRoute_oneBigObstacleOnLeftSideOfDirectPath_reasonableRoute();
		void calculateRoute_obstacleOnWayToPointBesideObstacle_reasonableRoute();
		void calculateRoute_obstacleOnWayToTargetFromPointBesideObstacle_reasonableRoute();
		void calculateRoute_obstacleOnWayToAndFromPointBesideObstacle_reasonableRoute();
		void calculateRoute_goingBetweenTwoObstacles_directRoute();
		void calculateRoute_severalObjectsAndOneOnTheWay_calculationIsNotTooSlow();
		void calculateRoute_shortWayOutsideField_noPointOfRouteIsOutside();
		void calculateRoute_onlyPossiblePointBesideIsBlockedByAnotherObstacle_reasonableRoute();
		void calculateRoute_softObstacleAtOwnPosition_validRoute();
		void calculateRoute_completeTurnAtStartNecessaryAndMaximumRotation_reasonableRoute();
		void calculateRoute_completeTurnAtEndNecessaryAndMaximumRotation_reasonableRoute();
		void calculateRoute_sharpBendBetweenNecessary_reasonableRoute();
		void calculateRoute_endRotationNotPossibleBecauseOfObstacles_invalidRoute();
		void calculateRoute_twoSmallObstaclesVeryClose_validRoute();
		void calculateRoute_targetOutsideOfTheField_invalidRoute();
		void calculateRoute_softObstacleOnTheWayAndIgnoreSoftObstacles_directConnection();
		void calculateRoute_hardObstacleOnTheWayAndIgnoreSoftObstacles_reasonableRouteBesideTheObstacle();
		void calculateRoute_completeTurnAtEndAndIgnoreFinalOrientation_directConnection();
		void calculateRoute_hardObstacleInsideStartPosition_directConnection();
		void calculateRoute_hardObstacleIntersectingWithStartPosition_reasonableRoute();
		void calculateRoute_targetInsideSoftObstacle_invalidRoute();
		void calculateRoute_startIsOutsideTheField_validRoute();
		void calculateRoute_startIsOutsideTheFieldAndAnObstacleOnTheWay_validRoute();
		void getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIsCorrect();
		void getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_longPointIsCorrect();
		void getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIsCorrect();
		void getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_longPointIsCorrect();
		void getPointsBesideObstacle_intersectFromLeftAndCircleCenterNotOnPath_shortPointIsOk();
		void getPointsBesideObstacle_intersectFromRightAndCircleCenterNotOnPath_shortPointIsOk();
		void getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_shortPointIsCorrect();
		void getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_longPointIsCorrect();
		void getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_shortPointIsCorrect();
		void getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_longPointIsCorrect();
		void getPointsBesideObstacle_intersectFromLeftAndCircleCenterIsOnPath_shortPointIsOk();
		void getPointsBesideObstacle_intersectFromRightAndCircleCenterIsOnPath_shortPointIsOk();
		void getPointsBesideObstacle_pathFrom1And1To1And10AndSmallObstacleBetween_resultSizeIs2();
		void getPointsBesideObstacle_smallObstacleBetweenAt2And0p5_shortPointIsCorrect();
		void getPointsBesideObstacle_smallObstacleBetweenAt2And0p5_longPointIsCorrect();
		void getPointsBesideObstacle_bigObstacleOnRightSide_resultSizeIs2();
		void getPointsBesideObstacle_bigObstacleOnRightSide_bothPointsDoNotIntersectWithTheObstacle();
		void getPointsBesideObstacle_bigObstacleOnRightSide_bothPointsHaveReasonableCoordinates();
		void getPointsBesideObstacle_bigObstacleOnRightSide_shortPointIsCorrect();
		void getPointsBesideObstacle_bigObstacleOnRightSide_longPointIsCorrect();
		void getPointsBesideObstacle_bigObstacleCloseOnLeftSide_onePointIsLeftAndOneRight();
		void getPointsBesideObstacle_bigObstacle_newStartBesideObstacleDoesntIntersectWithObstacleInWorstCaseOrientationFromStart();
		void detectLoopInConsideredObstacles_noObstacles_false();
		void detectLoopInConsideredObstacles_oneObstacle_false();
		void detectLoopInConsideredObstacles_twiceTheSameObstacle_false();
		void detectLoopInConsideredObstacles_twiceTheSameObstacleAtEnd_false();
		void detectLoopInConsideredObstacles_thriceTheSameObstacle_false();
		void detectLoopInConsideredObstacles_twiceTheSameObstacleInTheMiddle_false();
		void detectLoopInConsideredObstacles_twiceTheSameObstacleAtBegin_false();
		void detectLoopInConsideredObstacles_loopOverOne_true();
		void detectLoopInConsideredObstacles_loopOverTwo_true();
		void detectLoopInConsideredObstacles_sameAsSecond_true();
		void detectLoopInConsideredObstacles_somewhereInBetweenALoop_false();
		void detectLoopInConsideredObstacles_triedOnceLeftAndRightBesideSameObstacleDirectFollowed_true();
		void detectLoopInConsideredObstacles_triedOnceLeftAndRightBesideSameObstacle_true();
		void getPointsBesideObstacle_obstacleAtStart_resultSizeIs0();
		void getPointsBesideObstacle_obstacleAtEnd_resultSizeIs0();

	private:
		static bool routeIsInsideField(const Route &route, const Field &field);
	};
}
}
}

#endif
