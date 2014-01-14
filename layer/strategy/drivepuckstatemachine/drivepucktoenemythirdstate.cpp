#include "layer/strategy/drivepuckstatemachine/drivepucktoenemythirdstate.h"
#include "layer/strategy/drivepuckstatemachine/drivepucktopositionstate.h"
#include "layer/strategy/drivepuckstatemachine/leavepuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"
#include "layer/strategy/common/colordependentpucktargetfetcher.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

DrivePuckToEnemyThirdState::DrivePuckToEnemyThirdState(Robot &robot, Field &field, Referee &referee, RoboHockey::Common::Logger &logger, const ColorDependentPuckTargetFetcher &puckTargetFetcher) :
	State(robot, field, referee, logger, true),
	m_puckTargetFetcher(puckTargetFetcher)
{ }

State *DrivePuckToEnemyThirdState::nextState()
{
	if(m_robot.isPuckCollected())
		return new DriveToState(
					m_robot, m_field, m_referee, m_logger, m_field.getTargetsInEnemyThird(),
					new LeavePuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher, false),
					new LeavePuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher, false));
	else
		return new DriveToCollectPuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher);
}

std::string DrivePuckToEnemyThirdState::getName()
{
	return "DriveToEnemyThird";
}

void DrivePuckToEnemyThirdState::updateInternal()
{ }
