#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVETOFINALPOSITION_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVETOFINALPOSITION_H

#include "layer/strategy/state.h"


namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
class DriveToFinalPosition:
        public State
    {
    public:
        DriveToFinalPosition(Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee);

        virtual State* nextState();
        virtual void update();

    };
}
}
}

#endif
