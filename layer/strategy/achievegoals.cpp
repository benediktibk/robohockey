#include "layer/strategy/achievegoals.h"
#include "layer/strategy/referee.h"

using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

AchieveGoals::AchieveGoals(Robot &robot, Field &field, Referee &referee) :
    State(robot, field, referee)
{ }

State* AchieveGoals::nextState()
{
    return 0;
}

void AchieveGoals::update()
{ }
