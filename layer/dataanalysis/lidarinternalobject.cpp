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
{ }

double LidarInternalObject::getWidthInMeter() const
{
	Compare compare(0.001);

	if (compare.isFuzzyEqual(m_width.getValueBetweenMinusPiAndPi(), 0))
		return 0;
	else
		return 2*m_distance/(1/tan(m_width.getValueBetweenMinusPiAndPi()/2) - 1);
}

Point LidarInternalObject::getPositionRelativeToRobot() const
{
	double diameter = getWidthInMeter();
	double totalDistance = m_distance + diameter/2;
	return Point(totalDistance, m_orientationRelativeToRobot);
}
