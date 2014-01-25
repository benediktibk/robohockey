#ifndef ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_DETECTFIELD_H
#define ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_DETECTFIELD_H

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
	class DetectField :
			public Common::State
	{
	public:
		DetectField(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, RoboHockey::Common::Logger &logger,
					unsigned int numberOfTurns);

		virtual State* nextState();
		virtual std::string getName();

	protected:
		virtual void updateInternal();

	private:
		bool m_successful;
		unsigned int m_numberOfTries;
		unsigned int m_numberOfTurns;
	};
}
}
}
}

#endif
