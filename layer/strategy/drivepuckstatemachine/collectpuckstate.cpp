#include "layer/strategy/drivepuckstatemachine/collectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetopositionstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "common/robotposition.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

CollectPuckState::CollectPuckState(Robot &robot, Field &field, Referee &referee, DrivePuck *drivePuck) :
	State(robot, field, referee, true),
	m_drivePuck(drivePuck)
{ }

State* CollectPuckState::nextState()
{
	if(m_robot.isPuckCollected())
		return new DriveToPositionState(m_robot, m_field, m_referee, m_drivePuck);
	else if(m_robot.cantReachTarget())
		return new DriveToCollectPuckState(m_robot, m_field, m_referee, m_drivePuck);
	else
		return 0;
}

void CollectPuckState::updateInternal()
{
	m_robot.collectPuckInFront(m_drivePuck->getPositionsToCollectPuck().front().getPosition());
}
