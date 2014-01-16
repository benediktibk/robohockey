#include "layer/strategy/drivepuckstatemachine/findpuckturntostate.h"
#include "layer/strategy/drivepuckstatemachine/verifypuckstate.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"
#include "layer/strategy/common/waitcyclesstate.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

FindPuckTurnToState::FindPuckTurnToState(Robot &robot, Field &field, Referee &referee, RoboHockey::Common::Logger &logger, const ColorDependentPuckTargetFetcher &puckTargetFetcher):
	State(robot, field, referee, logger, true),
	m_puckTargetFetcher(puckTargetFetcher)
{ }

State *FindPuckTurnToState::nextState()
{
	return 0;
}

std::string FindPuckTurnToState::getName()
{
	return "FindPuck";
}

void FindPuckTurnToState::updateInternal()
{
}
