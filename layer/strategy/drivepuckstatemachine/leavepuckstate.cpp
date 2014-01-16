#include "layer/strategy/drivepuckstatemachine/leavepuckstate.h"
#include "layer/strategy/drivepuckstatemachine/initialstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/findpuckturntostate.h"
#include "common/robotposition.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

LeavePuckState::LeavePuckState(Robot &robot, Field &field, Referee &referee, RoboHockey::Common::Logger &logger, const ColorDependentPuckTargetFetcher &puckTargetFetcher, bool shouldIncreaseGoalCount) :
	State(robot, field, referee, logger, true),
	m_puckTargetFetcher(puckTargetFetcher),
	m_shouldIncreaseGoalCount(shouldIncreaseGoalCount)
{ }

State* LeavePuckState::nextState()
{
	if(m_robot.cantReachTarget())
		return new InitialState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher);
	else if(m_robot.reachedTarget() && m_puckTargetFetcher.getNumberOfKnownPucksNotInEnemyThird() == 0)
		return new FindPuckTurnToState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher, m_field.getTargetsForTurningToUnknownObjects());
	else if(m_robot.reachedTarget() && m_puckTargetFetcher.getNumberOfKnownPucksNotInEnemyThird() != 0)
		return new DriveToCollectPuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher);
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

	if (m_shouldIncreaseGoalCount)
	{
		m_field.increaseNumberOfEstimatedGoals();
		m_referee.reportGoal();
	}
}
