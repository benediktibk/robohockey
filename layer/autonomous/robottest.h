#ifndef ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTTEST_H
#define ROBOHOCKEY_LAYER_AUTONOMOUS_ROBOTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <list>
#include "common/robotposition.h"

namespace RoboHockey
{
namespace Common
{
	class WatchMock;
	class LoggerMock;
}

namespace Layer
{
namespace DataAnalysis
{
	class DataAnalyserMock;
	class OdometryMock;
	class EngineMock;
	class SonarMock;
	class LidarMock;
}

namespace Autonomous
{
	class RouterMock;
	class RobotImpl;
	class FieldMock;

	class RobotTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RobotTest);
		CPPUNIT_TEST(goTo_positionDifferentToCurrentOne_engineGotAtLeastOneCallToGoToStraightOrTurnTo);
		CPPUNIT_TEST(goTo_orientationToTargetCorrect_engineGotAtLeastOneCallToGoToStraight);
		CPPUNIT_TEST(goTo_orientationToTargetCompletelyWrong_engineGotNoCallToGoToStraight);
		CPPUNIT_TEST(goTo_orientationToTargetCompletelyWrong_engineGotAtLeastOneCallToTurnTo);
		CPPUNIT_TEST(goTo_orientationToTargetCompletelyWrong_isRotating);
		CPPUNIT_TEST(goTo_orientationToTargetCorrectAndUpdateCalledTwice_notReachedTarget);
		CPPUNIT_TEST(goTo_orientationReachedAfterSomeTime_notReachedTarget);
		CPPUNIT_TEST(goTo_lookingDownwardButHaveToGoUpAndOrientationReached_engineGotAtLeastOneCallToGoToStraight);
		CPPUNIT_TEST(goTo_targetPositionReached_reachedTarget);
		CPPUNIT_TEST(goTo_firstPointReached_notReachedTarget);
		CPPUNIT_TEST(goTo_firstPointReached_engineGotOneCallToTurnTo);
		CPPUNIT_TEST(goTo_firstPointReached_lastArgumentOfTurnToIsTargetPoint);
		CPPUNIT_TEST(goTo_firstPointAndRotationReached_engineGotOneCallToGoToStraight);
		CPPUNIT_TEST(goTo_finalPointReached_engineGotOneCallToTurnTo);
		CPPUNIT_TEST(goTo_finalOrientationReached_engineGotOneCallToStop);
		CPPUNIT_TEST(goTo_surroundedBySoftObstacles_canReachTarget);
		CPPUNIT_TEST(goTo_surroundedByHardObstacles_cantReachTarget);
		CPPUNIT_TEST(goTo_finalOrientationNotPossible_canReachTarget);
		CPPUNIT_TEST(goTo_twoTargetsAndFirstOnePossible_canReachFirstTarget);
		CPPUNIT_TEST(goTo_twoTargetsAndOnlySecondOnePossible_canReachSecondTarget);
		CPPUNIT_TEST(goTo_minuteWaited_cantReachTarget);
		CPPUNIT_TEST(goTo_obstacleSuddenlyAppearedDuringDriving_engineGotCallToStop);
		CPPUNIT_TEST(goTo_obstacleSuddenlyAppearedDuringTurning_engineGotCallToStop);
		CPPUNIT_TEST(goTo_hardObstacleAtStart_engineGotCallToTurnToTarget);
		CPPUNIT_TEST(goTo_hardObstacleMovedALittleBitIntoTheRoute_engineGotNoAdditionalCalls);
		CPPUNIT_TEST(goTo_puckCollectedButLostInBetween_newRouteStillConsideringThePuck);
		CPPUNIT_TEST(goTo_positionInsideHardObstacle_cantReachTarget);
		CPPUNIT_TEST(goTo_positionInsideSoftObstacle_canReachTarget);
		CPPUNIT_TEST(goTo_firstPointNearlyReachedAndSmallTurnNecessary_lastSpeedIsBig);
		CPPUNIT_TEST(goTo_firstPointReachedAndSmallTurnNecessary_noCallsToTurnToTarget);
		CPPUNIT_TEST(goTo_firstPointReachedAndSmallTurnNecessary_engineGotCorrectNextTarget);
		CPPUNIT_TEST(goTo_orientationDifferenceZero_engineGotOnlyCallToGoToStraight);
		CPPUNIT_TEST(goTo_orientationDifferenceSmall_engineGotOnlyCallToGoToStraight);
		CPPUNIT_TEST(goTo_noUpdateOfActuators_engineGotCallToStop);
		CPPUNIT_TEST(goTo_finalPointReached_engineGotCallToTurnToFinalOrientation);
		CPPUNIT_TEST(goTo_hardNotVisibleObstacleAtEnd_canReachTarget);
		CPPUNIT_TEST(stuckAtObstacle_tryingToTackleObstacle_true);
		CPPUNIT_TEST(stuckAtObstacle_notTryingToTackleObstacle_false);
		CPPUNIT_TEST(stuckAtObstacle_updateCalledTwiceAfterStuckAtObstacle_true);
		CPPUNIT_TEST(stuckAtObstacle_newTargetSet_false);
		CPPUNIT_TEST(stuckAtObstacle_collectPuckInFrontCalled_false);
		CPPUNIT_TEST(stuckAtObstacle_turnAroundCalled_false);
		CPPUNIT_TEST(stuckAtObstacle_leavePuckCalled_false);
		CPPUNIT_TEST(stuckAtObstacle_turnToCalled_false);
		CPPUNIT_TEST(reachedTarget_engineSaysNotReached_false);
		CPPUNIT_TEST(reachedTarget_currentPositionIsTargetPosition_true);
		CPPUNIT_TEST(updateActuators_empty_layerBelowGotAtLeastOneCallToUpdateActuators);
		CPPUNIT_TEST(updateSensorData_empty_layerBelowGotAtLeastOneCallToUpdateSensorData);
		CPPUNIT_TEST(stop_empty_engineGotAtLeastOneCallToStop);
		CPPUNIT_TEST(stuckAtObstacle_empty_engineGotAtLeastOneCallToTryingToTackleObstacle);
		CPPUNIT_TEST(turnToTarget_validPoint_engineGotAtLeastOneCallToTurnToTarget);
		CPPUNIT_TEST(turnToTarget_orientationReached_reachedTarget);
		CPPUNIT_TEST(turnToTarget_minuteWaited_cantReachTarget);
		CPPUNIT_TEST(updateActuators_tryingToTackleObstacle_engineGotAtLeastOneCallToStop);
		CPPUNIT_TEST(updateActuators_tryingToTackleObstacle_targetNotReached);
		CPPUNIT_TEST(updateActuators_tryingToTackleObstacleFromSonar_lastMessageContainssonar);
		CPPUNIT_TEST(updateActuators_tryingToTackleObstacleFromLidar_lastMessageContainslidar);
		CPPUNIT_TEST(updateSensorData_noObstacleDirectInFront_engineGotNoCallToLockForwardMovement);
		CPPUNIT_TEST(updateSensorData_noObstacleDirectInFront_engineGotAtLeastOneCallToUnlockForwardMovement);
		CPPUNIT_TEST(updateSensorData_obstacleDirectInFront_engineGotAtLeastOneCallToLockForwardMovement);
		CPPUNIT_TEST(updateSensorData_0bstacleDirectInFront_engineGotNoCallToUnlockForwardMovement);
		CPPUNIT_TEST(turnAround_empty_engineGotAtLeastOneCallToTurnAround);
		CPPUNIT_TEST(turnAround_turnAroundDone_reachedTarget);
		CPPUNIT_TEST(turnAround_minuteWaited_cantReachTarget);
		CPPUNIT_TEST(getCurrentPosition_position3And4InOdometry_3And4);
		CPPUNIT_TEST(reachedTarget_nearlyHitTargetButTookSomeAdditionalWayToStop_false);
		CPPUNIT_TEST(cantReachTarget_calledDirectAfterConstructor_false);
		CPPUNIT_TEST(cantReachTarget_drivingTowardsTheTarget_false);
		CPPUNIT_TEST(cantReachTarget_currentTargetSuddenlyNotPossible_true);
		CPPUNIT_TEST(cantReachTarget_notPossibleAnymoreDuringDriving_true);
		CPPUNIT_TEST(cantReachTarget_onlyLastTargetNotPossibleToReach_false);
		CPPUNIT_TEST(cantReachTarget_updateTwiceCalled_true);
		CPPUNIT_TEST(cantReachTarget_newTargetSet_false);
		CPPUNIT_TEST(cantReachTarget_collectPuckInFrontCalled_false);
		CPPUNIT_TEST(cantReachTarget_turnAroundCalled_false);
		CPPUNIT_TEST(cantReachTarget_turnToCalled_false);
		CPPUNIT_TEST(cantReachTarget_leavePuckCalled_false);
		CPPUNIT_TEST(cantReachTarget_stuckAtObstacle_true);
		CPPUNIT_TEST(isPuckCollected_lidarSaysNo_false);
		CPPUNIT_TEST(isPuckCollected_lidarSaysYesVeryShort_false);
		CPPUNIT_TEST(isPuckCollected_lidarSaysYesLong_true);
		CPPUNIT_TEST(isPuckCollectable_lidarSaysNo_false);
		CPPUNIT_TEST(isPuckCollectable_lidarSaysYes_true);
		CPPUNIT_TEST(collectPuckInFront_puckAhead_notStuckAtObstacle);
		CPPUNIT_TEST(collectPuckInFront_puckAheadAndStartedToMove_notStuckAtObstacle);
		CPPUNIT_TEST(collectPuckInFront_puckAheadAndAlreadyUpdatedTheEngine_notStuckAtObstacle);
		CPPUNIT_TEST(collectPuckInFront_puckCollectedButEngineTargetNotReached_reachedTarget);
		CPPUNIT_TEST(collectPuckInFront_puckNotYetCollected_notReachedTarget);
		CPPUNIT_TEST(collectPuckInFront_drivenToFarAndPuckNotYetCollected_notReachedTarget);
		CPPUNIT_TEST(collectPuckInFront_drivenToFarAndPuckNotYetCollected_cantReachTarget);
		CPPUNIT_TEST(collectPuckInFront_noPuckAhead_cantReachTarget);
		CPPUNIT_TEST(collectPuckInFront_puckAhead_canReachTarget);
		CPPUNIT_TEST(collectPuckInFront_differentPuckAheadThanDesiredOne_cantReachTarget);
		CPPUNIT_TEST(collectPuckInFront_validPuck_isCollectingPuck);
		CPPUNIT_TEST(collectPuckInFront_puckCollected_isNotCollectingPuck);
		CPPUNIT_TEST(collectPuckInFront_lookingLeftAndPuckAhead_canReachTarget);
		CPPUNIT_TEST(collectPuckInFront_orientationWrongAtBegin_canReachTarget);
		CPPUNIT_TEST(collectPuckInFront_orientationWrongAtBegin_engineGotCallToTurnTo);
		CPPUNIT_TEST(collectPuckInFront_orientationWrongAtBeginAndOrientationReached_engineGotCallToGoToStraightSlowly);
		CPPUNIT_TEST(collectPuckInFront_minuteWaited_cantReachTarget);
		CPPUNIT_TEST(collectPuckInFront_sonarDetectsCollision_notStuckAtObstacle);
		CPPUNIT_TEST(updatePuckPosition_newPositionOfPuck_goToStraightSlowlyCalledTwice);
		CPPUNIT_TEST(leaveCollectedPuck_drivenFarEnoughBack_reachedTarget);
		CPPUNIT_TEST(leaveCollectedPuck_minuteWaited_cantReachTarget);
		CPPUNIT_TEST(isRotating_waiting_false);
		CPPUNIT_TEST(isRotating_turnTo_true);
		CPPUNIT_TEST(isRotating_turnAround_true);
		CPPUNIT_TEST(isRotating_firstPhaseOfCollectingPuck_true);
		CPPUNIT_TEST(isRotating_secondPhaseOfCollectingPuck_false);
		CPPUNIT_TEST(isRotating_leavingPuck_false);
		CPPUNIT_TEST(isRotating_turningPartOfGoTo_true);
		CPPUNIT_TEST(isRotating_drivingPartOfGoToAndTurningFast_true);
		CPPUNIT_TEST(isRotating_drivingPartOfGoToAndTurningSlow_true);
		CPPUNIT_TEST(calculateFinalSpeedForGoingStraight_obtuseAngle_0);
		CPPUNIT_TEST(calculateFinalSpeedForGoingStraight_quarterRotation_0);
		CPPUNIT_TEST(calculateFinalSpeedForGoingStraight_zeroAngle_valueBig);
		CPPUNIT_TEST(calculateFinalSpeedForGoingStraight_eighthRotation_greaterThan0);
		CPPUNIT_TEST(calculateFinalSpeedForGoingStraight_zeroAngleButOnlyShortDistanceLeft_smallerThan05);
		CPPUNIT_TEST(calculateFinalSpeedForGoingStraight_smallAngle_betweenZeroAnd05);
		CPPUNIT_TEST(isMoving_drivingStraightPart_true);
		CPPUNIT_TEST(isMoving_drivingTurningPart_true);
		CPPUNIT_TEST(isMoving_turningTo_true);
		CPPUNIT_TEST(isMoving_waitingAndEngineSaysNotMoving_false);
		CPPUNIT_TEST(isMoving_waitingAndEngineSaysMoving_true);
		CPPUNIT_TEST(isMoving_turnAround_true);
		CPPUNIT_TEST(isMoving_leavingPuck_true);
		CPPUNIT_TEST(isMoving_collectingPuck_true);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void goTo_positionDifferentToCurrentOne_engineGotAtLeastOneCallToGoToStraightOrTurnTo();
		void goTo_orientationToTargetCorrect_engineGotAtLeastOneCallToGoToStraight();
		void goTo_orientationToTargetCompletelyWrong_engineGotNoCallToGoToStraight();
		void goTo_orientationToTargetCompletelyWrong_engineGotAtLeastOneCallToTurnTo();
		void goTo_orientationToTargetCompletelyWrong_isRotating();
		void goTo_orientationToTargetCorrectAndUpdateCalledTwice_notReachedTarget();
		void goTo_orientationReachedAfterSomeTime_notReachedTarget();
		void goTo_lookingDownwardButHaveToGoUpAndOrientationReached_engineGotAtLeastOneCallToGoToStraight();
		void goTo_targetPositionReached_reachedTarget();
		void goTo_firstPointReached_notReachedTarget();
		void goTo_firstPointReached_engineGotOneCallToTurnTo();
		void goTo_firstPointReached_lastArgumentOfTurnToIsTargetPoint();
		void goTo_firstPointAndRotationReached_engineGotOneCallToGoToStraight();
		void goTo_finalPointReached_engineGotOneCallToTurnTo();
		void goTo_finalOrientationReached_engineGotOneCallToStop();
		void goTo_surroundedBySoftObstacles_canReachTarget();
		void goTo_surroundedByHardObstacles_cantReachTarget();
		void goTo_finalOrientationNotPossible_canReachTarget();
		void goTo_twoTargetsAndFirstOnePossible_canReachFirstTarget();
		void goTo_twoTargetsAndOnlySecondOnePossible_canReachSecondTarget();
		void goTo_minuteWaited_cantReachTarget();
		void goTo_obstacleSuddenlyAppearedDuringDriving_engineGotCallToStop();
		void goTo_obstacleSuddenlyAppearedDuringTurning_engineGotCallToStop();
		void goTo_hardObstacleAtStart_engineGotCallToTurnToTarget();
		void goTo_hardObstacleMovedALittleBitIntoTheRoute_engineGotNoAdditionalCalls();
		void goTo_puckCollectedButLostInBetween_newRouteStillConsideringThePuck();
		void goTo_positionInsideHardObstacle_cantReachTarget();
		void goTo_positionInsideSoftObstacle_canReachTarget();
		void goTo_firstPointNearlyReachedAndSmallTurnNecessary_lastSpeedIsBig();
		void goTo_firstPointReachedAndSmallTurnNecessary_noCallsToTurnToTarget();
		void goTo_firstPointReachedAndSmallTurnNecessary_engineGotCorrectNextTarget();
		void goTo_orientationDifferenceZero_engineGotOnlyCallToGoToStraight();
		void goTo_orientationDifferenceSmall_engineGotOnlyCallToGoToStraight();
		void goTo_noUpdateOfActuators_engineGotCallToStop();
		void goTo_finalPointReached_engineGotCallToTurnToFinalOrientation();
		void goTo_hardNotVisibleObstacleAtEnd_canReachTarget();
		void stuckAtObstacle_tryingToTackleObstacle_true();
		void stuckAtObstacle_notTryingToTackleObstacle_false();
		void stuckAtObstacle_updateCalledTwiceAfterStuckAtObstacle_true();
		void stuckAtObstacle_newTargetSet_false();
		void stuckAtObstacle_collectPuckInFrontCalled_false();
		void stuckAtObstacle_turnAroundCalled_false();
		void stuckAtObstacle_leavePuckCalled_false();
		void stuckAtObstacle_turnToCalled_false();
		void reachedTarget_engineSaysNotReached_false();
		void reachedTarget_currentPositionIsTargetPosition_true();
		void updateActuators_empty_layerBelowGotAtLeastOneCallToUpdateActuators();
		void updateSensorData_empty_layerBelowGotAtLeastOneCallToUpdateSensorData();
		void stop_empty_engineGotAtLeastOneCallToStop();
		void stuckAtObstacle_empty_engineGotAtLeastOneCallToTryingToTackleObstacle();
		void turnToTarget_validPoint_engineGotAtLeastOneCallToTurnToTarget();
		void turnToTarget_orientationReached_reachedTarget();
		void turnToTarget_minuteWaited_cantReachTarget();
		void updateActuators_tryingToTackleObstacle_engineGotAtLeastOneCallToStop();
		void updateActuators_tryingToTackleObstacle_targetNotReached();
		void updateActuators_tryingToTackleObstacleFromSonar_lastMessageContainssonar();
		void updateActuators_tryingToTackleObstacleFromLidar_lastMessageContainslidar();
		void updateSensorData_noObstacleDirectInFront_engineGotNoCallToLockForwardMovement();
		void updateSensorData_noObstacleDirectInFront_engineGotAtLeastOneCallToUnlockForwardMovement();
		void updateSensorData_obstacleDirectInFront_engineGotAtLeastOneCallToLockForwardMovement();
		void updateSensorData_0bstacleDirectInFront_engineGotNoCallToUnlockForwardMovement();
		void turnAround_empty_engineGotAtLeastOneCallToTurnAround();
		void turnAround_turnAroundDone_reachedTarget();
		void turnAround_minuteWaited_cantReachTarget();
		void getCurrentPosition_position3And4InOdometry_3And4();
		void reachedTarget_nearlyHitTargetButTookSomeAdditionalWayToStop_false();
		void cantReachTarget_calledDirectAfterConstructor_false();
		void cantReachTarget_drivingTowardsTheTarget_false();
		void cantReachTarget_currentTargetSuddenlyNotPossible_true();
		void cantReachTarget_notPossibleAnymoreDuringDriving_true();
		void cantReachTarget_onlyLastTargetNotPossibleToReach_false();
		void cantReachTarget_updateTwiceCalled_true();
		void cantReachTarget_newTargetSet_false();
		void cantReachTarget_collectPuckInFrontCalled_false();
		void cantReachTarget_turnAroundCalled_false();
		void cantReachTarget_turnToCalled_false();
		void cantReachTarget_leavePuckCalled_false();
		void cantReachTarget_stuckAtObstacle_true();
		void isPuckCollected_lidarSaysNo_false();
		void isPuckCollected_lidarSaysYesVeryShort_false();
		void isPuckCollected_lidarSaysYesLong_true();
		void isPuckCollectable_lidarSaysNo_false();
		void isPuckCollectable_lidarSaysYes_true();
		void collectPuckInFront_puckAhead_notStuckAtObstacle();
		void collectPuckInFront_puckAheadAndStartedToMove_notStuckAtObstacle();
		void collectPuckInFront_puckAheadAndAlreadyUpdatedTheEngine_notStuckAtObstacle();
		void collectPuckInFront_puckCollectedButEngineTargetNotReached_reachedTarget();
		void collectPuckInFront_puckNotYetCollected_notReachedTarget();
		void collectPuckInFront_drivenToFarAndPuckNotYetCollected_notReachedTarget();
		void collectPuckInFront_drivenToFarAndPuckNotYetCollected_cantReachTarget();
		void collectPuckInFront_noPuckAhead_cantReachTarget();
		void collectPuckInFront_puckAhead_canReachTarget();
		void collectPuckInFront_differentPuckAheadThanDesiredOne_cantReachTarget();
		void collectPuckInFront_validPuck_isCollectingPuck();
		void collectPuckInFront_puckCollected_isNotCollectingPuck();
		void collectPuckInFront_lookingLeftAndPuckAhead_canReachTarget();
		void collectPuckInFront_orientationWrongAtBegin_canReachTarget();
		void collectPuckInFront_orientationWrongAtBegin_engineGotCallToTurnTo();
		void collectPuckInFront_orientationWrongAtBeginAndOrientationReached_engineGotCallToGoToStraightSlowly();
		void collectPuckInFront_minuteWaited_cantReachTarget();
		void collectPuckInFront_sonarDetectsCollision_notStuckAtObstacle();
		void updatePuckPosition_newPositionOfPuck_goToStraightSlowlyCalledTwice();
		void leaveCollectedPuck_drivenFarEnoughBack_reachedTarget();
		void leaveCollectedPuck_minuteWaited_cantReachTarget();
		void isRotating_waiting_false();
		void isRotating_turnTo_true();
		void isRotating_turnAround_true();
		void isRotating_firstPhaseOfCollectingPuck_true();
		void isRotating_secondPhaseOfCollectingPuck_false();
		void isRotating_leavingPuck_false();
		void isRotating_turningPartOfGoTo_true();
		void isRotating_drivingPartOfGoToAndTurningFast_true();
		void isRotating_drivingPartOfGoToAndTurningSlow_true();
		void calculateFinalSpeedForGoingStraight_obtuseAngle_0();
		void calculateFinalSpeedForGoingStraight_quarterRotation_0();
		void calculateFinalSpeedForGoingStraight_zeroAngle_valueBig();
		void calculateFinalSpeedForGoingStraight_eighthRotation_greaterThan0();
		void calculateFinalSpeedForGoingStraight_zeroAngleButOnlyShortDistanceLeft_smallerThan05();
		void calculateFinalSpeedForGoingStraight_smallAngle_betweenZeroAnd05();
		void isMoving_drivingStraightPart_true();
		void isMoving_drivingTurningPart_true();
		void isMoving_turningTo_true();
		void isMoving_waitingAndEngineSaysNotMoving_false();
		void isMoving_waitingAndEngineSaysMoving_true();
		void isMoving_turnAround_true();
		void isMoving_leavingPuck_true();
		void isMoving_collectingPuck_true();

	private:
		RouterMock *m_routerMock;
		Common::WatchMock *m_watchMock;
		Common::LoggerMock *m_logger;
		std::list<Common::RobotPosition> m_targets;
		DataAnalysis::DataAnalyserMock *m_dataAnalyser;
		DataAnalysis::OdometryMock *m_odometry;
		DataAnalysis::EngineMock *m_engine;
		DataAnalysis::SonarMock *m_sonar;
		DataAnalysis::LidarMock *m_lidar;
		RobotImpl *m_robot;
		FieldMock *m_field;
	};
}
}
}

#endif
