#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_REFEREEMOCK_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_REFEREEMOCK_H

#include "layer/strategy/common/referee.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace Common
{
	class RefereeMock :
			public Referee
	{
	public:
		RefereeMock();

		virtual void reportReady();
		virtual void reportDone();
		virtual void sendAlive();
		virtual void tellTeamColor(RoboHockey::Common::FieldColor color);
		virtual void reportGoal();
		virtual void tellEgoPos(const RoboHockey::Common::Point &position);
		virtual bool detectionStart();
		virtual bool gameStart();
		virtual bool gameOver();
		virtual RoboHockey::Common::FieldColor trueColorOfTeam();
		virtual bool stopMovement();
		virtual bool isValid();
		void setDetectionStart(bool value);
		void setGameStart(bool value);
		void setGameOver(bool value);
		void setStopMovement(bool value);
		void setTrueColorOfTeam(RoboHockey::Common::FieldColor color);

	private:
		bool m_detectionStart;
		bool m_gameStart;
		bool m_gameOver;
		bool m_stopMovement;
		RoboHockey::Common::FieldColor m_trueColor;


	};
}
}
}
}

#endif
