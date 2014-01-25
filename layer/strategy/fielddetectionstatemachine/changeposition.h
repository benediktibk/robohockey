#ifndef ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_CHANGEPOSITION_H
#define ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_CHANGEPOSITION_H

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
namespace FieldDetectionStateMachine
{
	class ChangePosition:
		public Common::State
	{
	public:
		ChangePosition(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, RoboHockey::Common::Logger &logger);

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
