#ifndef ROBOHOCKEY_LAYER_STRATEGY_PAUSE_H
#define ROBOHOCKEY_LAYER_STRATEGY_PAUSE_H

#include "layer/strategy/state.h"
#include "layer/strategy/achievegoals.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
    class Calibrate;
    class AchieveGoals;
    class Pause :
            public State
    {
    public:
        Pause(Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee);
        virtual State* nextState();
        virtual void update();
    };
}
}
}

#endif
