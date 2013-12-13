#include "layer/strategy/mainstatemachine/hideenemypucks.h"
#include "layer/strategy/mainstatemachine/drivetofinalposition.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/field.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;

HideEnemyPucks::HideEnemyPucks(Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee):
    State(robot, field, referee)
{ }

State* HideEnemyPucks::nextState()
{
    if(m_referee.gameOver() || m_referee.stopMovement())
        return new Pause(m_robot, m_field, m_referee);
    else if(m_field.getNumberOfAchievedGoals() < 3)
        return new AchieveGoals(m_robot, m_field, m_referee);
    else if(m_field.getNumberOfHiddenPucks() >= 3)
        return new DriveToFinalPosition(m_robot, m_field, m_referee);
    else
        return 0;
}

void HideEnemyPucks::update()
{ }

