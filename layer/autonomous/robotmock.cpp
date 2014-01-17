#include "layer/autonomous/robotmock.h"
#include "common/robotposition.h"
#include "layer/autonomous/route.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Autonomous;
using namespace std;

RobotMock::RobotMock() :
	m_stuckAtObstacle(false),
	m_reachedTarget(false),
	m_callsToUpdateActuators(0),
	m_callsToUpdateSensorData(0),
	m_callsToStop(0),
	m_isMoving(false),
	m_isRotating(false),
	m_cantReachTarget(false),
	m_puckCollected(false),
	m_puckCollectable(false)
{ }

void RobotMock::goTo(const list<RobotPosition> &possibleTargets)
{
	m_lastTarget = possibleTargets.front();
}

bool RobotMock::stuckAtObstacle()
{
	return m_stuckAtObstacle;
}

bool RobotMock::reachedTarget()
{
	return m_reachedTarget;
}

void RobotMock::updateActuators(const Field &)
{
	++m_callsToUpdateActuators;
}

void RobotMock::updateSensorData()
{
	++m_callsToUpdateSensorData;
}

void RobotMock::stop()
{
	++m_callsToStop;
}

unsigned int RobotMock::getCallsToUpdateActuators() const
{
	return m_callsToUpdateActuators;
}

unsigned int RobotMock::getCallsToUpdateSensorData() const
{
	return m_callsToUpdateSensorData;
}

void RobotMock::setStuckAtObstacle(bool value)
{
	m_stuckAtObstacle = value;
}

void RobotMock::setReachedTarget(bool value)
{
	m_reachedTarget = value;
}

const RobotPosition &RobotMock::getLastTarget() const
{
	return m_lastTarget;
}

list<Point> RobotMock::getAllRoutePoints() const
{
	list<Common::Point> listOfRoutetest;
	return listOfRoutetest;
}

unsigned int RobotMock::getCallsToStop() const
{
	return m_callsToStop;
}

void RobotMock::collectPuckInFront(const Point &target)
{
	m_lastTarget = RobotPosition(target, Angle());
}

void RobotMock::updatePuckPosition(const Point &)
{ }

void RobotMock::leaveCollectedPuck()
{ }

bool RobotMock::isMoving() const
{
	return m_isMoving;
}

void RobotMock::turnAround()
{ }

void RobotMock::turnTo(const Point &position)
{
	m_lastTurnToTarget = position;
}

RobotPosition RobotMock::getCurrentPosition() const
{
	return RobotPosition();
}

bool RobotMock::cantReachTarget() const
{
	return m_cantReachTarget;
}

bool RobotMock::isPuckCollected() const
{
	return m_puckCollected;
}

bool RobotMock::isPuckCollectable() const
{
	return m_puckCollectable;
}

bool RobotMock::isCollectingPuck() const
{
	return false;
}

bool RobotMock::isRotating() const
{
	return m_isRotating;
}

void RobotMock::setIsMoving(bool value)
{
	m_isMoving = value;
}

void RobotMock::setIsRotating(bool value)
{
	m_isRotating = value;
}

void RobotMock::setCantReachedTarget(bool value)
{
	m_cantReachTarget = value;
}

void RobotMock::setPuckCollected(bool value)
{
	m_puckCollected = value;
}

void RobotMock::setPuckCollectable(bool value)
{
	m_puckCollectable = value;
}

const Point &RobotMock::getLastTurnToTarget() const
{
	return m_lastTurnToTarget;
}
