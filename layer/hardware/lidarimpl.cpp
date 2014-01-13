#include "layer/hardware/lidarimpl.h"
#include <libplayerc++/playerc++.h>
#include <iostream>
#include <fstream>

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

double LidarImpl::getDistance(int angle) const
{
	assert(angle >= getMinimumSensorNumber());
	assert(angle <= getMaximumSensorNumber());
	return m_laser->GetRange(angle);
}

void LidarImpl::writeDataToFile(const string &fileName) const
{
	fstream file(fileName.c_str(), ios_base::out | ios_base::trunc);

	for (int i = getMinimumSensorNumber(); i <= getMaximumSensorNumber(); ++i)
		file << i << ": " << getDistance(i) << endl;

	file.close();
}

LidarImpl::LidarImpl(const LidarImpl &)
{ }

void LidarImpl::operator=(const LidarImpl &)
{ }
