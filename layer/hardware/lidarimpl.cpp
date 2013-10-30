#include "layer/hardware/lidarimpl.h"

using namespace RoboHockey::Layer::Hardware;
using namespace PlayerCc;

LidarImpl::LidarImpl(PlayerClient *playerClient) :
	m_laser(playerClient, 0)
{ }

double LidarImpl::getDistance(unsigned int angle)
{
	return m_laser.GetRange(angle);
}
