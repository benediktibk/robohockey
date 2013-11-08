#include "layer/strategy/initialstate.h"

using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

InitialState::InitialState(Robot &robot) :
	State(robot)
{ }

State* InitialState::nextState()
{
	return 0;
}

void InitialState::update()
{ }
