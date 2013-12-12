#ifndef ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_DETECTFIELD_H
#define ROBOHOCKEY_LAYER_STRATEGY_FIELDDETECTIONSTATEMACHINE_DETECTFIELD_H

#include "layer/strategy/common/state.h"

namespace RoboHockey
{
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
		DetectField(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee);

		virtual State* nextState();
		virtual void update();

	private:
		bool m_successful;
		unsigned int m_numberOfTries;

	};
}
}
}
}

#endif
