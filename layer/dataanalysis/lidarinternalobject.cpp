#include "layer/dataanalysis/lidarinternalobject.h"
#include "common/point.h"
#include "common/compare.h"
#include <math.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::DataAnalysis;

LidarInternalObject::LidarInternalObject(const Angle &width, const Angle &orientation, double distance) :
	m_width(width),
	m_orientationRelativeToRobot(orientation),
	m_distance(distance)
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

void LidarInternalObject::calculateWidthInMeter()
{
	Compare compare(0.001);

	if (compare.isFuzzyEqual(m_width, Angle(0)))
		m_widthInMeter = 0;
	else
		m_widthInMeter = 2*m_distance/(1/tan(m_width.getValueBetweenMinusPiAndPi()/2) - 1);
}
