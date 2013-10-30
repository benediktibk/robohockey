#include "layer/hardware/sonarmock.h"

using namespace RoboHockey::Layer::Hardware;

SonarMock::SonarMock() :
	m_callsToGetDistanceForSensor(0)
{ }

double SonarMock::getDistanceForSensor(unsigned int)
{
	++m_callsToGetDistanceForSensor;
	return 0;
}

unsigned int SonarMock::getCallsToGetDistanceForSensor() const
{
	return m_callsToGetDistanceForSensor;
}
