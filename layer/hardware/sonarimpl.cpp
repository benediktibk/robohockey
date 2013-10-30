#include "layer/hardware/sonarimpl.h"

using namespace RoboHockey::Layer::Hardware;
using namespace PlayerCc;

SonarImpl::SonarImpl(PlayerCc::PlayerClient *playerClient) :
	m_sonar(playerClient, 0)
{
}

double SonarImpl::getDistanceForSensor(unsigned int sensorNumber)
{
	return m_sonar[sensorNumber];
}
