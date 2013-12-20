#include "layer/dataanalysis/lidarmock.h"
#include "common/robotposition.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;

LidarMock::LidarMock() :
	m_objects(Point()),
	m_puckCollected(false),
	m_puckCollectable(false),
	m_canBeSeen(true),
	m_canBeSeenPartly(true)
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

bool LidarMock::isPuckCollectable(double, const Angle&) const
{
	return m_puckCollectable;
}

bool LidarMock::isPuckCollected() const
{
	return m_puckCollected;
}

Angle LidarMock::getMaximumAngleRight() const
{
	return Angle::getQuarterRotation()*(-1);
}

Angle LidarMock::getMaximumAngleLeft() const
{
	return Angle::getQuarterRotation();
}

bool LidarMock::canBeSeen(const Circle &, const RobotPosition &) const
{
	return m_canBeSeen;
}

bool LidarMock::canBeSeenPartly(const Circle &, const RobotPosition &) const
{
	return m_canBeSeenPartly;
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

void LidarMock::setCanBeSeen(bool value)
{
	m_canBeSeen = value;
}

void LidarMock::setCanBeSeenPartly(bool value)
{
	m_canBeSeenPartly = value;
}
