#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVETOSTATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVETOSTATE_H

#include "layer/strategy/common/state.h"
#include "common/robotposition.h"
#include <list>

namespace RoboHockey
{
namespace Common
{
	class Logger;
}
namespace Layer
{
namespace Strategy
{
namespace Common
{
	class DriveToState :
			public State
	{
	public:
		DriveToState(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, RoboHockey::Common::Logger &logger,
				std::list<RoboHockey::Common::RobotPosition> targetList,
				State *stateAfterTargetReached, State *stateAfterTargetUnreachable);
		virtual ~DriveToState();

		virtual State* nextState();
		virtual std::string getName();

	protected:
		virtual void updateInternal();

	private:
		std::list<RoboHockey::Common::RobotPosition> m_target;
		State *m_stateAfterTargetReached;
		State *m_stateAfterTargetUnreachable;
	};
}
}
}
}

#endif
