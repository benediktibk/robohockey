#ifndef ROBOHOCKEY_LAYER_STRATEGY_INITIALSTATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_INITIALSTATE_H

#include "layer/strategy/state.h"
#include "layer/strategy/calibrate.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
    class Calibrate;

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
