#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDTEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_FIELDTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Layer
{
namespace DataAnalysis
{
	class OdometryMock;
	class LidarMock;
	class CameraMock;
}

namespace Autonomous
{
	class RobotMock;
	class FieldImpl;

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
		CPPUNIT_TEST(update_threePucksWithTeamColor_30ElementsInList);
		CPPUNIT_TEST(update_fourPucksWithTeamColorInRectangle1_40ElementsInList);
		CPPUNIT_TEST(update_twoPucksWithTeamColorInRectangle2_20ElementsInList);
		CPPUNIT_TEST(update_onePuckWithTeamColorInRectangle3_10ElementsInList);
		CPPUNIT_TEST(update_zeroPucksWithTeamColor_0ElementsInList);
		CPPUNIT_TEST(update_fivePucksWithTeamColorInRectangle4_50ElementsInList);
		CPPUNIT_TEST(update_sixPucksWithTeamColorInRectangle5_60ElementsInList);
		CPPUNIT_TEST(update_sevenPucksWithTeamColorInRectangle6_70ElementsInList);
		CPPUNIT_TEST(update_eightPucksWithTeamColorInRectangle7_80ElementsInList);
		CPPUNIT_TEST(update_ninePucksWithTeamColorInRectangle8_90ElementsInList);
		CPPUNIT_TEST(update_tenPucksWithTeamColorInRectangle9_100ElementsInList);
		CPPUNIT_TEST(getTargetsForFinalPosition_callFunction_17ElementsInList);
		CPPUNIT_TEST(update_objectsInFieldRobotOn00_correctlyUpdated);
		CPPUNIT_TEST(update_objectsInFieldRobotOn1And2_correctlyUpdated);
		CPPUNIT_TEST(update_movingAndLidarDataChanges_fieldObjectCountDoesntChange);
		CPPUNIT_TEST(update_movingAndLidatDataChangesSecondVersion_fieldObjectCountDoesntChange);
		CPPUNIT_TEST(update_movingAndLidarDataChangesThirdVersion_fieldObjectCountDoesntChange);
		CPPUNIT_TEST(update_enemyRobotInFront_oneFieldObject);
		CPPUNIT_TEST(update_enemyRobotInFront_oneHardObstacle);
		CPPUNIT_TEST(update_lidarReturnsObjectWhichCantBeSeenActually_noFieldObjects);
		CPPUNIT_TEST(update_lidarObjectSeenOnlyOnce_noFieldObjectsAndObstacles);
		CPPUNIT_TEST(update_lidarObjectSeenThreeTimes_oneFieldObjectAndObstacle);
		CPPUNIT_TEST(update_lidarObjectSeenOnlyOnce_noFieldObjects);
		CPPUNIT_TEST(update_lidarObjectSeenOnlyOnce_noObstacles);
		CPPUNIT_TEST(update_lidarObjectSeenTwice_oneFieldObject);
		CPPUNIT_TEST(update_lidarObjectNotSeenOnce_oneFieldObject);
		CPPUNIT_TEST(update_lidarObjectNotSeenOften_noFieldObjects);
		CPPUNIT_TEST(update_collectedPuckAndMovedForward_oneFieldObject);
		CPPUNIT_TEST(update_rotatingAndObjectALittleBitDistanceMoved_onlyFieldObjectStaysTheSame);
		CPPUNIT_TEST(update_rotatingAndObjectVeryClose_onlyFieldObjectIsUpdated);
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
		CPPUNIT_TEST(getAllHardObstacles_fairlyBigObject_diameterIs08);
		CPPUNIT_TEST(getEnemyTeamColor_OwnTeamColorYellow_blue);
		CPPUNIT_TEST(getEnemyTeamColor_OwnTeamColorBlue_yellow);
		CPPUNIT_TEST(getTargetsForScoringGoals_always_numberOfPositionsBigger4);
		CPPUNIT_TEST(getTargetsForScoringGoals_always_numberOfPositionsBigger5);
		CPPUNIT_TEST(getTargetsForScoringGoals_always_numberOfPositionsBigger6);
		CPPUNIT_TEST(getTargetsForScoringGoals_forEstimatedGoalsAre0AndEstimatedGoalsAre3_positionsAreEqual);
		CPPUNIT_TEST(getTargetsForFinalPosition_always_numberOfPositionsBigger1);
		CPPUNIT_TEST(getTargetsForSearchingPucks_always_numberOfPositionsBigger5);
		CPPUNIT_TEST(getTargetsForSearchingPucks_twoObjectsWithUnknownColor_numberOfPositions33);
		CPPUNIT_TEST(getTargetsForSearchingPucks_threeObjectsWithUnknownColor_numberOfPositions43);
		CPPUNIT_TEST(getTargetsForSearchingPucks_threeObjectsWithUnknownColorNotInField_numberOfPositions10);
		CPPUNIT_TEST(getTargetsForSearchungPucks_fourObjectsWithUnknownColorAndOneObjectWithKnownColorAndTwoPucksWithUnknownColorNotInField_numberOfPositions33);
		CPPUNIT_TEST(getTargetsInEnemyThird_always_numberOfPositionsBiggerThan4);
		CPPUNIT_TEST(getTargetsForWaitingPhase_always_numberOfPositionsBiggerThan2);
		CPPUNIT_TEST(getTargetsForHiddingEnemyPucks_always_numberOfPositionsBiggerThan8);
		CPPUNIT_TEST(detectTeamColorWithGoalInFront_yellowMuchBiggerBlue_teamYellow);
		CPPUNIT_TEST(detectTeamColorWithGoalInFront_yellowMuchSmallerBlue_teamBlue);
		CPPUNIT_TEST(detectTeamColorWithGoalInFront_yellowAndBlueEqual_teamNotUnknown);
		CPPUNIT_TEST(getNewOriginFromFieldDetection_realWorldExample1_correctNewOrigin);
		CPPUNIT_TEST(getNumberOfObjectsWithColor_noColoredObject_0);
		CPPUNIT_TEST(getNumberOfObjectsWithColor_3YellowAnd2GreenAnd1UnknownObject_correctValues);
		CPPUNIT_TEST(getNumberOfObjectsWithColor_2BlueObjects_2);
		CPPUNIT_TEST(getEstimatedNumberOfAchievedGoals_init_0);
		CPPUNIT_TEST(getEstimatedNumberOfAchievedGoals_2goals_2);
		CPPUNIT_TEST(getNumberOfPucksInEnemyThird_3PucksAnd2InEnemyThird_resultIs2);
		CPPUNIT_TEST(getTargetsForCollectingOnePuckNotInEnemyThird_3Objects1Unknown1InEnemyThird_numberOfPositions10);
		CPPUNIT_TEST(isPuckOfColorInFront_noPuckInFront_resultIsFalse);
		CPPUNIT_TEST(isPuckOfColorInFront_puckBehind_resultIsFalse);
		CPPUNIT_TEST(isPuckOfColorInFront_puckInFront_resultIsTrue);
		CPPUNIT_TEST(isPuckOfColorInFront_puckAlmostInFront_resultIsTrue);
		CPPUNIT_TEST(isPuckOfColorInFront_puckAlmostInFrontAndOnePuckLeft_resultIsTrue);
		CPPUNIT_TEST(isPuckcolorDetected_noPucksInSector_resultIsTrue);
		CPPUNIT_TEST(isPuckcolorDetected_twoPucksWithColor_resultIsTrue);
		CPPUNIT_TEST(isPuckcolorDetected_twoPucksWithColorAndOneWithout_resultIsFlase);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

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
		void update_threePucksWithTeamColor_30ElementsInList();
		void update_fourPucksWithTeamColorInRectangle1_40ElementsInList();
		void update_twoPucksWithTeamColorInRectangle2_20ElementsInList();
		void update_onePuckWithTeamColorInRectangle3_10ElementsInList();
		void update_zeroPucksWithTeamColor_0ElementsInList();
		void update_fivePucksWithTeamColorInRectangle4_50ElementsInList();
		void update_sixPucksWithTeamColorInRectangle5_60ElementsInList();
		void update_sevenPucksWithTeamColorInRectangle6_70ElementsInList();
		void update_eightPucksWithTeamColorInRectangle7_80ElementsInList();
		void update_ninePucksWithTeamColorInRectangle8_90ElementsInList();
		void update_tenPucksWithTeamColorInRectangle9_100ElementsInList();
		void getTargetsForFinalPosition_callFunction_17ElementsInList();
		void update_objectsInFieldRobotOn00_correctlyUpdated();
		void update_objectsInFieldRobotOn1And2_correctlyUpdated();
		void update_movingAndLidarDataChanges_fieldObjectCountDoesntChange();
		void update_movingAndLidatDataChangesSecondVersion_fieldObjectCountDoesntChange();
		void update_movingAndLidarDataChangesThirdVersion_fieldObjectCountDoesntChange();
		void update_enemyRobotInFront_oneFieldObject();
		void update_enemyRobotInFront_oneHardObstacle();
		void update_lidarReturnsObjectWhichCantBeSeenActually_noFieldObjects();
		void update_lidarObjectSeenOnlyOnce_noFieldObjectsAndObstacles();
		void update_lidarObjectSeenThreeTimes_oneFieldObjectAndObstacle();
		void update_lidarObjectSeenOnlyOnce_noFieldObjects();
		void update_lidarObjectSeenOnlyOnce_noObstacles();
		void update_lidarObjectSeenTwice_oneFieldObject();
		void update_lidarObjectNotSeenOnce_oneFieldObject();
		void update_lidarObjectNotSeenOften_noFieldObjects();
		void update_collectedPuckAndMovedForward_oneFieldObject();
		void update_rotatingAndObjectALittleBitDistanceMoved_onlyFieldObjectStaysTheSame();
		void update_rotatingAndObjectVeryClose_onlyFieldObjectIsUpdated();
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
		void getAllHardObstacles_fairlyBigObject_diameterIs08();
		void getEnemyTeamColor_OwnTeamColorYellow_blue();
		void getEnemyTeamColor_OwnTeamColorBlue_yellow();
		void getTargetsForScoringGoals_always_numberOfPositionsBigger4();
		void getTargetsForScoringGoals_always_numberOfPositionsBigger5();
		void getTargetsForScoringGoals_always_numberOfPositionsBigger6();
		void getTargetsForScoringGoals_forEstimatedGoalsAre0AndEstimatedGoalsAre3_positionsAreEqual();
		void getTargetsForFinalPosition_always_numberOfPositionsBigger1();
		void getTargetsForSearchingPucks_always_numberOfPositionsBigger5();
		void getTargetsForSearchingPucks_twoObjectsWithUnknownColor_numberOfPositions33();
		void getTargetsForSearchingPucks_threeObjectsWithUnknownColor_numberOfPositions43();
		void getTargetsForSearchingPucks_threeObjectsWithUnknownColorNotInField_numberOfPositions10();
		void getTargetsForSearchungPucks_fourObjectsWithUnknownColorAndOneObjectWithKnownColorAndTwoPucksWithUnknownColorNotInField_numberOfPositions33();
		void getTargetsInEnemyThird_always_numberOfPositionsBiggerThan4();
		void getTargetsForWaitingPhase_always_numberOfPositionsBiggerThan2();
		void getTargetsForHiddingEnemyPucks_always_numberOfPositionsBiggerThan8();
		void detectTeamColorWithGoalInFront_yellowMuchBiggerBlue_teamYellow();
		void detectTeamColorWithGoalInFront_yellowMuchSmallerBlue_teamBlue();
		void detectTeamColorWithGoalInFront_yellowAndBlueEqual_teamNotUnknown();
		void getNewOriginFromFieldDetection_realWorldExample1_correctNewOrigin();
		void getNumberOfObjectsWithColor_noColoredObject_0();
		void getNumberOfObjectsWithColor_3YellowAnd2GreenAnd1UnknownObject_correctValues();
		void getNumberOfObjectsWithColor_2BlueObjects_2();
		void getEstimatedNumberOfAchievedGoals_init_0();
		void getEstimatedNumberOfAchievedGoals_2goals_2();
		void getNumberOfPucksInEnemyThird_3PucksAnd2InEnemyThird_resultIs2();
		void getTargetsForCollectingOnePuckNotInEnemyThird_3Objects1Unknown1InEnemyThird_numberOfPositions10();
		void isPuckOfColorInFront_noPuckInFront_resultIsFalse();
		void isPuckOfColorInFront_puckBehind_resultIsFalse();
		void isPuckOfColorInFront_puckInFront_resultIsTrue();
		void isPuckOfColorInFront_puckAlmostInFront_resultIsTrue();
		void isPuckOfColorInFront_puckAlmostInFrontAndOnePuckLeft_resultIsTrue();
		void isPuckcolorDetected_noPucksInSector_resultIsTrue();
		void isPuckcolorDetected_twoPucksWithColor_resultIsTrue();
		void isPuckcolorDetected_twoPucksWithColorAndOneWithout_resultIsFlase();

	private:
		void updateFieldForObjectsToAppear(FieldImpl &field);
		void updateFieldForObjectsToDisappear(FieldImpl &field);
		void updateFieldForObjectsToAppear();
		void updateFieldForObjectsToDisappear();

	private:
		DataAnalysis::CameraMock *m_camera;
		DataAnalysis::LidarMock *m_lidar;
		DataAnalysis::OdometryMock *m_odometry;
		RobotMock *m_robot;
		FieldImpl *m_field;
	};
}
}
}

#endif
