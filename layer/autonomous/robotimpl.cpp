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
#include <math.h>
#include <assert.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Layer;
using namespace std;

RobotImpl::RobotImpl(DataAnalysis::DataAnalyser *dataAnalyser) :
	m_robotWidth(0.38),
	m_maximumDistanceToCollectPuck(0.75),
	m_maximumAngleToCollectPuck(10.0/180*M_PI),
	m_dataAnalyser(dataAnalyser),
	m_tryingToTackleObstacle(false),
	m_cantReachTarget(false),
	m_currentRoute(0),
	m_state(RobotStateWaiting),
	m_stateChanged(false)
{ }

RobotImpl::~RobotImpl()
{
	delete m_dataAnalyser;
	m_dataAnalyser = 0;
	clearRoute();
}

void RobotImpl::goTo(const Point &position)
{
	changeIntoState(RobotStateDriving);
	m_currentTarget = position;
}

void RobotImpl::turnTo(const Point &position)
{
	changeIntoState(RobotStateTurnTo);
	m_currentTarget = position;
}

bool RobotImpl::stuckAtObstacle()
{
	return m_tryingToTackleObstacle;
}

bool RobotImpl::reachedTarget()
{
	return m_state == RobotStateWaiting && !m_cantReachTarget;
}

void RobotImpl::updateEngineForDriving(const Field &field)
{
	updateRoute(getCurrentPosition().getPosition(), field);

	//! If there is no route at this point we can't reach the target.
	if (m_currentRoute == 0)
		m_cantReachTarget = true;
	else
		updateTargetOfEngineForRoute();
}

void RobotImpl::updateEngineForWaiting()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	engine.stop();
}

void RobotImpl::updateEngineForCollectingPuck()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	const DataAnalysis::Lidar &lidar = m_dataAnalyser->getLidar();
	bool lidarPuckCollectable = lidar.isPuckCollectable(m_maximumDistanceToCollectPuck, m_maximumAngleToCollectPuck);
	bool fromTargetPositionPuckCollectable = isCurrentTargetPuckCollectable();

	if (	!lidarPuckCollectable ||
			!fromTargetPositionPuckCollectable)
	{
		m_cantReachTarget = true;
		return;
	}

	Point currentPosition = getCurrentPosition().getPosition();
	double drivenDistance = m_startPosition.distanceTo(currentPosition);

	if (isPuckCollected())
	{
		changeIntoState(RobotStateWaiting);
		return;
	}
	else if (drivenDistance > m_maximumDistanceToCollectPuck)
	{
		m_cantReachTarget = true;
		return;
	}

	if (m_stateChanged || m_puckPositionChanged)
		engine.goToStraightSlowly(m_currentTarget);
}

void RobotImpl::updateEngineForLeavingPuck()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();

	if (m_stateChanged)
	{
		RobotPosition ownPosition = getCurrentPosition();
		Point puck(-0.2, 0);
		puck.rotate(ownPosition.getOrientation());
		Point targetPosition = ownPosition.getPosition() + puck;
		engine.goToStraightSlowlyBack(targetPosition);
	}
	else if (engine.reachedTarget())
		changeIntoState(RobotStateWaiting);
}

void RobotImpl::updateEngineForTurnAround()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();

	if (m_stateChanged)
		engine.turnAround();
	else if (engine.reachedTarget())
		changeIntoState(RobotStateWaiting);
}

void RobotImpl::updateEngineForTurnTo()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();

	if (m_stateChanged)
		engine.turnToTarget(m_currentTarget);
	else if (engine.reachedTarget())
		changeIntoState(RobotStateWaiting);
}

void RobotImpl::updateEngine(const Field &field)
{
	if (m_cantReachTarget || m_tryingToTackleObstacle)
	{
		DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
		engine.stop();
		return;
	}

	switch(m_state)
	{
	case RobotStateDriving:
		updateEngineForDriving(field);
		break;
	case RobotStateWaiting:
		updateEngineForWaiting();
		break;
	case RobotStateCollectingPuck:
		updateEngineForCollectingPuck();
		break;
	case RobotStateLeavingPuck:
		updateEngineForLeavingPuck();
		break;
	case RobotStateTurnAround:
		updateEngineForTurnAround();
		break;
	case RobotStateTurnTo:
		updateEngineForTurnTo();
		break;
	}
}

void RobotImpl::detectCollisions()
{
	DataAnalysis::Sonar &sonar = m_dataAnalyser->getSonar();
	const DataAnalysis::Lidar &lidar = m_dataAnalyser->getLidar();
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	double speed = engine.getCurrentSpeed();
	bool obstacleInFrontBySonar = sonar.isObstacleDirectInFront(speed);
	bool obstacleInFrontByLidar = lidar.isObstacleInFront(speed);
	bool lockForwardMovement = (obstacleInFrontBySonar && enableCollisionDetectionWithSonar()) || obstacleInFrontByLidar;

	if (lockForwardMovement)
		engine.lockForwardMovement();
	else
		engine.unlockForwardMovement();

	m_dataAnalyser->updateActuators();

	if (engine.tryingToTackleObstacle())
		m_tryingToTackleObstacle = true;
}

bool RobotImpl::enableCollisionDetectionWithSonar() const
{
	bool result;

	switch(m_state)
	{
	case RobotStateCollectingPuck:
		result = false;
		break;
	case RobotStateDriving:
	case RobotStateLeavingPuck:
	case RobotStateTurnTo:
	case RobotStateTurnAround:
	case RobotStateWaiting:
		result = true;
		break;
	}

	return result;
}

void RobotImpl::changeIntoState(RobotState state)
{
	clearRoute();
	m_currentTarget = Point();
	m_cantReachTarget = false;
	m_tryingToTackleObstacle = false;
	m_state = state;
	m_stateChanged = true;
}

bool RobotImpl::isCurrentTargetPuckCollectable() const
{
	RobotPosition currentPosition = getCurrentPosition();
	Angle orientation(currentPosition.getPosition(), m_currentTarget);
	double distance = m_currentTarget.distanceTo(currentPosition.getPosition());
	orientation.abs();

	return	distance < m_maximumDistanceToCollectPuck &&
			orientation.getValueBetweenMinusPiAndPi() < m_maximumAngleToCollectPuck.getValueBetweenMinusPiAndPi();
}

void RobotImpl::updateActuators(const Field &field)
{
	detectCollisions();
	updateEngine(field);
}

void RobotImpl::updateSensorData()
{
	m_stateChanged = false;
	m_puckPositionChanged = false;
	m_dataAnalyser->updateSensorData();
}

void RobotImpl::stop()
{
	changeIntoState(RobotStateWaiting);
}

void RobotImpl::collectPuckInFront(const Point &puckPosition)
{
	changeIntoState(RobotStateCollectingPuck);
	m_currentTarget = puckPosition;
	m_startPosition = getCurrentPosition().getPosition();
}

void RobotImpl::updatePuckPosition(const Point &puckPosition)
{
	assert(m_state == RobotStateCollectingPuck);
	m_currentTarget = puckPosition;
	m_puckPositionChanged = true;
}

void RobotImpl::leaveCollectedPuck()
{
	changeIntoState(RobotStateLeavingPuck);
}

bool RobotImpl::isMoving()
{
	return m_dataAnalyser->getEngine().isMoving();
}

void RobotImpl::turnAround()
{
	changeIntoState(RobotStateTurnAround);
}

RobotPosition RobotImpl::getCurrentPosition() const
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
	return m_cantReachTarget || m_tryingToTackleObstacle;
}

bool RobotImpl::isPuckCollected() const
{
	const DataAnalysis::Lidar &lidar = m_dataAnalyser->getLidar();
	return lidar.isPuckCollected();
}

bool RobotImpl::isPuckCollectable() const
{
	const DataAnalysis::Lidar &lidar = m_dataAnalyser->getLidar();
	return lidar.isPuckCollectable(m_maximumDistanceToCollectPuck, m_maximumAngleToCollectPuck);
}

bool RobotImpl::isCollectingPuck() const
{
	return m_state == RobotStateCollectingPuck;
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

void RobotImpl::updateTargetOfEngineForRoute()
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
	m_robotWidth(0),
	m_maximumDistanceToCollectPuck(0),
	m_maximumAngleToCollectPuck(0)
{ }

void RobotImpl::operator=(const RobotImpl &)
{ }
