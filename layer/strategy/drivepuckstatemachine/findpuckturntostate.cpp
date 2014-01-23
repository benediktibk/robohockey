#include "layer/strategy/drivepuckstatemachine/findpuckturntostate.h"
#include "layer/strategy/drivepuckstatemachine/verifypuckstate.h"
#include "layer/strategy/drivepuckstatemachine/findpuckstate.h"
#include "layer/strategy/drivepuckstatemachine/leavepuckstate.h"
#include "layer/strategy/common/drivetostate.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/field.h"
#include "layer/strategy/common/waitcyclesstate.h"

using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Strategy::DrivePuckStateMachine;
using namespace RoboHockey::Layer::Autonomous;

FindPuckTurnToState::FindPuckTurnToState(Robot &robot, Field &field, Referee &referee, RoboHockey::Common::Logger &logger,
										 ColorDependentPuckTargetFetcher &puckTargetFetcher,
										 std::list<RoboHockey::Common::Point> targetList):
	State(robot, field, referee, logger, true),
	m_puckTargetFetcher(puckTargetFetcher),
	m_target(targetList),
	m_startedWithEmptyTargetList(m_target.empty())
{ }

State *FindPuckTurnToState::nextState()
{
	if (m_startedWithEmptyTargetList)
		return new FindPuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher);
	else if(m_robot.stuckAtObstacle())
		return new LeavePuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher, false);
	else if(m_puckTargetFetcher.getNumberOfKnownPucksNotInEnemyThird() > 0 && !m_puckTargetFetcher.isCantReachTargetLimitReached())
		return new WaitCyclesState(m_robot, m_field, m_referee, m_logger,
								   new VerifyPuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher), 15, false);
	else if (!m_robot.reachedTarget() || !updateAlreadyCalled())
		return 0;
	else if(m_target.empty())
		return new FindPuckState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher);
	else
		return new WaitCyclesState(m_robot, m_field, m_referee, m_logger,
								   new FindPuckTurnToState(m_robot, m_field, m_referee, m_logger, m_puckTargetFetcher, m_target), 15, false);;
}

std::string FindPuckTurnToState::getName()
{
	return "FindPuckTurnTo";
}

void FindPuckTurnToState::updateInternal()
{
	if(!m_target.empty())
	{
		m_robot.turnTo(m_target.front());
		m_target.pop_front();
	}
}
