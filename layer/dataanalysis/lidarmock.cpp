#include "layer/dataanalysis/lidarmock.h"
#include "common/robotposition.h"

using namespace RoboHockey::Layer::DataAnalysis;
using namespace RoboHockey::Common;

LidarObjects LidarMock::getAllObjects(const RobotPosition &ownPosition) const
{
	return LidarObjects(ownPosition.getPosition());
}
