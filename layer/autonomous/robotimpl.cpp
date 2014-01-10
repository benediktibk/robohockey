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
#include <math.h>
#include <assert.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace RoboHockey::Layer;
using namespace std;

RobotImpl::RobotImpl(DataAnalysis::DataAnalyser *dataAnalyser, Router *router, Watch *watch) :
	m_robotWidth(0.38),
	m_maximumDistanceToCollectPuck(0.75),
	m_maximumAngleToCollectPuck(10.0/180*M_PI),
	m_timeout(50),
	m_dataAnalyser(dataAnalyser),
	m_router(router),
	m_watch(watch),
	m_watchDog(new StopWatch(*watch)),
	m_tryingToTackleObstacle(false),
	m_cantReachTarget(false),
	m_currentRoute(0),
	m_state(RobotStateWaiting),
	m_stateChanged(false),
	m_ignoringSoftObstacles(false),
	m_carryingPuck(false),
	m_puckCollected(new TimeSmoothedBoolean(*m_watch, false, 0.2))
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
	delete m_watch;
	m_watch = 0;
	clearRoute();
}

void RobotImpl::goTo(const list<RobotPosition> &possibleTargets)
{
	assert(possibleTargets.size() > 0);
	clearRoute();
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

void RobotImpl::updateEngineForDrivingStraightPart(const Field &field)
{
	if (checkTimeout())
		return;

	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	bool routeChanged = updateRoute(field);

	//! If there is no route at this point we can't reach the target.
	if (m_currentRoute == 0)
	{
		m_cantReachTarget = true;
		return;
	}

	if (routeChanged)
	{
		changeIntoState(RobotStateDrivingTurningPart);
		engine.turnToTarget(m_currentRoute->getSecondPoint());
	}
	else if (engine.reachedTarget())
	{
		m_currentRoute->removeFirstPoint();
		const Compare compare(0.001);

		if (m_currentRoute->getPointCount() == 1)
		{
			if (compare.isFuzzyEqual(m_finalSpeed, 0))
			{
				const Angle &finalOrientation = m_currentTarget.getOrientation();
				Point smallStep(1, 0);
				smallStep.rotate(finalOrientation);
				engine.turnToTarget(getCurrentPosition().getPosition() + smallStep);
				changeIntoState(RobotStateDrivingTurningPart);
			}
			else
			{
				changeIntoState(RobotStateDrivingStraightPart);
				m_finalSpeed = calculateNextFinalSpeedForGoingStraight();
				engine.goToStraight(m_currentRoute->getFirstPoint(), m_finalSpeed);
			}
		}
		else
		{
			if (compare.isFuzzyEqual(m_finalSpeed, 0))
			{
				changeIntoState(RobotStateDrivingTurningPart);
				engine.turnToTarget(m_currentRoute->getSecondPoint());
			}
			else
			{
				changeIntoState(RobotStateDrivingStraightPart);
				m_finalSpeed = calculateNextFinalSpeedForGoingStraight();
				engine.goToStraight(m_currentRoute->getSecondPoint(), m_finalSpeed);
			}
		}
	}
}

void RobotImpl::updateEngineForDrivingTurningPart(const Field &field)
{
	if (checkTimeout())
		return;

	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	bool routeChanged = updateRoute(field);

	if (m_currentRoute == 0)
	{
		m_cantReachTarget = true;
		return;
	}

	if (m_stateChanged || routeChanged)
		engine.turnToTarget(m_currentRoute->getSecondPoint());
	else if (engine.reachedTarget())
	{
		if (m_currentRoute->getPointCount() > 1)
		{
			changeIntoState(RobotStateDrivingStraightPart);
			m_finalSpeed = calculateNextFinalSpeedForGoingStraight();
			engine.goToStraight(m_currentRoute->getSecondPoint(), m_finalSpeed);
		}
		else
			changeIntoState(RobotStateWaiting);
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

void RobotImpl::updateEngineForTurnAround()
{
	if (checkTimeout())
		return;

	DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();

	if (m_stateChanged)
		engine.turnAround();
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
	m_watchDog->getTimeAndRestart();
	m_finalSpeed = 0;
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

double RobotImpl::calculateNextFinalSpeedForGoingStraight() const
{
	if (m_currentRoute->getPointCount() <= 2)
		return 0;
	else
		return calculateFinalSpeedForGoingStraight(
					m_currentRoute->getFirstPoint(), m_currentRoute->getSecondPoint(),
					m_currentRoute->getThirdPoint());
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
	const DataAnalysis::Lidar &lidar = m_dataAnalyser->getLidar();
	m_puckCollected->update(lidar.isPuckCollected());

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

double RobotImpl::calculateFinalSpeedForGoingStraight(
		const Point &current, const Point &next, const Point &nextButOne) const
{
	Angle angle = Angle::getHalfRotation() - Angle(next, current, nextButOne);
	angle.abs();
	const Angle maximumAngle = Angle::getEighthRotation();

	if (angle.getValueBetweenZeroAndTwoPi() > maximumAngle.getValueBetweenZeroAndTwoPi())
		return 0;

	Angle angleDifference = maximumAngle - angle;
	double speedFromAngle = angleDifference.getValueBetweenZeroAndTwoPi()*0.05;
	double distanceLeft = next.distanceTo(nextButOne);
	const DataAnalysis::Engine &engine = m_dataAnalyser->getEngine();
	double speedFromDistance = engine.calculateSpeedForGoingStraight(distanceLeft);
	return min(speedFromAngle, speedFromDistance);
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

	m_ignoringSoftObstacles = false;
	*m_currentRoute = m_router->calculateRoute(
				robotPosition, target, field, maximumRotation,
				minimumStepAfterMaximumRotation, ignoreFinalOrientation,
				hardObstacles, softObstacles);

	return isRouteFeasible(filteredObstacles);
}

bool RobotImpl::updateRoute(const Field &field)
{
	const RobotPosition robotPosition = getCurrentPosition();
	vector<Circle> softObstacles = field.getAllSoftObstacles();
	vector<Circle> hardObstacles = field.getAllHardObstacles();

	if (m_ignoringSoftObstacles)
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
	const vector<Circle> allObstaclesGrown = m_router->filterObstacles(softObstaclesGrown, hardObstaclesGrown, robotPosition.getPosition());

	//! If the current route is not feasible anymore we try to create a new one.
	clearRoute();
	m_currentRoute = new Route(m_robotWidth);
	bool success = false;

	m_ignoringSoftObstacles = false;
	for (list<RobotPosition>::const_iterator i = m_possibleTargets.begin(); i != m_possibleTargets.end() && !success; ++i)
	{
		m_currentTarget = *i;
		success = updateRouteForTarget(
					field, m_currentTarget, allObstaclesGrown, false, hardObstaclesGrown, softObstaclesGrown);
	}

	if (success)
		return true;

	m_ignoringSoftObstacles = true;
	for (list<RobotPosition>::const_iterator i = m_possibleTargets.begin(); i != m_possibleTargets.end() && !success; ++i)
	{
		m_currentTarget = *i;
		success = updateRouteForTarget(
					field, m_currentTarget, hardObstaclesGrown, false, hardObstaclesGrown, vector<Circle>());
	}

	if (success)
		return true;

	m_ignoringSoftObstacles = true;
	for (list<RobotPosition>::const_iterator i = m_possibleTargets.begin(); i != m_possibleTargets.end() && !success; ++i)
	{
		m_currentTarget = *i;
		success = updateRouteForTarget(
					field, m_currentTarget, hardObstaclesGrown, true, hardObstaclesGrown, vector<Circle>());
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

RobotImpl::RobotImpl(const RobotImpl &) :
	m_robotWidth(0),
	m_maximumDistanceToCollectPuck(0),
	m_maximumAngleToCollectPuck(0),
	m_timeout(0)
{ }

void RobotImpl::operator=(const RobotImpl &)
{ }
