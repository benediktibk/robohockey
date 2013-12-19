#include "layer/strategy/common/drivepucktoachivegoals.h"
#include "common/robotposition.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Common;
using namespace std;

DrivePuckToAchiveGoals::DrivePuckToAchiveGoals()
{ }

vector<RobotPosition> DrivePuckToAchiveGoals::getTargetPoint()
{
	return vector<RobotPosition>();
}

vector<RobotPosition> DrivePuckToAchiveGoals::getPointToCollectPuck()
{
	return vector<RobotPosition>();
}

FieldColor DrivePuckToAchiveGoals::getColorOfTargetPucks()
{
	return FieldColorUnknown;
}

