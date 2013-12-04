#include "layer/strategy/initialstate.h"
#include "layer/strategy/referee.h"

using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

InitialState::InitialState(Robot &robot, Field &field, Referee &referee) :
    State(robot, field, referee)
{ }

State* InitialState::nextState()
{
    if(m_referee.detectionStart())
        return new Calibrate(m_robot, m_field, m_referee);
    else
        return 0;
}

void InitialState::update()
{}
