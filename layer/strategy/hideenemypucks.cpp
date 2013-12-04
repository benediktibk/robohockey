#include "layer/strategy/hideenemypucks.h"
#include "layer/strategy/referee.h"
#include "layer/autonomous/field.h"

using namespace RoboHockey::Layer::Strategy;

HideEnemyPucks::HideEnemyPucks(Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee):
    State(robot, field, referee)
{ }

State* HideEnemyPucks::nextState()
{
    if(m_referee.gameOver() || m_referee.stopMovement())
        return new Pause(m_robot, m_field, m_referee);
    else if(m_field.achievedGoals() < 3)
        return new AchieveGoals(m_robot, m_field, m_referee);
    else
        return 0;
}

void HideEnemyPucks::update()
{ }

