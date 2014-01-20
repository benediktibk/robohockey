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
#include "common/watch.h"
#include "common/stopwatch.h"
#include "common/timesmoothedboolean.h"
#include "common/logger.h"
#include <math.h>
#include <assert.h>
#include <sstream>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Layer;
using namespace std;

RobotImpl::RobotImpl(DataAnalysis::DataAnalyser *dataAnalyser, Router *router, const Watch &watch, Common::Logger &logger) :
	m_logger(logger),
	m_robotWidth(0.38),
	m_maximumDistanceToCollectPuck(0.75),
	m_maximumAngleToCollectPuck(10.0/180*M_PI),
	m_timeout(30),
	m_maximumAngleForSmoothTurn(Angle::getHalfRotation()/3),
	m_dataAnalyser(dataAnalyser),
	m_router(router),
	m_watch(watch),
	m_watchDog(new StopWatch(watch)),
	m_tryingToTackleObstacle(false),
	m_cantReachTarget(false),
	m_currentRoute(0),
	m_state(RobotStateWaiting),
	m_stateChanged(false),
	m_ignoringSoftObstacles(false),
	m_ignoringNotVisibleObstacle(false),
	m_carryingPuck(false),
	m_puckCollected(new TimeSmoothedBoolean(m_watch, false, 0.2))
{ }

RobotImpl::~RobotImpl()
{
	delete m_dataAnalyser;
	m_dataAnalyser = 0;
	delete m_router;
	m_router = 0;
	delete m_watchDog;
	m_watchDog = 0;
	delete m_puckCollected;
	m_puckCollected = 0;
	clearRoute();
}

void RobotImpl::goTo(const list<RobotPosition> &possibleTargets)
{
	assert(possibleTargets.size() > 0);
	clearRoute();
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	engine.stop();
	changeIntoState(RobotStateDrivingTurningPart);
	m_possibleTargets = possibleTargets;
	m_currentTarget = m_possibleTargets.front();
	m_carryingPuck = isPuckCollected();
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

void RobotImpl::updateEngineForDrivingStraightPart()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();

	if (engine.reachedTarget())
	{
		const Common::Point &target = m_currentRoute->getSecondPoint();
		engine.goToStraight(target);
	}
}

void RobotImpl::updateEngineForDrivingTurningPart()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();

	if (engine.reachedTarget())
	{
		Point target;

		if (m_currentRoute->getPointCount() >= 2)
			target = m_currentRoute->getSecondPoint();
		else
		{
			target = Point(1, 0);
			target.rotate(m_currentTarget.getOrientation());
			target = target + getCurrentPosition().getPosition();
		}

		engine.turnToTarget(target);
	}
}

void RobotImpl::updateDrivingState(const Field &field)
{
	if (checkTimeout())
		return;

	bool routeChanged = updateRoute(field);

	//! If there is no route at this point we can't reach the target.
	if (m_currentRoute == 0)
	{
		m_cantReachTarget = true;
		return;
	}

	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();

	if (engine.reachedTarget() && m_state == RobotStateDrivingStraightPart)
		m_currentRoute->removeFirstPoint();
	else if (engine.reachedTarget() && m_currentRoute->getPointCount() < 2)
	{
		stop();
		return;
	}

	if (routeChanged)
		engine.stop();

	if (routeChanged || engine.reachedTarget())
	{
		if (m_currentRoute->getPointCount() == 1)
			changeIntoState(RobotStateDrivingTurningPart);
		else
		{
			const Point &nextTarget = getNextTarget();

			if (isOrientationDifferenceSmallEnoughForSmoothTurn(nextTarget))
				changeIntoState(RobotStateDrivingStraightPart);
			else
				changeIntoState(RobotStateDrivingTurningPart);
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
	if (checkTimeout())
		return;

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
	if (checkTimeout())
		return;

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

void RobotImpl::updateEngineForTurnTo()
{
	if (checkTimeout())
		return;

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
	case RobotStateDrivingTurningPart:
		updateDrivingState(field);
		updateEngineForDriving();
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
	case RobotStateTurnTo:
		updateEngineForTurnTo();
		break;
	}
}

void RobotImpl::updateEngineForDriving()
{
	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();

	if (m_cantReachTarget)
	{
		engine.stop();
		return;
	}

	switch(m_state)
	{
	case RobotStateDrivingStraightPart:
		updateEngineForDrivingStraightPart();
		break;
	case RobotStateDrivingTurningPart:
		updateEngineForDrivingTurningPart();
		break;
	case RobotStateWaiting:
		engine.stop();
		break;
	case RobotStateCollectingPuck:
	case RobotStateLeavingPuck:
	case RobotStateTurnTo:
		assert(false);
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
		result = true;
		break;
	}

	return result;
}

void RobotImpl::changeIntoState(RobotState state)
{
	if (m_state == RobotStateWaiting)
		m_watchDog->getTimeAndRestart();

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

bool RobotImpl::checkTimeout()
{
	if (m_watchDog->getTime() > m_timeout)
	{
		stop();
		m_cantReachTarget = true;
		return true;
	}
	else
		return false;
}

vector<Circle> RobotImpl::shrinkObstacles(const vector<Circle> &obstacles) const
{
	vector<Circle> result;
	result.reserve(obstacles.size());

	for (vector<Circle>::const_iterator i = obstacles.begin(); i != obstacles.end(); ++i)
	{
		Circle circle = *i;
		double diameter = circle.getDiameter();
		circle.setDiameter(diameter*0.9);
		result.push_back(circle);
	}

	return result;
}

vector<Circle> RobotImpl::growObstacles(const vector<Circle> &obstacles) const
{
	vector<Circle> result;
	result.reserve(obstacles.size());

	for (vector<Circle>::const_iterator i = obstacles.begin(); i != obstacles.end(); ++i)
	{
		Circle circle = *i;
		double diameter = circle.getDiameter();
		circle.setDiameter(diameter*1.1);
		result.push_back(circle);
	}

	return result;
}

bool RobotImpl::isOrientationDifferenceSmallEnoughForSmoothTurn(const Angle &angle) const
{
	const DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	double currentSpeed = engine.getCurrentSpeed();
	double speedModification = 1 + fabs(currentSpeed);
	return fabs(speedModification*angle.getValueBetweenMinusPiAndPi()) < m_maximumAngleForSmoothTurn.getValueBetweenZeroAndTwoPi();
}

bool RobotImpl::isOrientationDifferenceSmallEnoughForSmoothTurn(const Point &point) const
{
	return isOrientationDifferenceSmallEnoughForSmoothTurn(getCurrentPosition().getRelativeOrientationTo(point));
}

const Point &RobotImpl::getNextTarget() const
{
	assert(m_currentRoute->getPointCount() >= 2);
	return m_currentRoute->getLastPoint();
}

void RobotImpl::updateActuators(const Field &field)
{
	detectCollisions();
	updateEngine(field);
	m_dataAnalyser->updateActuators();

	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	if (engine.tryingToTackleObstacle())
	{
		const DataAnalysis::Lidar &lidar = m_dataAnalyser->getLidar();
		const DataAnalysis::Sonar &sonar = m_dataAnalyser->getSonar();
		double speed = engine.getCurrentSpeed();
		m_tryingToTackleObstacle = true;
		if (lidar.isObstacleInFront(speed))
			m_logger.logToConsoleAndGlobalLogFile("lidar detected collision");
		if (sonar.isObstacleDirectInFront(speed))
		{
			stringstream message;
			message << "sonar detected collision: (left, right) = (";
			message << sonar.getLeftFrontValue() << ", " << sonar.getRightFrontValue() << ")";
			m_logger.logToConsoleAndGlobalLogFile(message.str());
		}
	}
}

void RobotImpl::updateSensorData()
{
	m_stateChanged = false;
	m_puckPositionChanged = false;
	m_dataAnalyser->updateSensorData();
	const DataAnalysis::Lidar &lidar = m_dataAnalyser->getLidar();
	m_puckCollected->update(lidar.isPuckCollected());

	if (m_currentRoute != 0 && m_currentRoute->isValid() && m_currentRoute->getPointCount() > 1)
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
	const DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	switch(m_state)
	{
	case RobotStateWaiting:
		return engine.isMoving();
	case RobotStateDrivingStraightPart:
	case RobotStateDrivingTurningPart:
	case RobotStateTurnTo:
	case RobotStateLeavingPuck:
	case RobotStateCollectingPuck:
		return true;
	}

	assert(false);
	return true;
}

RobotPosition RobotImpl::getCurrentPosition() const
{
	DataAnalysis::Odometry &odometry = m_dataAnalyser->getOdometry();
	return odometry.getCurrentPosition();
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
	return m_puckCollected->get();
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
	const DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	switch (m_state)
	{
	case RobotStateWaiting:
		return false;
	case RobotStateDrivingStraightPart:
		return fabs(engine.getCurrentRotationSpeed()) > 0.2;
	case RobotStateDrivingTurningPart:
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

string RobotImpl::getCurrentState() const
{
	switch(m_state)
	{
	case RobotStateWaiting:
		return string("Waiting");
	case RobotStateDrivingStraightPart:
		return string("DrivingStraight");
	case RobotStateDrivingTurningPart:
		return string("DrivingTurning");
	case RobotStateTurnTo:
		return string("TurnTo");
	case RobotStateLeavingPuck:
		return string("LeavingPuck");
	case RobotStateCollectingPuck:
		return string("CollectingPuck");
	}

	assert(false);
	return string();
}

void RobotImpl::clearRoute()
{
	delete m_currentRoute;
	m_currentRoute = 0;
}

bool RobotImpl::updateRouteForTarget(
		const FieldPositionChecker &field, const Common::RobotPosition &target,
		const vector<Circle> &filteredObstacles, bool ignoreFinalOrientation,
		const vector<Circle> &hardObstacles, const vector<Circle> &softObstacles)
{
	const RobotPosition robotPosition = getCurrentPosition();
	Angle maximumRotation = Angle::getHalfRotation();
	double minimumStepAfterMaximumRotation = 0.1;

	if (m_carryingPuck)
		maximumRotation = Angle::getQuarterRotation();

	*m_currentRoute = m_router->calculateRoute(
				robotPosition, target, field, maximumRotation,
				minimumStepAfterMaximumRotation, ignoreFinalOrientation,
				hardObstacles, softObstacles);

	return isRouteFeasible(filteredObstacles);
}

bool RobotImpl::updateRoute(const Field &field)
{
	const RobotPosition robotPosition = getCurrentPosition();
	const vector<Circle> &softObstacles = field.getAllSoftObstacles();
	const vector<Circle> &hardObstacles = field.getAllHardObstacles();
	const vector<Circle> &hardAndVisibleObstacles = field.getAllHardAndVisibleObstacles();

	if (m_ignoringNotVisibleObstacle)
	{
		vector<Circle> visibleObstaclesShrinked = shrinkObstacles(hardAndVisibleObstacles);

		if (isRouteFeasible(visibleObstaclesShrinked))
				return false;
	}
	else if (m_ignoringSoftObstacles)
	{
		vector<Circle> softObstaclesShrinked = shrinkObstacles(softObstacles);

		if (isRouteFeasible(softObstaclesShrinked))
				return false;
	}
	else
	{
		vector<Circle> softObstaclesShrinked = shrinkObstacles(softObstacles);
		vector<Circle> hardObstaclesShrinked = shrinkObstacles(hardObstacles);
		const vector<Circle> allObstaclesShrinked = m_router->filterObstacles(softObstaclesShrinked, hardObstaclesShrinked, robotPosition.getPosition());

		if (isRouteFeasible(allObstaclesShrinked))
			return false;
	}

	vector<Circle> softObstaclesGrown = growObstacles(softObstacles);
	vector<Circle> hardObstaclesGrown = growObstacles(hardObstacles);
	vector<Circle> hardAndVisibleObstaclesGrown = growObstacles(hardAndVisibleObstacles);
	const vector<Circle> allObstaclesGrown = m_router->filterObstacles(softObstaclesGrown, hardObstaclesGrown, robotPosition.getPosition());

	//! If the current route is not feasible anymore we try to create a new one.
	clearRoute();
	m_currentRoute = new Route(m_robotWidth);
	bool success = false;

	m_ignoringSoftObstacles = false;
	m_ignoringNotVisibleObstacle = false;
	for (list<RobotPosition>::const_iterator i = m_possibleTargets.begin(); i != m_possibleTargets.end() && !success; ++i)
	{
		m_currentTarget = *i;
		success = updateRouteForTarget(
					field, m_currentTarget, allObstaclesGrown, false, hardObstaclesGrown, softObstaclesGrown);
	}

	if (success)
		return true;

	m_ignoringSoftObstacles = true;
	m_ignoringNotVisibleObstacle = false;
	for (list<RobotPosition>::const_iterator i = m_possibleTargets.begin(); i != m_possibleTargets.end() && !success; ++i)
	{
		m_currentTarget = *i;
		success = updateRouteForTarget(
					field, m_currentTarget, hardObstaclesGrown, false, hardObstaclesGrown, vector<Circle>());
	}

	if (success)
		return true;

	m_ignoringSoftObstacles = true;
	m_ignoringNotVisibleObstacle = true;
	for (list<RobotPosition>::const_iterator i = m_possibleTargets.begin(); i != m_possibleTargets.end() && !success; ++i)
	{
		m_currentTarget = *i;
		success = updateRouteForTarget(
					field, m_currentTarget, hardAndVisibleObstaclesGrown, false, hardAndVisibleObstaclesGrown, vector<Circle>());
	}

	if (success)
		return true;

	m_ignoringSoftObstacles = true;
	m_ignoringNotVisibleObstacle = true;
	for (list<RobotPosition>::const_iterator i = m_possibleTargets.begin(); i != m_possibleTargets.end() && !success; ++i)
	{
		m_currentTarget = *i;
		success = updateRouteForTarget(
					field, m_currentTarget, hardAndVisibleObstaclesGrown, true, hardAndVisibleObstaclesGrown, vector<Circle>());
	}

	if (!success)
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

RobotImpl::RobotImpl(const RobotImpl &rhs) :
	m_logger(rhs.m_logger),
	m_robotWidth(0),
	m_maximumDistanceToCollectPuck(0),
	m_maximumAngleToCollectPuck(0),
	m_timeout(0),
	m_watch(rhs.m_watch)
{ }

void RobotImpl::operator=(const RobotImpl &)
{ }
