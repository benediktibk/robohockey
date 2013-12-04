#include "layer/strategy/calibrate.h"
using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

Calibrate::Calibrate(Robot &robot, Field &field, Referee &referee) :
    State(robot, field, referee)
{ }

State* Calibrate::nextState()
{
    return new AchieveGoals(m_robot, m_field, m_referee);
}

void Calibrate::update()
{ }




