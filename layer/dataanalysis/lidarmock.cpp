#include "layer/dataanalysis/lidarmock.h"
#include "common/robotposition.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;

LidarMock::LidarMock() :
	m_objects(Point()),
	m_puckCollected(false),
	m_puckCollectable(false)
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
	return m_puckCollectable;
}

bool LidarMock::isPuckCollected() const
{
	return m_puckCollected;
}

void LidarMock::setAllObjects(const LidarObjects &objects)
{
	m_objects = objects;
}

void LidarMock::setPuckCollected(bool value)
{
	m_puckCollected = value;
}

void LidarMock::setPuckCollectable(bool value)
{
	m_puckCollectable = value;
}
