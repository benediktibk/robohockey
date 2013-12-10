#ifndef ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_HIDEENEMYPUCKS_H
#define ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_HIDEENEMYPUCKS_H

#include "layer/strategy/common/state.h"
#include "layer/strategy/mainstatemachine/pause.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
class HideEnemyPucks :
        public State
{
public:
    HideEnemyPucks(Autonomous::Robot &robot, Autonomous::Field &field, Referee &referee);

    virtual State* nextState();
    virtual void update();

};
}
}
}

#endif
