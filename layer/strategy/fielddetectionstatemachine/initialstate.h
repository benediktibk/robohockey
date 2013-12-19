#ifndef ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_INITIALSTATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_INITIALSTATE_H

#include "layer/strategy/common/state.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace FieldDetectionStateMachine
{
	class InitialState :
			public Common::State
	{
	public:
		InitialState(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee);

		virtual State* nextState();

	protected:
		virtual void updateInternal();
	};
}
}
}
}

#endif
