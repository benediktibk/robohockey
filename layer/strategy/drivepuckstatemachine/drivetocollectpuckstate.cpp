#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/collectpuckstate.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

DriveToCollectPuckState::DriveToCollectPuckState(Robot &robot, Field &field, Referee &referee, DrivePuck *drivePuck) :
	State(robot, field, referee),
	m_drivePuck(drivePuck),
	m_foundPuck(false)
{ }

State* DriveToCollectPuckState::nextState()
{
	if(m_foundPuck)
		return new CollectPuckState(m_robot, m_field, m_referee, m_drivePuck);
	else
		return 0;
}

void DriveToCollectPuckState::update()
{
}
