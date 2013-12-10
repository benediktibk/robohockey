#include "layer/strategy/drivetofinalposition.h"
#include "layer/strategy/achievegoals.h"
#include "layer/strategy/pause.h"
#include "layer/strategy/hideenemypucks.h"
#include "layer/strategy/referee.h"
#include "layer/autonomous/field.h"

using namespace RoboHockey::Layer::Strategy;

DriveToFinalPosition::DriveToFinalPosition(Robot &robot, Field &field, Referee &referee) :
    State(robot, field, referee)
{ }

State *DriveToFinalPosition::nextState()
{
    if(m_referee.stopMovement() || m_referee.gameOver())
        return new Pause(m_robot, m_field, m_referee);
    else if(m_field.achievedGoals() < 3)
        return new AchieveGoals(m_robot, m_field, m_referee);
    else
        return 0;
}

void DriveToFinalPosition::update()
{
}


