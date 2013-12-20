#include "layer/strategy/drivepuckstatemachine/findpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/collectpuckstate.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"
#include "common/robotposition.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

FindPuckState::FindPuckState(Robot &robot, Field &field, Referee &referee, DrivePuck *drivePuck) :
	DriveTo(robot, field, referee, field.getTargetsForSearchingPucks(),
			new CollectPuckState(robot, field, referee, drivePuck),
			new FindPuckState(robot, field, referee, drivePuck))
{ }

std::string FindPuckState::getName()
{
	return "FindPuck";
}
