#include "layer/strategy/hideenemypucks.h"

using namespace RoboHockey::Layer::Strategy;

HideEnemyPucks::HideEnemyPucks(Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee):
    State(robot, field, referee)
{ }

State* HideEnemyPucks::nextState()
{
    return new Pause(m_robot, m_field, m_referee);
}

void HideEnemyPucks::update()
{ }

