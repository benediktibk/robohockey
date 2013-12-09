#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/route.h"
#include "layer/autonomous/router.h"
#include "layer/autonomous/fieldimpl.h"
#include "layer/dataanalysis/dataanalyser.h"
#include "layer/dataanalysis/engine.h"
#include "layer/dataanalysis/sonar.h"
#include "layer/dataanalysis/odometry.h"
#include "layer/dataanalysis/lidar.h"
#include "common/compare.h"
#include "common/path.h"
#include <math.h>
#include <assert.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Layer;
using namespace std;

RobotImpl::RobotImpl(DataAnalysis::DataAnalyser *dataAnalyser, Router *router) :
	m_robotWidth(0.38),
	m_maximumDistanceToCollectPuck(0.75),
	m_maximumAngleToCollectPuck(10.0/180*M_PI),
	m_dataAnalyser(dataAnalyser),
	m_router(router),
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
	delete m_router;
	m_router = 0;
	clearRoute();
}

void RobotImpl::goTo(const Point &position)
{
	clearRoute();
	changeIntoState(RobotStateDrivingTurningPart);
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

void RobotImpl::updateEngineForDrivingStraightPart(const Field &field)
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	bool routeChanged = updateRoute(field);

	//! If there is no route at this point we can't reach the target.
	if (m_currentRoute == 0)
		m_cantReachTarget = true;
	else
	{
		if (routeChanged)
			changeIntoState(RobotStateDrivingTurningPart);
		else if (engine.reachedTarget())
		{
			m_currentRoute->removeFirstPoint();

			if (m_currentRoute->getPointCount() == 1)
				changeIntoState(RobotStateWaiting);
			else
			{
				changeIntoState(RobotStateDrivingTurningPart);
				engine.turnToTarget(m_currentRoute->getSecondPoint());
			}
		}
	}
}

void RobotImpl::updateEngineForDrivingTurningPart(const Field &field)
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	bool routeChanged = updateRoute(field);

	if (m_currentRoute == 0)
		m_cantReachTarget = true;
	else
	{
		if (m_stateChanged || routeChanged)
			engine.turnToTarget(m_currentRoute->getSecondPoint());
		else if (engine.reachedTarget())
		{
			changeIntoState(RobotStateDrivingStraightPart);
			engine.goToStraight(m_currentRoute->getSecondPoint());
		}
	}
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
	Point currentPosition = getCurrentPosition().getPosition();
	double drivenDistance = m_startPosition.distanceTo(currentPosition);
	bool lidarPuckCollectable = lidar.isPuckCollectable(m_maximumDistanceToCollectPuck, m_maximumAngleToCollectPuck);
	bool fromTargetPositionPuckCollectable = isCurrentTargetPuckCollectable();
	bool justReachedOrientation = false;

	if (!m_rotationReached && !m_stateChanged)
	{
		m_rotationReached = engine.reachedTarget();
		if (m_rotationReached)
			justReachedOrientation = true;
	}

	if (isPuckCollected())
	{
		changeIntoState(RobotStateWaiting);
		return;
	}

	if ((!lidarPuckCollectable || !fromTargetPositionPuckCollectable) && m_rotationReached)
	{
		m_cantReachTarget = true;
		return;
	}
	else if (drivenDistance > m_maximumDistanceToCollectPuck)
	{
		m_cantReachTarget = true;
		return;
	}

	if (m_stateChanged || m_puckPositionChanged || justReachedOrientation)
	{
		if (m_rotationReached)
			engine.goToStraightSlowly(m_currentTarget);
		else
			engine.turnToTarget(m_currentTarget);
	}
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
	case RobotStateDrivingStraightPart:
		updateEngineForDrivingStraightPart(field);
		break;
	case RobotStateDrivingTurningPart:
		updateEngineForDrivingTurningPart(field);
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
	bool result = false;

	switch(m_state)
	{
	case RobotStateWaiting:
	case RobotStateCollectingPuck:
		result = false;
		break;
	case RobotStateDrivingStraightPart:
	case RobotStateDrivingTurningPart:
	case RobotStateLeavingPuck:
	case RobotStateTurnTo:
	case RobotStateTurnAround:
		result = true;
		break;
	}

	return result;
}

void RobotImpl::changeIntoState(RobotState state)
{
	m_currentTarget = Point();
	m_cantReachTarget = false;
	m_tryingToTackleObstacle = false;
	m_state = state;
	m_stateChanged = true;
	m_rotationReached = false;
}

bool RobotImpl::isCurrentTargetPuckCollectable() const
{
	RobotPosition currentPosition = getCurrentPosition();
	Angle orientationAbsolute(currentPosition.getPosition(), m_currentTarget);
	Angle orientationDifference = orientationAbsolute - currentPosition.getOrientation();
	double distance = m_currentTarget.distanceTo(currentPosition.getPosition());
	orientationDifference.abs();

	return	distance < m_maximumDistanceToCollectPuck &&
			orientationDifference.getValueBetweenMinusPiAndPi() < m_maximumAngleToCollectPuck.getValueBetweenMinusPiAndPi();
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

	if (m_currentRoute != 0 && m_currentRoute->isValid())
	{
		const RobotPosition position = getCurrentPosition();
		m_currentRoute->replaceFirstPoint(position.getPosition());
	}
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

bool RobotImpl::isMoving() const
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

bool RobotImpl::isRotating() const
{
	switch (m_state)
	{
	case RobotStateWaiting:
		return false;
	case RobotStateDrivingStraightPart:
		return false;
	case RobotStateDrivingTurningPart:
		return true;
	case RobotStateTurnAround:
		return true;
	case RobotStateTurnTo:
		return true;
	case RobotStateLeavingPuck:
		return false;
	case RobotStateCollectingPuck:
		return !m_rotationReached;
	}

	assert(false);
	return true;
}

void RobotImpl::clearRoute()
{
	delete m_currentRoute;
	m_currentRoute = 0;
}

bool RobotImpl::updateRoute(const Field &field)
{
	const RobotPosition robotPosition = getCurrentPosition();
	const Point &ownPosition = robotPosition.getPosition();
	vector<Circle> obstacles = field.getAllObstacles();

	if (isRouteFeasible(obstacles))
		return false;

	//! If the current route is not feasible anymore we try to create a new one.
	clearRoute();
	m_currentRoute = new Route(m_robotWidth);
	*m_currentRoute = m_router->calculateRoute(ownPosition, m_currentTarget, field);

	if (!isRouteFeasible(obstacles))
		clearRoute();

	return true;
}

bool RobotImpl::isRouteFeasible(const vector<Circle> &obstacles) const
{
	if (m_currentRoute == 0)
		return false;

	return	m_currentRoute->isValid() &&
			!m_currentRoute->intersectsWith(obstacles);
}

RobotImpl::RobotImpl(const RobotImpl &) :
	m_robotWidth(0),
	m_maximumDistanceToCollectPuck(0),
	m_maximumAngleToCollectPuck(0)
{ }

void RobotImpl::operator=(const RobotImpl &)
{ }
