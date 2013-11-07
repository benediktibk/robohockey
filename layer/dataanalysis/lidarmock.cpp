#include "layer/dataanalysis/lidarmock.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;

LidarObjects LidarMock::getAllObjects(const Point &ownPosition, double) const
{
	return LidarObjects(ownPosition);
}
