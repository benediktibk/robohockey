#ifndef ROBOHOCKEY_MAIN_GAMEAUTOMATIC_H
#define ROBOHOCKEY_MAIN_GAMEAUTOMATIC_H

#include "main/game.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
	class StateMachine;
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
		Layer::Strategy::StateMachine *m_stateMachine;
	};
}
}

#endif


