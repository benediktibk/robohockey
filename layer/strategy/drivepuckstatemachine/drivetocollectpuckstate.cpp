#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/findpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/initialstate.h"
#include "layer/strategy/drivepuckstatemachine/verifypuckstate.h"
#include "layer/strategy/common/waitcyclesstate.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

DriveToCollectPuckState::DriveToCollectPuckState(Robot &robot, Field &field, Referee &referee, RoboHockey::Common::Logger &logger, const ColorDependentPuckTargetFetcher &puckTargetFetcher) :
	State(robot, field, referee, logger, true),
	m_puckTargetFetcher(puckTargetFetcher)
{ }

State* DriveToCollectPuckState::nextState()
{
	if(m_puckTargetFetcher.getNumberOfKnownPucksNotInEnemyThird() == 0)
		return new FindPuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher);
	else
		return new DriveToState(
					m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher.getPositionsToCollectPuck(),
					new WaitCyclesState(m_robot, m_field, m_referee, m_logger,
							new VerifyPuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher), 5),
					new InitialState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher));
}

std::string DriveToCollectPuckState::getName()
{
	return "DriveToCollectPuck";
}

void DriveToCollectPuckState::updateInternal()
{ }
