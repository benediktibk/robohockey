#include "layer/dataanalysis/enginemock.h"

using namespace RoboHockey::Layer::DataAnalysis;

EngineMock::EngineMock() :
	m_callsToGoToStraight(0),
	m_callsToStop(0),
	m_callsToUpdateSpeedAndMagnitude(0),
	m_tryingToTackleObstacle(false)
{ }

void EngineMock::goToStraight(const Common::Point &)
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
{ }

void EngineMock::turnToTarget(const Common::Point &)
{ }

void EngineMock::lockForwardMovement()
{ }

void EngineMock::unlockForwardMovement()
{ }

bool EngineMock::tryingToTackleObstacle() const
{
	return m_tryingToTackleObstacle;
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

void EngineMock::setTryingToTackleObstacle(bool value)
{
	m_tryingToTackleObstacle = value;
}


