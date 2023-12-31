#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/findpuckturntostate.h"
#include "layer/strategy/drivepuckstatemachine/initialstate.h"
#include "layer/strategy/drivepuckstatemachine/verifypuckstate.h"
#include "layer/strategy/common/waitcyclesstate.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/strategy/drivepuckstatemachine/leavepuckstate.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

DriveToCollectPuckState::DriveToCollectPuckState(Robot &robot, Field &field, Referee &referee, RoboHockey::Common::Logger &logger, ColorDependentPuckTargetFetcher &puckTargetFetcher) :
	State(robot, field, referee, logger, true),
	m_puckTargetFetcher(puckTargetFetcher)
{ }

State* DriveToCollectPuckState::nextState()
{
	if(m_puckTargetFetcher.getNumberOfKnownPucksNotInEnemyThird() == 0)
		return new FindPuckTurnToState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher, m_field.getTargetsForTurningToUnknownObjects());
	else
		return new DriveToState(
					m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher.getPositionsToCollectPuck(),
					new WaitCyclesState(m_robot, m_field, m_referee, m_logger,
							new VerifyPuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher), 15, false),
					new InitialState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher),
					new LeavePuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher, false));
}

std::string DriveToCollectPuckState::getName()
{
	return "DriveToCollectPuck";
}

void DriveToCollectPuckState::updateInternal()
{ }
