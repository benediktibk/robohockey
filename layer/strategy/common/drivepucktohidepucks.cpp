#include "layer/strategy/common/drivepucktohidepucks.h"
#include "common/robotposition.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Common;
using namespace std;

DrivePuckToHidePucks::DrivePuckToHidePucks()
{ }

list<RobotPosition> DrivePuckToHidePucks::getTargetPositions()
{
	return list<RobotPosition>();
}

list<RobotPosition> DrivePuckToHidePucks::getPositionsToCollectPuck()
{
	return list<RobotPosition>();
}

FieldColor DrivePuckToHidePucks::getColorOfTargetPucks()
{
	return FieldColorUnknown;
}

unsigned int DrivePuckToHidePucks::getNumberOfKnownPucksNotInTarget()
{
	return 0;
}

