#ifndef ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_INITIALSTATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_INITIALSTATE_H

#include "layer/strategy/common/state.h"

namespace RoboHockey
{
namespace Common
{
	class Logger;
}
namespace Layer
{
namespace Strategy
{
namespace MainStateMachine
{
	class InitialState :
			public Common::State
	{
	public:
		InitialState(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, RoboHockey::Common::Logger &logger);

		virtual State* nextState();
		virtual std::string getName();
		virtual bool allowLogMessages();

	protected:
		virtual void updateInternal();
	};
}
}
}
}

#endif
