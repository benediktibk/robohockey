#include "layer/strategy/mainstatemachine/achievegoals.h"
#include "layer/strategy/mainstatemachine/referee.h"
#include "layer/autonomous/field.h"
#include "layer/strategy/mainstatemachine/pause.h"
#include "layer/strategy/mainstatemachine/hideenemypucks.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
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
