#include "layer/strategy/mainstatemachine/drivetofinalposition.h"
#include "layer/strategy/mainstatemachine/achievegoals.h"
#include "layer/strategy/mainstatemachine/pause.h"
#include "layer/strategy/mainstatemachine/hideenemypucks.h"
#include "layer/strategy/mainstatemachine/referee.h"
#include "layer/autonomous/field.h"
#include "layer/autonomous/robot.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;

DriveToFinalPosition::DriveToFinalPosition(Robot &robot, Field &field, Referee &referee) :
    State(robot, field, referee)
{ }

State *DriveToFinalPosition::nextState()
{
    if(m_referee.stopMovement() || m_referee.gameOver())
        return new Pause(m_robot, m_field, m_referee);
    else if(m_field.achievedGoals() < 3)
        return new AchieveGoals(m_robot, m_field, m_referee);
    else if(m_robot.reachedTarget())
        return new Pause(m_robot, m_field, m_referee);
    else if(m_field.enemyHiddenPucks() < 3 && m_field.achievedGoals() >= 3)
        return new HideEnemyPucks(m_robot, m_field, m_referee);
    else
        return 0;
}

void DriveToFinalPosition::update()
{
}


