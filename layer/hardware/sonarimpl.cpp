#include "layer/hardware/sonarimpl.h"
#include <player-3.0/libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;
using namespace PlayerCc;

SonarImpl::SonarImpl(PlayerCc::PlayerClient *playerClient) :
	m_sonar(new SonarProxy(playerClient, 0))
{
}

double SonarImpl::getDistanceForSensor(unsigned int sensorNumber)
{
	return m_sonar->GetScan(sensorNumber);
}
