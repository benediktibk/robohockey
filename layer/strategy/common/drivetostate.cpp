#include "layer/strategy/common/drivetostate.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "common/angle.h"
#include "common/point.h"
#include <assert.h>

using namespace std;
using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;

DriveToState::DriveToState(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, Logger &logger,
		list<RobotPosition> targetList,
		State *stateAfterTargetReached, State *stateAfterTargetUnreachable) :
	State(robot, field, referee, logger, true),
	m_target(targetList),
	m_stateAfterTargetReached(stateAfterTargetReached),
	m_stateAfterTargetUnreachable(stateAfterTargetUnreachable)
{
	assert(m_stateAfterTargetReached != m_stateAfterTargetUnreachable);
	assert(m_stateAfterTargetReached != 0);
	assert(m_stateAfterTargetUnreachable != 0);
}

DriveToState::~DriveToState()
{
	delete m_stateAfterTargetReached;
	m_stateAfterTargetReached = 0;
	delete m_stateAfterTargetUnreachable;
	m_stateAfterTargetUnreachable = 0;
}

State* DriveToState::nextState()
{
	assert(m_stateAfterTargetReached != 0);
	assert(m_stateAfterTargetUnreachable != 0);

	if (m_robot.stuckAtObstacle() || m_robot.cantReachTarget())
	{
		State *result = m_stateAfterTargetUnreachable;
		m_stateAfterTargetUnreachable = 0;
		return result;
	}
	else if (m_robot.reachedTarget())
	{
		State *result = m_stateAfterTargetReached;
		m_stateAfterTargetReached = 0;
		return result;
	}

	return 0;
}

string DriveToState::getName()
{
	return "DriveTo";
}

void DriveToState::updateInternal()
{
	m_robot.goTo(m_target);
}
