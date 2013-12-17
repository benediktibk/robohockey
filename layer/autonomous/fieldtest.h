#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDTEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace Autonomous
{
	class FieldTest:
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(FieldTest);
		CPPUNIT_TEST(update_noLidarObjects_noFieldObjects);
		CPPUNIT_TEST(update_oneObjectFromLidarInView_oneObject);
		CPPUNIT_TEST(update_oneObjectFromLidarNotInViewAnymoreDuringSecondCall_noFieldObjects);
		CPPUNIT_TEST(update_oneObjectFromLidarLeftNotInViewAnymoreDuringSecondCall_noFieldObjects);
		CPPUNIT_TEST(update_oneObjectFromLidarRightNotInViewAnymoreDuringSecondCall_noFieldObjects);
		CPPUNIT_TEST(update_objectFromLidarNotInViewAnymoreThroughRotation_oneFieldObject);
		CPPUNIT_TEST(update_oneObjectFromLidarAndNoObjectFromCamera_noColor);
		CPPUNIT_TEST(update_twoObjectsFromLidarAndOneFromCamera_correctColor);
		CPPUNIT_TEST(update_twoObjectsFromLidarAndOneFromCameraNoColorAnymoreDuringSecondCall_stillCorrectColor);
		CPPUNIT_TEST(update_oneObjectOutAndOneObjectInsideOfCalibratedField_correctObjectAddedToField);
		CPPUNIT_TEST(update_threeObjectsAndTwoObjectsInGoal_twoAchievedGoals);
        CPPUNIT_TEST(update_threeObjectsAndThreeObjectsInGoal_threeAchievedGoals);
        CPPUNIT_TEST(update_fourObjectsAndFourObjectsInGoal_fourAchievedGoals);
        CPPUNIT_TEST(update_fourObjectsAndThreeObjectsInGoal_threeAchievedGoals);
        CPPUNIT_TEST(update_oneObjectAndZeroObjectsInGoal_ZeroAchievedGoals);
        CPPUNIT_TEST(update_threeObjectsAndTwoObjectsHidden_twoHiddenPucks);
        CPPUNIT_TEST(update_threeObjectsAndThreeObjectsHidden_threeHiddenPucks);
        CPPUNIT_TEST(update_threeObjectsAndZeroObjectsHidden_zeroHiddenPucks);
        CPPUNIT_TEST(update_fourObjectsAndTwoObjectsHidden_twoHiddenPucks);
        CPPUNIT_TEST(update_fourObjectsAndFourObjectsHidden_fourHiddenPucks);
        CPPUNIT_TEST(update_fourObjectsAndThreeObjectsHidden_threeHiddenPucks);
		CPPUNIT_TEST(calibratePosition_noValidPattern_false);
		CPPUNIT_TEST(calibratePosition_validPattern_true);
		CPPUNIT_TEST(calibratePosition_noValidPattern_noTransformation);
		CPPUNIT_TEST(calibratePosition_validPattern_transformed);
		CPPUNIT_TEST(calibratePosition_validPattern_correctNumberOfFieldObjects);
		CPPUNIT_TEST(calibratePosition_validPattern_correctTransformation);
		CPPUNIT_TEST(calibratePosition_realWorldExample_positionIsCorrect);
		CPPUNIT_TEST(calibratePosition_validPattern_objectsOutsideFieldAreDeleted);
		CPPUNIT_TEST(getObjectsWithColorOrderedByDistance_oneObjectWithCorrectColorAndOneWithNoColor_resultSizeIsCorrect);
		CPPUNIT_TEST(getObjectsWithColorOrderedByDistance_twoObjectsWithCorrectColorInAscendingOrder_orderIsCorrect);
		CPPUNIT_TEST(getObjectsWithColorOrderedByDistance_twoObjectsWithCorrectColorInDescendingOrder_orderIsCorrect);
		CPPUNIT_TEST(isPointInsideField_notCalibrated_true);
		CPPUNIT_TEST(isPointInsideField_pointIsInside_true);
		CPPUNIT_TEST(isPointInsideField_pointIsOutside_false);
		CPPUNIT_TEST(isPointInsideField_pointIsUnderField_false);
		CPPUNIT_TEST(numberOfPucksChanged_emptyField_false);
		CPPUNIT_TEST(numberOfPucksChanged_onePuckAdded_true);
		CPPUNIT_TEST(numberOfPucksChanged_onePuckRemoved_true);
		CPPUNIT_TEST(numberOfPucksChanged_onePuckAddedOnePuckRemoved_true);
		CPPUNIT_TEST(getTargetsForGoalDetection_correctPosition);
		CPPUNIT_TEST(getAllSoftObstacles_oneBluePuck_resultSizeIs1);
		CPPUNIT_TEST(getAllSoftObstacles_oneSmallObstacleWithUnknownColor_resultSizeIs1);
		CPPUNIT_TEST(getAllSoftObstacles_oneGreenObstacle_resultSizeIs0);
		CPPUNIT_TEST(getAllSoftObstacles_oneBigObstacle_resultSizeIs0);
		CPPUNIT_TEST(getAllSoftObstacles_onePuckDisappeared_resultSizeIs0);
		CPPUNIT_TEST(getAllSoftObstacles_oneSmallObstacleWithUnknownColor_resultDiameterIs0p12);
		CPPUNIT_TEST(getAllHardObstacles_oneGreenObject_resultSizeIs1);
		CPPUNIT_TEST(getAllHardObstacles_oneBigObstacle_resultSizeIs1);
		CPPUNIT_TEST(getAllHardObstacles_oneSmallObstacleWithUnknownColor_resultSizeIs0);
		CPPUNIT_TEST(getAllHardObstacles_oneBigObstacleDisappeared_resultSizeIs0);
        CPPUNIT_TEST(getEnemyTeamColor_OwnTeamColorYellow_blue);
        CPPUNIT_TEST(getEnemyTeamColor_OwnTeamColorBlue_yellow);
		CPPUNIT_TEST(getTargetsForScoringGoals_always_numberOfPositionsBigger4);
		CPPUNIT_TEST(getTargetsForFinalPosition_always_numberOfPositionsBigger1);
		CPPUNIT_TEST(getTargetsForSearchingPucks_always_numberOfPositionsBigger5);
		CPPUNIT_TEST(detectTeamColorWithGoalInFront_yellowMuchBiggerBlue_teamYellow);
		CPPUNIT_TEST(detectTeamColorWithGoalInFront_yellowMuchSmallerBlue_teamBlue);
		CPPUNIT_TEST(detectTeamColorWithGoalInFront_yellowAndBlueFuzzyEqual_teamUnknown);
		CPPUNIT_TEST(getNewOriginFromFieldDetection_realWorldExample1_correctNewOrigin);
		CPPUNIT_TEST(getNewOriginFromFieldDetection_realWorldExample2_correctNewOrigin);
		CPPUNIT_TEST(getNewOriginFromFieldDetection_realWorldExample3_correctNewOrigin);
		CPPUNIT_TEST_SUITE_END();

	private:
		void update_noLidarObjects_noFieldObjects();
		void update_oneObjectFromLidarInView_oneObject();
		void update_oneObjectFromLidarNotInViewAnymoreDuringSecondCall_noFieldObjects();
		void update_oneObjectFromLidarLeftNotInViewAnymoreDuringSecondCall_noFieldObjects();
		void update_oneObjectFromLidarRightNotInViewAnymoreDuringSecondCall_noFieldObjects();
		void update_objectFromLidarNotInViewAnymoreThroughRotation_oneFieldObject();
		void update_oneObjectFromLidarAndNoObjectFromCamera_noColor();
		void update_twoObjectsFromLidarAndOneFromCamera_correctColor();
		void update_twoObjectsFromLidarAndOneFromCameraNoColorAnymoreDuringSecondCall_stillCorrectColor();
		void update_oneObjectOutAndOneObjectInsideOfCalibratedField_correctObjectAddedToField();
        void update_threeObjectsAndTwoObjectsInGoal_twoAchievedGoals();
        void update_threeObjectsAndThreeObjectsInGoal_threeAchievedGoals();
        void update_fourObjectsAndFourObjectsInGoal_fourAchievedGoals();
        void update_fourObjectsAndThreeObjectsInGoal_threeAchievedGoals();
        void update_oneObjectAndZeroObjectsInGoal_ZeroAchievedGoals();
        void update_threeObjectsAndTwoObjectsHidden_twoHiddenPucks();
        void update_threeObjectsAndThreeObjectsHidden_threeHiddenPucks();
        void update_threeObjectsAndZeroObjectsHidden_zeroHiddenPucks();
        void update_fourObjectsAndTwoObjectsHidden_twoHiddenPucks();
        void update_fourObjectsAndFourObjectsHidden_fourHiddenPucks();
        void update_fourObjectsAndThreeObjectsHidden_threeHiddenPucks();
		void calibratePosition_noValidPattern_false();
		void calibratePosition_validPattern_true();
		void calibratePosition_noValidPattern_noTransformation();
		void calibratePosition_validPattern_transformed();
		void calibratePosition_validPattern_correctNumberOfFieldObjects();
		void calibratePosition_validPattern_correctTransformation();
		void calibratePosition_realWorldExample_positionIsCorrect();
		void calibratePosition_validPattern_objectsOutsideFieldAreDeleted();
		void getObjectsWithColorOrderedByDistance_oneObjectWithCorrectColorAndOneWithNoColor_resultSizeIsCorrect();
		void getObjectsWithColorOrderedByDistance_twoObjectsWithCorrectColorInAscendingOrder_orderIsCorrect();
		void getObjectsWithColorOrderedByDistance_twoObjectsWithCorrectColorInDescendingOrder_orderIsCorrect();
		void isPointInsideField_notCalibrated_true();
		void isPointInsideField_pointIsInside_true();
		void isPointInsideField_pointIsOutside_false();
		void isPointInsideField_pointIsUnderField_false();
		void numberOfPucksChanged_emptyField_false();
		void numberOfPucksChanged_onePuckAdded_true();
		void numberOfPucksChanged_onePuckRemoved_true();
		void numberOfPucksChanged_onePuckAddedOnePuckRemoved_true();
		void getTargetsForGoalDetection_correctPosition();
		void getAllSoftObstacles_oneBluePuck_resultSizeIs1();
		void getAllSoftObstacles_oneSmallObstacleWithUnknownColor_resultSizeIs1();
		void getAllSoftObstacles_oneGreenObstacle_resultSizeIs0();
		void getAllSoftObstacles_oneBigObstacle_resultSizeIs0();
		void getAllSoftObstacles_onePuckDisappeared_resultSizeIs0();
		void getAllSoftObstacles_oneSmallObstacleWithUnknownColor_resultDiameterIs0p12();
		void getAllHardObstacles_oneGreenObject_resultSizeIs1();
		void getAllHardObstacles_oneBigObstacle_resultSizeIs1();
		void getAllHardObstacles_oneSmallObstacleWithUnknownColor_resultSizeIs0();
		void getAllHardObstacles_oneBigObstacleDisappeared_resultSizeIs0();
        void getEnemyTeamColor_OwnTeamColorYellow_blue();
        void getEnemyTeamColor_OwnTeamColorBlue_yellow();
		void getTargetsForScoringGoals_always_numberOfPositionsBigger4();
		void getTargetsForFinalPosition_always_numberOfPositionsBigger1();
		void getTargetsForSearchingPucks_always_numberOfPositionsBigger5();
		void detectTeamColorWithGoalInFront_yellowMuchBiggerBlue_teamYellow();
		void detectTeamColorWithGoalInFront_yellowMuchSmallerBlue_teamBlue();
		void detectTeamColorWithGoalInFront_yellowAndBlueFuzzyEqual_teamUnknown();
		void getNewOriginFromFieldDetection_realWorldExample1_correctNewOrigin();
		void getNewOriginFromFieldDetection_realWorldExample2_correctNewOrigin();
		void getNewOriginFromFieldDetection_realWorldExample3_correctNewOrigin();
	};
}
}
}

#endif
