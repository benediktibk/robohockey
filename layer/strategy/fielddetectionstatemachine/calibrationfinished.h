#ifndef ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_CALIBRATIONFINISHED_H
#define ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_CALIBRATIONFINISHED_H

#include "layer/strategy/common/state.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace FieldDetectionStateMachine
{
	class CalibrationFinished :
			public Common::State
	{
	public:
		CalibrationFinished(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee);

		virtual State* nextState();

	protected:
		virtual void updateInternal();
	};
}
}
}
}

#endif
