#include "layer/strategy/drivepuckstatemachine/collectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivepucktopositionstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "common/robotposition.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

CollectPuckState::CollectPuckState(Robot &robot, Field &field, Referee &referee, const ColorDependentPuckTargetFetcher &drivePuck) :
	State(robot, field, referee, true),
	m_drivePuck(drivePuck),
	m_isPuckNotCollectable(true)
{ }

State* CollectPuckState::nextState()
{
	if(m_robot.isPuckCollected())
		return new DrivePuckToPositionState(m_robot, m_field, m_referee, m_drivePuck);
	else if(m_robot.cantReachTarget() || m_isPuckNotCollectable)
		return new DriveToCollectPuckState(m_robot, m_field, m_referee, m_drivePuck);
	else
		return 0;
}

std::string CollectPuckState::getName()
{
	return "CollectPuck";
}

void CollectPuckState::updateInternal()
{
	if(m_robot.isPuckCollectable())
	{
		m_isPuckNotCollectable = false;
		m_robot.collectPuckInFront(
					m_field.getObjectsWithColorOrderdByDistance(
					m_drivePuck.getColorOfTargetPucks(),
					m_robot.getCurrentPosition().getPosition()).front().getCircle().getCenter());
	}
}
