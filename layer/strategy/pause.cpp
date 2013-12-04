#include "layer/strategy/pause.h"
#include "layer/strategy/calibrate.h"

using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

Pause::Pause(Robot &robot, Field &field, Referee &referee) :
    State(robot, field, referee)
{ }

State* Pause::nextState()
{
    return new Calibrate(m_robot, m_field, m_referee);
}

void Pause::update()
{ }

