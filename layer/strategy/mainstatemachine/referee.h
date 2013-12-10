#ifndef ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_REFEREE_H
#define ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_REFEREE_H

#include "extern/angelina/teamcolor.h"

namespace RoboHockey
{
namespace Common
{
    class Point;
}

namespace Layer
{
namespace Strategy
{
    class Referee
    {
    public:
        virtual ~Referee() { }

        virtual void reportReady() = 0;
        virtual void reportDone() = 0;
        virtual void sendAlive() = 0;
        virtual void tellTeamColor(Extern::Angelina::TeamColor color) = 0;
        virtual void reportGoal() = 0;
        virtual void tellEgoPos(const Common::Point &position) = 0;
        virtual bool detectionStart() = 0;
        virtual bool gameStart() = 0;
        virtual bool gameOver() = 0;
        virtual Extern::Angelina::TeamColor trueColorOfTeam() = 0;
        virtual bool stopMovement() = 0;
        virtual bool isValid() = 0;

    };
}
}
}

#endif


