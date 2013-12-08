#include "layer/strategy/achievegoals.h"
#include "layer/strategy/referee.h"
#include "layer/autonomous/field.h"
#include "layer/strategy/pause.h"
#include "hideenemypucks.h"

using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

AchieveGoals::AchieveGoals(Robot &robot, Field &field, Referee &referee) :
    State(robot, field, referee)
{ }

State* AchieveGoals::nextState()
{
    if(m_referee.stopMovement() || m_referee.gameOver())
        return new Pause(m_robot, m_field, m_referee);
    else if(m_field.achievedGoals() < 3)
        return 0;
    else
        return new HideEnemyPucks(m_robot, m_field, m_referee);
}

void AchieveGoals::update()
{ }
