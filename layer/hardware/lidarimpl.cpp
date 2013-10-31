#include "layer/hardware/lidarimpl.h"
#include <libplayerc++/playerc++.h>

using namespace RoboHockey::Layer::Hardware;
using namespace PlayerCc;

LidarImpl::LidarImpl(PlayerClient *playerClient) :
	m_laser(new LaserProxy(playerClient, 0))
{ }

LidarImpl::~LidarImpl()
{
	delete m_laser;
}

double LidarImpl::getDistance(unsigned int angle)
{
	return m_laser->GetRange(angle);
}
