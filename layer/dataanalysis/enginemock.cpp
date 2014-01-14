#include "layer/dataanalysis/enginemock.h"
#include "common/point.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::DataAnalysis;

EngineMock::EngineMock() :
	m_tryingToTackleObstacle(false),
	m_reachedTarget(true),
	m_isGoingStraight(false),
	m_lastFinalSpeed(0),
	m_speedForGoingStraight(0),
	m_isMoving(true)
{
	resetCounters();
}

void EngineMock::goToStraight(const Point &target, double finalSpeed)
{
	++m_callsToGoToStraight;
	m_lastTarget = target;
	m_lastFinalSpeed = finalSpeed;
}

void EngineMock::goToStraightSlowly(const Point &target)
{
	++m_callsToGoToStraightSlowly;
	m_lastTarget = target;
}

void EngineMock::goToStraightSlowlyBack(const Point &target)
{
	++m_callsToGoToStraightSlowlyBack;
	m_lastTarget = target;
}

void EngineMock::updateSpeedAndRotation()
{
	++m_callsToUpdateSpeedAndMagnitude;
}

void EngineMock::stop()
{
	++m_callsToStop;
}

void EngineMock::turnAround()
{
	++m_callsToTurnAround;
}

void EngineMock::turnToTarget(const Point &target)
{
	++m_callsToTurnToTarget;
	m_lastTarget = target;
}

void EngineMock::lockForwardMovement()
{
	++m_callsToLockForwardMovement;
}

void EngineMock::unlockForwardMovement()
{
	++m_callsToUnlockForwardMovement;
}

bool EngineMock::tryingToTackleObstacle()
{
	++m_callsToTryingToTackleObstacle;
	return m_tryingToTackleObstacle;
}

bool EngineMock::reachedTarget() const
{
	return m_reachedTarget;
}

Point EngineMock::getCurrentTarget() const
{
	return Point();
}

bool EngineMock::isMoving() const
{
	return m_isMoving;
}

double EngineMock::getCurrentSpeed() const
{
	return 0;
}

void EngineMock::updateSensorData()
{ }

bool EngineMock::isGoingStraight() const
{
	return m_isGoingStraight;
}

double EngineMock::calculateSpeedForGoingStraight(double) const
{
	return m_speedForGoingStraight;
}

unsigned int EngineMock::getCallsToGoToStraight() const
{
	return m_callsToGoToStraight;
}

unsigned int EngineMock::getCallsToGoToStraightSlowly() const
{
	return m_callsToGoToStraightSlowly;
}

unsigned int EngineMock::getCallsToGoToStraightSlowlyBack() const
{
	return m_callsToGoToStraightSlowlyBack;
}

unsigned int EngineMock::getCallsToStop() const
{
	return m_callsToStop;
}

unsigned int EngineMock::getCallsToUpdateSpeedAndMagnitude() const
{
	return m_callsToUpdateSpeedAndMagnitude;
}

unsigned int EngineMock::getCallsToTryingToTackleObstacle() const
{
	return m_callsToTryingToTackleObstacle;
}

unsigned int EngineMock::getCallsToTurnToTarget() const
{
	return m_callsToTurnToTarget;
}

unsigned int EngineMock::getCallsToTurnAround() const
{
	return m_callsToTurnAround;
}

unsigned int EngineMock::getCallsToLockForwardMovement() const
{
	return m_callsToLockForwardMovement;
}

unsigned int EngineMock::getCallsToUnlockForwardMovement() const
{
	return m_callsToUnlockForwardMovement;
}

void EngineMock::setTryingToTackleObstacle(bool value)
{
	m_tryingToTackleObstacle = value;
}

void EngineMock::setReachedTarget(bool value)
{
	m_reachedTarget = value;
}

void EngineMock::setIsGoingStraight(bool value)
{
	m_isGoingStraight = value;
}

void EngineMock::resetCounters()
{
	m_callsToGoToStraight = 0;
	m_callsToGoToStraightSlowly = 0;
	m_callsToGoToStraightSlowlyBack = 0;
	m_callsToStop = 0;
	m_callsToUpdateSpeedAndMagnitude = 0;
	m_callsToTryingToTackleObstacle = 0;
	m_callsToTurnToTarget = 0;
	m_callsToTurnAround = 0;
	m_callsToLockForwardMovement = 0;
	m_callsToUnlockForwardMovement = 0;
}

const Point &EngineMock::getLastTarget() const
{
	return m_lastTarget;
}

double EngineMock::getLastFinalSpeed() const
{
	return m_lastFinalSpeed;
}

void EngineMock::setSpeedForGoingStraight(double value)
{
	m_speedForGoingStraight = value;
}

void EngineMock::setIsMoving(bool value)
{
	m_isMoving = value;
}


