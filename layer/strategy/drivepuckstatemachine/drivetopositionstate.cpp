#include "layer/strategy/drivepuckstatemachine/drivetopositionstate.h"
#include "layer/strategy/drivepuckstatemachine/findpuckstate.h"
#include "layer/strategy/common/referee.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

DriveToPositionState::DriveToPositionState(Robot &robot, Field &field, Referee &referee, DrivePuck *drivePuck) :
	State(robot, field, referee, true),
	m_drivePuck(drivePuck),
	m_puckAtPosition(false)
{ }

State* DriveToPositionState::nextState()
{
	if(m_puckAtPosition)
		return new FindPuckState(m_robot, m_field, m_referee, m_drivePuck);
	else
		return 0;
}

void DriveToPositionState::updateInternal()
{}
