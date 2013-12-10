#ifndef ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_INITIALSTATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_INITIALSTATE_H

#include "layer/strategy/common/state.h"
#include "layer/strategy/mainstatemachine/calibrate.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
    class InitialState :
			public State
	{
	public:
        InitialState(Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee);

		virtual State* nextState();
		virtual void update();

	};
}
}
}

#endif
