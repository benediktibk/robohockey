#include "layer/dataanalysis/enginemock.h"
#include "common/point.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::DataAnalysis;

EngineMock::EngineMock() :
	m_callsToGoToStraight(0),
	m_callsToStop(0),
	m_callsToUpdateSpeedAndMagnitude(0),
	m_callsToTryingToTackleObstacle(0),
	m_callsToTurnToTarget(0),
	m_callsToTurnAround(0),
	m_callsToLockForwardMovement(0),
	m_callsToUnlockForwardMovement(0),
	m_tryingToTackleObstacle(false),
	m_reachedTarget(true)
{ }

void EngineMock::goToStraight(const Point &)
{
	++m_callsToGoToStraight;
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

unsigned int EngineMock::getCallsToGoToStraight() const
{
	return m_callsToGoToStraight;
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


