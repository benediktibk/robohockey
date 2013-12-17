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
	m_stateChanged(false),
	m_ignoringSoftObstacles(false)
{ }

RobotImpl::~RobotImpl()
{
	delete m_dataAnalyser;
	m_dataAnalyser = 0;
	delete m_router;
	m_router = 0;
	clearRoute();
}

void RobotImpl::goTo(const list<RobotPosition> &possibleTargets)
{
	clearRoute();
	changeIntoState(RobotStateDrivingTurningPart);
	m_possibleTargets = possibleTargets;
	m_currentTarget = m_possibleTargets.front();
}

void RobotImpl::turnTo(const Point &position)
{
	changeIntoState(RobotStateTurnTo);
	m_currentTarget.setPosition(position);
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
			{
				const Angle &finalOrientation = m_currentTarget.getOrientation();
				Point smallStep(1, 0);
				smallStep.rotate(finalOrientation);
				engine.turnToTarget(getCurrentPosition().getPosition() + smallStep);
				changeIntoState(RobotStateDrivingTurningPart);
			}
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
			if (m_currentRoute->getPointCount() > 1)
			{
				changeIntoState(RobotStateDrivingStraightPart);
				engine.goToStraight(m_currentRoute->getSecondPoint());
			}
			else
				changeIntoState(RobotStateWaiting);
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
			engine.goToStraightSlowly(m_currentTarget.getPosition());
		else
			engine.turnToTarget(m_currentTarget.getPosition());
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
		engine.turnToTarget(m_currentTarget.getPosition());
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
	m_cantReachTarget = false;
	m_tryingToTackleObstacle = false;
	m_state = state;
	m_stateChanged = true;
	m_rotationReached = false;
}

bool RobotImpl::isCurrentTargetPuckCollectable() const
{
	RobotPosition currentPosition = getCurrentPosition();
	Angle orientationAbsolute(currentPosition.getPosition(), m_currentTarget.getPosition());
	Angle orientationDifference = orientationAbsolute - currentPosition.getOrientation();
	double distance = m_currentTarget.distanceTo(currentPosition);
	orientationDifference.abs();

	return	distance < m_maximumDistanceToCollectPuck &&
			orientationDifference.getValueBetweenMinusPiAndPi() < m_maximumAngleToCollectPuck.getValueBetweenMinusPiAndPi();
}

void RobotImpl::updateActuators(const Field &field)
{
	detectCollisions();
	updateEngine(field);
	m_dataAnalyser->updateActuators();

	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	if (engine.tryingToTackleObstacle())
		m_tryingToTackleObstacle = true;
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
	m_currentTarget.setPosition(puckPosition);
	m_startPosition = getCurrentPosition().getPosition();
}

void RobotImpl::updatePuckPosition(const Point &puckPosition)
{
	assert(m_state == RobotStateCollectingPuck);
	m_currentTarget.setPosition(puckPosition);
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

std::list<Point> RobotImpl::getAllRoutePoints() const
{
	if (m_currentRoute == 0)
	{
		std::list<Point> emptyList;
		return emptyList;
	}
	else
		return m_currentRoute->getAllPoints();
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

bool RobotImpl::updateRouteForTarget(
		const Field &field, const Common::RobotPosition &target,
		const vector<Circle> &hardObstacles, const vector<Circle> &filteredObstacles)
{
	const RobotPosition robotPosition = getCurrentPosition();
	Angle maximumRotation = Angle::getHalfRotation();
	double minimumStepAfterMaximumRotation = 0.1;

	if (isPuckCollected())
		maximumRotation = Angle::getQuarterRotation();

	m_ignoringSoftObstacles = false;
	*m_currentRoute = m_router->calculateRoute(
				robotPosition, target, field, maximumRotation,
				minimumStepAfterMaximumRotation, m_ignoringSoftObstacles, false);

	if (isRouteFeasible(filteredObstacles))
		return true;

	m_ignoringSoftObstacles = true;
	*m_currentRoute = m_router->calculateRoute(
				robotPosition, target, field, maximumRotation,
				minimumStepAfterMaximumRotation, m_ignoringSoftObstacles, false);

	if (isRouteFeasible(hardObstacles))
		return true;

	m_ignoringSoftObstacles = true;
	*m_currentRoute = m_router->calculateRoute(
				robotPosition, target, field, maximumRotation,
				minimumStepAfterMaximumRotation, m_ignoringSoftObstacles, true);

	return isRouteFeasible(hardObstacles);
}

bool RobotImpl::updateRoute(const Field &field)
{
	const RobotPosition robotPosition = getCurrentPosition();
	vector<Circle> softObstacles = field.getAllSoftObstacles();
	vector<Circle> hardObstacles = field.getAllHardObstacles();
	vector<Circle> allObstacles = m_router->filterObstacles(softObstacles, hardObstacles, robotPosition.getPosition());

	if (	(m_ignoringSoftObstacles && isRouteFeasible(softObstacles)) ||
			(!m_ignoringSoftObstacles && isRouteFeasible(allObstacles)))
		return false;

	//! If the current route is not feasible anymore we try to create a new one.
	clearRoute();
	m_currentRoute = new Route(m_robotWidth);

	if (!updateRouteForTarget(field, m_currentTarget, hardObstacles, allObstacles))
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
