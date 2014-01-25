#ifndef ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_TURNANGLE_H
#define ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_TURNANGLE_H

#include "common/robotposition.h"
#include "layer/strategy/common/state.h"
#include <list>

namespace RoboHockey
{
namespace Common
{
	class Logger;
	class Angle;
}
namespace Layer
{
namespace Strategy
{
namespace FieldDetectionStateMachine
{
	class TurnAngle :
			public Common::State
	{
	public:
		TurnAngle(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, RoboHockey::Common::Logger &logger,
				  RoboHockey::Common::Angle angle, unsigned int numberOfTurns);

		virtual State* nextState();
		virtual std::string getName();

	protected:
		virtual void updateInternal();

	private:
		RoboHockey::Common::Angle m_angle;
		unsigned int m_numberOfTurns;

	};
}
}
}
}

#endif
