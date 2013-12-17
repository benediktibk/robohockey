#include "layer/autonomous/robottest.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/autonomous/routermock.h"
#include "layer/dataanalysis/dataanalysermock.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/hardware/robotmock.h"
#include "common/compare.h"
#include "common/robotposition.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::Autonomous;

void RobotTest::setUp()
{
	m_routerMock = new RouterMock();
}

void RobotTest::tearDown()
{
	m_routerMock = 0;
}

void RobotTest::goTo_positionDifferentToCurrentOne_engineGotAtLeastOneCallToGoToStraightOrTurnTo()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(2, 3), 1));
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(5, 4), 0));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToGoToStraight() > 0 || engine.getCallsToTurnToTarget() > 0);
}

void RobotTest::goTo_orientationToTargetCorrect_engineGotAtLeastOneCallToGoToStraight()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	engine.setReachedTarget(false);
	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(1, 0), 0));
	robot.updateActuators(field);
	engine.setReachedTarget(true);
	robot.updateSensorData();
	robot.updateActuators(field);
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToGoToStraight() > 0);
}

void RobotTest::goTo_orientationToTargetCorrect_isNotRotating()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	engine.setReachedTarget(true);
	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(1, 0), 0));
	robot.updateActuators(field);
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.isRotating());
}

void RobotTest::goTo_orientationToTargetCompletelyWrong_engineGotNoCallToGoToStraight()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(-1, 0), Angle::getHalfRotation()));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToGoToStraight() == 0);
}

void RobotTest::goTo_orientationToTargetCompletelyWrong_engineGotAtLeastOneCallToTurnTo()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(-1, 0), Angle::getHalfRotation()));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToTurnToTarget() > 0);
}

void RobotTest::goTo_orientationToTargetCompletelyWrong_isRotating()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(-1, 0), Angle::getHalfRotation()));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.isRotating());
}

void RobotTest::goTo_orientationToTargetCorrectAndUpdateCalledTwice_notReachedTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(1, 0), Angle::getQuarterRotation()));
	robot.updateActuators(field);
	robot.updateSensorData();
	engine.setReachedTarget(false);
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.reachedTarget());
}

void RobotTest::goTo_orientationReachedAfterSomeTime_notReachedTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	engine.setReachedTarget(false);
	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(-1, 0), Angle::getHalfRotation()));
	robot.updateActuators(field);
	robot.updateSensorData();
	robot.updateActuators(field);
	engine.setReachedTarget(true);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.reachedTarget());
}

void RobotTest::goTo_lookingDownwardButHaveToGoUpAndOrientationReached_engineGotAtLeastOneCallToGoToStraight()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getThreeQuarterRotation()));
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	engine.setReachedTarget(false);
	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(0, 1), Angle::getQuarterRotation()));
	robot.updateActuators(field);
	robot.updateSensorData();
	robot.updateActuators(field);
	engine.setReachedTarget(true);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	robot.updateSensorData();
	robot.updateActuators(field);
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToGoToStraight() > 0);
}

void RobotTest::goTo_targetPositionReached_reachedTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getThreeQuarterRotation()));
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	engine.setReachedTarget(false);
	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(0, 1), Angle::getQuarterRotation()));
	robot.updateActuators(field);
	robot.updateSensorData();
	robot.updateActuators(field);
	engine.setReachedTarget(true);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	robot.updateSensorData();
	robot.updateActuators(field);
	odometry.setCurrentPosition(RobotPosition(Point(0, 1), Angle::getQuarterRotation()));
	engine.setReachedTarget(true);
	engine.setIsGoingStraight(false);
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.reachedTarget());
}

void RobotTest::goTo_firstPointReached_notReachedTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	m_routerMock->setChessMode(true);
	engine.setReachedTarget(false);
	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(1, 1), Angle::getEighthRotation()));
	robot.updateActuators(field);
	engine.setReachedTarget(true);
	engine.setIsGoingStraight(false);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	robot.updateSensorData();
	robot.updateActuators(field);
	odometry.setCurrentPosition(RobotPosition(Point(0, 1), Angle::getQuarterRotation()));
	engine.setReachedTarget(true);
	engine.setIsGoingStraight(false);
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.reachedTarget());
}

void RobotTest::goTo_firstPointReached_engineGotOneCallToTurnTo()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	m_routerMock->setChessMode(true);
	engine.setReachedTarget(false);
	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(1, 1), Angle::getEighthRotation()));
	robot.updateActuators(field);
	engine.setReachedTarget(true);
	engine.setIsGoingStraight(false);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	robot.updateSensorData();
	robot.updateActuators(field);
	odometry.setCurrentPosition(RobotPosition(Point(0, 1), Angle::getQuarterRotation()));
	engine.setReachedTarget(true);
	engine.setIsGoingStraight(false);
	engine.resetCounters();
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToTurnToTarget() > 0);
}

void RobotTest::goTo_firstPointReached_lastArgumentOfTurnToIsTargetPoint()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	m_routerMock->setChessMode(true);
	engine.setReachedTarget(false);
	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(1, 1), Angle::getEighthRotation()));
	robot.updateActuators(field);
	engine.setReachedTarget(true);
	engine.setIsGoingStraight(false);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	robot.updateSensorData();
	robot.updateActuators(field);
	odometry.setCurrentPosition(RobotPosition(Point(0, 1), Angle::getQuarterRotation()));
	engine.setReachedTarget(true);
	engine.setIsGoingStraight(false);
	engine.resetCounters();
	robot.updateSensorData();
	robot.updateActuators(field);

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1, 1), engine.getLastTarget()));
}

void RobotTest::goTo_firstPointAndRotationReached_engineGotOneCallToGoToStraight()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	m_routerMock->setChessMode(true);
	engine.setReachedTarget(false);
	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(1, 1), Angle::getEighthRotation()));
	robot.updateActuators(field);
	engine.setReachedTarget(true);
	engine.setIsGoingStraight(false);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	robot.updateSensorData();
	robot.updateActuators(field);
	odometry.setCurrentPosition(RobotPosition(Point(0, 1), Angle::getQuarterRotation()));
	engine.setReachedTarget(true);
	engine.setIsGoingStraight(false);
	robot.updateSensorData();
	robot.updateActuators(field);
	odometry.setCurrentPosition(RobotPosition(Point(0, 1), 0));
	engine.setReachedTarget(true);
	engine.setIsGoingStraight(false);
	engine.resetCounters();
	robot.updateSensorData();
	robot.updateActuators(field);

	Compare compare(0.00001);
	CPPUNIT_ASSERT(engine.getCallsToGoToStraight() > 0);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1, 1), engine.getLastTarget()));
}

void RobotTest::goTo_finalPointReached_engineGotOneCallToTurnTo()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	engine.setReachedTarget(false);
	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(1, 1), Angle::getQuarterRotation()));
	robot.updateActuators(field);
	engine.setIsGoingStraight(false);
	engine.setReachedTarget(true);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getEighthRotation()));
	robot.updateSensorData();
	robot.updateActuators(field);
	engine.setReachedTarget(false);
	engine.setIsGoingStraight(true);
	robot.updateSensorData();
	robot.updateActuators(field);
	odometry.setCurrentPosition(RobotPosition(Point(1, 1), Angle::getEighthRotation()));
	engine.setReachedTarget(true);
	engine.setIsGoingStraight(false);
	engine.resetCounters();
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToTurnToTarget() > 0);
}

void RobotTest::goTo_finalOrientationReached_engineGotOneCallToStop()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	engine.setReachedTarget(false);
	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(1, 1), Angle::getQuarterRotation()));
	robot.updateActuators(field);
	engine.setIsGoingStraight(false);
	engine.setReachedTarget(true);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getEighthRotation()));
	robot.updateSensorData();
	robot.updateActuators(field);
	engine.setReachedTarget(false);
	engine.setIsGoingStraight(true);
	robot.updateSensorData();
	robot.updateActuators(field);
	odometry.setCurrentPosition(RobotPosition(Point(1, 1), Angle::getEighthRotation()));
	engine.setReachedTarget(true);
	engine.setIsGoingStraight(false);
	robot.updateSensorData();
	robot.updateActuators(field);
	odometry.setCurrentPosition(RobotPosition(Point(1, 1), Angle::getQuarterRotation()));
	engine.setReachedTarget(true);
	engine.setIsGoingStraight(false);
	engine.resetCounters();
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToStop() > 0);
}

void RobotTest::stuckAtObstacle_tryingToTackleObstacle_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(true);
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.stuckAtObstacle());
}

void RobotTest::stuckAtObstacle_notTryingToTackleObstacle_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(false);
	RobotImpl robot(dataAnalyser, m_routerMock);

	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}

void RobotTest::stuckAtObstacle_updateCalledTwiceAfterStuckAtObstacle_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(true);
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);
	engine.setTryingToTackleObstacle(false);
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.stuckAtObstacle());
}

void RobotTest::stuckAtObstacle_newTargetSet_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(true);
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);
	engine.setTryingToTackleObstacle(false);
	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(5, 1), 0));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}

void RobotTest::stuckAtObstacle_collectPuckInFrontCalled_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(true);
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);
	engine.setTryingToTackleObstacle(false);
	robot.updateSensorData();
	robot.collectPuckInFront(Point(0.4, 0));
	robot.leaveCollectedPuck();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}

void RobotTest::stuckAtObstacle_turnAroundCalled_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(true);
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);
	engine.setTryingToTackleObstacle(false);
	robot.updateSensorData();
	robot.turnAround();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}

void RobotTest::stuckAtObstacle_leavePuckCalled_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(true);
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);
	engine.setTryingToTackleObstacle(false);
	robot.updateSensorData();
	robot.leaveCollectedPuck();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}

void RobotTest::stuckAtObstacle_turnToCalled_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(true);
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);
	engine.setTryingToTackleObstacle(false);
	robot.updateSensorData();
	robot.turnTo(Point(5, 1));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}

void RobotTest::reachedTarget_engineSaysNotReached_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;
	engine.setReachedTarget(false);

	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(4, 5), 0));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.reachedTarget());
}

void RobotTest::reachedTarget_currentPositionIsTargetPosition_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;
	engine.setReachedTarget(true);

	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.reachedTarget());
}

void RobotTest::updateActuators_empty_layerBelowGotAtLeastOneCallToUpdateActuators()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(dataAnalyser->getCallsToUpdateActuators() > 0);
}

void RobotTest::updateSensorData_empty_layerBelowGotAtLeastOneCallToUpdateSensorData()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(dataAnalyser->getCallsToUpdateSensorData() > 0);
}

void RobotTest::stop_empty_engineGotAtLeastOneCallToStop()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.stop();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToStop() > 0);
}

void RobotTest::stuckAtObstacle_empty_engineGotAtLeastOneCallToTryingToTackleObstacle()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);
	robot.stuckAtObstacle();

	CPPUNIT_ASSERT(engine.getCallsToTryingToTackleObstacle() > 0);
}

void RobotTest::turnToTarget_validPoint_engineGotAtLeastOneCallToTurnToTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.turnTo(Point(0, 1));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToTurnToTarget() > 0);
}

void RobotTest::turnToTarget_orientationReached_reachedTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.turnTo(Point(0, 1));
	robot.updateActuators(field);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.reachedTarget());
}

void RobotTest::updateActuators_notTryingToTackleObstacle_engineGotNoCallToStop()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(false);
	engine.setReachedTarget(false);
	RobotImpl robot(dataAnalyser, m_routerMock);
	robot.goTo(RobotPosition(Point(10, 0), 0));
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToStop() == 0);
}

void RobotTest::updateActuators_tryingToTackleObstacle_engineGotAtLeastOneCallToStop()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(true);
	RobotImpl robot(dataAnalyser, m_routerMock);
	robot.goTo(RobotPosition(Point(10, 0), 0));
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToStop() > 0);
}

void RobotTest::updateActuators_tryingToTackleObstacle_targetNotReached()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(true);
	RobotImpl robot(dataAnalyser, m_routerMock);
	robot.goTo(RobotPosition(Point(10, 0), 0));
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.reachedTarget());
}

void RobotTest::updateSensorData_noObstacleDirectInFront_engineGotNoCallToLockForwardMovement()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	DataAnalysis::SonarMock &sonar = dataAnalyser->getSonarMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;
	sonar.setIsObstacleDirectInFront(false);

	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToLockForwardMovement() == 0);
}

void RobotTest::updateSensorData_noObstacleDirectInFront_engineGotAtLeastOneCallToUnlockForwardMovement()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	DataAnalysis::SonarMock &sonar = dataAnalyser->getSonarMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	sonar.setIsObstacleDirectInFront(false);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToUnlockForwardMovement() > 0);
}

void RobotTest::updateSensorData_obstacleDirectInFront_engineGotAtLeastOneCallToLockForwardMovement()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	DataAnalysis::SonarMock &sonar = dataAnalyser->getSonarMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	sonar.setIsObstacleDirectInFront(true);
	FieldMock field;

	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(1, 0), 0));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToLockForwardMovement() > 0);
}

void RobotTest::updateSensorData_0bstacleDirectInFront_engineGotNoCallToUnlockForwardMovement()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	DataAnalysis::SonarMock &sonar = dataAnalyser->getSonarMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;
	sonar.setIsObstacleDirectInFront(true);

	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(1, 0), 0));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToUnlockForwardMovement() == 0);
}

void RobotTest::turnAround_empty_engineGotAtLeastOneCallToTurnAround()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.turnAround();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToTurnAround() > 0);
}

void RobotTest::turnAround_turnAroundDone_reachedTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.turnAround();
	robot.updateActuators(field);
	odometry.setCurrentPosition(RobotPosition(Point(), 9*M_PI/8));
	robot.updateSensorData();
	robot.updateActuators(field);
	odometry.setCurrentPosition(RobotPosition(Point(), 0));
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.reachedTarget());
}

void RobotTest::getCurrentPosition_position3And4InOdometry_3And4()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;
	odometry.setCurrentPosition(RobotPosition(Point(3, 4), 2));

	robot.updateSensorData();
	robot.updateActuators(field);

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(RobotPosition(Point(3, 4), 2), robot.getCurrentPosition()));
}

void RobotTest::reachedTarget_nearlyHitTargetButTookSomeAdditionalWayToStop_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	DataAnalysis::SonarMock &sonar = dataAnalyser->getSonarMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	engine.setReachedTarget(false);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	sonar.setIsObstacleDirectInFront(false);
	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(10, 0), 0));
	robot.updateActuators(field);
	odometry.setCurrentPosition(RobotPosition(Point(5, 0), 0));
	sonar.setIsObstacleDirectInFront(true);
	robot.updateSensorData();
	robot.updateActuators(field);
	engine.setTryingToTackleObstacle(true);
	robot.updateSensorData();
	robot.updateActuators(field);
	engine.setTryingToTackleObstacle(false);
	odometry.setCurrentPosition(RobotPosition(Point(5.2, 0), 0));
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.reachedTarget());
	CPPUNIT_ASSERT(robot.cantReachTarget());
}

void RobotTest::cantReachTarget_calledDirectAfterConstructor_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::cantReachTarget_drivingTowardsTheTarget_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(10, 0), 0));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::cantReachTarget_currentTargetSuddenlyNotPossible_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setReachedTarget(false);
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(10, 0), 0));
	robot.updateActuators(field);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	field.setSoftObstacles(obstacles);
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.cantReachTarget());
}

void RobotTest::cantReachTarget_notPossibleAnymoreDuringDriving_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setReachedTarget(false);
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	field.setSoftObstacles(obstacles);

	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(10, 0), 0));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.cantReachTarget());
}

void RobotTest::cantReachTarget_onlyLastTargetNotPossibleToReach_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	field.setSoftObstacles(obstacles);

	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(10, 0), 0));
	robot.updateActuators(field);
	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(-10, 0), 0));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::cantReachTarget_updateTwiceCalled_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	field.setSoftObstacles(obstacles);

	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(10, 0), 0));
	robot.updateActuators(field);
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.cantReachTarget());
}

void RobotTest::cantReachTarget_newTargetSet_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	field.setSoftObstacles(obstacles);

	robot.goTo(RobotPosition(Point(10, 0), 0));
	robot.updateActuators(field);
	robot.goTo(RobotPosition(Point(-10, 0), 0));

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::cantReachTarget_collectPuckInFrontCalled_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	field.setSoftObstacles(obstacles);

	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(10, 0), 0));
	robot.updateActuators(field);
	lidar.setPuckCollectable(true);
	robot.updateSensorData();
	robot.collectPuckInFront(Point(0.4, 0));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::cantReachTarget_turnAroundCalled_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	field.setSoftObstacles(obstacles);

	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(10, 0), 0));
	robot.updateActuators(field);
	robot.updateSensorData();
	robot.turnAround();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::cantReachTarget_turnToCalled_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	field.setSoftObstacles(obstacles);

	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(10, 0), 0));
	robot.updateActuators(field);
	robot.updateSensorData();
	robot.turnTo(Point(-10, 0));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::cantReachTarget_leavePuckCalled_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	field.setSoftObstacles(obstacles);

	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(10, 0), 0));
	robot.updateActuators(field);
	robot.updateSensorData();
	robot.leaveCollectedPuck();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::cantReachTarget_stuckAtObstacle_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.goTo(RobotPosition(Point(10, 0), 0));
	robot.updateActuators(field);
	engine.setTryingToTackleObstacle(true);
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.cantReachTarget());
}

void RobotTest::isPuckCollected_lidarSaysNo_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	lidar.setPuckCollected(false);
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.isPuckCollected());
}

void RobotTest::isPuckCollected_lidarSaysYes_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	lidar.setPuckCollected(true);
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.isPuckCollected());
}

void RobotTest::isPuckCollectable_lidarSaysNo_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	lidar.setPuckCollectable(false);
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.isPuckCollectable());
}

void RobotTest::isPuckCollectable_lidarSaysYes_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	lidar.setPuckCollectable(true);
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.isPuckCollectable());
}

void RobotTest::collectPuckInFront_puckAhead_notStuckAtObstacle()
{
	Hardware::RobotMock *hardwareRobot = new Hardware::RobotMock();
	DataAnalysis::DataAnalyser *dataAnalyser = new DataAnalysis::DataAnalyserImpl(hardwareRobot);
	Hardware::LidarMock &lidar = hardwareRobot->getLidarMock();
	Hardware::SonarMock &sonar = hardwareRobot->getSonarMock();
	lidar.readSensorDataFromFile("resources/testfiles/lidar_34.txt");
	sonar.readSensorDataFromFile("resources/testfiles/sonar_3.txt");
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.collectPuckInFront(Point(0.4, 0));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}

void RobotTest::collectPuckInFront_puckAheadAndStartedToMove_notStuckAtObstacle()
{
	Hardware::RobotMock *hardwareRobot = new Hardware::RobotMock();
	DataAnalysis::DataAnalyser *dataAnalyser = new DataAnalysis::DataAnalyserImpl(hardwareRobot);
	Hardware::LidarMock &lidar = hardwareRobot->getLidarMock();
	Hardware::SonarMock &sonar = hardwareRobot->getSonarMock();
	lidar.readSensorDataFromFile("resources/testfiles/lidar_34.txt");
	sonar.readSensorDataFromFile("resources/testfiles/sonar_3.txt");
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.collectPuckInFront(Point(0.4, 0));
	robot.updateActuators(field);
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}

void RobotTest::collectPuckInFront_puckAheadAndAlreadyUpdatedTheEngine_notStuckAtObstacle()
{
	Hardware::RobotMock *hardwareRobot = new Hardware::RobotMock();
	DataAnalysis::DataAnalyser *dataAnalyser = new DataAnalysis::DataAnalyserImpl(hardwareRobot);
	Hardware::LidarMock &lidar = hardwareRobot->getLidarMock();
	Hardware::SonarMock &sonar = hardwareRobot->getSonarMock();
	lidar.readSensorDataFromFile("resources/testfiles/lidar_34.txt");
	sonar.readSensorDataFromFile("resources/testfiles/sonar_3.txt");
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);
	robot.updateSensorData();
	robot.collectPuckInFront(Point(0.4, 0));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}

void RobotTest::collectPuckInFront_puckCollectedButEngineTargetNotReached_reachedTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	engine.setReachedTarget(false);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	lidar.setPuckCollectable(true);
	robot.updateSensorData();
	robot.collectPuckInFront(Point(0.4, 0));
	robot.updateActuators(field);
	lidar.setPuckCollectable(true);
	lidar.setPuckCollected(true);
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.reachedTarget());
}

void RobotTest::collectPuckInFront_puckNotYetCollected_notReachedTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	engine.setReachedTarget(false);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	lidar.setPuckCollectable(true);
	lidar.setPuckCollected(false);
	robot.updateSensorData();
	robot.collectPuckInFront(Point(0.4, 0));
	robot.updateActuators(field);
	lidar.setPuckCollectable(true);
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.reachedTarget());
}

void RobotTest::collectPuckInFront_drivenToFarAndPuckNotYetCollected_notReachedTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	engine.setReachedTarget(false);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	lidar.setPuckCollectable(true);
	lidar.setPuckCollected(false);
	robot.updateSensorData();
	robot.collectPuckInFront(Point(0.4, 0));
	robot.updateActuators(field);
	odometry.setCurrentPosition(RobotPosition(Point(1, 0), 0));
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.reachedTarget());
}

void RobotTest::collectPuckInFront_drivenToFarAndPuckNotYetCollected_cantReachTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	engine.setReachedTarget(false);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	lidar.setPuckCollectable(true);
	lidar.setPuckCollected(false);
	robot.updateSensorData();
	robot.collectPuckInFront(Point(0.4, 0));
	robot.updateActuators(field);
	odometry.setCurrentPosition(RobotPosition(Point(1, 0), 0));
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.cantReachTarget());
}

void RobotTest::collectPuckInFront_noPuckAhead_cantReachTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	lidar.setPuckCollectable(false);
	robot.updateSensorData();
	robot.collectPuckInFront(Point(0.4, 0));
	robot.updateActuators(field);
	engine.setReachedTarget(true);
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.cantReachTarget());
}

void RobotTest::collectPuckInFront_puckAhead_canReachTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	lidar.setPuckCollectable(true);
	robot.updateSensorData();
	robot.collectPuckInFront(Point(0.4, 0));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::collectPuckInFront_differentPuckAheadThanDesiredOne_cantReachTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	lidar.setPuckCollectable(false);
	lidar.setPuckCollectable(true);
	robot.updateSensorData();
	robot.collectPuckInFront(Point(0.4, 0));
	robot.updateActuators(field);
	engine.setReachedTarget(true);
	lidar.setPuckCollectable(true);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	robot.updateSensorData();
	robot.updateActuators(field);
	robot.updatePuckPosition(Point(0.4, -0.5));
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.cantReachTarget());
}

void RobotTest::collectPuckInFront_validPuck_isCollectingPuck()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	lidar.setPuckCollectable(true);
	robot.updateSensorData();
	robot.collectPuckInFront(Point(0.4, 0));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.isCollectingPuck());
}

void RobotTest::collectPuckInFront_puckCollected_isNotCollectingPuck()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	lidar.setPuckCollectable(true);
	robot.updateSensorData();
	robot.collectPuckInFront(Point(0.4, 0));
	robot.updateActuators(field);
	lidar.setPuckCollected(true);
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.isCollectingPuck());
}

void RobotTest::collectPuckInFront_lookingLeftAndPuckAhead_canReachTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	lidar.setPuckCollectable(true);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	robot.updateSensorData();
	robot.collectPuckInFront(Point(-0.4, 0));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::collectPuckInFront_orientationWrongAtBegin_canReachTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	robot.updateSensorData();
	robot.collectPuckInFront(Point(0, 0.4));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::collectPuckInFront_orientationWrongAtBegin_engineGotCallToTurnTo()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	robot.updateSensorData();
	robot.collectPuckInFront(Point(0, 0.4));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToTurnToTarget() == 1);
}

void RobotTest::collectPuckInFront_orientationWrongAtBeginAndOrientationReached_engineGotCallToGoToStraightSlowly()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	robot.updateSensorData();
	robot.collectPuckInFront(Point(0, 0.4));
	robot.updateActuators(field);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	engine.setReachedTarget(true);
	lidar.setPuckCollectable(true);
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToGoToStraightSlowly() == 1);
}

void RobotTest::updatePuckPosition_newPositionOfPuck_goToStraightSlowlyCalledTwice()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	lidar.setPuckCollectable(true);
	odometry.setCurrentPosition(RobotPosition(Point(4, 5), 0));
	robot.updateSensorData();
	robot.collectPuckInFront(Point(4.2, 5));
	robot.updateActuators(field);
	engine.setReachedTarget(true);
	robot.updateSensorData();
	robot.updateActuators(field);
	robot.updateSensorData();
	robot.updatePuckPosition(Point(4.3, 5));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToGoToStraightSlowly() == 2);
}

void RobotTest::leaveCollectedPuck_drivenFarEnoughBack_reachedTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	robot.updateSensorData();
	robot.leaveCollectedPuck();
	robot.updateActuators(field);
	odometry.setCurrentPosition(RobotPosition(Point(-0.2, 0), 0));
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.reachedTarget());
}

void RobotTest::isRotating_waiting_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.isRotating());
}

void RobotTest::isRotating_turnTo_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	robot.updateSensorData();
	robot.turnTo(Point(4, 5));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.isRotating());
}

void RobotTest::isRotating_turnAround_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	robot.updateSensorData();
	robot.turnAround();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.isRotating());
}

void RobotTest::isRotating_firstPhaseOfCollectingPuck_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	lidar.setPuckCollectable(false);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	robot.updateSensorData();
	robot.collectPuckInFront(Point(0, 0.4));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.isRotating());
}

void RobotTest::isRotating_secondPhaseOfCollectingPuck_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	lidar.setPuckCollectable(false);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	robot.updateSensorData();
	robot.collectPuckInFront(Point(0, 0.4));
	robot.updateActuators(field);
	lidar.setPuckCollectable(false);
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.isRotating());
}

void RobotTest::isRotating_leavingPuck_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::OdometryMock &odometry = dataAnalyser->getOdometryMock();
	RobotImpl robot(dataAnalyser, m_routerMock);
	FieldMock field;

	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	robot.updateSensorData();
	robot.leaveCollectedPuck();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.isRotating());
}
