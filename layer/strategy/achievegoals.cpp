#include "layer/strategy/achievegoals.h"

using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

AchieveGoals::AchieveGoals(Robot &robot, Field &field) :
    State(robot, field)
{ }

State* AchieveGoals::nextState()
{
    return 0;
}

void AchieveGoals::update()
{ }
