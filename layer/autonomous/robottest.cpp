#include "layer/autonomous/robottest.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/dataanalysis/dataanalysermock.h"
#include "common/compare.h"
#include "common/robotposition.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::Autonomous;

void RobotTest::goTo_positionDifferentToCurrentOne_engineGotAtLeastOneCallToGoToStraight()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(2, 3), 1));
	RobotImpl robot(dataAnalyser);

	robot.goTo(Point(5, 4));

	CPPUNIT_ASSERT(engine.getCallsToGoToStraight() > 0);
}

void RobotTest::stuckAtObstacle_tryingToTackleObstacle_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(true);
	RobotImpl robot(dataAnalyser);

	CPPUNIT_ASSERT(robot.stuckAtObstacle());
}

void RobotTest::stuckAtObstacle_notTryingToTackleObstacle_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(false);
	RobotImpl robot(dataAnalyser);

	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}

void RobotTest::reachedTarget_engineSaysNotReached_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser);
	engine.setReachedTarget(false);

	CPPUNIT_ASSERT(!robot.reachedTarget());
}

void RobotTest::reachedTarget_currentPositionIsTargetPosition_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser);
	engine.setReachedTarget(true);

	CPPUNIT_ASSERT(robot.reachedTarget());
}

void RobotTest::updateActuators_empty_layerBelowGotAtLeastOneCallToUpdateActuators()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser);

	robot.updateActuators();

	CPPUNIT_ASSERT(dataAnalyser->getCallsToUpdateActuators() > 0);
}

void RobotTest::updateSensorData_empty_layerBelowGotAtLeastOneCallToUpdateSensorData()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser);

	robot.updateSensorData();

	CPPUNIT_ASSERT(dataAnalyser->getCallsToUpdateSensorData() > 0);
}

void RobotTest::stop_empty_engineGotAtLeastOneCallToStop()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser);

	robot.stop();

	CPPUNIT_ASSERT(engine.getCallsToStop() > 0);
}

void RobotTest::stuckAtObstacle_empty_engineGotAtLeastOneCallToTryingToTackleObstacle()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser);

	robot.stuckAtObstacle();

	CPPUNIT_ASSERT(engine.getCallsToTryingToTackleObstacle() > 0);
}

void RobotTest::turnToTarget_validPoint_engineGotAtLeastOneCallToTurnToTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	RobotImpl robot(dataAnalyser);

	robot.turnTo(Point(0, 1));

	CPPUNIT_ASSERT(engine.getCallsToTurnToTarget() > 0);
}

void RobotTest::updateActuators_notTryingToTackleObstacle_engineGotNoCallToStop()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(false);
	RobotImpl robot(dataAnalyser);
	robot.goTo(Point(10, 0));

	robot.updateActuators();

	CPPUNIT_ASSERT(engine.getCallsToStop() == 0);
}

void RobotTest::updateActuators_tryingToTackleObstacle_engineGotAtLeastOneCallToStop()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(true);
	RobotImpl robot(dataAnalyser);
	robot.goTo(Point(10, 0));

	robot.updateActuators();

	CPPUNIT_ASSERT(engine.getCallsToStop() > 0);
}

void RobotTest::updateActuators_tryingToTackleObstacle_targetReached()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(true);
	RobotImpl robot(dataAnalyser);
	robot.goTo(Point(10, 0));

	robot.updateActuators();

	CPPUNIT_ASSERT(robot.reachedTarget());
}

void RobotTest::updateSensorData_noObstacleDirectInFront_engineGotNoCallToLockForwardMovement()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	DataAnalysis::SonarMock &sonar = dataAnalyser->getSonarMock();
	RobotImpl robot(dataAnalyser);
	sonar.setIsObstacleDirectInFront(false);

	robot.updateSensorData();

	CPPUNIT_ASSERT(engine.getCallsToLockForwardMovement() == 0);
}

void RobotTest::updateSensorData_noObstacleDirectInFront_engineGotAtLeastOneCallToUnlockForwardMovement()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	DataAnalysis::SonarMock &sonar = dataAnalyser->getSonarMock();
	RobotImpl robot(dataAnalyser);
	sonar.setIsObstacleDirectInFront(false);

	robot.updateSensorData();

	CPPUNIT_ASSERT(engine.getCallsToUnlockForwardMovement() > 0);
}

void RobotTest::updateSensorData_obstacleDirectInFront_engineGotAtLeastOneCallToLockForwardMovement()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	DataAnalysis::SonarMock &sonar = dataAnalyser->getSonarMock();
	RobotImpl robot(dataAnalyser);
	sonar.setIsObstacleDirectInFront(true);

	robot.updateSensorData();

	CPPUNIT_ASSERT(engine.getCallsToLockForwardMovement() > 0);
}

void RobotTest::updateSensorData_0bstacleDirectInFront_engineGotNoCallToUnlockForwardMovement()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	DataAnalysis::SonarMock &sonar = dataAnalyser->getSonarMock();
	RobotImpl robot(dataAnalyser);
	sonar.setIsObstacleDirectInFront(true);

	robot.updateSensorData();

	CPPUNIT_ASSERT(engine.getCallsToUnlockForwardMovement() == 0);
}

void RobotTest::turnAround_empty_engineGotAtLeastOneCallToTurnAround()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser);

	robot.turnAround();

	CPPUNIT_ASSERT(engine.getCallsToTurnAround() > 0);
}

void RobotTest::getCurrentPosition_position3And4InOdometry_3And4()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	RobotImpl robot(dataAnalyser);
	odometry.setCurrentPosition(RobotPosition(Point(3, 4), 2));

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(RobotPosition(Point(3, 4), 2), robot.getCurrentPosition()));
}

void RobotTest::reachedTarget_nearlyHitTargetButTookSomeAdditionalWayToStop_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	DataAnalysis::SonarMock &sonar = dataAnalyser->getSonarMock();
	RobotImpl robot(dataAnalyser);

	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	robot.goTo(Point(10, 0));
	sonar.setIsObstacleDirectInFront(false);
	robot.updateSensorData();
	robot.updateActuators();
	odometry.setCurrentPosition(RobotPosition(Point(5, 0), 0));
	sonar.setIsObstacleDirectInFront(true);
	robot.updateSensorData();
	robot.updateActuators();
	engine.setTryingToTackleObstacle(true);
	robot.updateSensorData();
	robot.updateActuators();
	engine.setTryingToTackleObstacle(false);
	odometry.setCurrentPosition(RobotPosition(Point(5.2, 0), 0));
	robot.updateSensorData();
	robot.updateActuators();

	CPPUNIT_ASSERT(robot.reachedTarget());
}
