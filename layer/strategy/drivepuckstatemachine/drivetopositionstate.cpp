#include "layer/strategy/drivepuckstatemachine/drivetopositionstate.h"
#include "layer/strategy/drivepuckstatemachine/leavepuckstate.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

DriveToPositionState::DriveToPositionState(Robot &robot, Field &field, Referee &referee, DrivePuck *drivePuck) :
	State(robot, field, referee, true),
	m_drivePuck(drivePuck)
{ }

DriveToPositionState::~DriveToPositionState()
{
	delete m_drivePuck;
	m_drivePuck = 0;
}

State* DriveToPositionState::nextState()
{
	if(m_robot.reachedTarget() || m_robot.cantReachTarget())
		return new LeavePuckState(m_robot, m_field, m_referee, m_drivePuck);
	else
		return 0;
}

std::string DriveToPositionState::getName()
{
	return "DriveToPosition";
}

void DriveToPositionState::updateInternal()
{}
