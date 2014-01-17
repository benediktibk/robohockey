#include "layer/strategy/drivepuckstatemachine/collectpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/drivepucktopositionstate.h"
#include "layer/strategy/drivepuckstatemachine/drivetocollectpuckstate.h"
#include "common/robotposition.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"
#include <iostream>
#include <assert.h>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

CollectPuckState::CollectPuckState(Robot &robot, Field &field, Referee &referee, Logger &logger, ColorDependentPuckTargetFetcher &puckTargetFetcher) :
	State(robot, field, referee, logger, true),
	m_puckTargetFetcher(puckTargetFetcher)
{ }

State* CollectPuckState::nextState()
{
	vector<FieldObject> targetPositions =
			m_field.getObjectsWithColorOrderdByDistance(m_puckTargetFetcher.getColorOfTargetPucks());

	if(m_robot.isPuckCollected())
		return new DrivePuckToPositionState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher);
	else if(m_robot.cantReachTarget() || !m_robot.isPuckCollectable() || targetPositions.empty() || m_robot.stuckAtObstacle())
		return new DriveToCollectPuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher);
	else
		return 0;
}

string CollectPuckState::getName()
{
	return "CollectPuck";
}

void CollectPuckState::updateInternal()
{
	vector<FieldObject> targetPositions =
			m_field.getObjectsWithColorOrderdByDistance(m_puckTargetFetcher.getColorOfTargetPucks());

	if(m_robot.isPuckCollectable() && !targetPositions.empty())
		m_robot.collectPuckInFront(targetPositions.front().getCircle().getCenter());
}
