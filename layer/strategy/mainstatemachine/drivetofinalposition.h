#ifndef ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_DRIVETOFINALPOSITION_H
#define ROBOHOCKEY_LAYER_STRATEGY_MAINSTATEMACHINE_DRIVETOFINALPOSITION_H

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
class DriveToFinalPosition:
		public Common::State
	{
	public:
		DriveToFinalPosition(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, RoboHockey::Common::Logger &logger);

		virtual State* nextState();
		virtual std::string getName();

	protected:
		virtual void updateInternal();
	};
}
}
}
}

#endif
