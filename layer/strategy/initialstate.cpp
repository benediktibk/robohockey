#include "layer/strategy/initialstate.h"

using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

InitialState::InitialState(Robot &robot, Field &field, Referee &referee) :
    State(robot, field, referee)
{ }

State* InitialState::nextState()
{
    return new Calibrate(m_robot, m_field, m_referee);
}

void InitialState::update()
{ }
