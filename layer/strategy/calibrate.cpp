#include "layer/strategy/calibrate.h"
#include "layer/strategy/referee.h"
#include "layer/strategy/achievegoals.h"
#include "layer/strategy/pause.h"

using namespace RoboHockey::Layer::Strategy;
using namespace RoboHockey::Layer::Autonomous;

Calibrate::Calibrate(Robot &robot, Field &field, Referee &referee) :
    State(robot, field, referee)
{ }

State* Calibrate::nextState()
{
    if(m_referee.gameStart())
        return new AchieveGoals(m_robot, m_field, m_referee);
    return new Pause(m_robot, m_field, m_referee);
}

void Calibrate::update()
{ }




