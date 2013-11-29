#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/route.h"
#include "layer/autonomous/router.h"
#include "layer/dataanalysis/dataanalyser.h"
#include "layer/dataanalysis/engine.h"
#include "layer/dataanalysis/sonar.h"
#include "layer/dataanalysis/odometry.h"
#include "layer/dataanalysis/lidar.h"
#include "common/compare.h"
#include "common/path.h"
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
	m_currentRoute(0),
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
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	DataAnalysis::Odometry &odometry = m_dataAnalyser->getOdometry();
	RobotPosition ownPosition = odometry.getCurrentPosition();

	//! @todo clean this mess up
	if (m_state == RobotStateDriving)
	{
		updateRoute(ownPosition.getPosition(), field);

		if (m_currentRoute != 0)
		{
			m_cantReachTarget = false;

			if (engine.reachedTarget())
			{
				m_currentRoute->removeFirstPoint();

				if (m_currentRoute->getPointCount() == 0)
					stop();
				else
				{
					Point newTarget = m_currentRoute->getFirstPoint();
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
	else
		m_cantReachTarget = false;

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
	if (engine.reachedTarget() && m_currentRoute == 0)
		m_state = RobotStateWaiting;
}

void RobotImpl::stop()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	engine.stop();
	m_state = RobotStateWaiting;
	clearRoute();
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
	return m_cantReachTarget;
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

void RobotImpl::updateRoute(const Point &ownPosition, const Field &field)
{
	Router router(m_robotWidth, field);
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	vector<Circle> obstacles = field.getAllObstacles();
	bool currentRouteValid = m_currentRoute != 0 && m_currentRoute->isValid();

	if (currentRouteValid && m_currentRoute->getPointCount() > 0)
	{
		Path path(ownPosition, m_currentRoute->getFirstPoint(), m_robotWidth);
		if (path.intersectsWith(obstacles) || m_currentRoute->intersectsWith(obstacles))
			currentRouteValid = false;
	}

	if (!currentRouteValid)
	{
		clearRoute();
		m_currentRoute = new Route(m_robotWidth);
		*m_currentRoute = router.calculateRoute(ownPosition, m_currentTarget);
		currentRouteValid = m_currentRoute->isValid();

		if (currentRouteValid)
		{
			Path path(ownPosition, m_currentRoute->getFirstPoint(), m_robotWidth);
			if (path.intersectsWith(obstacles) || m_currentRoute->intersectsWith(obstacles))
				currentRouteValid = false;
		}

		if (currentRouteValid)
		{
			Point newTarget = m_currentRoute->getFirstPoint();
			engine.goToStraight(newTarget);
		}
		else
			clearRoute();
	}
}

RobotImpl::RobotImpl(const RobotImpl &) :
	m_robotWidth(0)
{ }

void RobotImpl::operator=(const RobotImpl &)
{ }
