#ifndef ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_TURNANGLE_H
#define ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_TURNANGLE_H

#include "layer/strategy/common/state.h"

namespace RoboHockey
{
namespace Common
{
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
		TurnAngle(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, RoboHockey::Common::Angle angle);

		virtual State* nextState();
		virtual void update();

	private:
		RoboHockey::Common::Angle &m_angle;
		bool m_targetSet;

	};
}
}
}
}

#endif
