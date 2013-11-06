#include "layer/hardware/lidarimpl.h"
#include <libplayerc++/playerc++.h>
#include <iostream>

using namespace RoboHockey::Layer::Hardware;
using namespace PlayerCc;
using namespace std;

LidarImpl::LidarImpl(PlayerClient *playerClient) :
	m_laser(new LaserProxy(playerClient, 0))
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

bool LidarImpl::isValid() const
{
	if (m_laser->GetCount() == getMaximumSensorNumber() - getMinimumSensorNumber() + 1)
		return true;

	cout << "maximum sensor number of the lidar is " << m_laser->GetCount() << endl;
	return false;
}
