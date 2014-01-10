#include "layer/strategy/drivepuckstatemachine/drivepucktoenemythirdstate.h"
#include "layer/strategy/drivepuckstatemachine/drivepucktopositionstate.h"
#include "layer/strategy/drivepuckstatemachine/leavepuckstate.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/autonomous/robot.h"
#include "layer/strategy/common/colordependentpucktargetfetcher.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

DrivePuckToEnemyThirdState::DrivePuckToEnemyThirdState(Robot &robot, Field &field, Referee &referee, const ColorDependentPuckTargetFetcher &puckTargetFetcher) :
	State(robot, field, referee, true),
	m_puckTargetFetcher(puckTargetFetcher)
{ }

State *DrivePuckToEnemyThirdState::nextState()
{
	return 0;
}

std::string DrivePuckToEnemyThirdState::getName()
{
	return "DriveToPosition";
}

void DrivePuckToEnemyThirdState::updateInternal()
{ }
