#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_COLLECTPUCKSTATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_COLLECTPUCKSTATE_H

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
	class CollectPuckState :
			public Common::State
	{
	public:
		CollectPuckState(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, RoboHockey::Layer::Strategy::Common::DrivePuck *drivePuck);

		virtual State* nextState();
		virtual void update();

	private:
		Common::DrivePuck *m_drivePuck;
};
}
}
}
}

#endif
