#ifndef ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_PAUSE_H
#define ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_PAUSE_H

#include "layer/strategy/common/state.h"
#include "layer/strategy/mainstatemachine/achievegoals.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace MainStateMachine
{
	class Pause :
			public Common::State
	{
	public:
		Pause(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee);

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
