#include "layer/strategy/drivepuckstatemachine/drivepucktopositionstate.h"
#include "layer/strategy/drivepuckstatemachine/leavepuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/autonomous/robot.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

DrivePuckToPositionState::DrivePuckToPositionState(Robot &robot, Field &field, Referee &referee, const DrivePuck &drivePuck) :
	State(robot, field, referee, true),
	m_drivePuck(drivePuck)
{ }

State *DrivePuckToPositionState::nextState()
{
	if(m_robot.isPuckCollected())
		return new DriveToState(
					m_robot, m_field, m_referee, m_drivePuck.getTargetPositions(),
					new LeavePuckState(m_robot, m_field, m_referee, m_drivePuck),
					new LeavePuckState(m_robot, m_field, m_referee, m_drivePuck));
	else
		return new DriveToCollectPuckState(m_robot, m_field, m_referee, m_drivePuck);
}

std::string DrivePuckToPositionState::getName()
{
	return "DriveToPosition";
}

void DrivePuckToPositionState::updateInternal()
{ }
