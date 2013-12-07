#include "layer/dataanalysis/enginemock.h"
#include "common/point.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::DataAnalysis;

EngineMock::EngineMock() :
	m_callsToGoToStraight(0),
	m_callsToGoToStraightSlowly(0),
	m_callsToGoToStraightThrough(0),
	m_callsToGoToStraightSlowlyBack(0),
	m_callsToStop(0),
	m_callsToUpdateSpeedAndMagnitude(0),
	m_callsToTryingToTackleObstacle(0),
	m_callsToTurnToTarget(0),
	m_callsToTurnAround(0),
	m_callsToLockForwardMovement(0),
	m_callsToUnlockForwardMovement(0),
	m_tryingToTackleObstacle(false),
	m_reachedTarget(true),
	m_isGoingStraight(false)
{ }

void EngineMock::goToStraight(const Point &)
{
	++m_callsToGoToStraight;
}

void EngineMock::goToStraightSlowly(const Point &)
{
	++m_callsToGoToStraightSlowly;
}

void EngineMock::goToStraightThrough(const Point &)
{
	++m_callsToGoToStraightThrough;
}

void EngineMock::goToStraightSlowlyBack(const Point &)
{
	++m_callsToGoToStraightSlowlyBack;
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

void EngineMock::turnToTarget(const Point &)
{
	++m_callsToTurnToTarget;
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
	return true;
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

unsigned int EngineMock::getCallsToGoToStraight() const
{
	return m_callsToGoToStraight;
}

unsigned int EngineMock::getCallsToGoToStraightSlowly() const
{
	return m_callsToGoToStraightSlowly;
}

unsigned int EngineMock::getCallsToGoToStraightThrough() const
{
	return m_callsToGoToStraightThrough;
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


