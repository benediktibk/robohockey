#include "layer/dataanalysis/enginetest.h"
#include "layer/dataanalysis/engineimpl.h"
#include "layer/hardware/enginemock.h"
#include "layer/hardware/odometrymock.h"
#include "common/compare.h"
#include <math.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

void EngineTest::goToStraight_currentPositionDifferentToTarget_atLeastOneCallToSetSpeed()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(1, 2), 0));

	engine.goToStraight(Point(4, 20), 0);
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getCallsToSetSpeed() > 0);
}

void EngineTest::goToStraight_lookingRightButHaveToGoLeftUp_lastRotationIsLeft()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(1, 1), 0));

	engine.goToStraight(Point(0, 2), 0);
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastRotation() > 0);
}

void EngineTest::goToStraight_lookingRightButHaveToGoDown_lastRotationIsRight()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(1, 1), 0));

	engine.goToStraight(Point(1, -2), 0);
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getCallsToSetSpeed() > 0);
	CPPUNIT_ASSERT(hardwareEngine.getLastRotation() < 0);
}

void EngineTest::goToStraight_startOrientationCompletelyWrong_lastMagnitudeIsNotZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.goToStraight(Point(-1, 0), 0);
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getCallsToSetSpeed() > 0);
	CPPUNIT_ASSERT(hardwareEngine.getLastMagnitude() > 0);
}

void EngineTest::goToStraight_startOrientationCorrect_lastMagnitudeIsNotZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.goToStraight(Point(1, 0), 0);
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastMagnitude() > 0.01);
}

void EngineTest::goToStraight_orientationReachedAfterSomeTime_lastMagnitudeIsNotZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.goToStraight(Point(-1, 0), 0);
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), M_PI));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastMagnitude() > 0.1);
}

void EngineTest::goToStraight_stillMoving_lastSpeedsAreZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	hardwareEngine.setIsMoving(true);
	engine.updateSensorData();
	engine.goToStraight(Point(1, 0), 0);
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, hardwareEngine.getLastMagnitude(), 0.00001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, hardwareEngine.getLastRotation(), 0.00001);
}

void EngineTest::goToStraight_movingFinishedFromPreviousMovement_lastSpeedIsNotZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	hardwareEngine.setIsMoving(true);
	engine.updateSensorData();
	engine.goToStraight(Point(1, 0), 0);
	engine.updateSpeedAndRotation();
	hardwareEngine.setIsMoving(false);
	engine.updateSensorData();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastMagnitude() > 0.1);
}

void EngineTest::goToStraight_droveToFar_lastRotationAndMagnitudeIsZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	hardwareEngine.setIsMoving(false);
	engine.updateSensorData();
	engine.goToStraight(Point(1, 0), 0.3);
	engine.updateSpeedAndRotation();
	hardwareEngine.setIsMoving(true);
	engine.updateSensorData();
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0.9, 0), 0));
	engine.updateSensorData();
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(2, 0), 0));
	engine.updateSensorData();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, hardwareEngine.getLastMagnitude(), 0.000001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, hardwareEngine.getLastRotation(), 0.000001);
}

void EngineTest::goToStraight_atEndAndFinalSpeed02_magnitudeIs02()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	hardwareEngine.setIsMoving(false);
	engine.updateSensorData();
	engine.goToStraight(Point(1, 0), 0.2);
	engine.updateSpeedAndRotation();
	hardwareEngine.setIsMoving(true);
	engine.updateSensorData();
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(1, 0), 0));
	engine.updateSensorData();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2, hardwareEngine.getLastMagnitude(), 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, hardwareEngine.getLastRotation(), 0.000001);
}

void EngineTest::goToStraight_atEndAndOnceAgainCalled_magnitudeIsZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	hardwareEngine.setIsMoving(false);
	engine.updateSensorData();
	engine.goToStraight(Point(1, 0), 0.2);
	engine.updateSpeedAndRotation();
	hardwareEngine.setIsMoving(true);
	engine.updateSensorData();
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(1, 0), 0));
	engine.updateSensorData();
	engine.updateSpeedAndRotation();
	engine.updateSensorData();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, hardwareEngine.getLastMagnitude(), 0.000001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, hardwareEngine.getLastRotation(), 0.000001);
}

void EngineTest::stop_movingSomewhere_lastMagnitudeIsZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	engine.goToStraight(Point(1, 0), 0);
	engine.updateSpeedAndRotation();

	engine.stop();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastMagnitude() == 0);
}

void EngineTest::stop_movingSomewhere_lastRotationIsZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	engine.goToStraight(Point(-1, 0), 0);
	engine.updateSpeedAndRotation();

	engine.stop();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastRotation() == 0);
}

void EngineTest::turnAround_empty_lastMagnitudeIsZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.turnAround();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastMagnitude() == 0);
}

void EngineTest::turnAround_empty_lastRotationIsNotZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.turnAround();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(fabs(hardwareEngine.getLastRotation()) > 0.1);
}

void EngineTest::turnToTarget_differentToStartOrientation_lastMagnitudeIsZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.turnToTarget(Point(0, 1));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastMagnitude() == 0);
}

void EngineTest::turnToTarget_targetLeft_lastRotationIsGreaterZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.turnToTarget(Point(0, 1));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastRotation() > 0.1);
}

void EngineTest::turnToTarget_targetRight_lastRotationIsSmallerZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.turnToTarget(Point(0, -1));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastRotation() < -0.1);
}

void EngineTest::turnToTarget_twiceCalled_hardwareEngineGotNoCallToSlowDown()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	hardwareEngine.setIsMoving(false);
	engine.updateSensorData();
	engine.turnToTarget(Point(0, -1));
	engine.updateSpeedAndRotation();
	hardwareEngine.setIsMoving(true);
	engine.updateSensorData();
	engine.turnToTarget(Point(0, 1));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastRotation() != 0);
}

void EngineTest::lockForwardMovement_tryingToDriveForward_lastMagnitudeIsZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	engine.goToStraight(Point(10, 0), 0);
	engine.updateSpeedAndRotation();

	engine.lockForwardMovement();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastMagnitude() == 0);
}

void EngineTest::unlockForwardMovement_tryingToDriveForward_lastMagnitudeIsNotZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	engine.lockForwardMovement();
	engine.goToStraight(Point(10, 0), 0);
	engine.updateSpeedAndRotation();

	engine.unlockForwardMovement();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastMagnitude() > 0.01);
}

void EngineTest::unlockForwardMovement_tryingToDriveForward_notTryingToTackleObstacle()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	engine.lockForwardMovement();
	engine.goToStraight(Point(10, 0), 0);
	engine.updateSpeedAndRotation();

	engine.unlockForwardMovement();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(!engine.tryingToTackleObstacle());
}

void EngineTest::tryingToTackleObstacle_drivingForwardAndForwardMovementLocked_true()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.lockForwardMovement();
	engine.goToStraight(Point(10, 0), 0);
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(engine.tryingToTackleObstacle());
}

void EngineTest::tryingToTackleObstacle_drivingForwardAndForwardMovementNotLocked_false()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.goToStraight(Point(10, 0), 0);
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(!engine.tryingToTackleObstacle());
}

void EngineTest::tryingToTackleObstacle_turningAroundAndForwardMovementLocked_false()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	engine.lockForwardMovement();
	engine.goToStraight(Point(10, 0), 0);
	engine.updateSpeedAndRotation();

	engine.turnAround();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(!engine.tryingToTackleObstacle());
}

void EngineTest::tryingToTackleObstacle_turningToTargetAndForwardMovementLocked_false()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	engine.lockForwardMovement();
	engine.goToStraight(Point(10, 0), 0);
	engine.updateSpeedAndRotation();

	engine.turnToTarget(Point(0, 1));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(!engine.tryingToTackleObstacle());
}

void EngineTest::tryingToTackleObstacle_turningToNewTargetAndForwardMovementLocked_true()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	engine.lockForwardMovement();
	engine.goToStraight(Point(10, 0), 0);
	engine.updateSpeedAndRotation();

	engine.goToStraight(Point(-1, 0), 0);
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(engine.tryingToTackleObstacle());
}

void EngineTest::tryingToTackleObstacle_stoppedAndForwardMovementLocked_false()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	engine.lockForwardMovement();
	engine.goToStraight(Point(10, 0), 0);
	engine.updateSpeedAndRotation();

	engine.stop();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(!engine.tryingToTackleObstacle());
}

void EngineTest::turnAround_turnedNotAHalfYet_lastRotationIsGreaterThanZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.turnAround();
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0.1));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastRotation() > 0.1);
}

void EngineTest::turnAround_turnedMoreThanAHalft_lastRotationIsGreaterThanZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.turnAround();
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0.1));
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 3.5));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastRotation() > 0.1);
}

void EngineTest::turnAround_turnedNearlyFull_lastRotationIsGreaterThanZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.turnAround();
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0.1));
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 3.5));
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 1.9*M_PI));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastRotation() > 0.01);
}

void EngineTest::turnAround_turnedMoreThanOnce_lastRotationIsZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.turnAround();
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0.1));
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 3.5));
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 1.9*M_PI));
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0.1));
	engine.updateSpeedAndRotation();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastRotation() == 0);
}

void EngineTest::goToStraight_validTargetPosition_startPositionIsCorrect()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(3, 5), 0));

	engine.goToStraight(Point(6, 7), 0);

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(3, 5), engine.getStartPosition()));
}

void EngineTest::goToStraight_moveAwayFromStartPosition_startPositionIsCorrect()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(3, 5), 0));

	engine.goToStraight(Point(6, 7), 0);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(4, 5), 0));
	engine.updateSpeedAndRotation();

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(3, 5), engine.getStartPosition()));
}

void EngineTest::goToStraight_rotationDoneAndLittleBitLeftOfDirectConnection_lastRotationIsSmallerThanZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.goToStraight(Point(5, 5), 0);
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()/2));
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(1, 1.1), Angle::getQuarterRotation()/2));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastMagnitude() > 0);
	CPPUNIT_ASSERT(hardwareEngine.getLastRotation() < 0);
}

void EngineTest::goToStraight_rotationDoneAndLittleBitRightOfDirectConnection_lastRotationIsGreaterThanZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.goToStraight(Point(5, 5), 0);
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()/2));
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(1.1, 1), Angle::getQuarterRotation()/2));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastMagnitude() > 0);
	CPPUNIT_ASSERT(hardwareEngine.getLastRotation() > 0);
}

void EngineTest::goToStraightSlowly_currentPositionDifferentToTarget_atLeastOneCallToSetSpeed()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(1, 2), 0));

	engine.goToStraightSlowly(Point(4, 20));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getCallsToSetSpeed() > 0);
}

void EngineTest::goToStraightSlowly_twiceCalled_hardwareEngineGotNoCallToSlowDown()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));

	hardwareEngine.setIsMoving(false);
	engine.updateSensorData();
	engine.goToStraightSlowly(Point(1, 0));
	engine.updateSpeedAndRotation();
	hardwareEngine.setIsMoving(true);
	engine.updateSensorData();
	engine.goToStraightSlowly(Point(2, 0));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastMagnitude() > 0);
}

void EngineTest::goToStraightSlowlyBack_currentPositionDifferentToTarget_atLeastOneCallToSetSpeed()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(1, 2), 0));

	engine.goToStraightSlowlyBack(Point(0, 2));
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getCallsToSetSpeed() > 0);
}

void EngineTest::goToStraightSlowlyBack_TargetPassedAfterSomeTime_lastMagnitudeIs0()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.goToStraightSlowlyBack(Point(-1, 0));
	engine.updateSpeedAndRotation();
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(-1.05, 0), 0));
	engine.updateSpeedAndRotation();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT_EQUAL(0.0, hardwareEngine.getLastMagnitude());
}

void EngineTest::goToStraightSlowlyBack_forwardMovementLocked_lastMagnitudeIsSmallerThanZero()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.goToStraightSlowlyBack(Point(-1, 0));
	engine.lockForwardMovement();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(hardwareEngine.getLastMagnitude() < 0);
}

void EngineTest::goToStraightSlowlyBack_forwardMovementLocked_notTryingToTackleObstacle()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.goToStraightSlowlyBack(Point(-1, 0));
	engine.lockForwardMovement();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT(!engine.tryingToTackleObstacle());
}

void EngineTest::updateSpeedAndRotation_forwardMovementLockedButNotTryingToTackleObstacle_motorIsEnabled()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.updateSensorData();
	engine.lockForwardMovement();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, hardwareEngine.getCallsToSetEnabled());
	CPPUNIT_ASSERT(hardwareEngine.getEnabled());
}

void EngineTest::updateSpeedAndRotation_forwardMovementUnlocked_motorIsEnabled()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.updateSensorData();
	engine.unlockForwardMovement();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, hardwareEngine.getCallsToSetEnabled());
	CPPUNIT_ASSERT(hardwareEngine.getEnabled());
}

void EngineTest::updateSpeedAndRotation_forwardMovementLockedAndCalledTwiceAndNotTryingToTackleObstacle_motorIsEnabled()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.updateSensorData();
	engine.lockForwardMovement();
	engine.updateSpeedAndRotation();
	engine.updateSensorData();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, hardwareEngine.getCallsToSetEnabled());
	CPPUNIT_ASSERT(hardwareEngine.getEnabled());
}

void EngineTest::updateSpeedAndRotation_forwardMovementUnlockedAndCalledTwice_motorIsEnabled()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.updateSensorData();
	engine.unlockForwardMovement();
	engine.updateSpeedAndRotation();
	engine.updateSensorData();
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, hardwareEngine.getCallsToSetEnabled());
	CPPUNIT_ASSERT(hardwareEngine.getEnabled());
}

void EngineTest::updateSpeedAndRotation_tryingToTackleObstacle_motorIsDisabled()
{
	Hardware::EngineMock hardwareEngine;
	Hardware::OdometryMock hardwareOdometry;
	EngineImpl engine(hardwareEngine, hardwareOdometry);
	hardwareOdometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));

	engine.updateSensorData();
	engine.lockForwardMovement();
	engine.goToStraight(Point(1, 0), 0);
	engine.updateSpeedAndRotation();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, hardwareEngine.getCallsToSetEnabled());
	CPPUNIT_ASSERT(!hardwareEngine.getEnabled());
}
