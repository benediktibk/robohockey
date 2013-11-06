#include "layer/hardware/lidarmock.h"

using namespace RoboHockey::Layer::Hardware;

LidarMock::LidarMock() :
	m_callsToGetDistance(0)
{ }

double LidarMock::getDistance(unsigned int)
{
	++m_callsToGetDistance;
	return 0;
}

unsigned int LidarMock::getCallsToGetDistance() const
{
	return m_callsToGetDistance;
}

bool LidarMock::isValid() const
{
	return true;
}
