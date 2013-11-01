#include "layer/dataanalysis/lidarimpl.h"

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer;
using namespace RoboHockey::Layer::DataAnalysis;

LidarImpl::LidarImpl(const Hardware::Lidar &lidar) :
	m_lidar(lidar)
{ }

LidarObjects LidarImpl::getAllObjects(const Point &ownPosition) const
{
	LidarObjects objects(ownPosition);

	return objects;
}
