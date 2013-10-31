#include "layer/hardware/sonarimpl.h"
#include <libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;
using namespace PlayerCc;

SonarImpl::SonarImpl(PlayerCc::PlayerClient *playerClient) :
	m_sonar(new SonarProxy(playerClient, 0))
{
}

SonarImpl::~SonarImpl()
{
	delete m_sonar;
	m_sonar = 0;
}

double SonarImpl::getDistanceForSensor(unsigned int sensorNumber)
{
	return m_sonar->GetScan(sensorNumber);
}
