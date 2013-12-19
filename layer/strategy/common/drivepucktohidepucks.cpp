#include "layer/strategy/common/drivepucktohidepucks.h"
#include "common/robotposition.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Common;
using namespace std;

DrivePuckToHidePucks::DrivePuckToHidePucks()
{ }

vector<RobotPosition> DrivePuckToHidePucks::getTargetPoint()
{
	return vector<RobotPosition>();
}

vector<RobotPosition> DrivePuckToHidePucks::getPointToCollectPuck()
{
	return vector<RobotPosition>();
}

FieldColor DrivePuckToHidePucks::getColorOfTargetPucks()
{
	return FieldColorUnknown;
}

