#include "layer/strategy/mainstatemachine/pause.h"
#include "layer/strategy/mainstatemachine/calibrate.h"
#include "layer/strategy/mainstatemachine/referee.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::MainStateMachine;
using namespace RoboHockey::Layer::Autonomous;

Pause::Pause(Robot &robot, Field &field, Referee &referee) :
    State(robot, field, referee)
{ }

State* Pause::nextState()
{
    if(m_referee.detectionStart())
        return new Calibrate(m_robot, m_field, m_referee);
    else if(m_referee.gameStart())
        return new AchieveGoals(m_robot, m_field, m_referee);
    else
        return 0;
}

void Pause::update()
{ }

