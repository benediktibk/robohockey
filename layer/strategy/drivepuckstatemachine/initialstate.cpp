#include "layer/strategy/drivepuckstatemachine/initialstate.h"
#include "layer/strategy/drivepuckstatemachine/findpuckturntostate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/leavepuckstate.h"
#include "layer/autonomous/field.h"
#include "layer/autonomous/robot.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

InitialState::InitialState(Robot &robot, Field &field, Referee &referee, RoboHockey::Common::Logger &logger, ColorDependentPuckTargetFetcher &puckTargetFetcher) :
	State(robot, field, referee, logger, false),
	m_puckTargetFetcher(puckTargetFetcher)
{ }

State* InitialState::nextState()
{
	if(m_robot.isPuckCollected() || m_robot.stuckAtObstacle())
		return new LeavePuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher, false);
	if(m_puckTargetFetcher.getNumberOfKnownPucksNotInEnemyThird() > 0 && !m_puckTargetFetcher.isCantReachTargetLimitReached())
		return new DriveToCollectPuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher);
	else
		return new FindPuckTurnToState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher, m_field.getTargetsForTurningToUnknownObjects());
}

std::string InitialState::getName()
{
	return "Initial";
}

void InitialState::updateInternal()
{
	if(m_robot.cantReachTarget())
		m_puckTargetFetcher.increaseCantReachTargetCounter();
	else
		m_puckTargetFetcher.resetCantReachTargetCounter();
}
