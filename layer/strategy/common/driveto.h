#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVETO_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_DRIVETO_H

#include "layer/strategy/common/state.h"

namespace RoboHockey
{
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
		DriveTo(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee);

		virtual State* nextState();
		virtual void update();

	};
}
}
}
}

#endif
