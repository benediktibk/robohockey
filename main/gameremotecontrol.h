#ifndef ROBOHOCKEY_MAIN_GAMEREMOTECONTROL_H
#define ROBOHOCKEY_MAIN_GAMEREMOTECONTROL_H

#include "main/game.h"
#include "common/point.h"

namespace RoboHockey
{
namespace Layer
{
namespace View
{
	class Model;
	class Controller;
}
}
namespace Main
{
	class GameRemoteControl :
			public Game
	{
	public:
		GameRemoteControl(int argc, char **argv);
		virtual ~GameRemoteControl();

		virtual bool keepRunning() const;

	protected:
		virtual void executeRobotControl();

	private:
		bool cantReachTargetOrStuckAtObstacleNewTillLastCall();

	private:
		Layer::View::Model *m_model;
		Layer::View::Controller *m_controller;
		bool m_cantReachTargetOld;
		bool m_stuckAtObstacleOld;
		Common::Point m_lastTarget;
	};
}
}

#endif


