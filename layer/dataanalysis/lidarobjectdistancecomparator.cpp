#include "layer/dataanalysis/lidarobjectdistancecomparator.h"
#include "layer/dataanalysis/lidarobject.h"

using namespace RoboHockey::Layer::DataAnalysis;

LidarObjectDistanceComparator::LidarObjectDistanceComparator(const RoboHockey::Common::Point &ownPosition) :
	m_ownPosition(ownPosition)
{ }

bool LidarObjectDistanceComparator::operator()(const LidarObject &one, const LidarObject &two) const
{
	return one.getDistanceTo(m_ownPosition) < two.getDistanceTo(m_ownPosition);
}
