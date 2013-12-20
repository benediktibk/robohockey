#include "layer/strategy/drivepuckstatemachine/findpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/common/driveto.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

FindPuckState::FindPuckState(Robot &robot, Field &field, Referee &referee, DrivePuck *drivePuck):
	State(robot, field, referee, true),
	m_drivePuck(drivePuck)
{ }

State *FindPuckState::nextState()
{
	return new DriveTo(m_robot, m_field, m_referee, m_field.getTargetsForSearchingPucks(),
					   new DriveToCollectPuckState(m_robot, m_field, m_referee, m_drivePuck),
					   new FindPuckState(m_robot, m_field, m_referee, m_drivePuck));

}

std::string FindPuckState::getName()
{
	return "FindPuck";
}

void FindPuckState::updateInternal()
{
}
