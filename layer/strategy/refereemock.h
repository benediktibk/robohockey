#ifndef ROBOHOCKEY_LAYER_STRATEGY_REFEREEMOCK_H
#define ROBOHOCKEY_LAYER_STRATEGY_REFEREEMOCK_H

#include "layer/strategy/referee.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
    class RefereeMock :
            public Referee
    {
    public:
        RefereeMock();

        virtual void reportReady();
        virtual void reportDone();
        virtual void sendAlive();
        virtual void tellTeamColor(Extern::Angelina::TeamColor color);
        virtual void reportGoal();
        virtual void tellEgoPos(const Common::Point &position);
        virtual bool detectionStart();
        virtual bool gameStart();
        virtual bool gameOver();
        virtual Extern::Angelina::TeamColor trueColorOfTeam();
        virtual bool stopMovement();
        virtual bool isValid();

    };
}
}
}

#endif


