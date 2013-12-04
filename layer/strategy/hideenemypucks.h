#ifndef ROBOHOCKEY_LAYER_STRATEGY_HIDEENEMYPUCKS_H
#define ROBOHOCKEY_LAYER_STRATEGY_HIDEENEMYPUCKS_H

#include "layer/strategy/state.h"
#include "layer/strategy/pause.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
class Pause;
class HideEnemyPucks :
        public State
{
public:
    HideEnemyPucks(Autonomous::Robot &robot, Autonomous::Field &field);

    virtual State* nextState();
    virtual void update();

};
}
}
}
