#include "layer/autonomous/robotimpl.h"
#include "layer/dataanalysis/dataanalyser.h"
#include "layer/dataanalysis/engine.h"
#include "layer/dataanalysis/sonar.h"
#include "layer/dataanalysis/odometry.h"
#include "layer/dataanalysis/lidar.h"
#include "common/compare.h"
#include "layer/autonomous/fieldimpl.h"
#include <iostream>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Layer;
using namespace std;

RobotImpl::RobotImpl(DataAnalysis::DataAnalyser *dataAnalyser) :
	m_dataAnalyser(dataAnalyser),
	m_tryingToTackleObstacle(false),
	m_collectingPuck(false)
{ }

RobotImpl::~RobotImpl()
{
	delete m_dataAnalyser;
}

void RobotImpl::goTo(const RoboHockey::Common::Point &position)
{
	m_collectingPuck = false;
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();

	//! @todo imlement a router to find a path to the target without tackling obstacles
	engine.goToStraight(position);
}

void RobotImpl::turnTo(const Point &position)
{
	m_collectingPuck = false;
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	engine.turnToTarget(position);
}

bool RobotImpl::stuckAtObstacle()
{
	return m_tryingToTackleObstacle;
}

bool RobotImpl::reachedTarget()
{
	//! @todo won't be enough if we try to reach the target in more than one step
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	return engine.reachedTarget();
}

void RobotImpl::updateActuators()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	DataAnalysis::Sonar &sonar = m_dataAnalyser->getSonar();
	const DataAnalysis::Lidar &lidar = m_dataAnalyser->getLidar();
	m_dataAnalyser->updateActuators();
	double speed = engine.getCurrentSpeed();

	if ((sonar.isObstacleDirectInFront(speed) || lidar.isObstacleInFront(speed)) && !m_collectingPuck)
		engine.lockForwardMovement();
	else
		engine.unlockForwardMovement();

	m_tryingToTackleObstacle = engine.tryingToTackleObstacle();
	if (m_tryingToTackleObstacle)
		engine.stop();
}

void RobotImpl::updateSensorData()
{
	m_dataAnalyser->updateSensorData();
}

void RobotImpl::stop()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	engine.stop();
}

void RobotImpl::collectPuckInFront()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	RobotPosition ownPosition = getCurrentPosition();

	Point puck(0.2,0);
	puck.rotate(ownPosition.getOrientation());
	Point targetPosition = ownPosition.getPosition() + puck;

	m_collectingPuck = true;
	engine.goToStraightSlowly(targetPosition);
}

void RobotImpl::leaveCollectedPuck()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	RobotPosition ownPosition = getCurrentPosition();

	Point puck(-0.2,0);
	puck.rotate(ownPosition.getOrientation());
	Point targetPosition = ownPosition.getPosition() + puck;

	m_collectingPuck = false;
	engine.goToStraightSlowlyBack(targetPosition);
}

bool RobotImpl::isMoving()
{
	return m_dataAnalyser->getEngine().isMoving();
}

void RobotImpl::turnAround()
{
	m_collectingPuck = false;
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	engine.turnAround();
}

RobotPosition RobotImpl::getCurrentPosition()
{
	DataAnalysis::Odometry &odometry = m_dataAnalyser->getOdometry();
	return odometry.getCurrentPosition();
}

Point RobotImpl::getCurrentTarget() const
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	return engine.getCurrentTarget();
}

RobotImpl::RobotImpl(const RobotImpl &)
{ }

void RobotImpl::operator=(const RobotImpl &)
{ }
