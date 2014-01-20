#include "layer/autonomous/robottest.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/fieldmock.h"
#include "layer/autonomous/routermock.h"
#include "layer/autonomous/routerimpl.h"
#include "layer/dataanalysis/dataanalysermock.h"
#include "layer/dataanalysis/dataanalyserimpl.h"
#include "layer/hardware/robotmock.h"
#include "common/compare.h"
#include "common/robotposition.h"
#include "common/watchmock.h"
#include "common/loggermock.h"

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::Autonomous;

void RobotTest::setUp()
{
	m_routerMock = new RouterMock();
	m_watchMock = new WatchMock();
	m_logger = new LoggerMock();
	m_dataAnalyser = new DataAnalysis::DataAnalyserMock();
	m_odometry = &(m_dataAnalyser->getOdometryMock());
	m_engine = &(m_dataAnalyser->getEngineMock());
	m_sonar = &(m_dataAnalyser->getSonarMock());
	m_lidar = &(m_dataAnalyser->getLidarMock());
	m_targets.clear();
	m_robot = new RobotImpl(m_dataAnalyser, m_routerMock, *m_watchMock, *m_logger, true);
	m_field = new FieldMock;
}

void RobotTest::tearDown()
{
	delete m_field;
	m_field = 0;
	delete m_robot;
	m_robot = 0;
	m_routerMock = 0;
	m_dataAnalyser = 0;
	m_odometry = 0;
	m_engine = 0;
	m_sonar = 0;
	m_lidar = 0;
	delete m_logger;
	m_logger = 0;
	delete m_watchMock;
	m_watchMock = 0;
}

void RobotTest::goTo_positionDifferentToCurrentOne_engineGotAtLeastOneCallToGoToStraightOrTurnTo()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(2, 3), 1));

	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(5, 4), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_engine->getCallsToGoToStraight() > 0 || m_engine->getCallsToTurnToTarget() > 0);
}

void RobotTest::goTo_orientationToTargetCorrect_engineGotAtLeastOneCallToGoToStraight()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(1, 0), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_engine->getCallsToGoToStraight() > 0);
}

void RobotTest::goTo_orientationToTargetCompletelyWrong_engineGotNoCallToGoToStraight()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(-1, 0), Angle::getHalfRotation()));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_engine->getCallsToGoToStraight() == 0);
}

void RobotTest::goTo_orientationToTargetCompletelyWrong_engineGotAtLeastOneCallToTurnTo()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(-1, 0), Angle::getHalfRotation()));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_engine->getCallsToTurnToTarget() > 0);
}

void RobotTest::goTo_orientationToTargetCompletelyWrong_isRotating()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(-1, 0), Angle::getHalfRotation()));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->isRotating());
}

void RobotTest::goTo_orientationToTargetCorrectAndUpdateCalledTwice_notReachedTarget()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(1, 0), Angle::getQuarterRotation()));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_robot->updateSensorData();
	m_engine->setReachedTarget(false);
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->reachedTarget());
}

void RobotTest::goTo_orientationReachedAfterSomeTime_notReachedTarget()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(-1, 0), Angle::getHalfRotation()));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(false);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->reachedTarget());
}

void RobotTest::goTo_lookingDownwardButHaveToGoUpAndOrientationReached_engineGotAtLeastOneCallToGoToStraight()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getThreeQuarterRotation()));

	m_engine->setReachedTarget(false);
	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(0, 1), Angle::getQuarterRotation()));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_engine->getCallsToGoToStraight() > 0);
}

void RobotTest::goTo_targetPositionReached_reachedTarget()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getThreeQuarterRotation()));

	m_engine->setReachedTarget(false);
	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(0, 1), Angle::getQuarterRotation()));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 1), Angle::getQuarterRotation()));
	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 1), Angle::getQuarterRotation()));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->reachedTarget());
}

void RobotTest::goTo_firstPointReached_notReachedTarget()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_routerMock->setChessMode(true);
	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(1, 10), Angle(tan(10/1))));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 10), Angle::getQuarterRotation()));
	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->reachedTarget());
}

void RobotTest::goTo_firstPointReached_engineGotOneCallToTurnTo()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_routerMock->setChessMode(true);
	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(1, 10), Angle(tan(10/1))));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 10), Angle::getQuarterRotation()));
	m_engine->setReachedTarget(true);
	m_engine->resetCounters();
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_engine->getCallsToTurnToTarget() > 0);
}

void RobotTest::goTo_firstPointReached_lastArgumentOfTurnToIsTargetPoint()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_routerMock->setChessMode(true);
	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(1, 10), Angle(0)));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 10), Angle::getQuarterRotation()));
	m_engine->setReachedTarget(true);
	m_engine->resetCounters();
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	Compare compare(0.00001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1, 10), m_engine->getLastTarget()));
}

void RobotTest::goTo_firstPointAndRotationReached_engineGotOneCallToGoToStraight()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_routerMock->setChessMode(true);
	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(1, 10), Angle(tan(10/1))));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 10), Angle::getQuarterRotation()));
	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 10), 0));
	m_engine->setReachedTarget(true);
	m_engine->resetCounters();
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	Compare compare(0.00001);
	CPPUNIT_ASSERT(m_engine->getCallsToGoToStraight() > 0);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(1, 10), m_engine->getLastTarget()));
}

void RobotTest::goTo_finalPointReached_engineGotOneCallToTurnTo()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(1, 10), Angle::getQuarterRotation()));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle(tan(10/1))));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(false);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(1, 10), Angle::getQuarterRotation()));
	m_engine->setReachedTarget(true);
	m_engine->resetCounters();
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_engine->getCallsToTurnToTarget() > 0);
}

void RobotTest::goTo_finalOrientationReached_engineGotOneCallToStop()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_engine->setReachedTarget(false);
	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(1, 1), Angle::getQuarterRotation()));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getEighthRotation()));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(false);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(1, 1), Angle::getEighthRotation()));
	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(1, 1), Angle::getQuarterRotation()));
	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(1, 1), Angle::getQuarterRotation()));
	m_engine->setReachedTarget(true);
	m_engine->resetCounters();
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_engine->getCallsToStop() > 0);
	CPPUNIT_ASSERT(m_robot->reachedTarget());
}

void RobotTest::goTo_surroundedBySoftObstacles_canReachTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = m_dataAnalyser->getOdometry();
	RobotImpl robot(dataAnalyser, new RouterImpl(0.5), *m_watchMock, *m_logger, true);
	odometry.setCurrentPosition(RobotPosition(Point(0.5, 0.5), 0));
	m_field->setNegativeCoordinatesOutside(true);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(0.5, 2), 1));
	obstacles.push_back(Circle(Point(1.5, 2), 1));
	obstacles.push_back(Circle(Point(2, 1.5), 1));
	obstacles.push_back(Circle(Point(2, 0.5), 1));
	m_field->setSoftObstacles(obstacles);

	robot.updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 10), Angle(0)));
	robot.goTo(m_targets);
	robot.updateActuators(*m_field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::goTo_surroundedByHardObstacles_cantReachTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = m_dataAnalyser->getOdometry();
	RobotImpl robot(dataAnalyser, new RouterImpl(0.5), *m_watchMock, *m_logger, true);
	odometry.setCurrentPosition(RobotPosition(Point(0.5, 0.5), 0));
	m_field->setNegativeCoordinatesOutside(true);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(0.5, 2), 1));
	obstacles.push_back(Circle(Point(1.5, 2), 1));
	obstacles.push_back(Circle(Point(2, 1.5), 1));
	obstacles.push_back(Circle(Point(2, 0.5), 1));
	m_field->setHardObstacles(obstacles);
	m_field->setHardAndVisibleObstacles(obstacles);

	robot.updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 10), Angle(0)));
	robot.goTo(m_targets);
	robot.updateActuators(*m_field);

	CPPUNIT_ASSERT(robot.cantReachTarget());
}

void RobotTest::goTo_finalOrientationNotPossible_canReachTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	RobotImpl robot(dataAnalyser, new RouterImpl(0.5), *m_watchMock, *m_logger, true);
	m_field->setNegativeCoordinatesOutside(false);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 1), 1));
	obstacles.push_back(Circle(Point(10, -1), 1));
	obstacles.push_back(Circle(Point(11, 0), 1));
	m_field->setHardObstacles(obstacles);

	robot.updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 0), Angle::getHalfRotation()));
	robot.goTo(m_targets);
	robot.updateActuators(*m_field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::goTo_twoTargetsAndFirstOnePossible_canReachFirstTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	RobotImpl robot(dataAnalyser, new RouterImpl(0.5), *m_watchMock, *m_logger, true);
	m_field->setNegativeCoordinatesOutside(false);

	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	m_targets.push_back(RobotPosition(Point(-5, 0), Angle::getHalfRotation()));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->cantReachTarget());
	list<Point> routePoints = m_robot->getAllRoutePoints();
	CPPUNIT_ASSERT_EQUAL((size_t)2, routePoints.size());
	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(10, 0), routePoints.back()));
}

void RobotTest::goTo_twoTargetsAndOnlySecondOnePossible_canReachSecondTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	RobotImpl robot(dataAnalyser, new RouterImpl(0.5), *m_watchMock, *m_logger, true);
	m_field->setNegativeCoordinatesOutside(false);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 1));
	m_field->setSoftObstacles(obstacles);

	robot.updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	m_targets.push_back(RobotPosition(Point(-5, 0), Angle::getHalfRotation()));
	robot.goTo(m_targets);
	robot.updateActuators(*m_field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
	list<Point> routePoints = robot.getAllRoutePoints();
	CPPUNIT_ASSERT_EQUAL((size_t)2, routePoints.size());
	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(-5, 0), routePoints.back()));
}

void RobotTest::goTo_minuteWaited_cantReachTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	RobotImpl robot(dataAnalyser, new RouterImpl(0.5), *m_watchMock, *m_logger, true);

	robot.updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	robot.goTo(m_targets);
	robot.updateActuators(*m_field);
	m_watchMock->setTime(60);
	robot.updateSensorData();
	robot.updateActuators(*m_field);

	CPPUNIT_ASSERT(robot.cantReachTarget());
}

void RobotTest::goTo_obstacleSuddenlyAppearedDuringDriving_engineGotCallToStop()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	RobotImpl robot(dataAnalyser, new RouterImpl(0.5), *m_watchMock, *m_logger, true);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(5, 0), 1));

	engine.setReachedTarget(true);
	robot.updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	robot.goTo(m_targets);
	robot.updateActuators(*m_field);
	engine.setReachedTarget(false);
	robot.updateSensorData();
	robot.updateActuators(*m_field);
	m_field->setHardObstacles(obstacles);
	engine.resetCounters();
	robot.updateSensorData();
	robot.updateActuators(*m_field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, engine.getCallsToStop());
}

void RobotTest::goTo_obstacleSuddenlyAppearedDuringTurning_engineGotCallToStop()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	RobotImpl robot(dataAnalyser, new RouterImpl(0.5), *m_watchMock, *m_logger, true);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(5, 0), 1));

	robot.updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	robot.goTo(m_targets);
	robot.updateActuators(*m_field);
	m_field->setHardObstacles(obstacles);
	engine.resetCounters();
	robot.updateSensorData();
	robot.updateActuators(*m_field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, engine.getCallsToStop());
}

void RobotTest::goTo_hardObstacleAtStart_engineGotCallToTurnToTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	RobotImpl robot(dataAnalyser, new RouterImpl(0.5), *m_watchMock, *m_logger, true);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(0.8, 0), 2));
	m_field->setHardObstacles(obstacles);

	engine.setReachedTarget(true);
	robot.updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	robot.goTo(m_targets);
	robot.updateActuators(*m_field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, engine.getCallsToTurnToTarget());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, engine.getCallsToGoToStraight());
}

void RobotTest::goTo_hardObstacleMovedALittleBitIntoTheRoute_engineGotNoAdditionalCalls()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 1), Angle::getQuarterRotation()));
	RobotImpl robot(dataAnalyser, new RouterImpl(0.5), *m_watchMock, *m_logger, true);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(7, 1), 1));
	m_field->setHardObstacles(obstacles);
	m_field->setNegativeCoordinatesOutside(true);

	robot.updateSensorData();
	m_targets.push_back(RobotPosition(Point(14, 1), 0));
	robot.goTo(m_targets);
	robot.updateActuators(*m_field);
	engine.setReachedTarget(true);
	robot.updateSensorData();
	robot.updateActuators(*m_field);
	engine.setReachedTarget(false);
	robot.updateSensorData();
	robot.updateActuators(*m_field);
	engine.resetCounters();
	obstacles.push_back(Circle(Point(7, 1.1), 1));
	m_field->setHardObstacles(obstacles);
	robot.updateSensorData();
	robot.updateActuators(*m_field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, engine.getCallsToTurnToTarget());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, engine.getCallsToGoToStraight());
}

void RobotTest::goTo_puckCollectedButLostInBetween_newRouteStillConsideringThePuck()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	DataAnalysis::LidarMock &lidar = dataAnalyser->getLidarMock();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), 0));
	RobotImpl robot(dataAnalyser, new RouterImpl(0.5), *m_watchMock, *m_logger, true);
	m_targets.push_back(RobotPosition(Point(5, 0), Angle::getHalfRotation()));
	m_targets.push_back(RobotPosition(Point(-5, 0), Angle(0)));
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(5, 0), 1));

	m_watchMock->setTime(1);
	lidar.setPuckCollected(true);
	robot.updateSensorData();
	robot.goTo(m_targets);
	robot.updateActuators(*m_field);
	lidar.setPuckCollected(false);
	m_field->setHardObstacles(obstacles);
	robot.updateSensorData();
	robot.updateActuators(*m_field);

	list<Point> routePoints = robot.getAllRoutePoints();
	CPPUNIT_ASSERT(routePoints.size() > 2);
}

void RobotTest::goTo_positionInsideHardObstacle_cantReachTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	RobotImpl robot(dataAnalyser, new RouterImpl(0.5), *m_watchMock, *m_logger, true);
	m_targets.push_back(RobotPosition(Point(5, 5), Angle(0)));
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(5, 5), 1));

	m_field->setHardObstacles(obstacles);
	m_field->setHardAndVisibleObstacles(obstacles);
	robot.updateSensorData();
	robot.goTo(m_targets);
	robot.updateActuators(*m_field);

	CPPUNIT_ASSERT(robot.cantReachTarget());
}

void RobotTest::goTo_positionInsideSoftObstacle_canReachTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	RobotImpl robot(dataAnalyser, new RouterImpl(0.5), *m_watchMock, *m_logger, true);
	m_targets.push_back(RobotPosition(Point(5, 5), Angle(0)));
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(5, 5), 1));

	m_field->setSoftObstacles(obstacles);
	robot.updateSensorData();
	robot.goTo(m_targets);
	robot.updateActuators(*m_field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
}

void RobotTest::goTo_firstPointReachedAndSmallTurnNecessary_noCallsToTurnToTarget()
{
	m_routerMock->setRoute(Point(0, 0), Point(5, 0), Point(7, 0.1));
	m_targets.push_back(RobotPosition(Point(7, 0.1), Angle(0)));

	m_engine->setReachedTarget(false);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	m_robot->updateSensorData();
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_engine->resetCounters();
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(false);
	m_odometry->setCurrentPosition(RobotPosition(Point(5, 0), Angle(0)));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_engine->getCallsToTurnToTarget());
}

void RobotTest::goTo_firstPointReachedAndSmallTurnNecessary_engineGotCorrectNextTarget()
{
	m_routerMock->setRoute(Point(0, 0), Point(5, 0), Point(7, 0.1));
	m_targets.push_back(RobotPosition(Point(7, 0.1), Angle(0)));

	m_engine->setReachedTarget(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	m_robot->updateSensorData();
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(false);
	m_engine->resetCounters();
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_engine->resetCounters();
	m_odometry->setCurrentPosition(RobotPosition(Point(5, 0), Angle(0)));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_engine->getCallsToGoToStraight());
	const Point &lastTarget = m_engine->getLastTarget();
	Compare compare(0.001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(7, 0.1), lastTarget));
}

void RobotTest::goTo_orientationDifferenceZero_engineGotOnlyCallToGoToStraight()
{
	m_targets.push_back(RobotPosition(Point(-10, 0), Angle(0)));

	m_engine->setReachedTarget(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	m_robot->updateSensorData();
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_engine->getCallsToTurnToTarget());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_engine->getCallsToGoToStraight());
	const Point &lastTarget = m_engine->getLastTarget();
	Compare compare(0.001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(-10, 0), lastTarget));
}

void RobotTest::goTo_orientationDifferenceSmall_engineGotOnlyCallToGoToStraight()
{
	m_targets.push_back(RobotPosition(Point(-10, 0.1), Angle(0)));

	m_engine->setReachedTarget(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	m_robot->updateSensorData();
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_engine->getCallsToTurnToTarget());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_engine->getCallsToGoToStraight());
	const Point &lastTarget = m_engine->getLastTarget();
	Compare compare(0.001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(-10, 0.1), lastTarget));
}

void RobotTest::goTo_noUpdateOfActuators_engineGotCallToStop()
{
	m_targets.push_back(RobotPosition(Point(10, 0), Angle(0)));

	m_engine->setReachedTarget(false);
	m_robot->updateSensorData();
	m_robot->goTo(m_targets);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_engine->getCallsToStop());
}

void RobotTest::goTo_finalPointReached_engineGotCallToTurnToFinalOrientation()
{
	m_targets.push_back(RobotPosition(Point(10, 10), Angle::getQuarterRotation()));

	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(10, 10), Angle::getEighthRotation()));
	m_engine->setReachedTarget(true);
	m_engine->resetCounters();
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_engine->getCallsToTurnToTarget());
	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(10, 11), m_engine->getLastTarget()));
}

void RobotTest::goTo_hardNotVisibleObstacleAtEnd_canReachTarget()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	DataAnalysis::Odometry &odometry = dataAnalyser->getOdometry();
	odometry.setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	RobotImpl robot(dataAnalyser, new RouterImpl(0.5), *m_watchMock, *m_logger, true);
	m_targets.push_back(RobotPosition(Point(10, 0), Angle(0)));
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 0.3));

	m_field->setHardObstacles(obstacles);
	engine.setReachedTarget(true);
	robot.updateSensorData();
	robot.goTo(m_targets);
	robot.updateActuators(*m_field);
	engine.resetCounters();
	engine.setReachedTarget(false);
	robot.updateSensorData();
	robot.updateActuators(*m_field);

	CPPUNIT_ASSERT(!robot.cantReachTarget());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, engine.getCallsToStop());
}

void RobotTest::goTo_tookAVeryLongTime_cantReachTarget()
{
	list<RobotPosition> targets;
	targets.push_back(RobotPosition(Point(10, 0), Angle(0)));

	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	m_robot->updateSensorData();
	m_robot->goTo(targets);
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	m_watchMock->setTime(20);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_watchMock->setTime(40);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->cantReachTarget());
}

void RobotTest::goTo_sonarDetectsObstacleButSonarDistabled_engineGotNoCallToLockForwardMovement()
{
	DataAnalysis::DataAnalyserMock *dataAnalyser = new DataAnalysis::DataAnalyserMock();
	RobotImpl robot(dataAnalyser, new RouterMock(), *m_watchMock, *m_logger, false);
	const DataAnalysis::EngineMock &engine = dataAnalyser->getEngineMock();
	DataAnalysis::SonarMock &sonar = dataAnalyser->getSonarMock();
	list<RobotPosition> targets;
	targets.push_back(RobotPosition(Point(10, 0), Angle(0)));

	robot.updateSensorData();
	robot.goTo(targets);
	robot.updateActuators(*m_field);
	sonar.setIsObstacleDirectInFront(true);
	robot.updateSensorData();
	robot.updateActuators(*m_field);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, engine.getCallsToLockForwardMovement());
	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}

void RobotTest::goTo_finalPointAndOrientationReached_reachedTarget()
{
	list<RobotPosition> targets;
	targets.push_back(RobotPosition(Point(10, 0), Angle(0)));

	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	m_engine->setReachedTarget(false);
	m_robot->updateSensorData();
	m_robot->goTo(targets);
	m_robot->updateActuators(*m_field);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(10, 0), Angle(0)));
	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->reachedTarget());
	CPPUNIT_ASSERT(!m_robot->cantReachTarget());
}

void RobotTest::goTo_droveALittleBitToFarToFinalPoint_reachedTarget()
{
	list<RobotPosition> targets;
	targets.push_back(RobotPosition(Point(10, 0), Angle(0)));

	m_engine->setReachedTarget(false);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));
	m_robot->updateSensorData();
	m_robot->goTo(targets);
	m_robot->updateActuators(*m_field);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(10.1, 0), Angle(0)));
	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->reachedTarget());
	CPPUNIT_ASSERT(!m_robot->cantReachTarget());
}

void RobotTest::stuckAtObstacle_tryingToTackleObstacle_true()
{
	m_engine->setTryingToTackleObstacle(true);

	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->stuckAtObstacle());
}

void RobotTest::stuckAtObstacle_notTryingToTackleObstacle_false()
{
	m_engine->setTryingToTackleObstacle(false);

	CPPUNIT_ASSERT(!m_robot->stuckAtObstacle());
}

void RobotTest::stuckAtObstacle_updateCalledTwiceAfterStuckAtObstacle_true()
{
	m_engine->setTryingToTackleObstacle(true);

	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_engine->setTryingToTackleObstacle(false);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->stuckAtObstacle());
}

void RobotTest::stuckAtObstacle_newTargetSet_false()
{
	m_engine->setTryingToTackleObstacle(true);

	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_engine->setTryingToTackleObstacle(false);
	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(5, 1), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->stuckAtObstacle());
}

void RobotTest::stuckAtObstacle_collectPuckInFrontCalled_false()
{
	m_engine->setTryingToTackleObstacle(true);

	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_engine->setTryingToTackleObstacle(false);
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(0.4, 0));
	m_robot->leaveCollectedPuck();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->stuckAtObstacle());
}

void RobotTest::stuckAtObstacle_leavePuckCalled_false()
{
	m_engine->setTryingToTackleObstacle(true);

	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_engine->setTryingToTackleObstacle(false);
	m_robot->updateSensorData();
	m_robot->leaveCollectedPuck();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->stuckAtObstacle());
}

void RobotTest::stuckAtObstacle_turnToCalled_false()
{
	m_engine->setTryingToTackleObstacle(true);

	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_engine->setTryingToTackleObstacle(false);
	m_robot->updateSensorData();
	m_robot->turnTo(Point(5, 1));
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->stuckAtObstacle());
}

void RobotTest::reachedTarget_engineSaysNotReached_false()
{
	m_engine->setReachedTarget(false);

	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(4, 5), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->reachedTarget());
}

void RobotTest::reachedTarget_currentPositionIsTargetPosition_true()
{
	m_engine->setReachedTarget(true);

	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->reachedTarget());
}

void RobotTest::updateActuators_empty_layerBelowGotAtLeastOneCallToUpdateActuators()
{
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_dataAnalyser->getCallsToUpdateActuators() > 0);
}

void RobotTest::updateSensorData_empty_layerBelowGotAtLeastOneCallToUpdateSensorData()
{
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_dataAnalyser->getCallsToUpdateSensorData() > 0);
}

void RobotTest::stop_empty_engineGotAtLeastOneCallToStop()
{
	m_robot->updateSensorData();
	m_robot->stop();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_engine->getCallsToStop() > 0);
}

void RobotTest::stuckAtObstacle_empty_engineGotAtLeastOneCallToTryingToTackleObstacle()
{
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_robot->stuckAtObstacle();

	CPPUNIT_ASSERT(m_engine->getCallsToTryingToTackleObstacle() > 0);
}

void RobotTest::turnToTarget_validPoint_engineGotAtLeastOneCallToTurnToTarget()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_robot->updateSensorData();
	m_robot->turnTo(Point(0, 1));
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_engine->getCallsToTurnToTarget() > 0);
}

void RobotTest::turnToTarget_orientationReached_reachedTarget()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));

	m_robot->updateSensorData();
	m_robot->turnTo(Point(0, 1));
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->reachedTarget());
}

void RobotTest::turnToTarget_minuteWaited_cantReachTarget()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));

	m_robot->updateSensorData();
	m_robot->turnTo(Point(1, 1));
	m_robot->updateActuators(*m_field);
	m_watchMock->setTime(60);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->cantReachTarget());
}

void RobotTest::updateActuators_tryingToTackleObstacle_engineGotAtLeastOneCallToStop()
{
	m_engine->setTryingToTackleObstacle(true);
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	m_robot->goTo(m_targets);

	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_engine->getCallsToStop() > 0);
}

void RobotTest::updateActuators_tryingToTackleObstacle_targetNotReached()
{
	m_engine->setTryingToTackleObstacle(true);
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	m_robot->goTo(m_targets);

	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->reachedTarget());
}

void RobotTest::updateActuators_tryingToTackleObstacleFromSonar_lastMessageContainssonar()
{
	m_engine->setTryingToTackleObstacle(true);
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	m_robot->goTo(m_targets);
	m_sonar->setIsObstacleDirectInFront(true);

	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	const string &message = m_logger->getLastMessage();
	CPPUNIT_ASSERT(message.find("sonar") != string::npos);
}

void RobotTest::updateActuators_tryingToTackleObstacleFromLidar_lastMessageContainslidar()
{
	m_engine->setTryingToTackleObstacle(true);
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	m_robot->goTo(m_targets);
	m_lidar->setObstacleInFront(true);

	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	const string &message = m_logger->getLastMessage();
	CPPUNIT_ASSERT(message.find("lidar") != string::npos);
}

void RobotTest::updateSensorData_noObstacleDirectInFront_engineGotNoCallToLockForwardMovement()
{
	m_sonar->setIsObstacleDirectInFront(false);

	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_engine->getCallsToLockForwardMovement() == 0);
}

void RobotTest::updateSensorData_noObstacleDirectInFront_engineGotAtLeastOneCallToUnlockForwardMovement()
{
	m_sonar->setIsObstacleDirectInFront(false);

	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_engine->getCallsToUnlockForwardMovement() > 0);
}

void RobotTest::updateSensorData_obstacleDirectInFront_engineGotAtLeastOneCallToLockForwardMovement()
{
	m_sonar->setIsObstacleDirectInFront(true);

	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(1, 0), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_engine->getCallsToLockForwardMovement() > 0);
}

void RobotTest::updateSensorData_0bstacleDirectInFront_engineGotNoCallToUnlockForwardMovement()
{
	m_sonar->setIsObstacleDirectInFront(true);

	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(1, 0), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_engine->getCallsToUnlockForwardMovement() == 0);
}

void RobotTest::getCurrentPosition_position3And4InOdometry_3And4()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(3, 4), 2));

	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	Compare compare(0.0001);
	CPPUNIT_ASSERT(compare.isFuzzyEqual(RobotPosition(Point(3, 4), 2), m_robot->getCurrentPosition()));
}

void RobotTest::reachedTarget_nearlyHitTargetButTookSomeAdditionalWayToStop_false()
{
	m_engine->setReachedTarget(false);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_sonar->setIsObstacleDirectInFront(false);
	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(5, 0), 0));
	m_sonar->setIsObstacleDirectInFront(true);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_engine->setTryingToTackleObstacle(true);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_engine->setTryingToTackleObstacle(false);
	m_odometry->setCurrentPosition(RobotPosition(Point(5.2, 0), 0));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->reachedTarget());
	CPPUNIT_ASSERT(m_robot->cantReachTarget());
}

void RobotTest::cantReachTarget_calledDirectAfterConstructor_false()
{
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->cantReachTarget());
}

void RobotTest::cantReachTarget_drivingTowardsTheTarget_false()
{
	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->cantReachTarget());
}

void RobotTest::cantReachTarget_currentTargetSuddenlyNotPossible_true()
{
	m_engine->setReachedTarget(false);

	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	m_field->setHardObstacles(obstacles);
	m_field->setHardAndVisibleObstacles(obstacles);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->cantReachTarget());
}

void RobotTest::cantReachTarget_notPossibleAnymoreDuringDriving_true()
{
	m_engine->setReachedTarget(true);
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	m_field->setHardObstacles(obstacles);
	m_field->setHardAndVisibleObstacles(obstacles);

	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->cantReachTarget());
}

void RobotTest::cantReachTarget_onlyLastTargetNotPossibleToReach_false()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	m_field->setSoftObstacles(obstacles);

	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_robot->updateSensorData();
	m_targets.clear();
	m_targets.push_back(RobotPosition(Point(-10, 0), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->cantReachTarget());
}

void RobotTest::cantReachTarget_updateTwiceCalled_true()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	m_field->setHardObstacles(obstacles);
	m_field->setHardAndVisibleObstacles(obstacles);

	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->cantReachTarget());
}

void RobotTest::cantReachTarget_newTargetSet_false()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	m_field->setSoftObstacles(obstacles);

	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_robot->updateSensorData();
	m_targets.clear();
	m_targets.push_back(RobotPosition(Point(-10, 0), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->cantReachTarget());
}

void RobotTest::cantReachTarget_collectPuckInFrontCalled_false()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	m_field->setSoftObstacles(obstacles);

	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_lidar->setPuckCollectable(true);
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(0.4, 0));
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->cantReachTarget());
}

void RobotTest::cantReachTarget_turnToCalled_false()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	m_field->setSoftObstacles(obstacles);

	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_robot->updateSensorData();
	m_robot->turnTo(Point(-10, 0));
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->cantReachTarget());
}

void RobotTest::cantReachTarget_leavePuckCalled_false()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(10, 0), 2));
	m_field->setSoftObstacles(obstacles);

	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_robot->updateSensorData();
	m_robot->leaveCollectedPuck();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->cantReachTarget());
}

void RobotTest::cantReachTarget_stuckAtObstacle_true()
{
	m_robot->updateSensorData();
	m_targets.push_back(RobotPosition(Point(10, 0), 0));
	m_robot->goTo(m_targets);
	m_robot->updateActuators(*m_field);
	m_engine->setTryingToTackleObstacle(true);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->cantReachTarget());
}

void RobotTest::isPuckCollected_lidarSaysNo_false()
{
	m_lidar->setPuckCollected(false);

	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->isPuckCollected());
}

void RobotTest::isPuckCollected_lidarSaysYesVeryShort_false()
{
	m_lidar->setPuckCollected(false);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_lidar->setPuckCollected(true);
	m_watchMock->setTime(0.1);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->isPuckCollected());
}

void RobotTest::isPuckCollected_lidarSaysYesLong_true()
{
	m_lidar->setPuckCollected(false);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_lidar->setPuckCollected(true);
	m_watchMock->setTime(1);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->isPuckCollected());
}

void RobotTest::isPuckCollectable_lidarSaysNo_false()
{
	m_lidar->setPuckCollectable(false);

	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->isPuckCollectable());
}

void RobotTest::isPuckCollectable_lidarSaysYes_true()
{
	m_lidar->setPuckCollectable(true);

	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->isPuckCollectable());
}

void RobotTest::collectPuckInFront_puckAhead_notStuckAtObstacle()
{
	Hardware::RobotMock *hardwareRobot = new Hardware::RobotMock();
	Hardware::LidarMock &lidar = hardwareRobot->getLidarMock();
	Hardware::SonarMock &sonar = hardwareRobot->getSonarMock();
	lidar.readDataFromFile("resources/testfiles/lidar_34.txt");
	sonar.readDataFromFile("resources/testfiles/sonar_3.txt");
	DataAnalysis::DataAnalyser *dataAnalyser = new DataAnalysis::DataAnalyserImpl(hardwareRobot, *m_watchMock);
	RobotImpl robot(dataAnalyser, new RouterMock(), *m_watchMock, *m_logger, true);

	robot.updateSensorData();
	robot.collectPuckInFront(Point(0.4, 0));
	robot.updateActuators(*m_field);

	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}

void RobotTest::collectPuckInFront_puckAheadAndStartedToMove_notStuckAtObstacle()
{
	Hardware::RobotMock *hardwareRobot = new Hardware::RobotMock();
	Hardware::LidarMock &lidar = hardwareRobot->getLidarMock();
	Hardware::SonarMock &sonar = hardwareRobot->getSonarMock();
	lidar.readDataFromFile("resources/testfiles/lidar_34.txt");
	sonar.readDataFromFile("resources/testfiles/sonar_3.txt");
	DataAnalysis::DataAnalyser *dataAnalyser = new DataAnalysis::DataAnalyserImpl(hardwareRobot, *m_watchMock);
	RobotImpl robot(dataAnalyser, new RouterMock(), *m_watchMock, *m_logger, true);

	robot.updateSensorData();
	robot.collectPuckInFront(Point(0.4, 0));
	robot.updateActuators(*m_field);
	robot.updateSensorData();
	robot.updateActuators(*m_field);

	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}

void RobotTest::collectPuckInFront_puckAheadAndAlreadyUpdatedTheEngine_notStuckAtObstacle()
{
	Hardware::RobotMock *hardwareRobot = new Hardware::RobotMock();
	Hardware::LidarMock &lidar = hardwareRobot->getLidarMock();
	Hardware::SonarMock &sonar = hardwareRobot->getSonarMock();
	lidar.readDataFromFile("resources/testfiles/lidar_34.txt");
	sonar.readDataFromFile("resources/testfiles/sonar_3.txt");
	DataAnalysis::DataAnalyser *dataAnalyser = new DataAnalysis::DataAnalyserImpl(hardwareRobot, *m_watchMock);
	RobotImpl robot(dataAnalyser, new RouterMock(), *m_watchMock, *m_logger, true);

	robot.updateSensorData();
	robot.updateActuators(*m_field);
	robot.updateSensorData();
	robot.collectPuckInFront(Point(0.4, 0));
	robot.updateActuators(*m_field);

	CPPUNIT_ASSERT(!robot.stuckAtObstacle());
}

void RobotTest::collectPuckInFront_puckCollectedButEngineTargetNotReached_reachedTarget()
{
	m_engine->setReachedTarget(false);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_lidar->setPuckCollectable(true);
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(0.4, 0));
	m_robot->updateActuators(*m_field);
	m_watchMock->setTime(1);
	m_lidar->setPuckCollectable(true);
	m_lidar->setPuckCollected(true);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->reachedTarget());
}

void RobotTest::collectPuckInFront_puckNotYetCollected_notReachedTarget()
{
	m_engine->setReachedTarget(false);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_lidar->setPuckCollectable(true);
	m_lidar->setPuckCollected(false);
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(0.4, 0));
	m_robot->updateActuators(*m_field);
	m_lidar->setPuckCollectable(true);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->reachedTarget());
}

void RobotTest::collectPuckInFront_drivenToFarAndPuckNotYetCollected_notReachedTarget()
{
	m_engine->setReachedTarget(false);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_lidar->setPuckCollectable(true);
	m_lidar->setPuckCollected(false);
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(0.4, 0));
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(1, 0), 0));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->reachedTarget());
}

void RobotTest::collectPuckInFront_drivenToFarAndPuckNotYetCollected_cantReachTarget()
{
	m_engine->setReachedTarget(false);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_lidar->setPuckCollectable(true);
	m_lidar->setPuckCollected(false);
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(0.4, 0));
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(1, 0), 0));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->cantReachTarget());
}

void RobotTest::collectPuckInFront_noPuckAhead_cantReachTarget()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_lidar->setPuckCollectable(false);
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(0.4, 0));
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->cantReachTarget());
}

void RobotTest::collectPuckInFront_puckAhead_canReachTarget()
{
	m_lidar->setPuckCollectable(true);
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(0.4, 0));
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->cantReachTarget());
}

void RobotTest::collectPuckInFront_differentPuckAheadThanDesiredOne_cantReachTarget()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	m_lidar->setPuckCollectable(false);
	m_lidar->setPuckCollectable(true);
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(0.4, 0));
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_lidar->setPuckCollectable(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_robot->updatePuckPosition(Point(0.4, -0.5));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->cantReachTarget());
}

void RobotTest::collectPuckInFront_validPuck_isCollectingPuck()
{
	m_lidar->setPuckCollectable(true);
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(0.4, 0));
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->isCollectingPuck());
}

void RobotTest::collectPuckInFront_puckCollected_isNotCollectingPuck()
{
	m_lidar->setPuckCollectable(true);
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(0.4, 0));
	m_robot->updateActuators(*m_field);
	m_watchMock->setTime(1);
	m_lidar->setPuckCollected(true);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->isCollectingPuck());
}

void RobotTest::collectPuckInFront_lookingLeftAndPuckAhead_canReachTarget()
{
	m_lidar->setPuckCollectable(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(-0.4, 0));
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->cantReachTarget());
}

void RobotTest::collectPuckInFront_orientationWrongAtBegin_canReachTarget()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(0, 0.4));
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->cantReachTarget());
}

void RobotTest::collectPuckInFront_orientationWrongAtBegin_engineGotCallToTurnTo()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(0, 0.4));
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_engine->getCallsToTurnToTarget() == 1);
}

void RobotTest::collectPuckInFront_orientationWrongAtBeginAndOrientationReached_engineGotCallToGoToStraightSlowly()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(0, 0.4));
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	m_engine->setReachedTarget(true);
	m_lidar->setPuckCollectable(true);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_engine->getCallsToGoToStraightSlowly() == 1);
}

void RobotTest::collectPuckInFront_minuteWaited_cantReachTarget()
{
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(0, 0.4));
	m_robot->updateActuators(*m_field);
	m_watchMock->setTime(60);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->cantReachTarget());
}

void RobotTest::collectPuckInFront_sonarDetectsCollision_notStuckAtObstacle()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));

	m_lidar->setPuckCollectable(true);
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(0.4, 0));
	m_robot->updateActuators(*m_field);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_sonar->setIsObstacleDirectInFront(true);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->stuckAtObstacle());
	CPPUNIT_ASSERT(!m_robot->cantReachTarget());
}

void RobotTest::updatePuckPosition_newPositionOfPuck_goToStraightSlowlyCalledTwice()
{
	m_lidar->setPuckCollectable(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(4, 5), 0));
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(4.2, 5));
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_robot->updateSensorData();
	m_robot->updatePuckPosition(Point(4.3, 5));
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_engine->getCallsToGoToStraightSlowly() == 2);
}

void RobotTest::leaveCollectedPuck_drivenFarEnoughBack_reachedTarget()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_robot->updateSensorData();
	m_robot->leaveCollectedPuck();
	m_robot->updateActuators(*m_field);
	m_odometry->setCurrentPosition(RobotPosition(Point(-0.2, 0), 0));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->reachedTarget());
}

void RobotTest::leaveCollectedPuck_minuteWaited_cantReachTarget()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle(0)));

	m_robot->updateSensorData();
	m_robot->leaveCollectedPuck();
	m_robot->updateActuators(*m_field);
	m_watchMock->setTime(60);
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->cantReachTarget());
}

void RobotTest::isRotating_waiting_false()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->isRotating());
}

void RobotTest::isRotating_turnTo_true()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_robot->updateSensorData();
	m_robot->turnTo(Point(4, 5));
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->isRotating());
}

void RobotTest::isRotating_firstPhaseOfCollectingPuck_true()
{
	m_lidar->setPuckCollectable(false);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(0, 0.4));
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->isRotating());
}

void RobotTest::isRotating_secondPhaseOfCollectingPuck_false()
{
	m_lidar->setPuckCollectable(false);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getHalfRotation()));
	m_robot->updateSensorData();
	m_robot->collectPuckInFront(Point(0, 0.4));
	m_robot->updateActuators(*m_field);
	m_lidar->setPuckCollectable(false);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->isRotating());
}

void RobotTest::isRotating_leavingPuck_false()
{
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), 0));
	m_robot->updateSensorData();
	m_robot->leaveCollectedPuck();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(!m_robot->isRotating());
}

void RobotTest::isRotating_turningPartOfGoTo_true()
{
	list<RobotPosition> targets;
	targets.push_back(RobotPosition(Point(10, 0), Angle(1)));
	m_engine->setIsMoving(false);

	m_robot->goTo(targets);

	CPPUNIT_ASSERT(m_robot->isRotating());
}

void RobotTest::isRotating_drivingPartOfGoToAndTurningFast_true()
{
	list<RobotPosition> targets;
	targets.push_back(RobotPosition(Point(0, 10), Angle(1)));

	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_robot->goTo(targets);
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_engine->setCurrentRotationSpeed(10);

	CPPUNIT_ASSERT(m_robot->isRotating());
}

void RobotTest::isRotating_drivingPartOfGoToAndTurningSlow_true()
{
	list<RobotPosition> targets;
	targets.push_back(RobotPosition(Point(0, 10), Angle(1)));

	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_robot->goTo(targets);
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);
	m_engine->setCurrentRotationSpeed(0.05);

	CPPUNIT_ASSERT(!m_robot->isRotating());
}

void RobotTest::isMoving_drivingStraightPart_true()
{
	list<RobotPosition> targets;
	targets.push_back(RobotPosition(Point(0, 10), Angle(1)));

	m_engine->setReachedTarget(true);
	m_robot->updateSensorData();
	m_robot->goTo(targets);
	m_robot->updateActuators(*m_field);
	m_engine->setReachedTarget(true);
	m_odometry->setCurrentPosition(RobotPosition(Point(0, 0), Angle::getQuarterRotation()));
	m_robot->updateSensorData();
	m_robot->updateActuators(*m_field);

	CPPUNIT_ASSERT(m_robot->isMoving());
}

void RobotTest::isMoving_drivingTurningPart_true()
{
	list<RobotPosition> targets;
	targets.push_back(RobotPosition(Point(0, 10), Angle(1)));
	m_engine->setIsMoving(false);

	m_robot->goTo(targets);

	CPPUNIT_ASSERT(m_robot->isMoving());
}

void RobotTest::isMoving_turningTo_true()
{
	m_engine->setIsMoving(false);

	m_robot->turnTo(Point(1, 1));

	CPPUNIT_ASSERT(m_robot->isMoving());
}

void RobotTest::isMoving_waitingAndEngineSaysNotMoving_false()
{
	m_engine->setIsMoving(false);

	CPPUNIT_ASSERT(!m_robot->isMoving());
}

void RobotTest::isMoving_waitingAndEngineSaysMoving_true()
{
	m_engine->setIsMoving(true);

	CPPUNIT_ASSERT(m_robot->isMoving());
}

void RobotTest::isMoving_leavingPuck_true()
{
	m_engine->setIsMoving(false);

	m_robot->leaveCollectedPuck();

	CPPUNIT_ASSERT(m_robot->isMoving());
}

void RobotTest::isMoving_collectingPuck_true()
{
	m_engine->setIsMoving(false);

	m_robot->collectPuckInFront(Point(1, 0));

	CPPUNIT_ASSERT(m_robot->isMoving());
}

void RobotTest::isOrientationDifferenceSmallEnoughForSmoothTurn_currentSpeedZeroAndEighthRotation_true()
{
	m_engine->setCurrentSpeed(0);

	CPPUNIT_ASSERT(m_robot->isOrientationDifferenceSmallEnoughForSmoothTurn(Angle::getEighthRotation()));
}

void RobotTest::isOrientationDifferenceSmallEnoughForSmoothTurn_currentSpeedMaxAndEighthRotation_false()
{
	m_engine->setCurrentSpeed(0.5);

	CPPUNIT_ASSERT(!m_robot->isOrientationDifferenceSmallEnoughForSmoothTurn(Angle::getEighthRotation()));
}

void RobotTest::isOrientationDifferenceSmallEnoughForSmoothTurn_currentSpeedMaxVerySmallRotation_true()
{
	m_engine->setCurrentSpeed(0.5);

	CPPUNIT_ASSERT(m_robot->isOrientationDifferenceSmallEnoughForSmoothTurn(Angle::getEighthRotation()/3));
}
