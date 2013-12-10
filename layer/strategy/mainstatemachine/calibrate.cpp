#include "layer/strategy/mainstatemachine/calibrate.h"
#include "layer/strategy/mainstatemachine/referee.h"
#include "layer/strategy/mainstatemachine/achievegoals.h"
#include "layer/strategy/mainstatemachine/pause.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;

Calibrate::Calibrate(Robot &robot, Field &field, Referee &referee) :
    State(robot, field, referee)
{ }

State* Calibrate::nextState()
{
    if(m_referee.gameStart())
        return new AchieveGoals(m_robot, m_field, m_referee);
    else if(m_referee.stopMovement() || m_referee.gameOver())
        return new Pause(m_robot, m_field, m_referee);
    return 0;
}

void Calibrate::update()
{ }




