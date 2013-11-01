#include "layer/hardware/lidarstub.h"

using namespace RoboHockey::Layer::Hardware;
using namespace std;

LidarStub::LidarStub() :
	m_defaultDistance(0)
{ }

LidarStub::LidarStub(double defaultDistance) :
	m_defaultDistance(defaultDistance)
{ }

double LidarStub::getDistance(unsigned int angle)
{
	map<unsigned int, double>::const_iterator value = m_valueForAngle.find(angle);

	if (value == m_valueForAngle.end())
		return m_defaultDistance;
	else
		return value->second;
}

void LidarStub::setValueForAngle(unsigned int angle, double value)
{
	m_valueForAngle[angle] = value;
}
