#include "layer/strategy/calibrate.h"
using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

Calibrate::Calibrate(Robot &robot, Field &field) :
    State(robot, field)
{ }

State* Calibrate::nextState()
{
    return new AchieveGoals(m_robot, m_field);
}

void Calibrate::update()
{ }




