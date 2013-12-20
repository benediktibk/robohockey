#include "layer/strategy/common/drivepucktoachivegoals.h"
#include "common/robotposition.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Common;
using namespace std;

DrivePuckToAchiveGoals::DrivePuckToAchiveGoals()
{ }

list<RobotPosition> DrivePuckToAchiveGoals::getTargetPositions()
{
	return list<RobotPosition>();
}

list<RobotPosition> DrivePuckToAchiveGoals::getPositionsToCollectPuck()
{
	return list<RobotPosition>();
}

FieldColor DrivePuckToAchiveGoals::getColorOfTargetPucks()
{
	return FieldColorUnknown;
}

unsigned int DrivePuckToAchiveGoals::getNumberOfKnownPucksNotInTarget()
{
	return 0;
}

