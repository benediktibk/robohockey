#include "layer/hardware/enginemock.h"
#include <assert.h>
#include <fstream>

using namespace RoboHockey::Layer::Hardware;
using namespace std;

EngineMock::EngineMock() :
	m_callsToSetSpeed(0),
	m_callsToSetEnabled(0),
	m_lastMagnitude(0),
	m_lastRotation(0),
	m_enabled(true),
	m_isMoving(false),
	m_speed(0)
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

void EngineMock::readDataFromFile(const string &fileName)
{
	fstream file(fileName.c_str(), ios::in);

	file >> m_isMoving;
	file >> m_speed;

	file.close();
}

void EngineMock::setRotationSpeed(double value)
{
	m_rotationSpeed = value;
}

bool EngineMock::isMoving() const
{
	return m_isMoving;
}

double EngineMock::getSpeed() const
{
	return m_speed;
}

double EngineMock::getRotationSpeed() const
{
	return m_rotationSpeed;
}

void EngineMock::setEnabled(bool value)
{
	m_enabled = value;
	++m_callsToSetEnabled;
}

void EngineMock::writeDataToFile(const string &) const
{ }

void EngineMock::updateSensorData()
{ }
