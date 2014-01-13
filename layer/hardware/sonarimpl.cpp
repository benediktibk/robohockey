#include "layer/hardware/sonarimpl.h"
#include <libplayerc++/playerc++.h>
#include <fstream>

using namespace RoboHockey::Layer::Hardware;
using namespace PlayerCc;
using namespace std;

SonarImpl::SonarImpl(PlayerCc::PlayerClient *playerClient) :
	m_sonar(new RangerProxy(playerClient, 0))
{
	for (unsigned int i = getMinimumSensorNumber(); i <= getMaximumSensorNumber(); ++i)
		m_lastValues[i] = 4;
	m_currentValues = m_lastValues;
}

SonarImpl::~SonarImpl()
{
	delete m_sonar;
	m_sonar = 0;
}

void SonarImpl::updateSensorData()
{
	m_lastValues = m_currentValues;

	for (unsigned int i = getMinimumSensorNumber(); i <= getMaximumSensorNumber(); ++i)
	{
		double newValue = m_sonar->GetRange(i);
		m_currentValues[i] = newValue;
	}
}

double SonarImpl::getDistanceForSensor(unsigned int sensorNumber) const
{
	assert(m_currentValues.count(sensorNumber) != 0);
	assert(m_lastValues.count(sensorNumber) != 0);
	double currentValue = m_currentValues.at(sensorNumber);
	double lastValue = m_lastValues.at(sensorNumber);
	return std::min<double>(lastValue, currentValue);
}

void SonarImpl::writeDataToFile(const string &fileName) const
{
	fstream file(fileName.c_str(), ios::out | ios::trunc);

	for (unsigned int i = getMinimumSensorNumber(); i <= getMaximumSensorNumber(); ++i)
		file << i << ": " << getDistanceForSensor(i) << endl;

	file.close();
}

SonarImpl::SonarImpl(const SonarImpl &)
{ }

void SonarImpl::operator=(const SonarImpl &)
{ }
