#include "layer/strategy/fielddetectionstatemachine/checkgoalcolor.h"
#include "layer/strategy/common/referee.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;

CheckGoalColor::CheckGoalColor(Robot &robot, Field &field, Referee &referee) :
	State(robot, field, referee)
{ }

State* CheckGoalColor::nextState()
{
	return 0;
}

void CheckGoalColor::update()
{}
