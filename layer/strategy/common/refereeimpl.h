#ifndef ROBOHOCKEY_LAYER_STRATEGY_COMMON_REFEREEIMPL_H
#define ROBOHOCKEY_LAYER_STRATEGY_COMMON_REFEREEIMPL_H

#include "layer/strategy/common/referee.h"
#include <QtCore/QObject>
#include <string>

namespace Extern
{
namespace Angelina
{
	class Referee;
}
}

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace Common
{
	class RefereeImpl :
			public QObject,
			public Referee
	{
		Q_OBJECT
	public:
		RefereeImpl(const std::string &AngelinaAdressServer);
		~RefereeImpl();
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

	public Q_SLOTS:
		void slotDisconnected();
		void slotDetectionStart();
		void slotGameStart();
		void slotGameOver();
		void slotTrueColorOfTeam(Extern::Angelina::TeamColor color);
		void slotStopMovement();
		void slotConnected();
		void slotConnectFailed();

	private:
		Extern::Angelina::Referee *m_referee;
		bool m_disconnected;
		bool m_detectionStart;
		bool m_GameStart;
		bool m_GameOver;
		Extern::Angelina::TeamColor m_trueColorOfTeam;
		bool m_stopMovement;
		bool m_Connected;
		bool m_ConnectFailed;
		bool m_isValid;
	};
}
}
}
}

#endif
