#include "layer/strategy/drivepuckstatemachine/collectpuckstate.h"
#include "layer/strategy/common/referee.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

CollectPuckState::CollectPuckState(Robot &robot, Field &field, Referee &referee, DrivePuck *drivePuck) :
	State(robot, field, referee),
	m_drivePuck(drivePuck)
{ }

State* CollectPuckState::nextState()
{
	if(m_referee.detectionStart())
		return 0;
	else
		return 0;
}

void CollectPuckState::update()
{}
