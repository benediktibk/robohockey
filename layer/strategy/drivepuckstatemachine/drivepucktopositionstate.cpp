#include "layer/strategy/drivepuckstatemachine/drivepucktopositionstate.h"
#include "layer/strategy/drivepuckstatemachine/leavepuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/autonomous/robot.h"
#include "layer/strategy/common/colordependentpucktargetfetcher.h"
#include "layer/strategy/drivepuckstatemachine/drivepucktoenemythirdstate.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

DrivePuckToPositionState::DrivePuckToPositionState(Robot &robot, Field &field, Referee &referee, RoboHockey::Common::Logger &logger, const ColorDependentPuckTargetFetcher &puckTargetFetcher) :
	State(robot, field, referee, logger, true),
	m_puckTargetFetcher(puckTargetFetcher)
{ }

State *DrivePuckToPositionState::nextState()
{
	if(m_robot.isPuckCollected())
		return new DriveToState(
					m_robot, m_field, m_referee, m_puckTargetFetcher.getTargetPositions(),
					new LeavePuckState(m_robot, m_field, m_referee, m_puckTargetFetcher, m_puckTargetFetcher.isAchievingGoals()),
					new DrivePuckToEnemyThirdState(m_robot, m_field, m_referee, m_puckTargetFetcher));
	else
		return new DriveToCollectPuckState(m_robot, m_field, m_referee, m_puckTargetFetcher);
}

std::string DrivePuckToPositionState::getName()
{
	return "DriveToPosition";
}

void DrivePuckToPositionState::updateInternal()
{ }
