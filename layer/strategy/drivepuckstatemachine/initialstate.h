#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_INITIALSTATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_INITIALSTATE_H

#include "layer/strategy/common/state.h"
#include "layer/strategy/common/drivepuck.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace DrivePuckStateMachine
{
	class InitialState :
			public Common::State
	{
	public:
		InitialState(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, RoboHockey::Layer::Strategy::Common::DrivePuck *drivePuck);

		virtual State* nextState();

	protected:
		virtual void updateInternal();

	private:
		Common::DrivePuck *m_drivePuck;
	};
}
}
}
}

#endif
