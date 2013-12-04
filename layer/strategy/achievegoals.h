#ifndef ROBOHOCKEY_LAYER_STRATEGY_ACHIEVEGOALS_H
#define ROBOHOCKEY_LAYER_STRATEGY_ACHIEVEGOALS_H

#include "layer/strategy/state.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
    class AchieveGoals :
            public State
    {
    public:
        AchieveGoals(Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee);

        virtual State* nextState();
        virtual void update();

    private:
    };
}
}
}

#endif
