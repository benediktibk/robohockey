#include "layer/strategy/drivepuckstatemachine/collectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetopositionstate.h"
#include "layer/strategy/common/referee.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

CollectPuckState::CollectPuckState(Robot &robot, Field &field, Referee &referee, DrivePuck *drivePuck) :
	State(robot, field, referee, false),
	m_drivePuck(drivePuck),
	m_puckCollected(false)
{ }

State* CollectPuckState::nextState()
{
	if(m_puckCollected)
		return new DriveToPositionState(m_robot, m_field, m_referee, m_drivePuck);
	else
		return 0;
}

void CollectPuckState::updateInternal()
{}
