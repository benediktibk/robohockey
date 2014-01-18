#ifndef ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINETEST_H
#define ROBOHOCKEY_LAYER_DATAANALYSIS_ENGINETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboHockey
{
namespace Common
{
	class WatchMock;
}

namespace Layer
{
namespace Hardware
{
	class EngineMock;
	class OdometryMock;
}

namespace DataAnalysis
{
	class EngineImpl;

	class EngineTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(EngineTest);
		CPPUNIT_TEST(goToStraight_currentPositionDifferentToTarget_atLeastOneCallToSetSpeed);
		CPPUNIT_TEST(goToStraight_lookingRightButHaveToGoLeftUp_lastRotationIsLeft);
		CPPUNIT_TEST(goToStraight_lookingRightButHaveToGoDown_lastRotationIsRight);
		CPPUNIT_TEST(goToStraight_startOrientationCompletelyWrong_lastMagnitudeIsNotZero);
		CPPUNIT_TEST(goToStraight_startOrientationCorrect_lastMagnitudeIsNotZero);
		CPPUNIT_TEST(goToStraight_orientationReachedAfterSomeTime_lastMagnitudeIsNotZero);
		CPPUNIT_TEST(goToStraight_stillMoving_lastSpeedsAreZero);
		CPPUNIT_TEST(goToStraight_movingFinishedFromPreviousMovement_lastSpeedIsNotZero);
		CPPUNIT_TEST(goToStraight_droveToFar_lastRotationAndMagnitudeIsZero);
		CPPUNIT_TEST(goToStraight_atEndAndFinalSpeed02_magnitudeIs02);
		CPPUNIT_TEST(goToStraight_atEndAndOnceAgainCalled_magnitudeIsZero);
		CPPUNIT_TEST(stop_movingSomewhere_lastMagnitudeIsZero);
		CPPUNIT_TEST(stop_movingSomewhere_lastRotationIsZero);
		CPPUNIT_TEST(turnAround_empty_lastMagnitudeIsZero);
		CPPUNIT_TEST(turnAround_empty_lastRotationIsNotZero);
		CPPUNIT_TEST(turnToTarget_differentToStartOrientation_lastMagnitudeIsZero);
		CPPUNIT_TEST(turnToTarget_targetLeft_lastRotationIsGreaterZero);
		CPPUNIT_TEST(turnToTarget_targetRight_lastRotationIsSmallerZero);
		CPPUNIT_TEST(turnToTarget_twiceCalled_hardwareEngineGotNoCallToSlowDown);
		CPPUNIT_TEST(lockForwardMovement_tryingToDriveForward_lastMagnitudeIsZero);
		CPPUNIT_TEST(unlockForwardMovement_tryingToDriveForward_lastMagnitudeIsNotZero);
		CPPUNIT_TEST(unlockForwardMovement_tryingToDriveForward_notTryingToTackleObstacle);
		CPPUNIT_TEST(tryingToTackleObstacle_drivingForwardAndForwardMovementLocked_true);
		CPPUNIT_TEST(tryingToTackleObstacle_drivingForwardAndForwardMovementNotLocked_false);
		CPPUNIT_TEST(tryingToTackleObstacle_turningAroundAndForwardMovementLocked_false);
		CPPUNIT_TEST(tryingToTackleObstacle_turningToTargetAndForwardMovementLocked_false);
		CPPUNIT_TEST(tryingToTackleObstacle_turningToNewTargetAndForwardMovementLocked_true);
		CPPUNIT_TEST(tryingToTackleObstacle_stoppedAndForwardMovementLocked_false);
		CPPUNIT_TEST(turnAround_turnedNotAHalfYet_lastRotationIsGreaterThanZero);
		CPPUNIT_TEST(turnAround_turnedMoreThanAHalft_lastRotationIsGreaterThanZero);
		CPPUNIT_TEST(turnAround_turnedNearlyFull_lastRotationIsGreaterThanZero);
		CPPUNIT_TEST(turnAround_turnedMoreThanOnce_lastRotationIsZero);
		CPPUNIT_TEST(goToStraight_validTargetPosition_startPositionIsCorrect);
		CPPUNIT_TEST(goToStraight_moveAwayFromStartPosition_startPositionIsCorrect);
		CPPUNIT_TEST(goToStraight_rotationDoneAndLittleBitLeftOfDirectConnection_lastRotationIsSmallerThanZero);
		CPPUNIT_TEST(goToStraight_rotationDoneAndLittleBitRightOfDirectConnection_lastRotationIsGreaterThanZero);
		CPPUNIT_TEST(goToStraightSlowly_currentPositionDifferentToTarget_atLeastOneCallToSetSpeed);
		CPPUNIT_TEST(goToStraightSlowly_twiceCalled_hardwareEngineGotNoCallToSlowDown);
		CPPUNIT_TEST(goToStraightSlowlyBack_currentPositionDifferentToTarget_atLeastOneCallToSetSpeed);
		CPPUNIT_TEST(goToStraightSlowlyBack_TargetPassedAfterSomeTime_lastMagnitudeIs0);
		CPPUNIT_TEST(goToStraightSlowlyBack_forwardMovementLocked_lastMagnitudeIsSmallerThanZero);
		CPPUNIT_TEST(goToStraightSlowlyBack_forwardMovementLocked_notTryingToTackleObstacle);
		CPPUNIT_TEST(updateSpeedAndRotation_forwardMovementLockedButNotTryingToTackleObstacle_motorIsEnabled);
		CPPUNIT_TEST(updateSpeedAndRotation_forwardMovementUnlocked_motorIsEnabled);
		CPPUNIT_TEST(updateSpeedAndRotation_forwardMovementLockedAndCalledTwiceAndNotTryingToTackleObstacle_motorIsEnabled);
		CPPUNIT_TEST(updateSpeedAndRotation_forwardMovementUnlockedAndCalledTwice_motorIsEnabled);
		CPPUNIT_TEST(updateSpeedAndRotation_tryingToTackleObstacle_motorIsDisabled);
		CPPUNIT_TEST(getCurrentRotationSpeed_speedSet2_2);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void goToStraight_currentPositionDifferentToTarget_atLeastOneCallToSetSpeed();
		void goToStraight_lookingRightButHaveToGoLeftUp_lastRotationIsLeft();
		void goToStraight_lookingRightButHaveToGoDown_lastRotationIsRight();
		void goToStraight_startOrientationCompletelyWrong_lastMagnitudeIsNotZero();
		void goToStraight_startOrientationCorrect_lastMagnitudeIsNotZero();
		void goToStraight_orientationReachedAfterSomeTime_lastMagnitudeIsNotZero();
		void goToStraight_stillMoving_lastSpeedsAreZero();
		void goToStraight_movingFinishedFromPreviousMovement_lastSpeedIsNotZero();
		void goToStraight_droveToFar_lastRotationAndMagnitudeIsZero();
		void goToStraight_atEndAndFinalSpeed02_magnitudeIs02();
		void goToStraight_atEndAndOnceAgainCalled_magnitudeIsZero();
		void stop_movingSomewhere_lastMagnitudeIsZero();
		void stop_movingSomewhere_lastRotationIsZero();
		void turnAround_empty_lastMagnitudeIsZero();
		void turnAround_empty_lastRotationIsNotZero();
		void turnToTarget_differentToStartOrientation_lastMagnitudeIsZero();
		void turnToTarget_targetLeft_lastRotationIsGreaterZero();
		void turnToTarget_targetRight_lastRotationIsSmallerZero();
		void turnToTarget_twiceCalled_hardwareEngineGotNoCallToSlowDown();
		void lockForwardMovement_tryingToDriveForward_lastMagnitudeIsZero();
		void unlockForwardMovement_tryingToDriveForward_lastMagnitudeIsNotZero();
		void unlockForwardMovement_tryingToDriveForward_notTryingToTackleObstacle();
		void tryingToTackleObstacle_drivingForwardAndForwardMovementLocked_true();
		void tryingToTackleObstacle_drivingForwardAndForwardMovementNotLocked_false();
		void tryingToTackleObstacle_turningAroundAndForwardMovementLocked_false();
		void tryingToTackleObstacle_turningToTargetAndForwardMovementLocked_false();
		void tryingToTackleObstacle_turningToNewTargetAndForwardMovementLocked_true();
		void tryingToTackleObstacle_stoppedAndForwardMovementLocked_false();
		void turnAround_turnedNotAHalfYet_lastRotationIsGreaterThanZero();
		void turnAround_turnedMoreThanAHalft_lastRotationIsGreaterThanZero();
		void turnAround_turnedNearlyFull_lastRotationIsGreaterThanZero();
		void turnAround_turnedMoreThanOnce_lastRotationIsZero();
		void goToStraight_validTargetPosition_startPositionIsCorrect();
		void goToStraight_moveAwayFromStartPosition_startPositionIsCorrect();
		void goToStraight_rotationDoneAndLittleBitLeftOfDirectConnection_lastRotationIsSmallerThanZero();
		void goToStraight_rotationDoneAndLittleBitRightOfDirectConnection_lastRotationIsGreaterThanZero();
		void goToStraightSlowly_currentPositionDifferentToTarget_atLeastOneCallToSetSpeed();
		void goToStraightSlowly_twiceCalled_hardwareEngineGotNoCallToSlowDown();
		void goToStraightSlowlyBack_currentPositionDifferentToTarget_atLeastOneCallToSetSpeed();
		void goToStraightSlowlyBack_TargetPassedAfterSomeTime_lastMagnitudeIs0();
		void goToStraightSlowlyBack_forwardMovementLocked_lastMagnitudeIsSmallerThanZero();
		void goToStraightSlowlyBack_forwardMovementLocked_notTryingToTackleObstacle();
		void updateSpeedAndRotation_forwardMovementLockedButNotTryingToTackleObstacle_motorIsEnabled();
		void updateSpeedAndRotation_forwardMovementUnlocked_motorIsEnabled();
		void updateSpeedAndRotation_forwardMovementLockedAndCalledTwiceAndNotTryingToTackleObstacle_motorIsEnabled();
		void updateSpeedAndRotation_forwardMovementUnlockedAndCalledTwice_motorIsEnabled();
		void updateSpeedAndRotation_tryingToTackleObstacle_motorIsDisabled();
		void getCurrentRotationSpeed_speedSet2_2();

	private:
		Common::WatchMock *m_watch;
		Hardware::EngineMock *m_hardwareEngine;
		Hardware::OdometryMock *m_hardwareOdometry;
		EngineImpl *m_engine;
	};
}
}
}

#endif
