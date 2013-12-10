#ifndef ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_REFEREEMOCK_H
#define ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_REFEREEMOCK_H

#include "layer/strategy/mainstatemachine/referee.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace MainStateMachine
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
		virtual void tellEgoPos(const RoboHockey::Common::Point &position);
        virtual bool detectionStart();
        virtual bool gameStart();
        virtual bool gameOver();
        virtual Extern::Angelina::TeamColor trueColorOfTeam();
        virtual bool stopMovement();
        virtual bool isValid();
        void setDetectionStart(bool value);
        void setGameStart(bool value);
        void setGameOver(bool value);
        void setStopMovement(bool value);

    private:
        bool m_detectionStart;
        bool m_gameStart;
        bool m_gameOver;
        bool m_stopMovement;


    };
}
}
}
}

#endif


