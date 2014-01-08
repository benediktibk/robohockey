#include "layer/strategy/drivepuckstatemachine/leavepuckstate.h"
#include "layer/strategy/drivepuckstatemachine/initialstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/findpuckstate.h"
#include "common/robotposition.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

LeavePuckState::LeavePuckState(Robot &robot, Field &field, Referee &referee, const DrivePuck &drivePuck) :
	State(robot, field, referee, true),
	m_drivePuck(drivePuck)
{ }

State* LeavePuckState::nextState()
{
	if(m_robot.cantReachTarget())
		return new InitialState(m_robot, m_field, m_referee, m_drivePuck);
	else if(m_robot.reachedTarget() && m_drivePuck.getNumberOfKnownPucksNotInTarget() == 0)
		return new FindPuckState(m_robot, m_field, m_referee, m_drivePuck);
	else if(m_robot.reachedTarget() && m_drivePuck.getNumberOfKnownPucksNotInTarget() != 0)
		return new DriveToCollectPuckState(m_robot, m_field, m_referee, m_drivePuck);
	else
		return 0;

}

std::string LeavePuckState::getName()
{
	return "LeavePuck";
}

void LeavePuckState::updateInternal()
{
	m_robot.leaveCollectedPuck();
}
