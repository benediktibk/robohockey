#ifndef ROBOHOCKEY_LAYER_STRATEGY_CALIBRATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_CALIBRATE_H

#include "layer/strategy/state.h"
#include "layer/strategy/achievegoals.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
    class AchieveGoals;

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
