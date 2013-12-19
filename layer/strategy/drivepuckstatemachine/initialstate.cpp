#include "layer/strategy/drivepuckstatemachine/initialstate.h"
#include "layer/strategy/drivepuckstatemachine/findpuckstate.h"
#include "layer/strategy/common/referee.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

InitialState::InitialState(Robot &robot, Field &field, Referee &referee, DrivePuck *drivePuck) :
	State(robot, field, referee),
	m_drivePuck(drivePuck)
{ }

State* InitialState::nextState()
{
    if(m_referee.detectionStart())
		return new FindPuckState(m_robot, m_field, m_referee, m_drivePuck);
    else
        return 0;
}

void InitialState::update()
{}
