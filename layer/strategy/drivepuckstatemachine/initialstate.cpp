#include "layer/strategy/drivepuckstatemachine/initialstate.h"
#include "layer/strategy/drivepuckstatemachine/findpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/leavepuckstate.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

InitialState::InitialState(Robot &robot, Field &field, Referee &referee, RoboHockey::Common::Logger &logger, const ColorDependentPuckTargetFetcher &puckTargetFetcher) :
	State(robot, field, referee, logger, false),
	m_puckTargetFetcher(puckTargetFetcher)
{ }

State* InitialState::nextState()
{
	if(m_robot.isPuckCollected())
		return new LeavePuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher, false);
	if(m_puckTargetFetcher.getNumberOfKnownPucksNotInEnemyThird() > 0)
		return new DriveToCollectPuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher);
	else
		return new FindPuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher);
}

std::string InitialState::getName()
{
	return "Initial";
}

void InitialState::updateInternal()
{}
