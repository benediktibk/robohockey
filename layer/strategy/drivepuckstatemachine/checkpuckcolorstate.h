#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_CHECKPUCKCOLORSTATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_CHECKPUCKCOLORSTATE_H

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
	class CheckPuckColorState :
			public Common::State
	{
	public:
		CheckPuckColorState(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, RoboHockey::Layer::Strategy::Common::DrivePuck *drivePuck);

		virtual State* nextState();
		virtual void update();

	private:
		Common::DrivePuck *m_drivePuck;
		bool m_foundPuck;
};
}
}
}
}

#endif
