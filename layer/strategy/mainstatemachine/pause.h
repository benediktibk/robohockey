#ifndef ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_PAUSE_H
#define ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_PAUSE_H

#include "layer/strategy/common/state.h"
#include "layer/strategy/mainstatemachine/achievegoals.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace MainStateMachine
{
    class Calibrate;
    class AchieveGoals;
    class Pause :
			public Common::State
    {
    public:
        Pause(Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee);
        virtual State* nextState();
        virtual void update();
    };
}
}
}
}

#endif
