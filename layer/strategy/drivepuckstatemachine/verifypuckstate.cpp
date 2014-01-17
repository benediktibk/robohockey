#include "layer/strategy/drivepuckstatemachine/verifypuckstate.h"
#include "layer/strategy/drivepuckstatemachine/collectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

VerifyPuckState::VerifyPuckState(Robot &robot, Field &field, Referee &referee, RoboHockey::Common::Logger &logger, ColorDependentPuckTargetFetcher &puckTargetFetcher):
	State(robot, field, referee, logger, true),
	m_puckTargetFetcher(puckTargetFetcher)
{ }

State *VerifyPuckState::nextState()
{
	if(m_robot.isPuckCollectable() && m_field.isPuckOfColorInFront(m_puckTargetFetcher.getColorOfTargetPucks()))
		return new CollectPuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher);
	else
		return new DriveToCollectPuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher);
}

std::string VerifyPuckState::getName()
{
	return "VerifyPuck";
}

void VerifyPuckState::updateInternal()
{
}
