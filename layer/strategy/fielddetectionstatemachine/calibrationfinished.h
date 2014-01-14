#ifndef ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_CALIBRATIONFINISHED_H
#define ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_CALIBRATIONFINISHED_H

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
	class CalibrationFinished :
			public Common::State
	{
	public:
		CalibrationFinished(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, RoboHockey::Common::Logger &logger, unsigned int reachedTargets);

		virtual State* nextState();
		virtual std::string getName();

	protected:
		virtual void updateInternal();

	private:
		unsigned int m_reachedTargets;

	};
}
}
}
}

#endif
