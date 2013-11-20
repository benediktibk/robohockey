#include "layer/hardware/sonarimpl.h"
#include <libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;
using namespace PlayerCc;

SonarImpl::SonarImpl(PlayerCc::PlayerClient *playerClient) :
	m_sonar(new RangerProxy(playerClient, 0))
{ }

SonarImpl::~SonarImpl()
{
	delete m_sonar;
	m_sonar = 0;
}

void SonarImpl::updateSensorData()
{
	m_lastValues = m_currentValues;
	for (unsigned int i = getMinimumSensorNumber(); i <= getMaximumSensorNumber(); ++i)
		m_currentValues[i] = m_sonar->GetRange(i);
}

double SonarImpl::getDistanceForSensor(unsigned int sensorNumber)
{
	assert(m_currentValues.count(sensorNumber) != 0);
	assert(m_lastValues.count(sensorNumber) != 0);
	double currentValue = m_currentValues[sensorNumber];
	double lastValue = m_lastValues[sensorNumber];
	return (currentValue + lastValue)/2;
}

SonarImpl::SonarImpl(const SonarImpl &)
{ }

void SonarImpl::operator=(const SonarImpl &)
{ }
