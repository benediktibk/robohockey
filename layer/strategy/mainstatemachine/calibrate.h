#ifndef ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_CALIBRATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_CALIBRATE_H

#include "layer/strategy/common/state.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace MainStateMachine
{
    class Calibrate :
			public Common::State
    {
    public:
		Calibrate(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee);

        virtual State* nextState();
        virtual void update();

    private:
    };
}
}
}
}

#endif
