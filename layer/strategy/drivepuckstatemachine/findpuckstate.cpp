#include "layer/strategy/drivepuckstatemachine/findpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/verifypuckstate.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"
#include "layer/strategy/common/waitcyclesstate.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

FindPuckState::FindPuckState(Robot &robot, Field &field, Referee &referee, const ColorDependentPuckTargetFetcher &puckTargetFetcher):
	State(robot, field, referee, true),
	m_puckTargetFetcher(puckTargetFetcher)
{ }

State *FindPuckState::nextState()
{
	return new DriveToState(
				m_robot, m_field, m_referee, m_field.getTargetsForSearchingPucks(),
				new WaitCyclesState(m_robot, m_field, m_referee,
					new VerifyPuckState(m_robot, m_field, m_referee, m_puckTargetFetcher), 10),
				new FindPuckState(m_robot, m_field, m_referee, m_puckTargetFetcher));
}

std::string FindPuckState::getName()
{
	return "FindPuck";
}

void FindPuckState::updateInternal()
{
}
