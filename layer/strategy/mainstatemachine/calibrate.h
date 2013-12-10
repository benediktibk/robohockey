#ifndef ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_CALIBRATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_CALIBRATE_H

#include "layer/strategy/common/state.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
    class Calibrate :
            public State
    {
    public:
        Calibrate(Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee);

        virtual State* nextState();
        virtual void update();

    private:
    };
}
}
}

#endif
