#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/route.h"
#include "layer/autonomous/router.h"
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
	m_robotWidth(0.38),
	m_dataAnalyser(dataAnalyser),
	m_tryingToTackleObstacle(false),
	m_cantReachTarget(false),
	m_currentRoute(new Route(m_robotWidth)),
	m_state(RobotStateWaiting)
{ }

RobotImpl::~RobotImpl()
{
	delete m_dataAnalyser;
	m_dataAnalyser = 0;
	clearRoute();
}

void RobotImpl::goTo(const Point &position)
{
	clearRoute();
	m_currentTarget = position;
	m_state = RobotStateDriving;
}

void RobotImpl::turnTo(const Point &position)
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	engine.turnToTarget(position);
	m_state = RobotStateTurning;
}

bool RobotImpl::stuckAtObstacle()
{
	return m_tryingToTackleObstacle;
}

bool RobotImpl::reachedTarget()
{
	return m_state == RobotStateWaiting && !m_cantReachTarget;
}

void RobotImpl::updateActuators(const Field &field)
{
	Router router(m_robotWidth, field);
	vector<Circle> obstacles = field.getAllObstacles();
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	DataAnalysis::Odometry &odometry = m_dataAnalyser->getOdometry();
	RobotPosition ownPosition = odometry.getCurrentPosition();

	if (m_state == RobotStateDriving)
	{
		if (m_currentRoute == 0 || m_currentRoute->intersectsWith(obstacles))
		{
			m_currentRoute = new Route(m_robotWidth);
			*m_currentRoute = router.calculateRoute(ownPosition.getPosition(), m_currentTarget);

			if (!m_currentRoute->isValid())
				clearRoute();
		}

		if (m_currentRoute != 0)
		{
			m_cantReachTarget = false;

			if (engine.reachedTarget())
			{
				if (m_currentRoute->getPointCount() == 0)
					stop();
				else
				{
					Point newTarget = m_currentRoute->getFirstPoint();
					m_currentRoute->removeFirstPoint();
					engine.goToStraight(newTarget);
				}
			}
		}
		else
		{
			m_cantReachTarget = true;
			stop();
		}
	}

	DataAnalysis::Sonar &sonar = m_dataAnalyser->getSonar();
	const DataAnalysis::Lidar &lidar = m_dataAnalyser->getLidar();
	double speed = engine.getCurrentSpeed();
	bool obstacleInFrontBySonar = sonar.isObstacleDirectInFront(speed);
	bool obstacleInFrontByLidar = lidar.isObstacleInFront(speed);
	bool lockForwardMovement = (obstacleInFrontBySonar && m_state != RobotStateCollectingPuck) || obstacleInFrontByLidar;

	if (lockForwardMovement)
		engine.lockForwardMovement();
	else
		engine.unlockForwardMovement();

	m_dataAnalyser->updateActuators();

	m_tryingToTackleObstacle = engine.tryingToTackleObstacle();
	if (m_tryingToTackleObstacle)
		stop();
}

void RobotImpl::updateSensorData()
{
	m_dataAnalyser->updateSensorData();
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();

	if (engine.reachedTarget())
		m_state = RobotStateWaiting;
}

void RobotImpl::stop()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	engine.stop();
	m_state = RobotStateWaiting;
}

void RobotImpl::collectPuckInFront()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	RobotPosition ownPosition = getCurrentPosition();

	Point puck(0.2,0);
	puck.rotate(ownPosition.getOrientation());
	Point targetPosition = ownPosition.getPosition() + puck;

	m_state = RobotStateCollectingPuck;
	engine.goToStraightSlowly(targetPosition);
}

void RobotImpl::leaveCollectedPuck()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	RobotPosition ownPosition = getCurrentPosition();

	Point puck(-0.2,0);
	puck.rotate(ownPosition.getOrientation());
	Point targetPosition = ownPosition.getPosition() + puck;

	m_state = RobotStateLeavingPuck;
	engine.goToStraightSlowlyBack(targetPosition);
}

bool RobotImpl::isMoving()
{
	return m_dataAnalyser->getEngine().isMoving();
}

void RobotImpl::turnAround()
{
	m_state = RobotStateTurning;
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

bool RobotImpl::cantReachTarget() const
{
	return false;
}

bool RobotImpl::isPuckCollected() const
{
	const DataAnalysis::Lidar &lidar = m_dataAnalyser->getLidar();
	return lidar.isPuckCollected();
}

bool RobotImpl::isPuckCollectable() const
{
	const DataAnalysis::Lidar &lidar = m_dataAnalyser->getLidar();
	return lidar.isPuckCollectable();
}

void RobotImpl::clearRoute()
{
	delete m_currentRoute;
	m_currentRoute = 0;
}

RobotImpl::RobotImpl(const RobotImpl &) :
	m_robotWidth(0)
{ }

void RobotImpl::operator=(const RobotImpl &)
{ }
