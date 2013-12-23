#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/collectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/findpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/initialstate.h"
#include "layer/strategy/common/driveto.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

DriveToCollectPuckState::DriveToCollectPuckState(Robot &robot, Field &field, Referee &referee, DrivePuck *drivePuck) :
	State(robot, field, referee, true),
	m_drivePuck(drivePuck)
{ }

State* DriveToCollectPuckState::nextState()
{
	if(m_drivePuck->getNumberOfKnownPucksNotInTarget() == 0)
		return new FindPuckState(m_robot, m_field, m_referee, m_drivePuck);
	else
		return new DriveTo(m_robot, m_field, m_referee, m_drivePuck->getPositionsToCollectPuck(),
						   new CollectPuckState(m_robot, m_field, m_referee, m_drivePuck),
						   new InitialState(m_robot, m_field, m_referee, m_drivePuck));
}

std::string DriveToCollectPuckState::getName()
{
	return "DriveToCollectPuck";
}

void DriveToCollectPuckState::updateInternal()
{ }
