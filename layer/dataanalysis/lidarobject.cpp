#include "layer/dataanalysis/lidarobject.h"

using namespace RoboHockey::Layer::DataAnalysis;

LidarObject::LidarObject() :
	m_diameter(0)
{ }

LidarObject::LidarObject(const RoboHockey::Common::Point &position, double diameter) :
	m_position(position),
	m_diameter(diameter)
{ }

const RoboHockey::Common::Point &LidarObject::getPosition() const
{
	return m_position;
}

double LidarObject::getDiameter() const
{
	return m_diameter;
}
