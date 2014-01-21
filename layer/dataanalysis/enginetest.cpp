#include "layer/dataanalysis/enginetest.h"
#include "layer/dataanalysis/engineimpl.h"
#include "layer/hardware/enginemock.h"
#include "layer/hardware/odometrymock.h"
#include "common/compare.h"
#include "common/watchmock.h"
#include "common/loggermock.h"
#include <math.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

void EngineTest::setUp()
{
	m_watch = new WatchMock();
	m_logger = new LoggerMock();
	m_hardwareEngine = new Hardware::EngineMock();
	m_hardwareOdometry = new Hardware::OdometryMock();
	m_engine = new EngineImpl(*m_hardwareEngine, *m_hardwareOdometry, *m_watch, *m_logger);
}

void EngineTest::tearDown()
{
	delete m_engine;
	m_engine = 0;
	delete m_hardwareEngine;
	m_hardwareEngine = 0;
	delete m_hardwareOdometry;
	m_hardwareOdometry = 0;
	delete m_watch;
	m_watch = 0;
	delete m_logger;
	m_logger = 0;
}

void EngineTest::goToStraight_currentPositionDifferentToTarget_atLeastOneCallToSetSpeed()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(1, 2), 0));

	m_engine->goToStraight(Point(4, 20));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getCallsToSetSpeed() > 0);
}

void EngineTest::goToStraight_lookingRightButHaveToGoLeftUp_lastRotationIsLeft()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(1, 1), 0));

	m_engine->goToStraight(Point(0, 2));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getLastRotation() > 0);
}

void EngineTest::goToStraight_lookingRightButHaveToGoDown_lastRotationIsRight()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(1, 1), 0));

	m_engine->goToStraight(Point(1, -2));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getCallsToSetSpeed() > 0);
	CPPUNIT_ASSERT(m_hardwareEngine->getLastRotation() < 0);
}

void EngineTest::goToStraight_startOrientationCompletelyWrong_lastMagnitudeIsNotZero()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->goToStraight(Point(-1, 0));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getCallsToSetSpeed() > 0);
	CPPUNIT_ASSERT(m_hardwareEngine->getLastMagnitude() > 0);
}

void EngineTest::goToStraight_startOrientationCorrect_lastMagnitudeIsNotZero()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->goToStraight(Point(1, 0));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getLastMagnitude() > 0.01);
}

void EngineTest::goToStraight_orientationReachedAfterSomeTime_lastMagnitudeIsNotZero()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->goToStraight(Point(-1, 0));
	m_engine->updateSpeedAndRotation();
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), M_PI));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getLastMagnitude() > 0.1);
}

void EngineTest::goToStraight_stillMoving_lastSpeedsAreZero()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_hardwareEngine->setIsMoving(true);
	m_engine->updateSensorData();
	m_engine->goToStraight(Point(1, 0));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, m_hardwareEngine->getLastMagnitude(), 0.00001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, m_hardwareEngine->getLastRotation(), 0.00001);
}

void EngineTest::goToStraight_movingFinishedFromPreviousMovement_lastSpeedIsNotZero()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_hardwareEngine->setIsMoving(true);
	m_engine->updateSensorData();
	m_engine->goToStraight(Point(1, 0));
	m_engine->updateSpeedAndRotation();
	m_hardwareEngine->setIsMoving(false);
	m_engine->updateSensorData();
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getLastMagnitude() > 0.1);
}

void EngineTest::goToStraight_droveToFar_lastRotationAndMagnitudeIsZero()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_hardwareEngine->setIsMoving(false);
	m_engine->updateSensorData();
	m_engine->goToStraight(Point(1, 0));
	m_engine->updateSpeedAndRotation();
	m_hardwareEngine->setIsMoving(true);
	m_engine->updateSensorData();
	m_engine->updateSpeedAndRotation();
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0.9, 0), 0));
	m_engine->updateSensorData();
	m_engine->updateSpeedAndRotation();
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(2, 0), 0));
	m_engine->updateSensorData();
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, m_hardwareEngine->getLastMagnitude(), 0.000001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, m_hardwareEngine->getLastRotation(), 0.000001);
}

void EngineTest::goToStraight_atEndAndFinalSpeed02_magnitudeIs02()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_hardwareEngine->setIsMoving(false);
	m_engine->updateSensorData();
	m_engine->goToStraight(Point(1, 0));
	m_engine->updateSpeedAndRotation();
	m_hardwareEngine->setIsMoving(true);
	m_engine->updateSensorData();
	m_engine->updateSpeedAndRotation();
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(1, 0), 0));
	m_engine->updateSensorData();
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, m_hardwareEngine->getLastMagnitude(), 0.001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, m_hardwareEngine->getLastRotation(), 0.000001);
}

void EngineTest::goToStraight_atEndAndOnceAgainCalled_magnitudeIsZero()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_hardwareEngine->setIsMoving(false);
	m_engine->updateSensorData();
	m_engine->goToStraight(Point(1, 0));
	m_engine->updateSpeedAndRotation();
	m_hardwareEngine->setIsMoving(true);
	m_engine->updateSensorData();
	m_engine->updateSpeedAndRotation();
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(1, 0), 0));
	m_engine->updateSensorData();
	m_engine->updateSpeedAndRotation();
	m_engine->updateSensorData();
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, m_hardwareEngine->getLastMagnitude(), 0.000001);
	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, m_hardwareEngine->getLastRotation(), 0.000001);
}

void EngineTest::stop_movingSomewhere_lastMagnitudeIsZero()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_engine->goToStraight(Point(1, 0));
	m_engine->updateSpeedAndRotation();

	m_engine->stop();
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getLastMagnitude() == 0);
}

void EngineTest::stop_movingSomewhere_lastRotationIsZero()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_engine->goToStraight(Point(-1, 0));
	m_engine->updateSpeedAndRotation();

	m_engine->stop();
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getLastRotation() == 0);
}

void EngineTest::turnToTarget_differentToStartOrientation_lastMagnitudeIsZero()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->turnToTarget(Point(0, 1));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getLastMagnitude() == 0);
}

void EngineTest::turnToTarget_targetLeft_lastRotationIsGreaterZero()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->turnToTarget(Point(0, 1));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getLastRotation() > 0.1);
}

void EngineTest::turnToTarget_targetRight_lastRotationIsSmallerZero()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->turnToTarget(Point(0, -1));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getLastRotation() < -0.1);
}

void EngineTest::turnToTarget_twiceCalled_hardwareEngineGotNoCallToSlowDown()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_hardwareEngine->setIsMoving(false);
	m_engine->updateSensorData();
	m_engine->turnToTarget(Point(0, -1));
	m_engine->updateSpeedAndRotation();
	m_hardwareEngine->setIsMoving(true);
	m_engine->updateSensorData();
	m_engine->turnToTarget(Point(0, 1));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getLastRotation() != 0);
}

void EngineTest::lockForwardMovement_tryingToDriveForward_lastMagnitudeIsZero()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_engine->goToStraight(Point(10, 0));
	m_engine->updateSpeedAndRotation();

	m_engine->lockForwardMovement();
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getLastMagnitude() == 0);
}

void EngineTest::unlockForwardMovement_tryingToDriveForward_lastMagnitudeIsNotZero()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_engine->lockForwardMovement();
	m_engine->goToStraight(Point(10, 0));
	m_engine->updateSpeedAndRotation();

	m_engine->unlockForwardMovement();
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getLastMagnitude() > 0.01);
}

void EngineTest::unlockForwardMovement_tryingToDriveForward_notTryingToTackleObstacle()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_engine->lockForwardMovement();
	m_engine->goToStraight(Point(10, 0));
	m_engine->updateSpeedAndRotation();

	m_engine->unlockForwardMovement();
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(!m_engine->tryingToTackleObstacle());
}

void EngineTest::tryingToTackleObstacle_drivingForwardAndForwardMovementLocked_true()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->lockForwardMovement();
	m_engine->goToStraight(Point(10, 0));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_engine->tryingToTackleObstacle());
}

void EngineTest::tryingToTackleObstacle_drivingForwardAndForwardMovementNotLocked_false()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->goToStraight(Point(10, 0));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(!m_engine->tryingToTackleObstacle());
}

void EngineTest::tryingToTackleObstacle_turningToTargetAndForwardMovementLocked_false()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_engine->lockForwardMovement();
	m_engine->goToStraight(Point(10, 0));
	m_engine->updateSpeedAndRotation();

	m_engine->turnToTarget(Point(0, 1));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(!m_engine->tryingToTackleObstacle());
}

void EngineTest::tryingToTackleObstacle_turningToNewTargetAndForwardMovementLocked_true()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_engine->lockForwardMovement();
	m_engine->goToStraight(Point(10, 0));
	m_engine->updateSpeedAndRotation();

	m_engine->goToStraight(Point(-1, 0));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_engine->tryingToTackleObstacle());
}

void EngineTest::tryingToTackleObstacle_stoppedAndForwardMovementLocked_false()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_engine->lockForwardMovement();
	m_engine->goToStraight(Point(10, 0));
	m_engine->updateSpeedAndRotation();

	m_engine->stop();
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(!m_engine->tryingToTackleObstacle());
}

void EngineTest::goToStraight_validTargetPosition_startPositionIsCorrect()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(3, 5), 0));

	m_engine->goToStraight(Point(6, 7));

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(3, 5), m_engine->getStartPosition()));
}

void EngineTest::goToStraight_moveAwayFromStartPosition_startPositionIsCorrect()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(3, 5), 0));

	m_engine->goToStraight(Point(6, 7));
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(4, 5), 0));
	m_engine->updateSpeedAndRotation();

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(3, 5), m_engine->getStartPosition()));
}

void EngineTest::goToStraight_rotationDoneAndLittleBitLeftOfDirectConnection_lastRotationIsSmallerThanZero()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->goToStraight(Point(5, 5));
	m_engine->updateSpeedAndRotation();
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_engine->updateSpeedAndRotation();
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()/2));
	m_engine->updateSpeedAndRotation();
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(1, 1.1), Angle::getQuarterRotation()/2));
	m_engine->updateSpeedAndRotation();

	double magnitude = m_hardwareEngine->getLastMagnitude();
	CPPUNIT_ASSERT(magnitude >= 0);
	double rotation = m_hardwareEngine->getLastRotation();
	CPPUNIT_ASSERT(rotation < 0);
}

void EngineTest::goToStraight_rotationDoneAndLittleBitRightOfDirectConnection_lastRotationIsGreaterThanZero()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->goToStraight(Point(5, 5));
	m_engine->updateSpeedAndRotation();
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_engine->updateSpeedAndRotation();
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()/2));
	m_engine->updateSpeedAndRotation();
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(1.1, 1), Angle::getQuarterRotation()/2));
	m_engine->updateSpeedAndRotation();

	double magnitude = m_hardwareEngine->getLastMagnitude();
	CPPUNIT_ASSERT(magnitude >= 0);
	double rotation = m_hardwareEngine->getLastRotation();
	CPPUNIT_ASSERT(rotation > 0);
}

void EngineTest::goToStraightSlowly_currentPositionDifferentToTarget_atLeastOneCallToSetSpeed()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(1, 2), 0));

	m_engine->goToStraightSlowly(Point(4, 20));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getCallsToSetSpeed() > 0);
}

void EngineTest::goToStraightSlowly_twiceCalled_hardwareEngineGotNoCallToSlowDown()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));

	m_hardwareEngine->setIsMoving(false);
	m_engine->updateSensorData();
	m_engine->goToStraightSlowly(Point(1, 0));
	m_engine->updateSpeedAndRotation();
	m_hardwareEngine->setIsMoving(true);
	m_engine->updateSensorData();
	m_engine->goToStraightSlowly(Point(2, 0));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getLastMagnitude() > 0);
}

void EngineTest::goToStraightSlowlyBack_currentPositionDifferentToTarget_atLeastOneCallToSetSpeed()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(1, 2), 0));

	m_engine->goToStraightSlowlyBack(Point(0, 2));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getCallsToSetSpeed() > 0);
}

void EngineTest::goToStraightSlowlyBack_TargetPassedAfterSomeTime_lastMagnitudeIs0()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->goToStraightSlowlyBack(Point(-1, 0));
	m_engine->updateSpeedAndRotation();
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(-1.05, 0), 0));
	m_engine->updateSpeedAndRotation();
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT_EQUAL(0.0, m_hardwareEngine->getLastMagnitude());
}

void EngineTest::goToStraightSlowlyBack_forwardMovementLocked_lastMagnitudeIsSmallerThanZero()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->goToStraightSlowlyBack(Point(-1, 0));
	m_engine->lockForwardMovement();
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(m_hardwareEngine->getLastMagnitude() < 0);
}

void EngineTest::goToStraightSlowlyBack_forwardMovementLocked_notTryingToTackleObstacle()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->goToStraightSlowlyBack(Point(-1, 0));
	m_engine->lockForwardMovement();
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT(!m_engine->tryingToTackleObstacle());
}

void EngineTest::updateSpeedAndRotation_forwardMovementLockedButNotTryingToTackleObstacle_motorIsEnabled()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->updateSensorData();
	m_engine->lockForwardMovement();
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareEngine->getCallsToSetEnabled());
	CPPUNIT_ASSERT(m_hardwareEngine->getEnabled());
}

void EngineTest::updateSpeedAndRotation_forwardMovementUnlocked_motorIsEnabled()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->updateSensorData();
	m_engine->unlockForwardMovement();
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareEngine->getCallsToSetEnabled());
	CPPUNIT_ASSERT(m_hardwareEngine->getEnabled());
}

void EngineTest::updateSpeedAndRotation_forwardMovementLockedAndCalledTwiceAndNotTryingToTackleObstacle_motorIsEnabled()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->updateSensorData();
	m_engine->lockForwardMovement();
	m_engine->updateSpeedAndRotation();
	m_engine->updateSensorData();
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_hardwareEngine->getCallsToSetEnabled());
	CPPUNIT_ASSERT(m_hardwareEngine->getEnabled());
}

void EngineTest::updateSpeedAndRotation_forwardMovementUnlockedAndCalledTwice_motorIsEnabled()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->updateSensorData();
	m_engine->unlockForwardMovement();
	m_engine->updateSpeedAndRotation();
	m_engine->updateSensorData();
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_hardwareEngine->getCallsToSetEnabled());
	CPPUNIT_ASSERT(m_hardwareEngine->getEnabled());
}

void EngineTest::updateSpeedAndRotation_tryingToTackleObstacle_motorIsDisabled()
{
	m_hardwareOdometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->updateSensorData();
	m_engine->lockForwardMovement();
	m_engine->goToStraight(Point(1, 0));
	m_engine->updateSpeedAndRotation();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareEngine->getCallsToSetEnabled());
	CPPUNIT_ASSERT(!m_hardwareEngine->getEnabled());
}

void EngineTest::getCurrentRotationSpeed_speedSet2_2()
{
	m_hardwareEngine->setRotationSpeed(2);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, m_engine->getCurrentRotationSpeed(), 0.0001);
}
