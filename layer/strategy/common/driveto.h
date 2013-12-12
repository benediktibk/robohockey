#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVETO_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVETO_H

#include "layer/strategy/common/state.h"
#include "common/robotposition.h"

namespace RoboHockey
{
namespace Common
{
	class RobotPosition;
}
namespace Layer
{
namespace Strategy
{
namespace Common
{
	class DriveTo :
			public State
	{
	public:
		DriveTo(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee,
				const RoboHockey::Common::RobotPosition target,
				State *stateAfterTargetReached, State *stateAfterTargetUnreachable);

		virtual State* nextState();
		virtual void update();

	private:
		const RoboHockey::Common::RobotPosition m_target;
		State *m_stateAfterTargetReached;
		State *m_stateAfterTargetUnreachable;
		bool m_targetSet;
	};
}
}
}
}

#endif
