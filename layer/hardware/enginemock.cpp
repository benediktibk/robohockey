#include "layer/hardware/enginemock.h"
#include <assert.h>

using namespace RoboHockey::Layer::Hardware;

EngineMock::EngineMock() :
	m_callsToSetSpeed(0),
	m_callsToSetEnabled(0),
	m_lastMagnitude(0),
	m_lastRotation(0),
	m_enabled(true),
	m_isMoving(false)
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

unsigned int EngineMock::getCallsToSetEnabled() const
{
	return m_callsToSetEnabled;
}

bool EngineMock::getEnabled() const
{
	return m_enabled;
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

void EngineMock::setIsMoving(bool value)
{
	m_isMoving = value;
}

bool EngineMock::isMoving()
{
	return m_isMoving;
}

double EngineMock::getSpeed() const
{
	return 0;
}

void EngineMock::setEnabled(bool value)
{
	m_enabled = value;
	++m_callsToSetEnabled;
}
