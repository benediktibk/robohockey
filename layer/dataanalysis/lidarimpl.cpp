#include "layer/dataanalysis/lidarimpl.h"
#include "layer/hardware/lidar.h"
#include "common/discretefunction.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

LidarImpl::LidarImpl(Hardware::Lidar &lidar) :
	m_lidar(lidar)
{ }

LidarObjects LidarImpl::getAllObjects(const Point &ownPosition) const
{
	LidarObjects objects(ownPosition);
	DiscreteFunction distances(0, 360);

	for (size_t i = 0; i <= 360; ++i)
		distances.setValue(i, m_lidar.getDistance(i));

	distances.suppressNoise();
	distances.differentiate(1);

	return objects;
}
