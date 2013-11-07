#include "layer/hardware/lidarmock.h"
#include <assert.h>

using namespace RoboHockey::Layer::Hardware;
using namespace std;

LidarMock::LidarMock() :
	m_callsToGetDistance(0)
{ }

LidarMock::LidarMock(double defaultDistance) :
	m_defaultDistance(defaultDistance)
{ }

double LidarMock::getDistance(unsigned int angle)
{
	assert(angle >= getMinimumSensorNumber());
	assert(angle <= getMaximumSensorNumber());

	++m_callsToGetDistance;

	map<unsigned int, double>::const_iterator value = m_valueForAngle.find(angle);

	if (value == m_valueForAngle.end())
		return m_defaultDistance;
	else
		return value->second;
}

void LidarMock::setValueForAngle(unsigned int angle, double value)
{
	m_valueForAngle[angle] = value;
}

unsigned int LidarMock::getCallsToGetDistance() const
{
	return m_callsToGetDistance;
}