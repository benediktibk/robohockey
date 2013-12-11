#include "layer/strategy/fielddetectionstatemachine/initialstate.h"
#include "layer/strategy/common/referee.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::FieldDetectionStateMachine;
using namespace RoboHockey::Layer::Autonomous;

InitialState::InitialState(Robot &robot, Field &field, Referee &referee) :
    State(robot, field, referee)
{ }

State* InitialState::nextState()
{
    if(m_referee.detectionStart())
		return 0;
    else
        return 0;
}

void InitialState::update()
{}
