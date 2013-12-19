#ifndef ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_CHECKGOALCOLOR_H
#define ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_CHECKGOALCOLOR_H

#include "layer/strategy/common/state.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace FieldDetectionStateMachine
{
	class CheckGoalColor :
			public Common::State
	{
	public:
		CheckGoalColor(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee);

		virtual State* nextState();

	protected:
		virtual void updateInternal();

	private:
		bool m_teamColorSend;
		bool m_gotResponse;

	};
}
}
}
}

#endif
