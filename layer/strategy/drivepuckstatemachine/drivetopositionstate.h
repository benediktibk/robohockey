#ifndef ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_DRIVETOPOSITIONSTATE_H
#define ROBOHOCKEY_LAYER_STRATEGY_DRIVEPUCKSTATEMACHINE_DRIVETOPOSITIONSTATE_H

#include "layer/strategy/common/state.h"

namespace RoboHockey
{
namespace Layer
{
namespace Strategy
{
namespace Common
{
	class DrivePuck;
}
namespace DrivePuckStateMachine
{
	class DriveToPositionState :
			public Common::State
	{
	public:
		DriveToPositionState(Autonomous::Robot &robot, Autonomous::Field &field, Common::Referee &referee, RoboHockey::Layer::Strategy::Common::DrivePuck *drivePuck);

		virtual State* nextState();
		virtual void update();

};
}
}
}
}

#endif
