#include "layer/hardware/sonarmock.h"

using namespace RoboHockey::Layer::Hardware;

SonarMock::SonarMock() :
	m_callsToGetDistanceForSensor(0)
{ }

void SonarMock::updateSensorData()
{ }

double SonarMock::getDistanceForSensor(unsigned int sensorNumber)
{
	++m_callsToGetDistanceForSensor;

	if (m_values.count(sensorNumber) != 0)
		return m_values[sensorNumber];
	else
		return 0;
}

unsigned int SonarMock::getCallsToGetDistanceForSensor() const
{
	return m_callsToGetDistanceForSensor;
}

void SonarMock::setValue(unsigned int sensorNumber, double value)
{
	m_values[sensorNumber] = value;
}
