#include "layer/strategy/common/driveto.h"
#include "layer/strategy/common/referee.h"
#include "layer/autonomous/robot.h"
#include "common/angle.h"
#include "common/point.h"
#include <assert.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace RoboHockey::Layer::Autonomous;

DriveTo::DriveTo(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee,
				 std::list<RobotPosition> targetList,
				 State *stateAfterTargetReached, State *stateAfterTargetUnreachable) :
	State(robot,field, referee),
	m_target(targetList),
	m_stateAfterTargetReached(stateAfterTargetReached),
	m_stateAfterTargetUnreachable(stateAfterTargetUnreachable),
	m_targetSet(false)
{
	assert(m_stateAfterTargetReached != 0);
	assert(m_stateAfterTargetUnreachable != 0);
}

State* DriveTo::nextState()
{
	assert(m_targetSet);

	if (m_robot.stuckAtObstacle() || m_robot.cantReachTarget())
	{
		if (m_stateAfterTargetReached != m_stateAfterTargetUnreachable)
		{
			delete m_stateAfterTargetReached;
			m_stateAfterTargetReached = 0;
		}
		return m_stateAfterTargetUnreachable;
	}
	else if (m_robot.reachedTarget())
	{
		if (m_stateAfterTargetReached != m_stateAfterTargetUnreachable)
		{
			delete m_stateAfterTargetUnreachable;
			m_stateAfterTargetUnreachable = 0;
		}
		return m_stateAfterTargetReached;
	}
	return 0;
}

void DriveTo::update()
{
	//! @todo robot.goTo() should get a list of targets, when it can handle a list of targets.
	m_targetSet = true;
	m_robot.goTo(m_target.front());
}
