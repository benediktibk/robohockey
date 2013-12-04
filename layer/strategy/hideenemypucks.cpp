#include "layer/strategy/hideenemypucks.h"

using namespace RoboHockey::Layer::Strategy;

HideEnemyPucks::HideEnemyPucks(Autonomous::Robot &robot, Autonomous::Field &field):
    State(robot, field)
{ }

State* HideEnemyPucks::nextState()
{
    return new Pause(m_robot, m_field);
}

void HideEnemyPucks::update()
{ }

