#ifndef ROBOHOCKEY_MAIN_GAMEAUTOMATIC_H
#define ROBOHOCKEY_MAIN_GAMEAUTOMATIC_H

#include "main/game.h"

namespace RoboHockey
{
namespace Layer
{
namespace View
{
	class Model;
	class Controller;
}
namespace Strategy
{
namespace Common
{
	class StateMachine;
}
}
}

namespace Main
{
	class GameAutomatic :
			public Game
	{
	public:
		GameAutomatic(int argc, char **argv);
		virtual ~GameAutomatic();

		virtual bool keepRunning() const;

	protected:
		virtual void executeRobotControl();

	private:
		Layer::Strategy::Common::StateMachine *m_stateMachine;
		std::string m_stateString;
		std::string m_robotString;
		Layer::View::Model *m_model;
		Layer::View::Controller *m_controller;
	};
}
}

#endif


