#include "layer/hardware/lidarimpl.h"
#include <libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;
using namespace PlayerCc;

LidarImpl::LidarImpl(PlayerClient *playerClient) :
	m_laser(new RangerProxy(playerClient, 0))
{ }

LidarImpl::~LidarImpl()
{
	delete m_laser;
	m_laser = 0;
}

double LidarImpl::getDistance(unsigned int angle)
{
	return m_laser->GetRange(angle);
}
