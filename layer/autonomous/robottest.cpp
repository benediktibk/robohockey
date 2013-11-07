#include "layer/autonomous/robottest.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/dataanalysis/dataanalysermock.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::Autonomous;

void RobotTest::goTo_positionDifferentToCurrentOne_engineGotAtLeastOneCallToGoToStraight()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(Point(2, 3), 1);
	RobotImpl robot(dataAnalyser);

	robot.goTo(Point(5, 4));

	CPPUNIT_ASSERT(engine.getCallsToGoToStraight() > 0);
}

void RobotTest::stuckAtObstacle_obstacleDirectInFront_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::SonarMock &sonar = dataAnalyser->getSonarMock();
	sonar.setIsObstacleDirectInFront(true);
	RobotImpl robot(dataAnalyser);

	CPPUNIT_ASSERT(robot.stuckAtObstacle());
}

void RobotTest::stuckAtObstacle_noObstacleDirectInFront_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::SonarMock &sonar = dataAnalyser->getSonarMock();
	sonar.setIsObstacleDirectInFront(false);
	RobotImpl robot(dataAnalyser);

	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}

void RobotTest::reachedTarget_currentPositionDifferentToTarget_false()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	odometry.setCurrentPosition(Point(2, 3), 1);
	RobotImpl robot(dataAnalyser);
	robot.goTo(Point(5, 4));
	robot.updateSensorData();

	CPPUNIT_ASSERT(!robot.reachedTarget());
}

void RobotTest::reachedTarget_currentPositionIsTargetPosition_true()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	odometry.setCurrentPosition(Point(2, 3), 1);
	RobotImpl robot(dataAnalyser);
	robot.goTo(Point(2, 3));
	robot.updateSensorData();

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
