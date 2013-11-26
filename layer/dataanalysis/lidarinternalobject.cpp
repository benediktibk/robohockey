#include "layer/dataanalysis/lidarinternalobject.h"
#include "common/point.h"
#include "common/compare.h"
#include <math.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::DataAnalysis;

LidarInternalObject::LidarInternalObject() :
	m_distance(0),
	m_widthInMeter(0)
{ }

LidarInternalObject::LidarInternalObject(const Angle &width, const Angle &orientation, double distance) :
	m_width(width),
	m_orientationRelativeToRobot(orientation),
	m_distance(distance),
	m_widthInMeter(0)
{
	calculateWidthInMeter();
}

double LidarInternalObject::getWidthInMeter() const
{
	return m_widthInMeter;
}

Point LidarInternalObject::getPositionRelativeToRobot() const
{
	double totalDistance = m_distance + m_widthInMeter/2;
	return Point(totalDistance, m_orientationRelativeToRobot);
}

const Angle &LidarInternalObject::getOrientationRelativeToRobot() const
{
	return m_orientationRelativeToRobot;
}

double LidarInternalObject::getDistance() const
{
	return m_distance;
}

void LidarInternalObject::calculateWidthInMeter()
{
	Compare compare(0.001);

	if (compare.isFuzzyEqual(m_width, Angle(0)))
		m_widthInMeter = 0;
	else
		m_widthInMeter = 2*m_distance/(1/tan(m_width.getValueBetweenMinusPiAndPi()/2) - 1);
}
