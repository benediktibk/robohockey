#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTETEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROUTETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class RouteTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RouteTest);
		CPPUNIT_TEST(constructor_validWidth_isNotValid);
		CPPUNIT_TEST(constructor_validWidth_pointCountIs0);
		CPPUNIT_TEST(constructor_03_widthIs03);
		CPPUNIT_TEST(addPoint_onceCalled_pointCountIs1);
		CPPUNIT_TEST(addPoint_twiceCalled_pointCountIs2);
		CPPUNIT_TEST(isValid_onePointAdded_true);
		CPPUNIT_TEST(getLastPoint_onePointAdded_lastAddedPoint);
		CPPUNIT_TEST(getLastPoint_twoPointsAdded_lastAddedPoint);
		CPPUNIT_TEST(getFirstPoint_twoPointsAdded_firstPoint);
		CPPUNIT_TEST(removeFirstPoint_onePointAdded_pointCountIs0);
		CPPUNIT_TEST(removeFirstPoint_twoPointsAdded_onlyPointIsLastAddedPoint);
		CPPUNIT_TEST(intersectsWith_noObstacles_false);
		CPPUNIT_TEST(intersectsWith_oneObstacleFarAway_false);
		CPPUNIT_TEST(intersectsWith_oneObstacleOnTheWay_true);
		CPPUNIT_TEST(intersectsWith_oneObstacleFarAwayAndOneOnTheWay_true);
		CPPUNIT_TEST(intersectsWith_bigObstacleButOnlyOneNode_false);
		CPPUNIT_TEST(intersectsWith_firstRoutePartIntersectingWithObstacle_true);
		CPPUNIT_TEST(intersectsWith_secondRoutePartIntersectingWithObstacle_true);
		CPPUNIT_TEST(intersectsWith_threeRoutePartsAndOneNotDisturbingObstacle_false);
		CPPUNIT_TEST(intersectsWith_widthTooSmallForIntersection_false);
		CPPUNIT_TEST(getLength_from1And2To3And2To3And5_5);
		CPPUNIT_TEST(add_validRoute_countOfPointsIsCorrect);
		CPPUNIT_TEST(getMaximumBend_directConnection_0);
		CPPUNIT_TEST(getMaximumBend_oneCompleteTurnAtStart_halfRotation);
		CPPUNIT_TEST(getMaximumBend_oneCompleteTurnAtEnd_halfRotation);
		CPPUNIT_TEST(getMaximumBend_halfTurnUpwardsInBetween_quarterRotation);
		CPPUNIT_TEST(getMaximumBend_halfTurnDownwardsInBetween_quarterRotation);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_validWidth_isNotValid();
		void constructor_validWidth_pointCountIs0();
		void constructor_03_widthIs03();
		void addPoint_onceCalled_pointCountIs1();
		void addPoint_twiceCalled_pointCountIs2();
		void isValid_onePointAdded_true();
		void getLastPoint_onePointAdded_lastAddedPoint();
		void getLastPoint_twoPointsAdded_lastAddedPoint();
		void getFirstPoint_twoPointsAdded_firstPoint();
		void removeFirstPoint_onePointAdded_pointCountIs0();
		void removeFirstPoint_twoPointsAdded_onlyPointIsLastAddedPoint();
		void intersectsWith_noObstacles_false();
		void intersectsWith_oneObstacleFarAway_false();
		void intersectsWith_oneObstacleOnTheWay_true();
		void intersectsWith_oneObstacleFarAwayAndOneOnTheWay_true();
		void intersectsWith_bigObstacleButOnlyOneNode_false();
		void intersectsWith_firstRoutePartIntersectingWithObstacle_true();
		void intersectsWith_secondRoutePartIntersectingWithObstacle_true();
		void intersectsWith_threeRoutePartsAndOneNotDisturbingObstacle_false();
		void intersectsWith_widthTooSmallForIntersection_false();
		void getLength_from1And2To3And2To3And5_5();
		void add_validRoute_countOfPointsIsCorrect();
		void getMaximumBend_directConnection_0();
		void getMaximumBend_oneCompleteTurnAtStart_halfRotation();
		void getMaximumBend_oneCompleteTurnAtEnd_halfRotation();
		void getMaximumBend_halfTurnUpwardsInBetween_quarterRotation();
		void getMaximumBend_halfTurnDownwardsInBetween_quarterRotation();
	};
}
}
}

#endif
