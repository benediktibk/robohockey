#include "layer/autonomous/robottest.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/dataanalysis/dataanalysermock.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/hardware/robotmock.h"
#include "common/compare.h"
#include "common/robotposition.h"

using namespace std;
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
	FieldMock field;

	robot.updateSensorData();
	robot.goTo(Point(5, 4));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToGoToStraight() > 0);
}

void RobotTest::stuckAtObstacle_tryingToTackleObstacle_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(true);
	RobotImpl robot(dataAnalyser);
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
	RobotImpl robot(dataAnalyser);

	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}

void RobotTest::stuckAtObstacle_updateCalledTwiceAfterStuckAtObstacle_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(true);
	RobotImpl robot(dataAnalyser);
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
	RobotImpl robot(dataAnalyser);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);
	engine.setTryingToTackleObstacle(false);
	robot.updateSensorData();
	robot.goTo(Point(5, 1));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}

void RobotTest::stuckAtObstacle_collectPuckInFrontCalled_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(true);
	RobotImpl robot(dataAnalyser);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);
	engine.setTryingToTackleObstacle(false);
	robot.collectPuckInFront();
	robot.leaveCollectedPuck();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}

void RobotTest::stuckAtObstacle_turnAroundCalled_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(true);
	RobotImpl robot(dataAnalyser);
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
	RobotImpl robot(dataAnalyser);
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
	RobotImpl robot(dataAnalyser);
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
	RobotImpl robot(dataAnalyser);
	FieldMock field;
	engine.setReachedTarget(false);

	robot.goTo(Point(4, 5));
	robot.updateActuators(field);

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
	FieldMock field;

	robot.updateActuators(field);

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
	FieldMock field;

	robot.stop();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToStop() > 0);
}

void RobotTest::stuckAtObstacle_empty_engineGotAtLeastOneCallToTryingToTackleObstacle()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser);
	FieldMock field;

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
	RobotImpl robot(dataAnalyser);

	robot.turnTo(Point(0, 1));

	CPPUNIT_ASSERT(engine.getCallsToTurnToTarget() > 0);
}

void RobotTest::updateActuators_notTryingToTackleObstacle_engineGotNoCallToStop()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(false);
	engine.setReachedTarget(false);
	RobotImpl robot(dataAnalyser);
	robot.goTo(Point(10, 0));
	FieldMock field;

	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToStop() == 0);
}

void RobotTest::updateActuators_tryingToTackleObstacle_engineGotAtLeastOneCallToStop()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(true);
	RobotImpl robot(dataAnalyser);
	robot.goTo(Point(10, 0));
	FieldMock field;

	robot.updateActuators(field);

	CPPUNIT_ASSERT(engine.getCallsToStop() > 0);
}

void RobotTest::updateActuators_tryingToTackleObstacle_targetNotReached()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setTryingToTackleObstacle(true);
	RobotImpl robot(dataAnalyser);
	robot.goTo(Point(10, 0));
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
	RobotImpl robot(dataAnalyser);
	sonar.setIsObstacleDirectInFront(true);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);

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
	FieldMock field;

	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	robot.goTo(Point(10, 0));
	sonar.setIsObstacleDirectInFront(false);
	robot.updateSensorData();
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

	CPPUNIT_ASSERT(robot.reachedTarget());
}

void RobotTest::cantReachTarget_calledDirectAfterConstructor_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::cantReachTarget_drivingTowardsTheTarget_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser);
	FieldMock field;

	robot.goTo(Point(10, 0));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::cantReachTarget_currentTargetSuddenlyNotPossible_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setReachedTarget(false);
	RobotImpl robot(dataAnalyser);
	FieldMock field;

	robot.updateSensorData();
	robot.goTo(Point(10, 0));
	robot.updateActuators(field);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	field.setObstacles(obstacles);
	robot.updateSensorData();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.cantReachTarget());
}

void RobotTest::cantReachTarget_notPossibleAnymoreDuringDriving_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	engine.setReachedTarget(false);
	RobotImpl robot(dataAnalyser);
	FieldMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	field.setObstacles(obstacles);

	robot.goTo(Point(10, 0));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.cantReachTarget());
}

void RobotTest::cantReachTarget_onlyLastTargetNotPossibleToReach_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser);
	FieldMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	field.setObstacles(obstacles);

	robot.updateSensorData();
	robot.goTo(Point(10, 0));
	robot.updateActuators(field);
	robot.updateSensorData();
	robot.goTo(Point(-10, 0));
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::cantReachTarget_updateTwiceCalled_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser);
	FieldMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	field.setObstacles(obstacles);

	robot.goTo(Point(10, 0));
	robot.updateActuators(field);
	robot.updateActuators(field);

	CPPUNIT_ASSERT(robot.cantReachTarget());
}

void RobotTest::cantReachTarget_newTargetSet_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser);
	FieldMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	field.setObstacles(obstacles);

	robot.goTo(Point(10, 0));
	robot.updateActuators(field);
	robot.goTo(Point(-10, 0));

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::cantReachTarget_collectPuckInFrontCalled_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser);
	FieldMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	field.setObstacles(obstacles);

	robot.goTo(Point(10, 0));
	robot.updateActuators(field);
	robot.collectPuckInFront();

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::cantReachTarget_turnAroundCalled_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser);
	FieldMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	field.setObstacles(obstacles);

	robot.goTo(Point(10, 0));
	robot.updateActuators(field);
	robot.turnAround();

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::cantReachTarget_turnToCalled_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser);
	FieldMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	field.setObstacles(obstacles);

	robot.goTo(Point(10, 0));
	robot.updateActuators(field);
	robot.turnTo(Point(-10, 0));

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::cantReachTarget_leavePuckCalled_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser);
	FieldMock field;
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	field.setObstacles(obstacles);

	robot.goTo(Point(10, 0));
	robot.updateActuators(field);
	robot.leaveCollectedPuck();

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::isPuckCollected_lidarSaysNo_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	lidar.setPuckCollected(false);
	RobotImpl robot(dataAnalyser);

	CPPUNIT_ASSERT(!robot.isPuckCollected());
}

void RobotTest::isPuckCollected_lidarSaysYes_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	lidar.setPuckCollected(true);
	RobotImpl robot(dataAnalyser);

	CPPUNIT_ASSERT(robot.isPuckCollected());
}

void RobotTest::isPuckCollectable_lidarSaysNo_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	lidar.setPuckCollectable(false);
	RobotImpl robot(dataAnalyser);

	CPPUNIT_ASSERT(!robot.isPuckCollectable());
}

void RobotTest::isPuckCollectable_lidarSaysYes_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	lidar.setPuckCollectable(true);
	RobotImpl robot(dataAnalyser);

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
	RobotImpl robot(dataAnalyser);
	FieldMock field;

	robot.updateSensorData();
	robot.collectPuckInFront();
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
	RobotImpl robot(dataAnalyser);
	FieldMock field;

	robot.updateSensorData();
	robot.collectPuckInFront();
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
	RobotImpl robot(dataAnalyser);
	FieldMock field;

	robot.updateSensorData();
	robot.updateActuators(field);
	robot.updateSensorData();
	robot.collectPuckInFront();
	robot.updateActuators(field);

	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}
