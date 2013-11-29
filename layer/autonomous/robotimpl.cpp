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

	if (m_state == RobotStateDriving)
	{
		updateRoute(ownPosition.getPosition(), field);

		//! If there is no route at this point we can't reach the target.
		if (m_currentRoute == 0)
		{
			m_cantReachTarget = true;
			stop();
		}
		else
		{
			m_cantReachTarget = false;
			updateTargetForEngine();
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
	vector<Circle> obstacles = field.getAllObstacles();

	if (isRouteFeasible(ownPosition, obstacles))
		return;

	//! If the current route is not feasible anymore we try to create a new one.
	clearRoute();
	m_currentRoute = new Route(m_robotWidth);
	*m_currentRoute = router.calculateRoute(ownPosition, m_currentTarget);

	//! If this one is now feasible we go towards the first point.
	if (isRouteFeasible(ownPosition, obstacles))
		goToFirstPointOfRoute();
	//! If the route is still not feasible we clear it to signal that something went wrong.
	else
		clearRoute();
}

bool RobotImpl::isRouteFeasible(const Point &ownPosition, const vector<Circle> &obstacles) const
{
	if (m_currentRoute == 0)
		return false;

	if (!m_currentRoute->isValid())
		return false;

	Path path(ownPosition, m_currentRoute->getFirstPoint(), m_robotWidth);
	return !path.intersectsWith(obstacles) && !m_currentRoute->intersectsWith(obstacles);
}

void RobotImpl::goToFirstPointOfRoute()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	Point target = m_currentRoute->getFirstPoint();
	engine.goToStraight(target);
}

void RobotImpl::updateTargetForEngine()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();

	if (engine.reachedTarget())
	{
		m_currentRoute->removeFirstPoint();

		if (m_currentRoute->getPointCount() == 0)
			stop();
		else
			goToFirstPointOfRoute();
	}
}

RobotImpl::RobotImpl(const RobotImpl &) :
	m_robotWidth(0)
{ }

void RobotImpl::operator=(const RobotImpl &)
{ }
