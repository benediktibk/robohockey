#include "layer/hardware/enginemock.h"
#include <assert.h>

using namespace RoboHockey::Layer::Hardware;

EngineMock::EngineMock() :
	m_callsToSetSpeed(0),
	m_lastMagnitude(0),
	m_lastRotation(0)
{ }

void EngineMock::setSpeed(double magnitude, double rotation)
{
	++m_callsToSetSpeed;
	m_lastMagnitude = magnitude;
	m_lastRotation = rotation;
}

unsigned int EngineMock::getCallsToSetSpeed() const
{
	return m_callsToSetSpeed;
}

double EngineMock::getLastMagnitude() const
{
	assert(getCallsToSetSpeed() > 0);
	return m_lastMagnitude;
}

double EngineMock::getLastRotation() const
{
	assert(getCallsToSetSpeed() > 0);
	return m_lastRotation;
}

bool EngineMock::isMoving() const
{
	return true;
}

double EngineMock::getSpeed() const
{
	return 0;
}
