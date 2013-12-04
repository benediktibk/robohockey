#include "layer/strategy/initialstate.h"

using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

InitialState::InitialState(Robot &robot, Field &field) :
    State(robot, field)
{ }

State* InitialState::nextState()
{
    return new Calibrate(m_robot, m_field);
}

void InitialState::update()
{ }
