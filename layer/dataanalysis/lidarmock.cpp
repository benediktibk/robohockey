#include "layer/dataanalysis/lidarmock.h"
#include "common/robotposition.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;

LidarMock::LidarMock() :
	m_objects(Point())
{ }

LidarObjects LidarMock::getAllObjects(const RobotPosition &) const
{
	return m_objects;
}

bool LidarMock::isObstacleInFront(double) const
{
	return false;
}

void LidarMock::updateSensorData()
{ }

bool LidarMock::isPuckCollectable() const
{
	return false;
}

bool LidarMock::isPuckCollected() const
{
	return false;
}

void LidarMock::setAllObjects(const LidarObjects &objects)
{
	m_objects = objects;
}
