#include "layer/dataanalysis/lidarstub.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;

LidarObjects LidarStub::getAllObjects(const Point &ownPosition) const
{
	return LidarObjects(ownPosition);
}
