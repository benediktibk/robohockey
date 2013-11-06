#include "layer/hardware/lidarimpl.h"
#include <libplayerc++/playerc++.h>
#include <iostream>

using namespace RoboHockey::Layer::Hardware;
using namespace PlayerCc;
using namespace std;

LidarImpl::LidarImpl(PlayerClient *playerClient) :
	m_laser(new RangerProxy(playerClient, 1))
{ }

LidarImpl::~LidarImpl()
{
	delete m_laser;
	m_laser = 0;
}

double LidarImpl::getDistance(unsigned int angle)
{
	assert(angle >= getMinimumSensorNumber());
	assert(angle <= getMaximumSensorNumber());
	return m_laser->GetRange(angle);
}
