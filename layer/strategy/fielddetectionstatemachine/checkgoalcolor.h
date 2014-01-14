#ifndef ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_CHECKGOALCOLOR_H
#define ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_CHECKGOALCOLOR_H

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
	class CheckGoalColor :
			public Common::State
	{
	public:
		CheckGoalColor(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, RoboHockey::Common::Logger &logger);

		virtual State* nextState();
		virtual std::string getName();

	protected:
		virtual void updateInternal();

	private:
		bool m_teamColorSend;
		bool m_gotResponse;
		unsigned int m_numberOfTries;

	};
}
}
}
}

#endif
